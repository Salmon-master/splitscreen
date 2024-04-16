#pragma once

#include "menu.h"
#include "menu_button.h"
#include "menu_image.h"
#include "menu_item.h"
#include "menu_text.h"

Menu* menu = new Menu;
MenuItem* player1_overlay =
    new MenuItem({304, 100, 132, 188}, SDL_Color{30, 30, 30, 120});
void OverlayShow(bool dir) {
  if (dir) {
    player1_overlay->Show();
  }
}
void OverlayHide() { player1_overlay->Hide(); }
MenuImage* player1_image = new MenuImage(314, 100, "player");

void Hover11(bool dir) { OverlayShow(dir); }
MenuButton* player1_gun1 =
    new MenuButton({274, 100, 30, 30}, NULL, Hover11,
                   new MenuText(0, 0, "1", {255, 255, 255, 255}));

void Hover12(bool dir) { OverlayShow(dir); }
MenuButton* player1_gun2 =
    new MenuButton({274, 139, 30, 30}, NULL, Hover12,
                   new MenuText(0, 0, "2", {255, 255, 255, 255}));

void Hover13(bool dir) { OverlayShow(dir); }
MenuButton* player1_gun3 =
    new MenuButton({274, 179, 30, 30}, NULL, Hover13,
                   new MenuText(0, 0, "3", {255, 255, 255, 255}));

void Hover14(bool dir) { OverlayShow(dir); }
MenuButton* player1_gun4 =
    new MenuButton({274, 219, 30, 30}, NULL, Hover14,
                   new MenuText(0, 0, "4", {255, 255, 255, 255}));

void Hover15(bool dir) { OverlayShow(dir); }
MenuButton* player1_gun5 =
    new MenuButton({274, 258, 30, 30}, NULL, Hover15,
                   new MenuText(0, 0, "5", {255, 255, 255, 255}));






MenuImage* player2_image = new MenuImage(564, 100, "player");
MenuButton* player2_gun1 =
    new MenuButton({524, 100, 30, 30}, NULL, NULL,
                   new MenuText(0, 0, "1", {255, 255, 255, 255}));
MenuButton* player2_gun2 =
    new MenuButton({524, 139, 30, 30}, NULL, NULL,
                   new MenuText(0, 0, "2", {255, 255, 255, 255}));
MenuButton* player2_gun3 =
    new MenuButton({524, 179, 30, 30}, NULL, NULL,
                   new MenuText(0, 0, "3", {255, 255, 255, 255}));
MenuButton* player2_gun4 =
    new MenuButton({524, 219, 30, 30}, NULL, NULL,
                   new MenuText(0, 0, "4", {255, 255, 255, 255}));
MenuButton* player2_gun5 =
    new MenuButton({524, 258, 30, 30}, NULL, NULL,
                   new MenuText(0, 0, "5", {255, 255, 255, 255}));
