#include "room.h"

#include <time.h>

#include <cstdlib>
#include <iostream>
#include <stack>

#include "vector.h"

Room::Room() {
  std::vector<std::vector<Room::States>> map = Generate();
  for (int y = 0; y < map.size() - 1; y++) {
    for (int x = 0; x < map[0].size() - 1; x++) {
      if (map[y][x] == Empty || map[y][x] == NextToArea) {
        walls.push_back(new Wall(x * 128, y * 128));
      }
    }
    walls.push_back(new Wall((map[0].size() - 1) * 128, y * 128));
    std::cout << std::endl;
  }
  for (int x = 0; x < map[0].size(); x++) {
    walls.push_back(new Wall(x * 128, (map.size() - 1) * 128));
  }
}

std::vector<Wall*> Room::GetWalls() { return walls; }

Room::~Room() {
  for (Wall* wall : walls) {
    delete wall;
  }
}

std::vector<std::vector<Room::States>> Room::Generate() {
  // srand(time(0));
  srand(34560);
  std::vector<std::vector<Room::States>> output;
  // generate blank feild
  int width = (rand() % (40 - 20 + 1)) + 20;
  int height = (rand() % (40 - 20 + 1)) + 20;
  std::vector<Room::States> push;
  for (int i = 0; i < width; i++) {
    push.push_back(Empty);
  }
  for (int i = 0; i < height; i++) {
    output.push_back(push);
  }
  // room generation
  for (int i = 0; i < (rand() % (20 - 10 + 1)) + 10; i++) {
    // random room size
    int room_width = (rand() % ((width / 4) - (width / 8) + 1)) + (width / 8);
    int room_height =
        (rand() % ((height / 4) - (height / 8) + 1)) + (width / 8);
    for (int j = 0; j < 50; j++) {
      // random position
      bool placable = true;
      int x = rand() % (width - room_width) + 1;
      int y = rand() % (height - room_height) + 1;
      // checking if the room is placeble
      for (int l = 0; l < room_height; l++) {
        for (int f = 0; f < room_width; f++) {
          if (output[l + y][x + f] != Empty) {
            placable = false;
          }
        }
      }
      if (placable) {
        for (int l = -1; l < room_height + 1; l++) {
          for (int f = -1; f < room_width + 1; f++) {
            if (l < 0 || l >= room_height || f < 0 || f >= room_width) {
              if ((l + y) > 0 && (l + y) < height - 1 && (f + x) > 0 &&
                  (f + x) < width - 1) {
                output[l + y][x + f] = NextToArea;
              }
            } else {
              output[l + y][x + f] = Area;
            }
          }
        }
        break;
      }
    }
  }

  // corridor generation
  std::vector<SDL_Point> starting_points = {};
  // getting a list of possible starting points
  for (int i = 1; i < output.size() - 2; i++) {
    for (int j = 1; j < output[i].size() - 2; j++) {
      if (output[i][j] == Empty) {
        int startable = false;
        for (SDL_Point pos : GetSurroundingCells(j, i)) {
          if (output[pos.y][pos.x] == Empty ||
              output[pos.y][pos.x] == NextToArea) {
            startable++;
          }
        }
        if (startable == 4) {
          starting_points.push_back({j, i});
        }
      }
    }
  }
  while (starting_points.size() != 0) {
    // getting a starting point
    SDL_Point starting_point = starting_points[rand() % starting_points.size()];

    // staring maze generation algorithim
    std::stack<SDL_Point> pos;
    pos.push(starting_point);

    while (!pos.empty()) {
      std::stack<Vector> directions;
      output[pos.top().y][pos.top().x] = Corridor;
      // left
      if (pos.top().x > 1) {
        if (output[pos.top().y][pos.top().x - 1] == Empty &&
            output[pos.top().y][pos.top().x - 2] != Corridor &&
            output[pos.top().y + 1][pos.top().x - 1] != Corridor &&
            output[pos.top().y - 1][pos.top().x - 1] != Corridor) {
          directions.push({-1, 0});
        }
      }
      // right
      if (pos.top().x < width - 2) {
        if (output[pos.top().y][pos.top().x + 1] == Empty &&
            output[pos.top().y][pos.top().x + 2] != Corridor &&
            output[pos.top().y + 1][pos.top().x + 1] != Corridor &&
            output[pos.top().y - 1][pos.top().x + 1] != Corridor) {
          directions.push({1, 0});
        }
      }
      // up
      if (pos.top().y > 1) {
        if (output[pos.top().y - 1][pos.top().x] == Empty &&
            output[pos.top().y - 2][pos.top().x] != Corridor &&
            output[pos.top().y - 1][pos.top().x + 1] != Corridor &&
            output[pos.top().y - 1][pos.top().x - 1] != Corridor) {
          directions.push({0, -1});
        }
      }
      // down
      if (pos.top().y < height - 2) {
        if (output[pos.top().y + 1][pos.top().x] == Empty &&
            output[pos.top().y + 2][pos.top().x] != Corridor &&
            output[pos.top().y + 1][pos.top().x + 1] != Corridor &&
            output[pos.top().y + 1][pos.top().x - 1] != Corridor) {
          directions.push({0, 1});
        }
      }
      if (directions.empty()) {
        pos.pop();
      } else {
        if (directions.size() - 1 != 0) {
          int length = rand() % directions.size() - 1;
          for (int i = 0; i < length; i++) {
            directions.pop();
          }
        }
        SDL_Point next = {(pos.top().x + directions.top().x),
                          (pos.top().y + directions.top().y)};
        pos.push(next);
      }
    }
    starting_points = {};
    for (int i = 1; i < output.size() - 2; i++) {
      for (int j = 1; j < output[i].size() - 2; j++) {
        if (output[i][j] == Empty) {
          int startable = false;
          for (SDL_Point pos : GetSurroundingCells(j, i)) {
            if (output[pos.y][pos.x] == Empty ||
                output[pos.y][pos.x] == NextToArea) {
              startable++;
            }
          }
          if (startable == 4) {
            starting_points.push_back({j, i});
          }
        }
      }
    }
  }
  // doorways
  std::stack<SDL_Point> group;
  unsigned int group_counter = 0;

  // horizontal
  for (int y = 1; y < output.size() - 2; y++) {
    for (int x = 1; x < output[0].size() - 2; x++) {
      int area = 0;
      int corridor = 0;
      // checking if the cell is a potential doorway
      std::vector<SDL_Point> cells = GetSurroundingCells(x, y);
      for (int i = 0; i < 4; i += 2) {
        SDL_Point point = cells[i];
        if (output[point.y][point.x] == Area) {
          area++;
        }
        if (output[point.y][point.x] == Corridor) {
          corridor++;
        }
      }
      if ((area >= 2 || (area + corridor >= 2 && corridor == 1)) &&
          (output[y][x] == Empty || output[y][x] == NextToArea)) {
        // to figure out where the door should be placed
        if (!group.empty()) {
          if (group.top().x == x - 1) {
            group_counter++;
            group.push({x, y});
          } else {
            if (group_counter > 0) {
              int length = rand() % group_counter + 1;
              if (length != 0) {
                for (int i = 0; i < length; i++) {
                  group.pop();
                }
              }
              output[group.top().y][group.top().x] = Door;
              length = group.size();
              for (int i = 0; i < length; i++) {
                group.pop();
              }
              group_counter = 0;
              group.push({x, y});
            } else {
              output[group.top().y][group.top().x] = Door;
              group.pop();
              group.push({x, y});
            }
          }
        } else {
          group.push({x, y});
        }
      }
    }
  }
  output[group.top().y][group.top().x] = Door;
  group = {};
  group_counter = 0;
  // vertical
  for (int x = 1; x < output[0].size() - 2; x++) {
    for (int y = 1; y < output.size() - 2; y++) {
      int area = 0;
      int corridor = 0;
      // checking if the cell is a potential doorway
      std::vector<SDL_Point> cells = GetSurroundingCells(x, y);
      for (int i = 1; i < 4; i += 2) {
        SDL_Point point = cells[i];
        if (output[point.y][point.x] == Area) {
          area++;
        }
        if (output[point.y][point.x] == Corridor) {
          corridor++;
        }
      }
      if ((area >= 2 || (area + corridor >= 2 && corridor == 1)) &&
          (output[y][x] == Empty || output[y][x] == NextToArea)) {
        // to figure out where the door should be placed
        if (!group.empty()) {
          if (group.top().y == y - 1) {
            group_counter++;
            group.push({x, y});
          } else {
            if (group_counter > 0) {
              int length = rand() % group_counter + 1;
              if (length != 0) {
                for (int i = 0; i < length; i++) {
                  group.pop();
                }
              }
              output[group.top().y][group.top().x] = Door;
              length = group.size();
              for (int i = 0; i < length; i++) {
                group.pop();
              }
              group_counter = 0;
              group.push({x, y});
            } else {
              output[group.top().y][group.top().x] = Door;
              group.pop();
              group.push({x, y});
            }
          }
        } else {
          group.push({x, y});
        }
      }
    }
  }
  output[group.top().y][group.top().x] = Door;

  // cleanup and dead end deletion
  int number_of_dead_ends = 1;
  while (number_of_dead_ends != 0) {
    number_of_dead_ends = 0;
    for (int y = 1; y < output.size() - 1; y++) {
      for (int x = 1; x < output[0].size() - 1; x++) {
        if (output[y][x] != Empty && output[y][x] != NextToArea) {
          int sum = 0;
          for (SDL_Point cell : GetSurroundingCells(x, y)) {
            if (output[cell.y][cell.x] != Empty &&
                output[cell.y][cell.x] != NextToArea) {
              sum++;
            }
          }
          if (sum <= 1) {
            output[y][x] = Empty;
            number_of_dead_ends++;
          }
        }
      }
    }
  }
  return output;
}

std::vector<SDL_Point> Room::GetSurroundingCells(int x, int y) {
  std::vector<SDL_Point> rv = {{x, y - 1}, {x + 1, y}, {x, y + 1}, {x - 1, y}};
  return rv;
}
