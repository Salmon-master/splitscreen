// Copyright 2024 Hugh Thompson

#ifndef SHIP_H_
#define SHIP_H_

#include <iostream>
#include <utility>
#include <vector>

#include "enemy.h"
#include "game_object.h"
#include "room.h"

// A collection of rooms, and an acessible way to naviate through them. Used by
// the main script to generate rooms, load them in and navigate through them
class Ship {
 public:
  // the constuctor, the input is a pointer to the current list of gameobjects
  // used, sorted by type, so that it may be modified to add, remove and modify
  // game objects from the game, maked explicit as it is a single paramter
  // constuctor
  Ship(std::vector<std::vector<GameObject*>>* game_objects,
                SaveManager* save);
  // uninitalise and destruct in a mem safe way
  ~Ship();
  // Retuns the dimensions, in px of the current room
  std::pair<int, int> GetDimensions();
  // if the input is true, the current room will advance by 1, if false, the
  // current room will decrease by 1.
  // Retuns whether or not this navigation is outside the range of the number of
  // rooms.
  // Used by the main game lopop when the player needs to be moved to the next
  // or previous level
  bool MoveRoom(bool dir);

 private:
  // A vector of pointers to the rooms in a ship
  std::vector<Room*> rooms_;
  // an index value of which room is currenlty loaded in / being played
  unsigned int room_number_ = 0;
  // a reference to the game object list
  std::vector<std::vector<GameObject*>>* game_objects_;
  // Loads in the room number inputted, this will remove the currenlty loaded
  // room's game objects from the game object list, and add the new room's ones
  // in the correct positions
  void LoadRoom(int room_number);
};

#endif  // !SHIP_H_
