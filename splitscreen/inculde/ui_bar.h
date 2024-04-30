// Copyright 2024 Hugh Thompson

#ifndef UI_BAR_H_
#define UI_BAR_H_

#include <iostream>
#include <utility>

#include "SDL2/include/SDL.h"

// a class used to display infomation to the player in the from of a bar, theese
// bars are assigned to an induvidular screen object which will display them.
class UIBar {
 public:
  // constructor, takes a max value, the color of that bar and a rect
  // represneting what place(in screen space) and dimensions the bar should
  // occupy
  UIBar(int max_value, SDL_Color color, SDL_Rect rect);
  // set the value of the bar
  void SetValue(int value);
  // modifies the value of the bar by the inputted amount
  void ChangeValue(float delta_value);
  // returns the a rect and color of the coloured part of the bar, called in the
  // render method in the screen object to display the bar
  std::pair<SDL_Rect*, SDL_Color> GetBar();
  // retuns the rect of the bar's background(x, y, width, height)
  SDL_Rect* GetRect();
  // retruns wether or not this bar's value is equal to the max value of that
  // bar
  bool Full();
  // returns the value of the bar
  float GetValue();
  // modifies the position of the bar on the screen by the inputted amount
  void Move(int x, int y);
  // sets the bar's position in screen space.
  void SetPos(int x, int y);

 private:
  // rectangle of the bar, used for display purposes (coorinates are in screen
  // space)
  SDL_Rect rect_ = {0, 0, 0, 0};
  // color of the bar, used for display purposes
  SDL_Color color_ = {255, 0, 0};
  // current value of the bar. used for display and game object purposes, can be
  // externally acessed via the GetValue() method
  float value_ = 0;
  // the maximum value the bar can be, defined in the constuctor and used for
  // diplay purposes and to cehck if the bar is full
  float max_value_ = 0;
  // The border size(in px) between the colored bit of the bar and the
  // background.
  static const int border = 2;
};

#endif  // !UI_BAR_H_
