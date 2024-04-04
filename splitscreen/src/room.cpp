#include "room.h"

#include <time.h>

#include <cstdlib>
#include <iostream>
#include <stack>

#include "door.h"
#include "vector.h"

Room::Room() {
  // convertin genretaed map into walls
  std::vector<std::vector<Room::States>> map = Generate();
  for (int y = 0; y < map.size() - 1; y++) {
    for (int x = 0; x < map[0].size() - 1; x++) {
      if (y == 0 && x == 1) {
        Door* door = new Door(x * 128, y * 128);
        walls_.push_back(door);
        door->Open();
      } else if (map[y][x] == kEmpty || map[y][x] == kNextToArea) {
        walls_.push_back(new Wall(x * 128, y * 128));
      } else {
        free_.push_back({(x * 128) + 64, (y * 128) + 64});
      }
    }
    walls_.push_back(new Wall((map[0].size() - 1) * 128, y * 128));
    std::cout << std::endl;
  }
  for (int x = 0; x < map[0].size(); x++) {
    if (x == map[0].size() - 2) {
      walls_.push_back(new Door(x * 128, (map.size() - 1) * 128));
    } else {
      walls_.push_back(new Wall(x * 128, (map.size() - 1) * 128));
    }
  }
  int size = (((rand() % (61)) + 70) / 100.0f) * (free_.size() / 12);
  for (int i = 0; i < size; i++) {
    int random = rand() % free_.size();
    Enemy* enemy =
        new Enemy(free_[random].first, free_[random].second, 1, this);
    free_.erase(free_.begin() + random);
    enemy->Move(-1 * enemy->GetCenter()->x, -1 * enemy->GetCenter()->y);
    enemies_.push_back(enemy);
  }
}

std::vector<GameObject*> Room::GetWalls() { return walls_; }

std::vector<Enemy*>* Room::GetEnemies() { return &enemies_; }

std::vector<std::pair<int, int>> Room::GetFree() { return free_; }

Room::~Room() {
  // as enemy deconstructor deletes itself from enemy list, the enemies cannot be
  // deleted while iterating over that list as it chnages size while iterating.
  std::stack<Enemy*> delete_stack;
  for (Enemy* enemy : enemies_) {
    delete_stack.push(enemy);
  }
  while (!delete_stack.empty()) {
    delete delete_stack.top();
    delete_stack.pop();
  }
  for (GameObject* wall : walls_) {
    delete wall;
  }
}

bool Room::Visit() {
  bool rv = visited_;
  visited_ = true;
  return rv;
}

