#include "menu_item.h"

SDL_Rect MenuItem::GetRect() { return rect_; }

SDL_Surface* MenuItem::GetSurface() { return surface_; }

void MenuItem::Show() { visable_ = true; }

void MenuItem::Hide() { visable_ = false; }

MenuItem::MenuItem(int x, int y, SDL_Surface* surface) {
  surface_ = surface;
  if (surface != NULL) {
    rect_ = {x, y, surface_->w, surface_->h};
  }
}
