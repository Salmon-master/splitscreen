#ifndef MENU_TEXT_H_
#define MENU_TEXT_H_

#include <string>

#include "SDL_ttf.h"

#include "menu_item.h"

// a class used to represnet text in the menu screens 
class MenuText : public MenuItem {
 public:
  MenuText(int x, int y, std::string text, SDL_Color text_color);
  void Update();

 private:
  TTF_Font* font_ = TTF_OpenFont("assets/menu/VeniteAdoremus.ttf", 28);
  std::string text_;
  std::string last_text_;
  SDL_Color text_color_ = {0, 0, 0};
};

#endif  // !MENU_TEXT_H_
