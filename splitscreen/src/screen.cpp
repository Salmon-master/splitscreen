#include "screen.h"

#include <cmath>

Screen::Screen(int x, int y) {
  // window creation using SDL
  win_ = SDL_CreateWindow("Window", x, y, 500, 500, 0);
  if (win_ == NULL) {
    std::cout << "Error window creation";
  }
  renderer_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED);
  if (renderer_ == NULL) {
    std::cout << "Error renderer creation";
  }
  window_id_ = SDL_GetWindowID(win_);
}

Screen::~Screen() {
  // clean up to avoid memory leaks
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(win_);
}

void Screen::Render(std::vector<GameObject*> game_objects) {
  // renderer setup
  SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer_);
  // update of cam postion if bound to object
  if (following_) {
    x_ = following_->GetRect().x;
    y_ = following_->GetRect().y;
  }
  // iterate through all game objects, rendering all if conditions met
  for (GameObject* obj : game_objects) {
    // calcuate position on screen
    SDL_FRect actual_rect = obj->GetRect();
    SDL_Rect render_rect = {(actual_rect.x - x_ + offset_.first),
                            (actual_rect.y - y_ + offset_.second),
                            actual_rect.w, actual_rect.h};
    // if the object is on screen, then render it
    if (render_rect.x > -1 * actual_rect.w && render_rect.x < 600 &&
        render_rect.y > -1 * actual_rect.h && render_rect.y < 500) {
      // render object on screen
      obj->rendered_ = true;
      SDL_Texture* texture =
          SDL_CreateTextureFromSurface(renderer_, obj->GetSurface());
      float angle = obj->GetRotation() * (180 / M_PI);
      SDL_RenderCopyEx(renderer_, texture, NULL, &render_rect, angle,
                       obj->GetCenter(), SDL_FLIP_NONE);
      SDL_DestroyTexture(texture);
    }
  }
  // Update screen
  SDL_RenderPresent(renderer_);
}

void Screen::Attach(GameObject* target) {
  // set target
  following_ = target;
  // set offset so target is centered on screen
  offset_.first = 250 - following_->GetCenter()->x;
  offset_.second = 250 - following_->GetCenter()->y;
}
