#include "DecisionModule.hpp"

DecisionModule::DecisionModule(GameAgent agent, int depthLimit) {
  this->_agent = agent;
  this->_depthLimit = depthLimit;
}
DecisionModule::DecisionModule() {
  this->_agent = GameAgent();
  this->_depthLimit = 6;
}
Directions DecisionModule::decide() {}
void DecisionModule::overrideAgent(GameAgent agent) { this->_agent = agent; }
int DecisionModule::evaluateState(GameAgent currAgent) {}
int DecisionModule::deepSearch(int depth, GameAgent currAgent) {}
