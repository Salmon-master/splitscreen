// Copyright 2024 Hugh Thompson

#ifndef ROOM_H_
#define ROOM_H_

#include <utility>
#include <vector>

#include "enemy.h"
#include "SDL.h"
#include "wall.h"
#include "save_manager.h"

class Enemy;
// A class used to represent room with the game, it is composed of wall of
// objects arranged into a 2d dunegon layout, with enemies populating that
// layout, used as a part of a ship object.
class Room {
 public:
  Room(SaveManager* save);
  std::vector<GameObject*> GetWalls();
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
  // generate a room to be used as part of a ship, given a diffculty
  std::vector<std::vector<States>> Generate();
  // returns the coordinates of the cells immedatly ajacendt to the inputted
  // cell
  std::vector<SDL_Point> GetSurroundingCells(int x, int y);
  // wall objects creaed from map generation
  std::vector<GameObject*> walls_ = {};
  // a list of free spaces (global coorinates at center of space)
  std::vector<std::pair<int, int>> free_;
  bool visited_ = false;
  // enemy objects from map generation
  std::vector<Enemy*> enemies_ = {};
};

#endif  // !ROOM_H_
