// Copyright 2024 Hugh Thompson

#ifndef BULLET_H_
#define BULLET_H_

#include "vector"

#include "game_object.h"
#include "player.h"
#include "vector.h"

class Player;

class Bullet : public GameObject {
 public:
  Bullet(GameObject* shooter, int damage);
  bool Update(std::vector<std::vector<GameObject*>>* objects);

 private:
  Vector velocity_ = {0, 0};
  int speed_ = 30;
  int damage_;
  GameObject* shooter_;
};

#endif  // !BULLET_H_
