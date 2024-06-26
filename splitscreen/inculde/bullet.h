// Copyright 2024 Hugh Thompson

#ifndef SPLITSCREEN_BULLET_H_
#define SPLITSCREEN_BULLET_H_

#include "game_object.h"
#include "robot.h"
#include "vector"
#include "vector.h"

class Robot;

// a class used to represent an in game bullet
class Bullet : public GameObject {
 public:
  // the constuctor of the bullet, used by the gun class to create an in game
  // bullet.
  Bullet(GameObject* shooter, int damage, int speed);
  // used in main game loop to step the bullet foward by veclocity and check for
  // collisions between the current list of gameobjects(input), retuns if the
  // bullet has hit an object and thefore needs to be destructed
  bool Update(std::vector<std::vector<GameObject*>>* objects);

 private:
  // the velocity of the bulet, set in constuctor.
  Vector velocity_ = {0, 0};
  // bullet speed
  int speed_ = 30;
  // damage of the bullet, set in constctor
  int damage_;
  // a reference to the object that the gun that shot this bullet belongs to,
  // given in constctor
  GameObject* shooter_;
};

#endif  // !SPLITSCREEN_BULLET_H_
