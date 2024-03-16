#include "enemy.h"

Enemy::Enemy(int x, int y, std::string type) : GameObject(x, y, type) {
  SetPos(x, y);
  for (size_t i = 0; i < num_rays_; i++) {
    float angle = (i * 2 * M_PI) / num_rays_;
    ray_directions_[i] = {cos(angle), sin(angle)};
  }
}

bool Enemy::Damage(int amount) {
  bool rv = false;
  health_ -= amount;
  if (health_ <= 0) {
    rv = true;
  }
  return rv;
}

std::vector<float> Enemy::SetInterest(Vector direction) {
  std::vector<float> interest(num_rays_);
  for (float i : interest) {
  }
}
