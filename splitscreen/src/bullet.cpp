#include "bullet.h"

Bullet::Bullet(Player* shooter)
    : GameObject(shooter->GetCenter()->x +
                     (sin(shooter->GetRotation()) * shooter->GetCenter()->y),
                 shooter->GetCenter()->y +
                     (cos(shooter->GetRotation()) * shooter->GetCenter()->y),
                 "bullet") {
  float x = sin(shooter->GetRotation()) * speed_;
  float y = cos(shooter->GetRotation()) * speed_;
  velocity_ = {x, y};
}