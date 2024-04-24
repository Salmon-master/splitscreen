// Copyright 2024 Hugh Thompson

#include "menu_button.h"

#include "iostream"

#include "menu_text.h"

MenuButton::MenuButton(SDL_Rect rect, void (*Click)(), void (*Hover)(bool dir),
                       MenuItem* display)
    : MenuItem(rect.x, rect.y) {
  // rect intilaistion
  rect_ = rect;
  // actions
  OnClick = Click;
  OnHover = Hover;
  // display initailsation
  display_ = display;
  // set display to center of button
  if (display_) {
    display_->GetRect()->x = rect_.x + ((rect.w - display_->GetRect()->w) / 2);
    display_->GetRect()->y = rect_.y + ((rect.h - display_->GetRect()->h) / 2);
    // wrap text to dimension of button
    MenuText* text = dynamic_cast<MenuText*>(display_);
    if (text) {
      text->SetWrap(rect_.w);
    }
  }
  // setting color
  color_ = {60, 60, 60, 255};
}

MenuButton::~MenuButton() { delete display_; }

void MenuButton::Update() {
  // getting mouse position
  int x, y;
  SDL_GetMouseState(&x, &y);
  if (visable_) {
    // checking if the button is being hovered over
    if (x > rect_.x && x < rect_.x + rect_.w && y > rect_.y &&
        y < rect_.y + rect_.h) {
      SDL_Event e;
      color_ = {220, 20, 20, 255};
      // execute hover code
      if (OnHover) {
        OnHover(true);
      }
      // checking if the button is clicked
      if (SDL_PollEvent(&e)) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
          if (OnClick) {
            OnClick();
          }
        }
      }
    } else {
      // revers hover code
      if (OnHover) {
        OnHover(false);
      }
      color_ = color_def_;
    }
  }
}

MenuItem* MenuButton::GetDisplay() { return display_; }

void MenuButton::SetColorDef(SDL_Color color) { color_def_ = color; }
