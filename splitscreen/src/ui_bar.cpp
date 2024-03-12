#include "ui_bar.h"

UI_Bar::UI_Bar(int max_value, SDL_Color color, SDL_Rect rect) { 
  rect_ = rect;
  color_ = color;
  value_size_ = rect_.w / max_value;

}

void UI_Bar::SetValue(int value) { value_ = value; }

void UI_Bar::ChangeValue(int delta_value) { value_ += delta_value; }

std::pair<SDL_Rect, SDL_Color> UI_Bar::GetBar() { 
  SDL_Rect bar = {rect_.x, rect_.y, value_size_ * value_, rect_.h};
  return {bar, color_}; 
}

SDL_Rect UI_Bar::GetRect() { return rect_; }
