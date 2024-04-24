// Copyright 2024 Hugh Thompson

#ifndef MENU_TEXT_H_
#define MENU_TEXT_H_

#include <string>

#include "SDL2_ttf/include/SDL_ttf.h"

#include "menu_item.h"

// a class used to represent text in the menu screens
class MenuText : public MenuItem {
 public:
  // consctructor for displaying text as a part of a button, inputs are the
  // string of text to display, the color of the text, and the size of the text
  MenuText(std::string text, SDL_Color text_color, int size);
  // constctor for displaying text as standalone text.
  // inputs are the position of the text, the string of text to display, the
  // color of the text, and the size of the text
  MenuText(int x, int y, std::string text, SDL_Color text_color, int size);
  // updates the display of the text if the string has changed since last call.
  void Update();
  // sets the wrap of the text, inputis of this wrap in px
  void SetWrap(int wrap);
  // sets the text of the object
  void SetText(std::string text);

 private:
  // the font used by this text
  TTF_Font* font_;
  // the string of text being displayed
  std::string text_;
  // the string of text last displayed when the last update was called
  std::string last_text_;
  // the text color
  SDL_Color text_color_ = {0, 0, 0, 255};
  // the warp of the text, if null, then all text will be one one line
  int wrap_ = NULL;
  // text size, set in consctor
  int size_ = 28;
};

#endif  // !MENU_TEXT_H_
