#include "menu.h"

#include <iostream>

#include "menu_button.h"


Menu::Menu() {
  // window creation using SDL
  win_ = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED, 750, 500, 0);
  if (win_ == NULL) {
    std::cout << "Error window creation";
  }
  renderer_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED);
  if (renderer_ == NULL) {
    std::cout << "Error renderer creation";
  }
  if (TTF_Init() < 0) {
    std::cout << "Error initializing SDL_ttf: " << TTF_GetError();
  }
}

Menu::~Menu() {
  for (MenuItem* item : menu_items_) {
    delete item;
  }
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(win_);
}

void Menu::Render() {
  SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer_);
  for (MenuItem* item : menu_items_) {
    item->Update();
    if (item->Visable()) {
      if (item->GetColor().r) {
        SDL_SetRenderDrawColor(renderer_, item->GetColor().r, item->GetColor().g,
                               item->GetColor().b, 1);
        SDL_RenderFillRect(renderer_, item->GetRect());
        SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
      }
      if (item->GetSurface()) {
        SDL_Texture* texture =
            SDL_CreateTextureFromSurface(renderer_, item->GetSurface());
        SDL_RenderCopy(renderer_, texture, NULL, item->GetRect());
        SDL_DestroyTexture(texture);
      }
    }
  }
  SDL_RenderPresent(renderer_);
}

void Menu::ChangeVisability() {
  if (visability_) {
    SDL_HideWindow(win_);
  } else {
    SDL_ShowWindow(win_);
  }
  visability_ != visability_;
}
