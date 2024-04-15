#include "menu_button.h"

MenuButton::MenuButton(SDL_Rect rect, void (*Func)(), MenuItem* display)
    : MenuItem(rect.x, rect.y) {
  if (!display) {
    rect_ = rect;
  }
  OnClick = Func;
  display_ = display;
  color_ = {60, 60, 60};
}

void MenuButton::Update() {
  int x, y;
  SDL_GetMouseState(&x, &y);
  if (x > rect_.x && x < rect_.x + rect_.w && y > rect_.y &&
      y < rect_.y + rect_.h) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_MOUSEBUTTONDOWN) {
        Clicked();
      } else {
        Hover();
      }
    }
  } else {
    color_ = {60, 60, 60};
  }
}

void MenuButton::Clicked() { OnClick(); }

void MenuButton::Hover() { color_ = {20, 20, 20}; }
