#pragma once
#include "GameState.hpp"
#include "Location.hpp"
#include "ghost/Ghost.hpp"

class IGhostAgent {
private:
  /**
   * @brief Predicts the scatter target of the ghost
   *
   * @param gameState The game state
   */
  virtual std::pair<int, int>
  getChaseTarget(const GameState &gameState) const = 0;
  /**
   * @brief Predicts the Scatter target of the ghost
   */
  virtual std::pair<int, int> getScatterTarget() const;
  /**
   * @brief Guess the next direction to move
   *
   * @param gameState The game state
   * @return The next direction to move
   */
  Directions guessMove(const GameState &gameState, const Ghost &ghost) const;

public:
  virtual ~IGhostAgent() = default;
  void move(GameState &gameState, Ghost &ghost);
};
