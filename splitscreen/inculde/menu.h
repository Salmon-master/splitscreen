// Copyright 2024 Hugh Thompson

#ifndef MENU_H_
#define MENU_H_

#include <SDL.h>

#include <vector>

#include "menu_item.h"
#include "menu_text.h"

class Menu {
 public:
  Menu();
  ~Menu();
  void Render();
  void ChangeVisability();
  std::vector<MenuItem*> menu_items_ = {};

 private:
  // SDL window data
  SDL_Window* win_ = nullptr;
  // SDL renderer data
  SDL_Renderer* renderer_ = nullptr;
  bool visability_ = true;
};

#endif  // !MENU_H_
