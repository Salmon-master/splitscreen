// Copyright 2024 Hugh Thompson

#include "enemy.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "door.h"
#include "main.h"
#include "wall.h"

Enemy::Enemy(int x, int y, int type, Room* room, SaveManager* save)
    : GameObject(x, y, "enemy_" + std::to_string(type + 1)) {
  // var initilaistion
  SetPos(x, y);
  room_ = room;
  rotation_center_.y = (rect_.h - 28);
  gun_ = new Gun(type, this, save);
  type_ = type;
  // setting up AI
  for (size_t i = 0; i < kNumRays; i++) {
    float angle = (i * 2 * M_PI) / kNumRays;
    ray_directions_[i] = {cos(angle), sin(angle)};
  }
  // setting up enemy type and loading in stats
  speed_ = kEnemyStats[type][0];
  attack_range_ = kEnemyStats[type][1];
  max_health_ =
      kEnemyStats[type][2] + ((kEnemyStats[type][2] * save->GetLevel()) / 10);
  // health bar
  health_bar_ = new UIBar(
      max_health_, {135, 211, 124},
      SDL_Rect{static_cast<int>(rect_.x), static_cast<int>(rect_.y - 10),
               static_cast<int>(rect_.w), 10});
  health_bar_->SetValue(max_health_);
}

bool Enemy::Damage(int amount) {
  bool rv = false;
  health_ -= amount;
  // speed boost if on low health
  if (health_ < max_health_ / 4) {
    speed_ *= 1.3;
  }
  // cehcking if the enemy is dead
  if (health_ <= 0) {
    rv = true;
    dead_ = true;
    health_bar_->SetValue(0);
  } else {
    health_bar_->SetValue(health_);
  }
  return rv;
}

