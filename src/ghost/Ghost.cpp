#include "ghost/Ghost.hpp"

int Ghost::getFreightenedSteps() const { return aux1 & 0x3F; }

bool Ghost::isFreightened() const { return getFreightenedSteps() > 0; }

void Ghost::setFreightenedSteps(int steps) {
  aux1 = (aux1 & ~0x3F) | (steps & 0x3F);
}

bool Ghost::isEaten() const { return aux2 >> 7; }

void Ghost::setEaten(bool eaten) {
  aux2 = (aux2 & ~0x80) | ((int)(eaten) << 7);
}

int Ghost::getTrappedSteps() const { return aux2 & 0x3F; }

void Ghost::setTrappedSteps(int steps) {
  aux2 = (aux2 & ~0x3F) | (steps & 0x3F);
}

bool Ghost::isSpawning() const { return aux1 >> 7; }

void Ghost::setSpawning(bool spawning) {
  aux1 = (aux1 & ~0x80) | ((int)(spawning) << 7);
}
