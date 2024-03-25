#include "bullet.h"

#include <stack>

#include "enemy.h"
#include "wall.h"

Bullet::Bullet(Player* shooter, int damage)
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
}

bool Bullet::Update(std::vector<GameObject*>* objects) {
  bool destruct = false;
  Move(velocity_.x, velocity_.y);
  std::stack<GameObject*> to_remove;
  for (GameObject* obj : *objects) {
    Player* player_type = dynamic_cast<Player*>(obj);
    Bullet* bullet_type = dynamic_cast<Bullet*>(obj);
    Enemy* enemy_type = dynamic_cast<Enemy*>(obj);
    Wall* wall_type = dynamic_cast<Wall*>(obj);
    if (wall_type) {
      int x_diff = abs((obj->GetCenter()->x + obj->GetRect().x) -
                       (rotation_center_.x + rect_.x));
      int y_diff = abs((obj->GetCenter()->y + obj->GetRect().y) -
                       (rotation_center_.y + rect_.y));
      if (x_diff < obj->GetRect().w / 2 && y_diff < obj->GetRect().h / 2) {
        destruct = true;
        break;
      }
    }
    if (enemy_type) {
      Vector diff = {(rotation_center_.x + rect_.x) -
                         (obj->GetCenter()->x + obj->GetRect().x),
                     (rotation_center_.y + rect_.y) -
                         (obj->GetCenter()->y + obj->GetRect().y)};
      if (diff.Norm() <= obj->GetCenter()->x) {
        if (enemy_type->Damage(damage_)) {
          to_remove.push(obj);
        }
        destruct = true;
        break;
      }
    }
  }
  while (!to_remove.empty()) {
    GameObject* removed = to_remove.top();
    Enemy* enemy_type = dynamic_cast<Enemy*>(to_remove.top());
    to_remove.pop();
    objects->erase(std::remove(objects->begin(), objects->end(), removed),
                   objects->end());
    if (enemy_type) {
      delete enemy_type;
    }
  }
  return destruct;
}
