#include "menu_button.h"

#include "iostream"

MenuButton::MenuButton(SDL_Rect rect, void (*Click)(), void (*Hover)(bool dir),
                       MenuItem* display)
    : MenuItem(rect.x, rect.y) {
  rect_ = rect;
  OnClick = Click;
  OnHover = Hover;
  display_ = display;
  if (display_) {
    display_->GetRect()->x = rect_.x;
    display_->GetRect()->y = rect_.y;
  }
  color_ = {60, 60, 60, 255};
}

MenuButton::~MenuButton() { delete display_; }

void MenuButton::Update() {
  int x, y;
  SDL_GetMouseState(&x, &y);
  if (visable_) {
    if (x > rect_.x && x < rect_.x + rect_.w && y > rect_.y &&
        y < rect_.y + rect_.h) {
      SDL_Event e;
      color_ = {220, 20, 20, 255};
      if (OnHover) {
        OnHover(true);
      }
      if (SDL_PollEvent(&e)) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
          if (OnClick) {
            OnClick();
          }
        }
      }
    } else {
      if (OnHover) {
        OnHover(false);
      }
      color_ = {60, 60, 60, 255};
    }
  }
}

MenuItem* MenuButton::GetDisplay() { return display_; }
