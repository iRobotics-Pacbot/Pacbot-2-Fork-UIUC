#pragma once

/**
 * @class IDelta
 * @brief Represents a delta to the game
 *
 */
struct IDelta {
  virtual ~IDelta() = default;
  virtual void perform() const = 0;
  virtual void undo() const = 0;
};
