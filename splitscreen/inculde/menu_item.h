// Copyright 2024 Hugh Thompson

#ifndef SPLITSCREEN_MENU_ITEM_H_
#define SPLITSCREEN_MENU_ITEM_H_

#include "SDL2/include/SDL.h"

// an class used mainly as an interface by the menu object to render the
// menu items(buttons text ect), but a menu obect may also be renderd to act as
// a block of color for example
class MenuItem {
 public:
  // the constructor used by child classes using this class as an iterface, a
  // postiton for the menu object is inputted.
  MenuItem(int x, int y);
  // the consctor used for a standalone menuitem, inputs are a position and
  // dimenison in a rect and a color for diplay
  MenuItem(SDL_Rect rect, SDL_Color color);
  ~MenuItem();
  // retuns the rect(x,y, width, height) of the bar
  SDL_Rect* GetRect();
  // retuns a pointer to the surface of the menu item
  SDL_Surface* GetSurface();
  // sets the visablitiy of the object to show
  void Show();
  // sets the visablitiy of the object to hidden
  void Hide();
  // virtual update function, not implemeted by this object but child objcets
  // have implemtations, and this is called evry frame by the menu.
  virtual void Update();
  // retuns the color of the object
  SDL_Color GetColor();
  // retuns the visaublity staus of the object, true for visable, false for
  // hidden
  bool Visable();

 protected:
  // sets the surface while updating rect
  void SetSurface(SDL_Surface* surface);
  // position and dimenion
  SDL_Rect rect_ = {0, 0, 0, 0};
  // the visablity status of the object, true for visable, false for hidden
  bool visable_ = true;
  // a pointer to the surface that this object is displaying.
  SDL_Surface* surface_ = nullptr;
  // color of this object
  SDL_Color color_ = {NULL, NULL, NULL};
};

#endif  // !SPLITSCREEN_MENU_ITEM_H_
