// Copyright 2024 Hugh Thompson

#ifndef SPLITSCREEN_ROOM_H_
#define SPLITSCREEN_ROOM_H_

#include <utility>
#include <vector>

#include "enemy.h"
#include "save_manager.h"
#include "SDL2/include/SDL.h"
#include "wall.h"

class Enemy;
// A class used to represent room with the game, it is composed of wall of
// objects arranged into a 2d dunegon layout, with enemies populating that
// layout, used as a part of a ship object.
class Room {
 public:
  // marked explicit as it is a one parameter consctor, this paramter is the
  // save which is then passed onto the enemy objects to initialise
  explicit Room(SaveManager* save);
  // retuns the list of wall pointers in the room
  std::vector<GameObject*> GetWalls();
  // retuns a list of pointer to the enemies in the room
  std::vector<Enemy*>* GetEnemies();
  // retuns the locations that are empty for enemy spawing, used to spawn
  // eneimes
  std::vector<std::pair<int, int>> GetFree();
  ~Room();
  // retruns wether or not room has been visited by the player, also sets that
  // the room has been visited. Used by the ship class to spawn in enemies.
  bool Visit();

 private:
  // enum of possible states that a tile in the map can be
  enum States { kEmpty = 0, kNextToArea, kCorridor, kArea, kDoor };
  // generate a room to be used as part of a ship
  std::vector<std::vector<States>> Generate();
  // returns the coordinates of the cells immedatly adjcendt to the inputted
  // cell, used as helper function to Generate()
  std::vector<SDL_Point> GetSurroundingCells(int x, int y);
  // wall objects creaed from map generation
  std::vector<GameObject*> walls_ = {};
  // a list of free spaces (global coorinates at center of space)
  std::vector<std::pair<int, int>> free_;
  // wether or not this room has been visited by the player
  bool visited_ = false;
  // enemy objects from map generation
  std::vector<Enemy*> enemies_ = {};
};

#endif  // !SPLITSCREEN_ROOM_H_
