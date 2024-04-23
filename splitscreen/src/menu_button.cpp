// Copyright 2024 Hugh Thompson

#include "menu_button.h"

#include "iostream"

#include "menu_text.h"

MenuButton::MenuButton(SDL_Rect rect, void (*Click)(), void (*Hover)(bool dir),
                       MenuItem* display)
    : MenuItem(rect.x, rect.y) {
  rect_ = rect;
  OnClick = Click;
  OnHover = Hover;
  display_ = display;
  if (display_) {
    display_->GetRect()->x = rect_.x + ((rect.w - display_->GetRect()->w) / 2);
    display_->GetRect()->y = rect_.y + ((rect.h - display_->GetRect()->h) / 2);
    MenuText* text = dynamic_cast<MenuText*>(display_);
    if (text) {
      text->SetWrap(rect_.w);
    }
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
      color_ = color_def_;
    }
  }
}

MenuItem* MenuButton::GetDisplay() { return display_; }

void MenuButton::SetColorDef(SDL_Color color) { color_def_ = color; }
