// Copyright 2024 Hugh Thompson

#ifndef SPLITSCREEN_MENU_H_
#define SPLITSCREEN_MENU_H_

#include <vector>

#include "menu_item.h"
#include "menu_text.h"
#include "SDL2/include/SDL.h"

class Menu {
 public:
  // initisation for a menu.
  Menu();
  ~Menu();
  // render all objects on the list of menu items, called every frame by the
  // menu loop
  void Render();
  // shows and hides the menu based on its current visability
  void ChangeVisability();
  // the list of menu items to render
  std::vector<MenuItem*> menu_items_ = {};
  // initisation for a popup, takes a location on the wider screen to initialse
  // at.
  Menu(int x, int y);

 private:
  // SDL window data
  SDL_Window* win_ = nullptr;
  // SDL renderer data
  SDL_Renderer* renderer_ = nullptr;
  // visabilty status, true for visable
  bool visability_ = true;
  // border, true for popus but not for menus
  bool border_ = false;
};

#endif  // !SPLITSCREEN_MENU_H_
