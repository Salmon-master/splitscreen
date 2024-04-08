// Copyright 2024 Hugh Thompson

#ifndef DOOR_H_
#define DOOR_H_

#include "game_object.h"

class Door : public GameObject {
 public:
  Door(int x, int y);
  bool Open();
  bool Collide(GameObject* obj);
  bool GetState();

 private:
  bool open_ = false;
};


#endif  // !DOOR_H_
