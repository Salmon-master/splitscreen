#ifndef GUN_H_
#define GUN_H_

#include "player.h"
#include "bullet.h"

class Player;
class Bullet;

class Gun {
 public:
  Gun(int type, Player* player);
  Bullet* Shoot();
 private:
  int cooldown_ = 200;
  int last_shot_ = 0;
  int type_ = 0;
  int damage_ = 20;
  Player* held_by_ = nullptr;
};

#endif  // !GUN_H_
