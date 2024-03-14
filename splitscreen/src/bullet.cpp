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

bool Bullet::Update() {
  Move(velocity_.x, velocity_.y);
  return true;
}