void Enemy::AI(std::vector<std::vector<GameObject*>>* game_objects, int delta) {
  std::vector<Vector> diff;
  // looping through robots and adding to lists
  for (GameObject* robot : game_objects->at(kRobots)) {
    if (static_cast<Robot*>(robot)) {
      diff.push_back({(robot->GetRect().x + robot->GetCenter()->x) -
                          (rect_.x + rotation_center_.x),
                      (robot->GetRect().y + robot->GetCenter()->y) -
                          (rect_.y + rotation_center_.y)});
    } else {
      std::cout << "incorrect type allocated to list" << std::endl;
    }
  }
  // cehcking if in range of robot
  if (!dead_ && (diff[0].Norm() < 500 || diff[1].Norm() < 500)) {
    if (delta == 0) {
      delta = 1;
    }
    // buffer lists of objects for use
    std::vector<GameObject*> danger_objects;
    std::vector<Vector> interest_objects;
    // iterating through all game objects and adding them to the buffer lists
    for (int i = 0; i < game_objects->size() - 1; i++) {
      for (GameObject* obj : game_objects->at(i)) {
        // if wall in search range, add to danger
        if (i == kWalls) {
          if (Vector{(obj->GetRect().x + obj->GetCenter()->x) -
                         (rect_.x + rotation_center_.x),
                     (obj->GetRect().y + obj->GetCenter()->y) -
                         (rect_.y + rotation_center_.y)}
                  .Norm() < search_range_) {
            danger_objects.push_back(obj);
          }
        }
        // if other enemy in search range, add to danger
        if (i == kEnemies) {
          if (obj != this) {
            if (Vector{(obj->GetRect().x + obj->GetCenter()->x) -
                           (rect_.x + rotation_center_.x),
                       (obj->GetRect().y + obj->GetCenter()->y) -
                           (rect_.y + rotation_center_.y)}
                    .Norm() < search_range_) {
              danger_objects.push_back(obj);
            }
          }
        }
        // if robot in range, add to interest, if low health, add inverse to
        // interest, if in attack range attack
        if (i == kRobots) {
          Vector diff = {(obj->GetRect().x + obj->GetCenter()->x) -
                             (rect_.x + rotation_center_.x),
                         (obj->GetRect().y + obj->GetCenter()->y) -
                             (rect_.y + rotation_center_.y)};
          if (diff.Norm() < search_range_ * 3) {
            if (health_ < max_health_ / 4) {
              interest_objects.push_back(Vector{obj->GetRect().x - rect_.x,
                                                obj->GetRect().y - rect_.y});
              if (diff.Norm() < attack_range_) {
                Bullet* bullet = Attack(diff);
                if (speed_ > 1) {
                  speed_ *= 0.95;
                }
                if (bullet) {
                  game_objects->at(kBullets).push_back(bullet);
                }
              } else {
                speed_ = kEnemyStats[type_][0];
              }
            } else {
              speed_ = kEnemyStats[type_][0] * 1.2;
              interest_objects.push_back(
                  Vector{(obj->GetRect().x - rect_.x) * -1,
                         (obj->GetRect().y - rect_.y) * -1});
            }
          }
        }
      }
    }
    // set interest
    std::vector<float> interest(kNumRays);
    if (!interest_objects.empty()) {
      interest = SetInterest(interest_objects[0]);
    } else {
      interest = SetInterest({0, 0});
    }
    // set dangeer
    std::vector<float> danger = SetDanger(danger_objects);
    // combine interest and danger
    for (int i = 0; i < kNumRays; i++) {
      if (danger[i] != 0.0f) {
        interest[i] = danger[i];
      }
    }
    // calculate net direction
    Vector chosen_dir = {0, 0};
    for (int i = 0; i < kNumRays; i++) {
      chosen_dir.x += interest[i] * ray_directions_[i].x;
      chosen_dir.y += interest[i] * ray_directions_[i].y;
    }
    // steering calculations
    if (chosen_dir.x != 0 && chosen_dir.y != 0) {
      Vector steer = {
          ((chosen_dir.Normalised().x) - velocity_.x) * steer_force_,
          ((chosen_dir.Normalised().y) - velocity_.y) * steer_force_};
      Vector chosen_direction = {velocity_.x + steer.x, velocity_.y + steer.y};
      Move(((chosen_direction.Normalised().x * speed_ * delta) / 1000),
           ((chosen_direction.Normalised().y * speed_ * delta) / 1000));
      velocity_ = {(chosen_direction.Normalised().x * speed_ * delta) / 1000,
                   (chosen_direction.Normalised().y * speed_ * delta) / 1000};
      float new_rotation = SetRotationFromVector(chosen_direction);
      if (abs(new_rotation - rotation_) > M_PI) {
        float amount =
            ((2 * M_PI) - abs(new_rotation - rotation_)) * steer_force_ / 5;
        if (rotation_ > new_rotation) {
          rotation_ += amount;
        } else {
          rotation_ -= amount;
        }
      } else {
        rotation_ += ((new_rotation - rotation_) * steer_force_ / 5);
      }
      if (rotation_ >= 2 * M_PI) {
        rotation_ -= 2 * M_PI;
      }
      if (rotation_ <= 0) {
        rotation_ += 2 * M_PI;
      }
    } else {
      velocity_ = {0, 0};
    }
  }
}

UIBar* Enemy::GetBar() { return health_bar_; }

Enemy::~Enemy() {
  // remove enmies in a memory safe way
  if (room_->GetEnemies()->size() != 0) {
    std::vector<Enemy*>* room_emenies = room_->GetEnemies();
    room_emenies->erase(
        std::remove(room_emenies->begin(), room_emenies->end(), this),
        room_emenies->end());
  }
  delete health_bar_;
  delete gun_;
}

std::vector<float> Enemy::SetInterest(Vector direction) {
  // reurns the chosen dirction represneted in the from of all the rays in the
  // ray dirctions scaled so that the sum of theese rays is equal to the
  // inputted dirctions.
  std::vector<float> interest_aray(kNumRays);
  for (int i = 0; i < kNumRays; i++) {
    float interest =
        ray_directions_[i].Normalised().Dot(direction.Normalised());
    interest_aray[i] = std::max(0.0f, interest);
  }
  return interest_aray;
}

