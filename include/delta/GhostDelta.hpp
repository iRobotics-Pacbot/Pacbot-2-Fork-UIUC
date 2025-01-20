#pragma once
#include "IDelta.hpp"
#include "ghost/Ghost.hpp"

struct GhostDelta : public IDelta {
  Location previousLocation, newLocation;
  GhostColors ghost;

  void perform() const override;
  void undo() const override;
};
