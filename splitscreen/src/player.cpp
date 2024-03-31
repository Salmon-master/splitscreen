#include "player.h"

#include <cmath>

Player::Player()
    : GameObject(0, 0, "player"),
      damage_bar_(500, {110, 59, 173},
                  SDL_Rect{(int)rect_.x, (int)rect_.y, 250, 40}) {
  // roataion center to center of player charter
  rotation_center_.y = (rect_.h - 28) + rect_.y;
  gun_ = new Gun(0, this);
}

void Player::Step(int delta_time) {
  // caluclating the componets of the vector to move given the rotation and
  // speed (scaled by delta time)
  float x = sin(rotation_) * speed_ * delta_time / 1000;
  float y = cos(rotation_) * speed_ * delta_time / 1000 * -1;
  velocity_ = {x, y};
  this->Move(x, y);
}

void Player::Rotate(bool dir, int delta_time) {
  if (dir == 1) {
    rotation_ += rotation_speed_ * delta_time;
  }
  if (dir == 0) {
    rotation_ -= rotation_speed_ * delta_time;
  }
}

Gun* Player::GetGun() { return gun_; }

bool Player::Damage(int amount) {
  bool rv = false;
  damage_ += amount;
  if (damage_ >= 500) {
    rv = true;
    damage_bar_.SetValue(0);
  } else {
    damage_bar_.SetValue(damage_);
  }
  return rv;
}

UIBar* Player::GetBar() { return &damage_bar_; }
