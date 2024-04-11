// Copyright 2024 Hugh Thompson

#include "ship.h"

#include <random>

#include "main.h"
#include "door.h"

Ship::Ship(std::vector<std::vector<GameObject*>>* game_objects) {
  game_objects_ = game_objects;
  // room generation, from 5 to 10 rooms generated
  for (int i = 0; i < (rand() % 6) + 5; i++) {
    rooms_.push_back(new Room());
  }
  // loads inital room into gameobjects
  LoadRoom(0);
}

Ship::~Ship() {
  for (Room* room : rooms_) {
    delete room;
  }
}

std::pair<int, int> Ship::GetDimensions() {
  return {rooms_[room_number_]->GetWalls().back()->GetRect().x,
          rooms_[room_number_]->GetWalls().back()->GetRect().y
  };
}

bool Ship::MoveRoom(bool dir) {
  bool rv = false;
  int to_be_loaded = room_number_;
  // increment room if input is positive, decermesemt teh room if negitave.
  if (dir) {
    if (room_number_ <= rooms_.size() - 1) {
      to_be_loaded++;
    } else {
      rv = true;
    }
  } else {
    if (room_number_ >= 1) {
      to_be_loaded--;
    } else {
      rv = true;
    }
  }
  // load new room
  if (to_be_loaded != room_number_) {
    LoadRoom(to_be_loaded);
  }
  return rv;
}

void Ship::LoadRoom(int room_number) {
  // deleteing all old wall and door objects
  game_objects_->at(kWalls).clear();
  game_objects_->at(kDoors).clear();
  // removing old enemy objects from game object list
  game_objects_->at(kEnemies).clear();
  // upadting room index
  room_number_ = room_number;
  Room* room = rooms_[room_number_];
  // loading in new walls
  std::vector<GameObject*> walls = room->GetWalls();
  for (GameObject* obj : walls) {
    int type = NULL;
    if (dynamic_cast<Wall*>(obj)) {
      type = kWalls;
    }
    if (dynamic_cast<Door*>(obj)) {
      type = kDoors;
    }
    game_objects_->at(type).push_back(obj);
  }
  // loading in enemies
  for (Enemy* enemy : *rooms_[room_number_]->GetEnemies()) {
    if (enemy) {
      game_objects_->at(kEnemies).push_back(enemy);
    }
  }
}
