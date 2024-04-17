// Copyright 2024 Hugh Thompson

#include "screen.h"

#include <cmath>
#include <stack>

#include "enemy.h"

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
  for (UIBar* bar : bars_) {
    delete bar;
  }
}

void Screen::Render(std::vector<std::vector<GameObject*>> game_objects) {
  // renderer setup
  SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer_);
  // update of cam postion if bound to object
  if (following_) {
    x_ = following_->GetRect().x;
    y_ = following_->GetRect().y;
  }
  // iterate through all game objects, rendering all if conditions met
  for (std::vector<GameObject*> type_vector : game_objects) {
    for (GameObject* obj : type_vector) {
      // calcuate position on screen
      SDL_FRect actual_rect = obj->GetRect();
      SDL_Rect render_rect = {(actual_rect.x - x_ + offset_.first),
                              (actual_rect.y - y_ + offset_.second),
                              actual_rect.w, actual_rect.h};
      // if the object is on screen, then render it
      if (render_rect.x > -1 * actual_rect.w && render_rect.x < 600 &&
          render_rect.y > -1 * actual_rect.h && render_rect.y < 600) {
        // render object on screen
        obj->rendered_ = true;
        SDL_Texture* texture =
            SDL_CreateTextureFromSurface(renderer_, obj->GetSurface());
        float angle = obj->GetRotation() * (180 / M_PI);
        SDL_RenderCopyEx(renderer_, texture, NULL, &render_rect, angle,
                         obj->GetCenter(), SDL_FLIP_NONE);
        SDL_DestroyTexture(texture);
        // add eney health bar to list if the bar has not been added to the list before.
        Enemy* enemy_type = dynamic_cast<Enemy*>(obj);
        if (enemy_type) {
          if (std::count(bars_.begin(), bars_.end(),
                                enemy_type->GetBar(this)) == 0) {
            bars_.push_back(enemy_type->GetBar(this));
          }
          SDL_FRect rect = enemy_type->GetRect();
          enemy_type->GetBar(this)->SetPos(rect.x - x_ + offset_.first,
                                           (rect.y + 20) - y_ + offset_.second);
        }
      }
    }
  }
  // UI_Bar rendering of bars attached to this screen
  if (bars_.size() > 0) {
    std::stack<UIBar*> to_remove;
    for (auto bar : bars_) {
      if (!bar) {
        to_remove.push(bar);
      } else {
        SDL_SetRenderDrawColor(renderer_, background_color_.r,
                               background_color_.g, background_color_.b, 1);
        SDL_RenderFillRect(renderer_, bar->GetRect());
        SDL_SetRenderDrawColor(renderer_, bar->GetBar().second.r,
                               bar->GetBar().second.g, bar->GetBar().second.b,
                               1);
        SDL_RenderFillRect(renderer_, bar->GetBar().first);
      }
    }
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 1);
    while (!to_remove.empty()) {
      bars_.erase(std::remove(bars_.begin(), bars_.end(), to_remove.top()),
                  bars_.end());
      to_remove.pop();
    }
  }
  // Update screen
  SDL_RenderPresent(renderer_);
}

void Screen::Attach(Player* target) {
  // set target
  following_ = target;
  // set offset so target is centered on screen
  offset_.first = 250 - following_->GetCenter()->x;
  offset_.second = 250 - following_->GetCenter()->y;
  // add the damage bar of the robot to the list of bars 
  bars_.push_back(following_->GetBar());
  bars_.back()->SetPos(10, 450);
}
UIBar* Screen::AddBar(int max_value, SDL_Color color, SDL_Rect rect,
                      int value) {
  std::cout << "addbar" << std::endl;
  bars_.push_back(new UIBar(max_value, color, rect));
  bars_.back()->SetValue(value);
  return bars_.back();
}

void Screen::RemoveBar(UIBar* bar_to_remove) {
  std::cout << "killbar" << std::endl;
  bars_.erase(std::remove(bars_.begin(), bars_.end(), bar_to_remove),
              bars_.end());
  delete bar_to_remove;
}

Player* Screen::GetAttached() { return following_; }

std::vector<UIBar*>* Screen::GetBars() { return &bars_; }
