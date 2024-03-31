#include "gun.h"

#include <SDL.h>

Gun::Gun(int type, GameObject* holder) { held_by_ = holder; }

Bullet* Gun::Shoot() {
  Bullet* rv = nullptr;
  if (SDL_GetTicks64() - last_shot_ > cooldown_) {
    last_shot_ = SDL_GetTicks64();
    rv = new Bullet(held_by_, damage_);
  }
  return rv;
}
