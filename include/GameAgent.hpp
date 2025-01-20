#pragma once
#include "GameState.hpp"
#include "delta/IDelta.hpp"
#include "ghost/agent/IGhostAgent.hpp"
#include "ghost/agent/RedGhostAgent.hpp"
#include <memory>
#include <stack>

/**
 * @class GameStateAgent
 * @brief An agent to play the game
 *
 */
class GameAgent {
private:
  GameState gameState;
  /**
   * @brief Stores the series of deltas that led to this gameState
   */
  std::stack<std::unique_ptr<IDelta>> deltas;
  /**
   * @brief Stores the indexes of the previous versions in the delta stack
   */
  std::stack<int> versions;
  std::array<std::unique_ptr<IGhostAgent>, 4> ghostAgents;
  void perform(std::unique_ptr<IDelta> &&action);

public:
  GameAgent()
      : ghostAgents{std::make_unique<RedGhostAgent>(),
                    std::make_unique<RedGhostAgent>(),
                    std::make_unique<RedGhostAgent>(),
                    std::make_unique<RedGhostAgent>()} {};
  /**
   * @brief Updates the game based on the direction the pacman moves
   *
   * @param numTicks The number of tics to simulate
   * @param pacmanDirection The action taken by the pacman in that time
   */
  void step(int numTicks, Directions pacmanDirection);
  /**
   * @brief Reverts to the previous game state
   */
  void undo();

  /**
   * @brief Copies the game state into the internal game state
   *
   * @param gameState The game state to copy
   */
  void update(const GameState &gameState);
  /**
   * @brief Moves the game state into the internal game state
   *
   * @param gameState The game state to move
   */
  void update(GameState &&gameState);
};
