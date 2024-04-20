// Copyright 2024 Hugh Thompson

#ifndef PLAYER_H_
#define PLAYER_H_

#include "game_object.h"
#include "gun.h"
#include "ui_bar.h"

// foward declations
class Gun;
// player class, used by the game to represnt a robot within the game
class Player : public GameObject {
 private:
  // speed vars
  int speed_ = 200;
  float rotation_speed_ = 0.002;
  // assigned in constructor
  Gun* gun_ = nullptr;
  // basically health
  int damage_ = 0;
  // assigned in consturctor
  UIBar* damage_bar_ = nullptr;
  // armour value, reduces damage taken, from 0 to 100 as a percentage of damage reduced
  int armour_ = 0;

 public:
  Player();
  ~Player();
  // convert the speed(magnitude) and rotation(angle) into x and y components to
  // feed to parent move function, and then move the player.(smoothed with delta
  // time)
  void Step(int delta_time);
  // change the rotation of the player, true is colcokwise, false is
  // anticlockwise, will rotate the player based upon the rotation speed and is
  // smoothed by delta time.
  void Rotate(bool direction, int delta_time);
  Gun* GetGun();
  // called when teh player receives damage, retuns wether or not the player is
  // alive.
  bool Damage(int amount);
  UIBar* GetBar();

};

#endif  // !PLAYER_H_
