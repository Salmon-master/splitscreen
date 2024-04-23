// Copyright 2024 Hugh Thompson

#ifndef DOOR_H_
#define DOOR_H_

#include "game_object.h"

// a class used to represnt a door in the game
class Door : public GameObject {
 public:
  Door(int x, int y);
  // switch the current state of the door, retuns the state of the door, true.
  // for open, false for closed
  bool Open();
  // check for collison between this door and the inputted game object.
  bool Collide(GameObject* obj);
  // retuns the state of the door. True for open, false for closed.
  bool GetState();

 private:
  // the current state of the door. True for open, false for closed.
  bool open_ = false;
};

#endif  // !DOOR_H_
