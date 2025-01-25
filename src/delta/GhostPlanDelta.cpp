#include "delta/GhostPlanDelta.hpp"

void GhostPlanDelta::perform() const {
  ghostAgent->plannedDirection = newDirection;
}

void GhostPlanDelta::undo() const {
  ghostAgent->plannedDirection = oldDirection;
}

std::unique_ptr<IDelta> GhostPlanDelta::clone() const {
  return std::make_unique<GhostPlanDelta>(*this);
}