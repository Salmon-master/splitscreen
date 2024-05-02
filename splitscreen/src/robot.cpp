// Copyright 2024 Hugh Thompson

#include "robot.h"

#include <cmath>

Robot::Robot(SaveManager* save, int gun) : GameObject(0, 0, "robot") {
  // setting id
  id_ = new_id_;
  new_id_++;
  // loading in from save
  std::vector<int> stats = save->GetRobotStats(id_);
  speed_ = stats[0];
  rotation_speed_ = static_cast<float>(stats[0]) / 100000;
  armour_ = stats[1];
  damage_ = save->GetDamage(id_);
  // roataion center to center of robot charter
  rotation_center_.y = (rect_.h - 28) + rect_.y;
  // gun initialisation
  gun_ = new Gun(gun, this, save);
  // damage bar initialisation
  damage_bar_ = new UIBar(
      100, {110, 59, 173},
      {static_cast<int>(rect_.x), static_cast<int>(rect_.y), 250, 40});
  damage_bar_->SetValue(damage_);
}

Robot::~Robot() { delete gun_; }

void Robot::Step(int delta_time) {
  // caluclating the componets of the vector to move given the rotation and
  // speed (scaled by delta time) if active
  if (active_) {
    float x = sin(rotation_) * speed_ * delta_time / 1000;
    float y = cos(rotation_) * speed_ * delta_time / 1000 * -1;
    velocity_ = {x, y};
    this->Move(x, y);
  }
}

void Robot::Rotate(bool dir, int delta_time) {
  // roatate based on direction if active
  if (active_) {
    if (dir == 1) {
      rotation_ += rotation_speed_ * delta_time;
    }
    if (dir == 0) {
      rotation_ -= rotation_speed_ * delta_time;
    }
  }
}

Gun* Robot::GetGun() { return gun_; }

bool Robot::Damage(int amount) {
  bool rv = false;
  int real_damage = amount - ((amount * armour_) / 100);
  // conditions based on if the robot has reached the maximim damage
  damage_ += real_damage;
  if (damage_ >= 100) {
    rv = true;
    damage_bar_->SetValue(100);
    damage_ = 100;
    active_ = false;
  } else {
    damage_bar_->SetValue(damage_);
  }
  return rv;
}

UIBar* Robot::GetBar() { return damage_bar_; }

int Robot::GetDamage() { return damage_; }
