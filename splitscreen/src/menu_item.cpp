#include "menu_item.h"

SDL_Rect* MenuItem::GetRect() { return &rect_; }

SDL_Surface* MenuItem::GetSurface() { return surface_; }

void MenuItem::Show() { visable_ = true; }

void MenuItem::Hide() { visable_ = false; }

void MenuItem::Update() {}

SDL_Color MenuItem::GetColor() { return color_; }

bool MenuItem::Visable() { return visable_; }

void MenuItem::SetSurface(SDL_Surface* surface) {
  surface_ = surface;
  rect_.w = surface->w;
  rect_.h = surface->h;
}

MenuItem::MenuItem(int x, int y) {
  rect_.x = x;
  rect_.y = y;
}
