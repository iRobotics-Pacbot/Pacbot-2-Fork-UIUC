#pragma once
#include "Location.hpp"
#include <array>
#include <cstdint>

enum GhostColors { RED, PINK, CYAN, ORANGE };

// Scatter targets for the ghosts
const static std::array<int, 4> SCATTER_ROW{-3, -3, 31, 31};
const static std::array<int, 4> SCATTER_COL{25, 2, 27, 0};

class Ghost {
private:
  uint8_t aux1, aux2;

public:
  Location location;

  bool isFreightened() const;
  int getFreightenedSteps() const;
  void setFreightenedSteps(int steps);

  bool isEaten() const;
  void setEaten(bool eaten);

  int getTrappedSteps() const;
  void setTrappedSteps(int steps);

  bool isSpawning() const;
  void setSpawning(bool spawning);
};
