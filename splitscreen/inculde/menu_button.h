#ifndef MENU_BUTTON_H_
#define MENU_BUTTON_H_

#include "menu_item.h"

class MenuButton : public MenuItem {
 public:
  MenuButton(SDL_Rect rect, void (*Func)(), MenuItem* display);
  void Update();
  void Clicked();
  void Hover();
 private:
  void (*OnClick)();
  MenuItem* display_ = nullptr;
};

#endif  // !MENU_BUTTON_H_

