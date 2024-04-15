#include "menu_text.h"

TTF_Font* MenuText::font_ = TTF_OpenFont("assets/BraveEightyone.ttf", 12);

MenuText::MenuText(int x, int y, std::string text)
    : MenuItem(x, y, TTF_RenderText_Solid(font_, text.c_str(), {0, 0, 0})) {
  text_ = text;
}
