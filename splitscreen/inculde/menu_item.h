#ifndef MENU_ITEM_H_
#define MENU_ITEM_H_

#include <SDL.h>

class MenuItem {
 public:
  MenuItem(int x, int y, SDL_Surface* surface);
  SDL_Rect GetRect();
  SDL_Surface* GetSurface();
  void Show();
  void Hide();

 protected:
  SDL_Rect rect_ = {0, 0, 0, 0};
  bool visable_ = true;
  SDL_Surface* surface_ = nullptr;
};

#endif  // !MENU_ITEM_H_
