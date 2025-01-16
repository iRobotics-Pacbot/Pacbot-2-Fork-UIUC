#pragma once
#include "ghost/Ghost.hpp"
#include <array>
#include <cstdint>

enum GameModes : uint8_t { PAUSED, SCATTER, CHASE };

const static std::array<int, 5> D_ROW{-1, 0, 1, 0, 0};
const static std::array<int, 5> D_COL{0, -1, 0, 1, 0};

struct GameState {
  uint16_t currTicks = 0;
  uint8_t updatePeriod = 12;
  GameModes gameMode = GameModes::PAUSED;
  uint8_t modeSteps = 0;
  uint8_t modeDuration = 255;
  uint16_t levelSteps = 0;
  uint8_t currScore = 0;
  uint8_t currLevel = 0;
  uint8_t currLives = 3;
  uint8_t ghostCombo = 0;
  std::array<Ghost, 4> ghosts;
  Location pacmanLoc;
  Location fruitLoc;
  uint8_t fruitSteps = 0;
  uint8_t fruitDuration = 30;
  std::array<uint32_t, 31> pelletArr;
};
