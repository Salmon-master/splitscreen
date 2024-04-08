// Copyright 2024 Hugh Thompson

#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <utility>
#include <vector>

#include "game_object.h"
#include "player.h"
#include "SDL.h"
#include "ui_bar.h"

// object to control a window on screen, used by the main.cc to create a window,
// so use instantiate the object with a screen position (top left corner) and
// and then render objects to the screen using the render function that takes a
// vector of game objects as an argument. the screen camrea postion can be set
// to the location of a game object using the attach method.
class Screen {
 private:
  // window data
  SDL_Window* win_;
  SDL_Renderer* renderer_;
  int window_id_;
  // camera pos
  float x_ = 0;
  float y_ = 0;
  // object following
  Player* following_ = nullptr;
  std::pair<int, int> offset_ = {0, 0};
  std::vector<UIBar*> bars_;
  const SDL_Color background_color_ = {26, 34, 38};

 public:
  Screen(int x, int y);
  ~Screen();
  // render all objects in veiw of camrea on screen, called in main method every
  // frame
  void Render(std::vector<std::vector<GameObject*>> game_ojbects);
  // bind camrea position of object position
  void Attach(Player* target);
  UIBar* AddBar(int max_value, SDL_Color color, SDL_Rect rect, int value);
  void RemoveBar(UIBar* bar_to_remove);
  Player* GetAttached();
  std::vector<UIBar*>* GetBars();

 private:
};

#endif  // !SCREEN_H_
