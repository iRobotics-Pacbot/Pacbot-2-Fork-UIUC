#pragma once
#include "GameState.hpp"
#include "Location.hpp"
#include "delta/IDelta.hpp"
#include "ghost/Ghost.hpp"
#include "memory"

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

public:
  /**
   * @brief Guess the next direction to move
   *
   * @param gameState The game state
   * @return The delta for changing its planned direction
   */
  std::unique_ptr<IDelta> guessMove(const GameState &gameState,
                                    const Ghost &ghost);

  virtual ~IGhostAgent() = default;
  /**
   * @brief Advances this ghost to the next position
   *
   * @param gameState The game state
   * @param ghost The ghost to act upon
   * @return The delta for moving
   */
  std::unique_ptr<IDelta> move(GameState &gameState, Ghost &ghost);
  Directions plannedDirection;
};