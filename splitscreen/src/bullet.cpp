#include "bullet.h"


Bullet::Bullet(Player* shooter)
    : GameObject(shooter->GetCenter()->x + shooter->GetRect().x + 
                     (sin(shooter->GetRotation()) * shooter->GetCenter()->y),
                 shooter->GetCenter()->y + shooter->GetRect().y +
                     (cos(shooter->GetRotation()) * shooter->GetCenter()->y * -1),
                 "bullet") {
  float x = sin(shooter->GetRotation()) * speed_;
  float y = cos(shooter->GetRotation()) * speed_ * -1;
  rotation_ = shooter->GetRotation();
  velocity_ = {x, y};
}

bool Bullet::Update(std::vector<GameObject*>* objects) {
  bool destruct = false;
  Move(velocity_.x, velocity_.y);
  for (GameObject* obj : *objects) {
    Player* player_type = dynamic_cast<Player*>(obj);
    Bullet* bullet_type = dynamic_cast<Bullet*>(obj);
    if (!player_type && !bullet_type) {
      int x_diff = abs((obj->GetCenter()->x + obj->GetRect().x) -
                       (rotation_center_.x + rect_.x));
      int y_diff = abs((obj->GetCenter()->y + obj->GetRect().y) -
                       (rotation_center_.y + rect_.y));
      if (x_diff < obj->GetRect().w / 2 && y_diff < obj->GetRect().h / 2) {
        destruct = true;
        break;
      }
    }
  }
  return destruct;
}
