#ifndef MENU_BUTTON_H_
#define MENU_BUTTON_H_

#include "menu_item.h"

class MenuButton : public MenuItem {
 public:
  MenuButton(SDL_Rect rect, void (*Click)(), void (*Hover)(bool dir), MenuItem* display);
  ~MenuButton();
  void Update();
  MenuItem* GetDisplay();
 private:
  void (*OnClick)() = NULL;
  void (*OnHover)(bool dir) = NULL;
  MenuItem* display_ = nullptr;
};

#endif  // !MENU_BUTTON_H_

