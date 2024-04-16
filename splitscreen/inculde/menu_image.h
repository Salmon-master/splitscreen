#ifndef MENU_IMAGE_H_
#define MENU_IMAGE_H_

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "menu_item.h"


class MenuImage : public MenuItem {
 public:
  MenuImage(int x, int y, std::string name);
};

#endif  // !MENU_IMAGE_H_


