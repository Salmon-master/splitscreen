// Copyright 2024 Hugh Thompson

#ifndef UI_BAR_H_
#define UI_BAR_H_

#include <iostream>
#include <utility>

#include "SDL2/include/SDL.h"

// a class used to display infomation to the player in the form of a bar, theese
// bars are assigned to an induvidular screen object which will display them.
class UIBar {
 public:
  UIBar(int max_value, SDL_Color color, SDL_Rect rect);
  ~UIBar();
  void SetValue(int value);
  void ChangeValue(float delta_value);
  // returns the a rect and color of the coloured part of teh bar, called in the
  // render method in the screen object to display the bar
  std::pair<SDL_Rect*, SDL_Color> GetBar();
  SDL_Rect* GetRect();
  // retruns wether or not this bar's value is equal to the max value of that
  // bar
  bool Full();
  float GetValue();
  // modifies the position of the bar on the screen by the inputted amount
  void Move(int x, int y);
  void SetPos(int x, int y);

 private:
  // rectangle of the bar, used for display purposes
  SDL_Rect rect_ = {0, 0, 0, 0};
  // color of the bar, used for display purposes
  SDL_Color color_ = {255, 0, 0};
  // current value of the bar. used for display and game object purposes, can be
  // externally acessed via the GetValue() method
  float value_ = 0;
  // the maximum value the bar can be, defined in teh constuctor and used for
  // diplay purposes and to cehck if the bar is full
  float max_value_ = 0;
  // The border size(in px) between the colored bit of teh bar and the
  // background.
  static const int border = 2;
};

#endif  // !UI_BAR_H_
