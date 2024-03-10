#include "player.h"

#include <cmath>

Player::Player() : GameObject(0, 0, "player") {
  // roataion center to center of player charter
  rotation_center_.y = (rect_.h - 28) + rect_.y;
}

void Player::Step(int delta_time) {
  // caluclating the componets of the vector to move given the rotation and
  // speed (scaled by delta time)
  float x = sin(rotation_) * speed_ * delta_time / 1000;
  float y = cos(rotation_) * speed_ * delta_time / 1000 * -1;
  velocity_ = {x, y};
  this->Move(x, y);
}

void Player::Rotate(bool dir) {
  if (dir == 1) {
    rotation_ += rotation_speed_;
  }
  if (dir == 0) {
    rotation_ -= rotation_speed_;
  }
}
