// Copyright 2024 Hugh Thompson

#ifndef MENU_IMAGE_H_
#define MENU_IMAGE_H_

#include <string>

#include "SDL2_image/include/SDL_image.h"
#include "SDL2/include/SDL.h"

#include "menu_item.h"

class MenuImage : public MenuItem {
 public:
  MenuImage(int x, int y, std::string name);
};

#endif  // !MENU_IMAGE_H_
