#ifndef MENU_ITEM_H_
#define MENU_ITEM_H_

#include <SDL.h>

// an purley virtual class used as an interface by the menu object to render the
// menu items(buttons text ect)
class MenuItem {
 public:
  MenuItem(int x, int y);
  SDL_Rect* GetRect();
  SDL_Surface* GetSurface();
  void Show();
  void Hide();
  virtual void Update();
  SDL_Color GetColor();
  bool Visable();

 protected:
  // sets the surface while updating rect
  void SetSurface(SDL_Surface* surface);
  SDL_Rect rect_ = {0, 0, 0, 0};
  bool visable_ = true;
  SDL_Surface* surface_ = nullptr;
  SDL_Color color_ = {NULL, NULL, NULL};
};

#endif  // !MENU_ITEM_H_
