#pragma once
#include "GameState.hpp"

struct IDelta {
  virtual ~IDelta() = 0;
  virtual void perform(GameState &gameState) const;
  virtual void undo(GameState &gameState) const;
};
