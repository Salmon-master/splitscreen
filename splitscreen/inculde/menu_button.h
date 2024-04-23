// Copyright 2024 Hugh Thompson

#ifndef MENU_BUTTON_H_
#define MENU_BUTTON_H_

#include "menu_item.h"

class MenuButton : public MenuItem {
 public:
  MenuButton(SDL_Rect rect, void (*Click)(), void (*Hover)(bool dir),
             MenuItem* display);
  ~MenuButton();
  void Update();
  MenuItem* GetDisplay();
  void SetColorDef(SDL_Color color);

 private:
  void (*OnClick)() = NULL;
  void (*OnHover)(bool dir) = NULL;
  MenuItem* display_ = nullptr;
  SDL_Color color_def_ = {60, 60, 60, 255};
};

#endif  // !MENU_BUTTON_H_
