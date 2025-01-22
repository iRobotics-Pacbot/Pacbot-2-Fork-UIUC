#include "ghost/agent/IGhostAgent.hpp"
#include "GameState.hpp"
#include "Location.hpp"
#include "delta/GhostMoveDelta.hpp"
#include "delta/GhostPlanDelta.hpp"
#include "ghost/Ghost.hpp"
#include "walls.hpp"
#include <cmath>
#include <limits>

std::unique_ptr<IDelta> IGhostAgent::guessMove(const GameState &gameState,
                                               const Ghost &ghost) {
  // Calculate the next position (Note that this is recalculated when getting
  // the target)
  int nextRow = ghost.location.getRow() + ghost.location.getRowDir();
  int nextCol = ghost.location.getCol() + ghost.location.getColDir();

  // Get the target
  std::pair<int, int> target;
  if (gameState.gameMode == GameModes::CHASE) {
    target = getChaseTarget(gameState);
  } else if (gameState.gameMode == GameModes::SCATTER) {
    target = getScatterTarget();
  }

  // Find the closest way to get to the target
  double minDistance = std::numeric_limits<double>::infinity();
  int maxDistance = -1;
  Directions minDirection = Directions::UP;
  Directions maxDirection = Directions::UP;

  // Check all directions
  for (Directions direction : DIRECTIONS_LIST) {
    // Check for repeats
    if ((D_ROW[direction] + ghost.location.getRowDir()) or
        (D_COL[direction] + ghost.location.getColDir())) {
      int newRow = nextRow + D_ROW[direction];
      int newCol = nextCol + D_COL[direction];

      // Check for collision
      if (!wallAt(newRow, newCol)) {
        // Get the lowest distance
        double squaredDistance = std::pow(newRow - target.first, 2) +
                                 std::pow(newCol - target.second, 2);
        if (squaredDistance < minDistance) {
          minDirection = direction;
          minDistance = squaredDistance;
        } else if (squaredDistance >= maxDistance) {
          maxDirection = direction;
          maxDistance = squaredDistance;
        }
      }
    }
  }

  // Check to see if the ghost should be running away
  Directions newPlan = ghost.isFreightened() ? maxDirection : minDirection;
  return std::make_unique<GhostPlanDelta>(this, newPlan, plannedDirection);
}

std::unique_ptr<IDelta> IGhostAgent::move(GameState &state, Ghost &ghost) {
  if (ghost.isSpawning()) {
    return nullptr;
  }
  return std::make_unique<GhostMoveDelta>(this, )
}