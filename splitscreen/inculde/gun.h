// Copyright 2024 Hugh Thompson

#ifndef GUN_H_
#define GUN_H_

#include "bullet.h"
#include "player.h"
#include "save_manager.h"

class Player;
class Bullet;

// a class used to represnt the weapon held by either an enemy or player, used
// by either of these classes to controll what anyting relating to the combat
// element of the game.
class Gun {
 public:
  // inputs are a reference to the type of gun and save to load that guns stats,
  // and a pointer to the gameobject that holds this gun for aiming purposes
  Gun(int type, GameObject* holder, SaveManager* save);
  // shoots a bullet in the current direction of the entity holding, returns a
  // pointer to this bullet fired.
  Bullet* Shoot();

 private:
  // the speed of the bullet fired
  int speed_ = 30;
  // how long between shots the gun is allowed to fire.
  int cooldown_ = 300;
  // timestamp for when the gun was last fired, in ms since the SDL
  // initilisation
  int last_shot_ = 0;
  // an int relating to the type of gun (0 based)
  int type_ = 0;
  // damage done by the bullets this weapon fires
  int damage_ = 10;
  // the gameobject that is firing the weapon, used to get a direction of where
  // the bullet should shoot, set in constctor.
  GameObject* held_by_ = nullptr;
};

#endif  // !GUN_H_
