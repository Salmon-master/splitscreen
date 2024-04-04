#ifndef SHIP_H_
#define SHIP_H_

#include <vector>
#include <iostream>

#include "enemy.h"
#include "game_object.h"
#include "room.h"

class Ship {
 public:
  Ship(std::vector<std::vector<GameObject*>>* game_objects);
  ~Ship();
  std::pair<int, int> GetDimensions();
  bool MoveRoom(bool dir);

 private:
  std::vector<Room*> rooms_;
  unsigned int room_number_ = 0;
  std::vector<std::vector<GameObject*>>* game_objects_;
  void LoadRoom(int room_number);
};

#endif  // !SHIP_H_