#ifndef BULLET_H_
#define BULLET_H_

#include "game_object.h"
#include "player.h"
#include "vector.h"

class Player;

class Bullet : public GameObject {
 public:
  Bullet(Player* shooter);
  bool Update(std::vector<GameObject*>* objects);

 private:
  Vector velocity_ = {0, 0};
  int speed_ = 10;
};

#endif  // !BULLET_H_
