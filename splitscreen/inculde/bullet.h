#ifndef BULLET_H_
#define BULLET_H_

#include "game_object.h"
#include "player.h"
#include "vector.h"

class Bullet : public GameObject {
 public:
  Bullet(Player* shooter);

 private:
  Vector velocity_ = {0, 0};
  int speed_ = 100;
};

#endif  // !BULLET_H_
