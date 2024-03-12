#ifndef UI_BAR_H_
#define UI_BAR_H_

#include <iostream>

#include "SDL.h"

class UI_Bar {
 public:
  UI_Bar(int max_value, SDL_Color color, SDL_Rect rect);
  void SetValue(int value);
  void ChangeValue(int delta_value);
  std::pair<SDL_Rect, SDL_Color> GetBar();
  SDL_Rect GetRect();

 private:
  SDL_Rect rect_ = {0, 0, 0, 0};
  SDL_Color color_ = {255, 0, 0};
  int value_ = 0;
  float value_size_ = 0;
};

#endif  // !UI_BAR_H_
