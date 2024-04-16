#include "menu_text.h"

#include <iostream>

MenuText::MenuText(int x, int y, std::string text, SDL_Color text_color)
    : MenuItem(x, y) {
  text_ = text;
  TTF_Font* font_ = TTF_OpenFont("assets/menu/VeniteAdoremus.ttf", 28);
  if (!font_) {
    std::cout << TTF_GetError() << std::endl;
  }
  if (text_color.r) {
    text_color_ = text_color;
  }
  SetSurface(TTF_RenderText_Solid(font_, text_.c_str(), text_color_));
}

void MenuText::Update() {
  if (text_ != last_text_) {
    last_text_ = text_;
    SetSurface(TTF_RenderText_Solid(font_, text_.c_str(), text_color_));
  }
}
