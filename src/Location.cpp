#include "Location.hpp"

uint8_t Location::getRow() const { return row & 0x3F; }

void Location::setRow(uint8_t row) { this->row = row | (this->row & ~0x3F); }

uint8_t Location::getRowDir() const { return (row >> 6) & 0x03; }

void Location::setRowDir(uint8_t rowDir) {
  this->row = (rowDir << 6) | (this->row & ~(0x3F << 6));
}

uint8_t Location::getCol() const { return col & 0x03; }

void Location::setCol(uint8_t col) { this->col = col | (this->col & ~0x3F); }

uint8_t Location::getColDir() const { return (col >> 6) & 0x03; }

void Location::setColDir(uint8_t colDir) {
  this->col = (colDir << 6) | (this->col & ~(0x3F << 6));
}
