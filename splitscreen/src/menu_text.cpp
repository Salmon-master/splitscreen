#include "menu_text.h"

#include <iostream>

MenuText::MenuText(std::string text, SDL_Color text_color, int size)
    : MenuItem(0, 0) {
  size_ = size;
  text_ = text;
  font_ = TTF_OpenFont("assets/menu/VeniteAdoremus.ttf", size);
  if (!font_) {
    std::cout << TTF_GetError() << std::endl;
  }
  if (text_color.r) {
    text_color_ = text_color;
  }
  SetSurface(TTF_RenderText_Solid(font_, text_.c_str(), text_color_));
}

MenuText::MenuText(int x, int y, std::string text, SDL_Color text_color,
                   int size)
    : MenuItem(x, y) {
  text_ = text;
  size_ = size;
  font_ = TTF_OpenFont("assets/menu/VeniteAdoremus.ttf", size_);
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
    if (wrap_) {
      SetSurface(TTF_RenderText_Solid_Wrapped(font_, text_.c_str(), text_color_, wrap_));
    } else {
      SetSurface(TTF_RenderText_Solid(font_, text_.c_str(), text_color_));
    }
  }
}

void MenuText::SetWrap(int wrap) { wrap_ = wrap; }

void MenuText::SetText(std::string text) { text_ = text; }
