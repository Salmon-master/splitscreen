// Copyright 2024 Hugh Thompson

#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <utility>
#include <vector>

#include "SDL2/include/SDL.h"

#include "game_object.h"
#include "player.h"
#include "ui_bar.h"

// object to control a window on screen, used by the main.cc to create a window,
// so use instantiate the object with a screen position (top left corner) and
// and then render objects to the screen using the render function that takes a
// vector of game objects as an argument. the screen camrea postion can be set
// to the location of a game object using the attach method.
class Screen {
 private:
  // SDL window data
  SDL_Window* win_;
  // SDL window data
  SDL_Renderer* renderer_;
  // an ID for when the need to distunguish between windows, set in constructor
  int window_id_;
  // camera pos x
  float x_ = 0;
  // camera pos y
  float y_ = 0;
  // object following
  Player* following_ = nullptr;
  // the camera offset
  std::pair<int, int> offset_ = {0, 0};
  // the list of UI_Bars this screen should currently be displaying
  std::vector<UIBar*> bars_;
  // the background color for all bars on this screen
  const SDL_Color background_color_ = {26, 34, 38};

 public:
  // inputs are the loction of the screen object's window on the actual screen
  Screen(int x, int y);
  // uninitalise and destruct in a mem safe way
  ~Screen();
  // render all objects in veiw of camrea on screen, called in main method every
  // frame
  void Render(std::vector<std::vector<GameObject*>> game_ojbects);
  // bind camrea position to the inputted player's position, and disply the
  // health of that player on screen
  void Attach(Player* target);
  // adds a bar to the list of bars, and consequently to the screen
  UIBar* AddBar(int max_value, SDL_Color color, SDL_Rect rect, int value);
  // removes a given bar from the screen object.
  void RemoveBar(UIBar* bar_to_remove);
  // returns a pointer to the currently attached player
  Player* GetAttached();
  // retuns a pointer to the screen's bars
  std::vector<UIBar*>* GetBars();
};

#endif  // !SCREEN_H_
