// Copyright (C) 2024 Hugh Thompson

#ifndef WALL_H_
#define WALL_H_

#include <iostream>
#include <vector>

#include "game_object.h"
#include "player.h"

// An in game wall peice, can collide with other objects using the collide
// method, used to add visable wall objects to the game
class Wall : public GameObject {
 public:
  Wall(int x, int y);
  // check for collision, and then move obj accordingly.
  // Will check for circular collision aginst rectangular wall
  bool Collision(GameObject* obj);

 private:
};

#endif  // !WALL_H_