std::vector<std::vector<Room::States>> Room::Generate() {
  std::vector<std::vector<Room::States>> output;
  // generate blank feild
  int width = (rand() % (22 - 12 + 1)) + 12;
  int height = (rand() % (22 - 12 + 1)) + 12;
  std::vector<Room::States> push;
  for (int i = 0; i < width; i++) {
    push.push_back(kEmpty);
  }
  for (int i = 0; i < height; i++) {
    output.push_back(push);
  }
  // 3x3 end room generation
  for (int l = height - 5; l < height; l++) {
    for (int f = width - 5; f < width; f++) {
      if (l == height - 5 || l == height || f == width - 5 || f == width) {
        output[l][f] = kNextToArea;

      } else {
        output[l][f] = kArea;
      }
    }
  }
  // 3x3 starting room generation
  for (int l = 0; l < 5; l++) {
    for (int f = 0; f < 5; f++) {
      if (l == 0 || l == 5 || f == 0 || f == 5) {
        output[l][f] = kNextToArea;

      } else {
        output[l][f] = kArea;
      }
    }
  }
  // room generation
  int area = width * height;
  for (int i = 0; i < area / 10; i++) {
    // random room size
    int room_width = (rand() % ((width / 2) - (width / 5) + 1)) + (width / 5);
    int room_height =
        (rand() % ((height / 2) - (height / 5) + 1)) + (width / 5);
    for (int j = 0; j < 50; j++) {
      // random position
      bool placable = true;
      int x = rand() % (width - room_width) + 1;
      int y = rand() % (height - room_height) + 1;
      // checking if the room is placeble
      for (int l = 0; l < room_height; l++) {
        for (int f = 0; f < room_width; f++) {
          if (output[l + y][x + f] != kEmpty) {
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
                output[l + y][x + f] = kNextToArea;
              }
            } else {
              output[l + y][x + f] = kArea;
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
      if (output[i][j] == kEmpty) {
        int startable = false;
        for (SDL_Point pos : GetSurroundingCells(j, i)) {
          if (output[pos.y][pos.x] == kEmpty ||
              output[pos.y][pos.x] == kNextToArea) {
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
      output[pos.top().y][pos.top().x] = kCorridor;
      // left
      if (pos.top().x > 1) {
        if (output[pos.top().y][pos.top().x - 1] == kEmpty &&
            output[pos.top().y][pos.top().x - 2] != kCorridor &&
            output[pos.top().y + 1][pos.top().x - 1] != kCorridor &&
            output[pos.top().y - 1][pos.top().x - 1] != kCorridor) {
          directions.push({-1, 0});
        }
      }
      // right
      if (pos.top().x < width - 2) {
        if (output[pos.top().y][pos.top().x + 1] == kEmpty &&
            output[pos.top().y][pos.top().x + 2] != kCorridor &&
            output[pos.top().y + 1][pos.top().x + 1] != kCorridor &&
            output[pos.top().y - 1][pos.top().x + 1] != kCorridor) {
          directions.push({1, 0});
        }
      }
      // up
      if (pos.top().y > 1) {
        if (output[pos.top().y - 1][pos.top().x] == kEmpty &&
            output[pos.top().y - 2][pos.top().x] != kCorridor &&
            output[pos.top().y - 1][pos.top().x + 1] != kCorridor &&
            output[pos.top().y - 1][pos.top().x - 1] != kCorridor) {
          directions.push({0, -1});
        }
      }
      // down
      if (pos.top().y < height - 2) {
        if (output[pos.top().y + 1][pos.top().x] == kEmpty &&
            output[pos.top().y + 2][pos.top().x] != kCorridor &&
            output[pos.top().y + 1][pos.top().x + 1] != kCorridor &&
            output[pos.top().y + 1][pos.top().x - 1] != kCorridor) {
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
        if (output[i][j] == kEmpty) {
          int startable = false;
          for (SDL_Point pos : GetSurroundingCells(j, i)) {
            if (output[pos.y][pos.x] == kEmpty ||
                output[pos.y][pos.x] == kNextToArea) {
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
        if (output[point.y][point.x] == kArea) {
          area++;
        }
        if (output[point.y][point.x] == kCorridor) {
          corridor++;
        }
      }
      if ((area >= 2 || (area + corridor >= 2 && corridor == 1)) &&
          (output[y][x] == kEmpty || output[y][x] == kNextToArea)) {
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
              output[group.top().y][group.top().x] = kDoor;
              length = group.size();
              for (int i = 0; i < length; i++) {
                group.pop();
              }
              group_counter = 0;
              group.push({x, y});
            } else {
              output[group.top().y][group.top().x] = kDoor;
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
  output[group.top().y][group.top().x] = kDoor;
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
        if (output[point.y][point.x] == kArea) {
          area++;
        }
        if (output[point.y][point.x] == kCorridor) {
          corridor++;
        }
      }
      if ((area >= 2 || (area + corridor >= 2 && corridor == 1)) &&
          (output[y][x] == kEmpty || output[y][x] == kNextToArea)) {
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
              output[group.top().y][group.top().x] = kDoor;
              length = group.size();
              for (int i = 0; i < length; i++) {
                group.pop();
              }
              group_counter = 0;
              group.push({x, y});
            } else {
              output[group.top().y][group.top().x] = kDoor;
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
  output[group.top().y][group.top().x] = kDoor;

  // cleanup and dead end deletion
  int number_of_dead_ends = 1;
  while (number_of_dead_ends != 0) {
    number_of_dead_ends = 0;
    for (int y = 1; y < output.size() - 1; y++) {
      for (int x = 1; x < output[0].size() - 1; x++) {
        if (output[y][x] != kEmpty && output[y][x] != kNextToArea) {
          int sum = 0;
          for (SDL_Point cell : GetSurroundingCells(x, y)) {
            if (output[cell.y][cell.x] != kEmpty &&
                output[cell.y][cell.x] != kNextToArea) {
              sum++;
            }
          }
          if (sum <= 1) {
            output[y][x] = kEmpty;
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
