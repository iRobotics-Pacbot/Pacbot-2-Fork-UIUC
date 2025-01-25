#pragma once
#include "GameAgent.hpp"
#include "Location.hpp"

class DecisionModule {
 public:
  DecisionModule(GameAgent agent, int depthLimit);
  DecisionModule();
  Directions decide();
  void overrideAgent(GameAgent agent);

 private:
  GameAgent _agent;
  int _depthLimit;
  int evaluateState(GameAgent currAgent);
  int deepSearch(int depth, GameAgent currAgent);
};