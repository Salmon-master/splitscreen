#ifndef MENU_TEXT_H_
#define MENU_TEXT_H_

#include <string>

#include "SDL2_ttf/include/SDL_ttf.h"

#include "menu_item.h"

// a class used to represnet text in the menu screens 
class MenuText : public MenuItem {
 public:
  MenuText(std::string text, SDL_Color text_color, int size);
  MenuText(int x, int y, std::string text, SDL_Color text_color, int size);
  void Update();
  void SetWrap(int wrap);
  void SetText(std::string text);

 private:
  TTF_Font* font_;
  std::string text_;
  std::string last_text_;
  SDL_Color text_color_ = {0, 0, 0, 255};
  int wrap_ = NULL;
  int size_ = 28;
};

#endif  // !MENU_TEXT_H_
