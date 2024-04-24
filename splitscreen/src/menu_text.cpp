// Copyright 2024 Hugh Thompson

#include "menu_text.h"

#include <iostream>

MenuText::MenuText(std::string text, SDL_Color text_color, int size)
    : MenuItem(0, 0) {
  // setting font paramters
  size_ = size;
  text_ = text;
  // loading in font and error capture
  font_ = TTF_OpenFont("assets/menu/VeniteAdoremus.ttf", size);
  if (!font_) {
    std::cout << TTF_GetError() << std::endl;
  }
  // setting text color if given, otherwise will default to {0,0,0,255}(black)
  if (text_color.r) {
    text_color_ = text_color;
  }
  // convert text to surface and set that surface to this surface
  SetSurface(TTF_RenderText_Solid(font_, text_.c_str(), text_color_));
}

MenuText::MenuText(int x, int y, std::string text, SDL_Color text_color,
                   int size)
    : MenuItem(x, y) {
  // setting font paramters
  text_ = text;
  size_ = size;
  // loading in font and error capture
  font_ = TTF_OpenFont("assets/menu/VeniteAdoremus.ttf", size_);
  if (!font_) {
    std::cout << TTF_GetError() << std::endl;
  }
  // setting text color if given, otherwise will default to {0,0,0,255}(black)
  if (text_color.r) {
    text_color_ = text_color;
  }
  // convert text to surface and set that surface to this surface
  SetSurface(TTF_RenderText_Solid(font_, text_.c_str(), text_color_));
}

void MenuText::Update() {
  // update if the text has changed since last called
  if (text_ != last_text_) {
    last_text_ = text_;
    if (wrap_) {
      // convert text to surface and set that surface to this surface with wrapping
      SetSurface(TTF_RenderText_Solid_Wrapped(font_, text_.c_str(), text_color_,
                                              wrap_));
    } else {
      // convert text to surface and set that surface to this surface
      SetSurface(TTF_RenderText_Solid(font_, text_.c_str(), text_color_));
    }
  }
}

void MenuText::SetWrap(int wrap) { wrap_ = wrap; }

void MenuText::SetText(std::string text) { text_ = text; }
