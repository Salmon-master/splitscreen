#include "menu.h"

#include <iostream>

Menu::Menu() {
  // window creation using SDL
  win_ = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED, 500, 750, 0);
  if (win_ == NULL) {
    std::cout << "Error window creation";
  }
  renderer_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED);
  if (renderer_ == NULL) {
    std::cout << "Error renderer creation";
  }
}