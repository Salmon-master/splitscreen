#include "bullet.h"

#include <stack>

#include "enemy.h"
#include "main.h"
#include "wall.h"

Bullet::Bullet(GameObject* shooter, int damage)
    : GameObject(
          shooter->GetCenter()->x + shooter->GetRect().x +
              (sin(shooter->GetRotation()) * shooter->GetCenter()->y),
          shooter->GetCenter()->y + shooter->GetRect().y +
              (cos(shooter->GetRotation()) * shooter->GetCenter()->y * -1),
          "bullet") {
  float x = sin(shooter->GetRotation()) * speed_;
  float y = cos(shooter->GetRotation()) * speed_ * -1;
  rotation_ = shooter->GetRotation();
  velocity_ = {x, y};
  damage_ = damage;
  shooter_ = shooter;
}

bool Bullet::Update(std::vector<std::vector<GameObject*>>* objects) {
  bool destruct = false;
  Move(velocity_.x, velocity_.y);
  std::stack<GameObject*> to_remove;
  for (int i = 0; i < objects->size() - 1; i++) {
    for (GameObject* obj : objects->at(i)) {
      if (obj != shooter_) {
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
            throw 10 + kEnemies;
          }
        }
        if (i == kPlayers) {
          Player* player = dynamic_cast<Player*>(obj);
          if (player) {
            Vector diff = {(rotation_center_.x + rect_.x) -
                               (obj->GetCenter()->x + obj->GetRect().x),
                           (rotation_center_.y + rect_.y) -
                               (obj->GetCenter()->y + obj->GetRect().y)};
            if (diff.Norm() <= obj->GetCenter()->x) {
              if (player->Damage(damage_)) {
                to_remove.push(obj);
              }
              destruct = true;
              break;
            }
          } else {
            throw 10 + kPlayers;
          }
        }
      }
    }
  }
  while (!to_remove.empty()) {
    GameObject* removed = to_remove.top();
    Enemy* enemy_type = dynamic_cast<Enemy*>(to_remove.top());
    to_remove.pop();
    for (int i = kPlayers; i < kBullets; i++) {
      objects->at(i).erase(
          std::remove(objects->at(i).begin(), objects->at(i).end(), removed),
          objects->at(i).end());
    }
    if (enemy_type) {
      delete enemy_type;
    }
  }
  return destruct;
}
