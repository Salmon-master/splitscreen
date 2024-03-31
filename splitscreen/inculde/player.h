#ifndef PLAYER_H_
#define PLAYER_H_

#include "game_object.h"
#include "gun.h"
#include "ui_bar.h"

// foward declations
class Gun;
// player class, used by the game to represnt the player
class Player : public GameObject {
 public:
 private:
  // speed vars
  int speed_ = 200;
  float rotation_speed_ = 0.002;
  Gun* gun_ = nullptr;
  int damage_ = 0;
  UIBar damage_bar_;

 public:
  Player();
  // convert the speed(magnitude) and rotation(angle) into x and y components to
  // feed to parent move function, and then move the player.
  void Step(int delta_time);
  void Rotate(bool direction, int delta_time);
  Gun* GetGun();
  bool Damage(int amount);
  UIBar* GetBar();

 private:
};

#endif  // !PLAYER_H_
