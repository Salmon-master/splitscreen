// Copyright 2024 Hugh Thompson

#include "menu.h"

#include <iostream>

#include "menu_button.h"

Menu::Menu() {
  // window creation using SDL and error caputre
  win_ = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED, 750, 465, 0);
  if (win_ == NULL) {
    std::cout << "Error window creation";
  }
  renderer_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED);
  if (renderer_ == NULL) {
    std::cout << "Error renderer creation";
  }
  // font initilasation
  if (TTF_Init() < 0) {
    std::cout << "Error initializing SDL_ttf: " << TTF_GetError();
  }
  // make it so that alpha values work correctly for transparency
  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
}

Menu::~Menu() {
  // deleting all menu items
  for (MenuItem* item : menu_items_) {
    delete item;
  }
  // destruction of window
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(win_);
}

void Menu::Render() {
  SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer_);
  // rendering border for popup
  if (border_) {
    SDL_RaiseWindow(win_);
    int w, h;
    SDL_GetWindowSize(win_, &w, &h);
    SDL_Rect rect = {0, 0, w, h};
    SDL_SetRenderDrawColor(renderer_, 60, 60, 60, 255);
    SDL_RenderDrawRect(renderer_, &rect);
    SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
  }
  // rendering menu items
  for (MenuItem* item : menu_items_) {
    if (item) {
      // update
      item->Update();
      if (item->Visable()) {
        // if a color is present, render a rectangle
        if (item->GetColor().r) {
          SDL_SetRenderDrawColor(renderer_, item->GetColor().r,
                                 item->GetColor().g, item->GetColor().b,
                                 item->GetColor().a);
          SDL_RenderFillRect(renderer_, item->GetRect());
          SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
        }
        SDL_Texture* texture = nullptr;
        // if a texture is present, render a texture
        if (item->GetSurface()) {
          texture = SDL_CreateTextureFromSurface(renderer_, item->GetSurface());
          SDL_RenderCopy(renderer_, texture, NULL, item->GetRect());
        }
        MenuButton* button = dynamic_cast<MenuButton*>(item);
        // render the button's display
        if (button) {
          MenuItem* display = button->GetDisplay();
          if (display) {
            display->Update();
            texture =
                SDL_CreateTextureFromSurface(renderer_, display->GetSurface());
            SDL_RenderCopy(renderer_, texture, NULL, display->GetRect());
          }
        }
        // clean up
        SDL_DestroyTexture(texture);
      }
    }
  }
  // push to screen
  SDL_RenderPresent(renderer_);
}

void Menu::ChangeVisability() {
  // revers the visablity staus and show/ hide the window
  if (visability_) {
    SDL_HideWindow(win_);
  } else {
    SDL_ShowWindow(win_);
  }
  visability_ = !visability_;
}

Menu::Menu(int x, int y) {
  // window creation using SDL, borderless window, error capture
  win_ = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_BORDERLESS);
  if (win_ == NULL) {
    std::cout << "Error window creation";
  }
  renderer_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED);
  if (renderer_ == NULL) {
    std::cout << "Error renderer creation";
  }
  // font initialisation
  if (TTF_Init() < 0) {
    std::cout << "Error initializing SDL_ttf: " << TTF_GetError();
  }
  // set so alpha values / tarnsparrence work on screen
  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
  // custom border
  border_ = true;
}
