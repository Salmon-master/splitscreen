#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>

#include "game_object.h"
#include "vector.h"

class Enemy : public GameObject {
 public:
  Enemy(int x, int y, std::string type);
  bool Damage(int amount);
  void AI(std::vector<GameObject*> game_objects);
  std::vector<float> SetInterest(Vector direction);

 private:
  int health_ = 100;
  int speed_ = 200;
  static const int num_rays_ = 32;
  Vector ray_directions_[num_rays_];
};

#endif  // !ENEMY_H_
