// Copyright 2024 Hugh Thompson

#include "gun.h"

#include <SDL.h>

Gun::Gun(int type, GameObject* holder, SaveManager* save) {
  held_by_ = holder;
  std::vector<int> stats = save->GetGunStats(type);
  damage_ = stats[0];
  cooldown_ = stats[1];
  speed_ = stats[2];
}

Bullet* Gun::Shoot() {
  Bullet* rv = nullptr;
  // setting the fire rate of the weapon
  if (SDL_GetTicks64() - last_shot_ > cooldown_) {
    last_shot_ = SDL_GetTicks64();
    rv = new Bullet(held_by_, damage_, speed_);
  }
  return rv;
}
