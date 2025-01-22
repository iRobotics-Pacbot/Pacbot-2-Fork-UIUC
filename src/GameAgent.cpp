#include "GameAgent.hpp"
#include "GameState.hpp"
#include "Location.hpp"
#include <memory>

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
