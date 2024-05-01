// Copyright 2024 Hugh Thompson

#include "menu_image.h"

#include <iostream>

MenuImage::MenuImage(int x, int y, std::string name) : MenuItem(x, y) {
  // loading in image from given name
  SDL_Surface* surface_buffer =
      IMG_Load(("assets/menu/" + name + ".png").c_str());
  if (!surface_buffer) {
    std::cout << "image assets/menu/" + name + ".png not found" << std::endl;
  }
  SetSurface(surface_buffer);
}
