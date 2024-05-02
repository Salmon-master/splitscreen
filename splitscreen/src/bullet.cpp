// Copyright 2024 Hugh Thompson

#include "bullet.h"

#include <stack>

#include "enemy.h"
#include "main.h"
#include "wall.h"

Bullet::Bullet(GameObject* shooter, int damage, int speed)
    : GameObject(
          shooter->GetCenter()->x + shooter->GetRect().x +
              (sin(shooter->GetRotation()) * shooter->GetCenter()->y),
          shooter->GetCenter()->y + shooter->GetRect().y +
              (cos(shooter->GetRotation()) * shooter->GetCenter()->y * -1),
          "bullet") {
  // setting bullet properties
  damage_ = damage;
  shooter_ = shooter;
  speed_ = speed;
  // setting kinematic properites
  float x = sin(shooter->GetRotation()) * speed_;
  float y = cos(shooter->GetRotation()) * speed_ * -1;
  rotation_ = shooter->GetRotation();
  velocity_ = {x, y};
}

bool Bullet::Update(std::vector<std::vector<GameObject*>>* objects) {
  bool destruct = false;
  // step
  Move(velocity_.x, velocity_.y);
  std::stack<GameObject*> to_remove;
  // iterate though all objects to check for collisions
  for (int i = 0; i < objects->size() - 1; i++) {
    for (GameObject* obj : objects->at(i)) {
      // dont interact with self
      if (obj != shooter_) {
        // walls
        if (i == kWalls) {
          int x_diff = abs((obj->GetCenter()->x + obj->GetRect().x) -
                           (rotation_center_.x + rect_.x));
          int y_diff = abs((obj->GetCenter()->y + obj->GetRect().y) -
                           (rotation_center_.y + rect_.y));
          if (x_diff < obj->GetRect().w / 2 && y_diff < obj->GetRect().h / 2) {
            destruct = true;
            break;
          }
        }
        // enemies take damage
        if (i == kEnemies) {
          Enemy* enemy = dynamic_cast<Enemy*>(obj);
          if (enemy) {
            Vector diff = {(rotation_center_.x + rect_.x) -
                               (obj->GetCenter()->x + obj->GetRect().x),
                           (rotation_center_.y + rect_.y) -
                               (obj->GetCenter()->y + obj->GetRect().y)};
            if (diff.Norm() <= obj->GetCenter()->x) {
              if (enemy->Damage(damage_)) {
                to_remove.push(obj);
              }
              destruct = true;
              break;
            }
          } else {
            std::cout << "incorrect type allocated to list" << std::endl;
            +kEnemies;
          }
        }
        // robots take damage
        if (i == kRobots) {
          Robot* robot = dynamic_cast<Robot*>(obj);
          if (robot) {
            Vector diff = {(rotation_center_.x + rect_.x) -
                               (obj->GetCenter()->x + obj->GetRect().x),
                           (rotation_center_.y + rect_.y) -
                               (obj->GetCenter()->y + obj->GetRect().y)};
            if (diff.Norm() <= obj->GetCenter()->x) {
              robot->Damage(damage_);
              destruct = true;
              break;
            }
          } else {
            std::cout << "incorrect type allocated to list" << std::endl;
          }
        }
      }
    }
  }
  // deconstuct and remove enemies that have run out of health.
  while (!to_remove.empty()) {
    GameObject* removed = to_remove.top();
    to_remove.pop();
    for (int i = kRobots; i < kBullets; i++) {
      objects->at(i).erase(
          std::remove(objects->at(i).begin(), objects->at(i).end(), removed),
          objects->at(i).end());
      if (i == kEnemies) {
        Enemy* enemy = dynamic_cast<Enemy*>(removed);
        if (enemy) {
          delete enemy;
        } else {
          std::cout << "incorrect type allocated to list " << std::endl;
        }
      }
    }
  }
  // retruns true if the bullet has collided with somthing
  return destruct;
}
