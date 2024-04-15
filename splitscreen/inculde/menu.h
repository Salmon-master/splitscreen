// Copyright 2024 Hugh Thompson

#ifndef MENU_H_
#define MENU_H_

#include <SDL.h>

class Menu {
 public:
  Menu();
  ~Menu();

 private:
  // SDL window data
  SDL_Window* win_ = nullptr;
  // SDL renderer data
  SDL_Renderer* renderer_ = nullptr;
};


#endif  // !MENU_H_
