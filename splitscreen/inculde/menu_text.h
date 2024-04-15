#ifndef MENU_TEXT_H_
#define MENU_TEXT_H_

#include <string>

#include "menu_item.h"
#include "SDL_ttf.h"

class MenuText : public MenuItem {
 public:
  MenuText(int x, int y, std::string text);

 private:
  static TTF_Font* font_;
  std::string text_;
};

#endif  // !MENU_TEXT_H_
