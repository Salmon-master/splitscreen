#ifndef UI_BAR_H_
#define UI_BAR_H_

#include <iostream>

#include "SDL.h"

class UIBar {
 public:
  UIBar(int max_value, SDL_Color color, SDL_Rect rect);
  ~UIBar();
  void SetValue(int value);
  void ChangeValue(float delta_value);
  std::pair<SDL_Rect*, SDL_Color> GetBar();
  SDL_Rect* GetRect();
  bool Full();
  float GetValue();

 private:
  SDL_Rect rect_ = {0, 0, 0, 0};
  SDL_Color color_ = {255, 0, 0};
  float value_ = 0;
  float max_value_ = 0;
  const int border = 2;
};

#endif  // !UI_BAR_H_
