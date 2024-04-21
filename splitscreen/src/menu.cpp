#include "menu.h"

#include <iostream>

#include "menu_button.h"

Menu::Menu() {
  // window creation using SDL
  win_ = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED, 750, 465, 0);
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
  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
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
  if (border_) {
    SDL_RaiseWindow(win_);
    int w, h;
    SDL_GetWindowSize(win_, &w, &h);
    SDL_Rect rect = {0, 0, w, h};
    SDL_SetRenderDrawColor(renderer_, 60, 60, 60, 255);
    SDL_RenderDrawRect(renderer_, &rect);
    SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
  }
  for (MenuItem* item : menu_items_) {
    if (item) {
      item->Update();
      if (item->Visable()) {
        if (item->GetColor().r) {
          SDL_SetRenderDrawColor(renderer_, item->GetColor().r,
                                 item->GetColor().g, item->GetColor().b,
                                 item->GetColor().a);
          SDL_RenderFillRect(renderer_, item->GetRect());
          SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
        }
        SDL_Texture* texture = nullptr;
        if (item->GetSurface()) {
          texture = SDL_CreateTextureFromSurface(renderer_, item->GetSurface());
          SDL_RenderCopy(renderer_, texture, NULL, item->GetRect());
        }
        MenuButton* button = dynamic_cast<MenuButton*>(item);
        if (button) {
          MenuItem* display = button->GetDisplay();
          if (display) {
            display->Update();
            texture =
                SDL_CreateTextureFromSurface(renderer_, display->GetSurface());
            SDL_RenderCopy(renderer_, texture, NULL, display->GetRect());
          }
        }
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
  visability_ = !visability_;
}

Menu::Menu(int x, int y) {
  // window creation using SDL
  win_ = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       x, y, SDL_WINDOW_BORDERLESS);
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
  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
  border_ = true;
}
