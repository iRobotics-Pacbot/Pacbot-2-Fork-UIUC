#pragma once
#include "IDelta.hpp"
#include "ghost/Ghost.hpp"

struct GhostDelta : public IDelta {
  Location previousLocation, newLocation;
  GhostColors ghost;

  void perform(GameState &gameState) const override;
  void undo(GameState &gameState) const override;
};
