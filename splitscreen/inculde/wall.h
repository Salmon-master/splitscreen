// Copyright (C) 2024 Hugh Thompson

#ifndef SPLITSCREEN_WALL_H_
#define SPLITSCREEN_WALL_H_

#include <iostream>
#include <vector>

#include "game_object.h"
#include "robot.h"

// An in game wall peice, can collide with other objects using the collide
// method, used to add visable wall objects to the game.
class Wall : public GameObject {
 public:
  // initalise the wall and given coorinates
  Wall(int x, int y);
  // Used for checking collision for collision against a game  object, and then
  // move obj accordingly. Will check for circular collision aginst rectangular
  // wall. the inputted object is the one that the collision check will be
  // performed against
  bool Collision(GameObject* obj);
};

#endif  // !SPLITSCREEN_WALL_H_
