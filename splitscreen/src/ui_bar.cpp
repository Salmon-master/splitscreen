#include "ui_bar.h"

UIBar::UIBar(int max_value, SDL_Color color, SDL_Rect rect) { 
  rect_ = rect;
  color_ = color;
  max_value_ = max_value;
}

UIBar::~UIBar() {
  std::cout << "destroyed bar" << std::endl;
}

void UIBar::SetValue(int value) { value_ = value; }

void UIBar::ChangeValue(float delta_value) {
  if (value_ < max_value_) {
    value_ += delta_value;
  }
}

std::pair<SDL_Rect*, SDL_Color> UIBar::GetBar() { 
  SDL_Rect bar = {
      rect_.x + border, rect_.y + border,
      (rect_.w - (border * static_cast<float>(2))) / max_value_ * value_,
      rect_.h - (border * 2)};
  return {&bar, color_}; 
}

SDL_Rect* UIBar::GetRect() { return &rect_; }

bool UIBar::Full() { return value_ >= max_value_; }

float UIBar::GetValue() { return value_; }

void UIBar::Move(int x, int y) {
  rect_.x += x;
  rect_.y += y;
}

void UIBar::SetPos(int x, int y) {
  rect_.x = x;
  rect_.y = y;
}
