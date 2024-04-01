#include "ship.h"

#include <random>

#include "main.h"

Ship::Ship(std::vector<std::vector<GameObject*>>* game_objects) {
  game_objects_ = game_objects;
  for (int i = 0; i < (rand() % 6) + 5; i++) {
    rooms_.push_back(new Room());
  }
  LoadRoom(0);
}

Ship::~Ship() {
  for (Room* room : rooms_) {
    delete room;
  }
}

void Ship::LoadRoom(int room_number) {
  // deleteing old wall objects
  for (Wall* wall : rooms_[room_number_]->GetWalls()) {
    game_objects_->at(kWalls).erase(
        std::remove(game_objects_->at(kWalls).begin(),
                    game_objects_->at(kWalls).end(), wall),
        game_objects_->at(kWalls).end());
  }
  // upadting room index
  room_number_ = room_number;
  Room* room = rooms_[room_number_];
  // loading in new walls
  std::vector<Wall*> walls = room->GetWalls();
  for (Wall* wall : walls) {
    game_objects_->at(kWalls).push_back(wall);
  }
  // loading in enemies
  std::vector<std::pair<int, int>> free = room->GetFree();
  int size = (((rand() % (61)) + 70) / 100.0f) * (free.size() / 12);
  for (int i = 0; i < size; i++) {
    int random = rand() % free.size();
    Enemy* enemy = new Enemy(free[random].first, free[random].second, 1);
    free.erase(free.begin() + random);
    enemy->Move(-1 * enemy->GetCenter()->x, -1 * enemy->GetCenter()->y);
    game_objects_->at(kEnemies).push_back(enemy);
  }
}
