#include "menu_text.h"

MenuText::MenuText(int x, int y, std::string text)
    : MenuItem(x, y) {
  text_ = text;
  SetSurface(TTF_RenderText_Solid(font_, text_.c_str(), {0, 0, 0}));
}

void MenuText::Update() {
  if (text_ != last_text_) {
    last_text_ = text_;
    SetSurface(TTF_RenderText_Solid(font_, text_.c_str(), {0, 0, 0}));
  }
}
