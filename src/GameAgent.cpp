#include "GameAgent.hpp"

#include <memory>
#include <vector>

#include "GameState.hpp"
#include "Location.hpp"

void GameAgent::step(int numTicks, Directions pacmanDirection) {
  // Store the index of the last version
  versions.push(deltas.size());

  // Generate the deltas associated with actions
  for (int i = 0; i < ghostAgents.size(); i++) {
    std::unique_ptr<IGhostAgent> &ghostAgent = ghostAgents[i];
    Ghost &ghost = gameState.ghosts[i];
    if (ghostAgent->plannedDirection == Directions::NONE) {
      // This has to be undone
      perform(ghostAgent->guessMove(gameState, ghost));
    }
  }

  for (int tick = 1; tick <= numTicks; tick++) {
    if ((gameState.currTicks + tick) % gameState.updatePeriod) {
      continue;
    }

    for (int i = 0; i < ghostAgents.size(); i++) {
      std::unique_ptr<IGhostAgent> &ghostAgent = ghostAgents[i];
      Ghost &ghost = gameState.ghosts[i];
      perform(ghostAgent->move(gameState, ghost));
    }
  }
}

void GameAgent::undo() {
  // Check to see if there was a previous version
  if (not versions.empty()) {
    int lastVersion = versions.top();

    // While not at the last version
    while (deltas.size() > lastVersion) {
      // Undoes the last delta
      std::unique_ptr<IDelta> &lastDelta = deltas.top();
      lastDelta->undo();
      deltas.pop();
    }
    versions.pop();
  }
}

void GameAgent::perform(std::unique_ptr<IDelta> &&delta) {
  if (delta) {
    delta->perform();
    deltas.push(delta);
  }
}

void GameAgent::update(const GameState &gameState) {
  this->gameState = gameState;
}

GameAgent &GameAgent::operator=(const GameAgent &other) {
  // Guard self assignment
  if (this == &other) return *this;

  this->gameState = other.gameState;
  std::stack<std::unique_ptr<IDelta>> d_stack = other.deltas;
  std::vector<std::unique_ptr<IDelta>> new_deltas;
  while(!d_stack.empty()) {
    std::unique_ptr<IDelta>& old_d = d_stack.top();
    d_stack.pop();
    new_deltas.push_back(old_d->clone());
  }
  while(!(this->deltas.empty())) {
    this->deltas.top().reset();
    this->deltas.pop();
  }
  for(unsigned int i = new_deltas.size() - 1; i >= 0; i--) {
    this->deltas.push(new_deltas[i]);
  }
  for(unsigned int i = 0; i < 4; i++) {
    this->ghostAgents[i].reset();
    this->ghostAgents[i] = other.ghostAgents[i]->clone();
  }
  return *this;
}