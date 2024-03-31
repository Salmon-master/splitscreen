#ifndef ROOM_H_
#define ROOM_H_

#include <vector>

#include "SDL.h"

#include "wall.h"

class Room {
 public:
 private:
 public:
  Room();
  std::vector<Wall*> GetWalls();
  std::vector<std::pair<int, int>> GetFree();
  ~Room();

 private:
  // enum of possible states that a tile in the map can be
  enum States { Empty = 0, NextToArea, Corridor, Area, Door };
  // generate a room to be used as part of a ship, given a diffculty
  std::vector<std::vector<States>> Generate();
  // returns the coordinates of the cells immedatly ajacendt to the inputted cell
  std::vector<SDL_Point> GetSurroundingCells(int x, int y);
  // wall objects creaed from map generation
  std::vector<Wall*> walls_ = {};
  // a list of free spaces (global coorinates at center of space)
  std::vector<std::pair<int, int>> free_;

};

#endif  // !ROOM_H_
