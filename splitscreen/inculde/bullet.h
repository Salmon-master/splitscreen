// Copyright 2024 Hugh Thompson

#ifndef BULLET_H_
#define BULLET_H_

#include "game_object.h"
#include "player.h"
#include "vector"
#include "vector.h"

class Player;

// a class used to represent an in game bullet
class Bullet : public GameObject {
 public:
  Bullet(GameObject* shooter, int damage, int speed);
  // used in main game loop to step the bullet foward by veclocity and check for
  // collisions between the current list of gameobjects(input)
  bool Update(std::vector<std::vector<GameObject*>>* objects);

 private:
  // the velocity of the bulet, set in constuctor.
  Vector velocity_ = {0, 0};
  // bullet speed
  int speed_ = 30;
  // damage of the bullet, set in constctor
  int damage_;
  // a reference to the object that the gun that shot this bullet belongs to.
  GameObject* shooter_;
};

#endif  // !BULLET_H_
