// Copyright 2024 Hugh Thompson

#ifndef SPLITSCREEN_MENU_IMAGE_H_
#define SPLITSCREEN_MENU_IMAGE_H_

#include <string>

#include "SDL2/include/SDL.h"
#include "SDL2_image/include/SDL_image.h"

#include "menu_item.h"

// a class used to represent a static image in a menu, add to a menu's list of
// menu objects and the button will appear on that menu.
class MenuImage : public MenuItem {
 public:
  // the location of that image and the name of the image file (whithout the
  // suffix) of the image wanted to be loaded
  MenuImage(int x, int y, std::string name);
};

#endif  // !SPLITSCREEN_MENU_IMAGE_H_