std::vector<float> Enemy::SetDanger(std::vector<GameObject*> objects) {
  std::vector<float> danger_aray(kNumRays);
  for (int i = 0; i < kNumRays; i++) {
    // calculating cast ray
    std::pair<SDL_Point, SDL_Point> ray = {
        SDL_Point{static_cast<int>(ray_directions_[i].Scaled(search_range_).x) +
                      static_cast<int>(rect_.x + rotation_center_.x),
                  static_cast<int>(ray_directions_[i].Scaled(search_range_).y) +
                      static_cast<int>(rect_.y + rotation_center_.y)},
        SDL_Point{static_cast<int>(rect_.x + rotation_center_.y),
                  static_cast<int>(rect_.y + rotation_center_.y)}};
    // iterates through all given game objects and checks for dangerous objects
    // in ray path
    for (GameObject* obj : objects) {
      // r is shorthand for the rect, not called rect as this uses too much
      // horizontal space
      SDL_Rect r = {obj->GetRect().x, obj->GetRect().y, obj->GetRect().w,
                    obj->GetRect().h};
      // division of that rectangle into its component line segments
      std::vector<std::pair<SDL_Point, SDL_Point>> lines = {
          {SDL_Point{r.x, r.y}, SDL_Point{r.x + r.w, r.y}},
          {SDL_Point{r.x + r.w, r.y}, SDL_Point{r.x + r.w, r.y + r.h}},
          {SDL_Point{r.x + r.w, r.y + r.h}, SDL_Point{r.x, r.y + r.h}},
          {SDL_Point{r.x, r.y + r.h}, SDL_Point{r.x, r.y}}};
      // checks each line segmemt of intercetions with the cast ray
      for (std::pair<SDL_Point, SDL_Point> line : lines) {
        float danger = 0;
        if (Intersect(line.first, line.second, ray.first, ray.second)) {
          // intersection with an object
          float diffrence;
          if (line.first.x == line.second.x) {
            diffrence = abs(line.first.x - (rect_.x + rotation_center_.x));
          } else {
            diffrence = abs(line.first.y - (rect_.y + rotation_center_.y));
          }
          Wall* wall_type = static_cast<Wall*>(obj);
          Door* door_type = static_cast<Door*>(obj);
          Enemy* enemy_type = static_cast<Enemy*>(obj);
          // wall or door else enemy
          if (wall_type || door_type) {
            danger = ((search_range_ - r.w) - diffrence) * 0.025;
          } else if (enemy_type) {
            danger = -0.001f;
          }
        }
        // if the ray has hit somthing, then no need to loop over the rest of
        // the objects
        danger_aray[i] = danger;
        if (danger != 0.0f && danger != -0.001f) {
          break;
        }
      }
      if (danger_aray[i] != 0.0f) {
        break;
      }
    }
  }
  return danger_aray;
}

bool Enemy::Intersect(SDL_Point r1, SDL_Point q1, SDL_Point r2, SDL_Point q2) {
  // algorithm from:
  // https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/,
  // checks orientation of the two tragnes formed by the lines, if diffrent
  // the the lines intersect
  int o1 = Orientation(r1, q1, r2);
  int o2 = Orientation(r1, q1, q2);
  int o3 = Orientation(r2, q2, r1);
  int o4 = Orientation(r2, q2, q1);
  if (o1 != o2 && o3 != o4) {
    return true;
  }
  return false;
}

int Enemy::Orientation(SDL_Point r1, SDL_Point r2, SDL_Point p3) {
  int val = (r2.y - r1.y) * (p3.x - r2.x) - (r2.x - r1.x) * (p3.y - r2.y);
  if (val == 0) return 0;    // collinear
  return (val > 0) ? 1 : 2;  // clock or counterclock wise
}
Bullet* Enemy::Attack(Vector location) {
  Bullet* bullet = gun_->Shoot();
  return bullet;
}

float Enemy::SetRotationFromVector(Vector rotation) {
  // basic angle, but only from 0 to PI/2
  float new_rotation = atan(velocity_.y / velocity_.x);
  // adding based of vector to get angle from 0 to 2PI
  if (rotation.y > 0) {
    if (rotation.x < 0) {
      new_rotation += M_PI;
    } else {
      new_rotation += M_PI * 2;
    }
  } else {
    if (rotation.x < 0) {
      new_rotation += M_PI;
    }
  }
  if (new_rotation < 0) {
    new_rotation += M_PI * 2;
  }
  new_rotation += M_PI / 2;
  if (new_rotation >= 2 * M_PI) {
    new_rotation -= 2 * M_PI;
  }
  return new_rotation;
}
