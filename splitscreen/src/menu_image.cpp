// Copyright 2024 Hugh Thompson

#include "menu_image.h"

MenuImage::MenuImage(int x, int y, std::string name) : MenuItem(x, y) {
  SetSurface(IMG_Load(("assets/menu/" + name + ".png").c_str()));
}
