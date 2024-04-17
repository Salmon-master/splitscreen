#pragma once

#include "menu.h"
#include "menu_button.h"
#include "menu_image.h"
#include "menu_item.h"
#include "menu_text.h"

Menu* menu = new Menu;

// overlay for p1 gun menu
int player1_selector = NULL;
MenuItem* player1_overlay =
    new MenuItem({304, 100, 132, 188}, SDL_Color{30, 30, 30, 120});
void UpgradeWeapon1() {}
MenuButton* player1_upgrade_weapon =
    new MenuButton({314, 253, 112, 30}, UpgradeWeapon1, NULL,
                   new MenuText("upgrade", {255, 255, 255, 255}, 19));
void Overlay1Show(bool dir) {
  if (dir) {
    player1_overlay->Show();
    player1_upgrade_weapon->Show();
  }
}
// player 1 menu image
MenuImage* player1_image = new MenuImage(314, 100, "player");

// p1 gun 1
MenuText* player1_gun1_text =
    new MenuText(314, 105, "Gun 1\n\nDAM:10\nROF:10\nSPE:1\n\nCost: 100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover11(bool dir) {
  player1_gun1_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    player1_selector = 1;
    player1_gun1_text->Show();
  }
}
MenuButton* player1_gun1 =
    new MenuButton({274, 100, 30, 30}, NULL, Hover11,
                   new MenuText(0, 0, "1", {255, 255, 255, 255}, 24));

// p1 gun 2
MenuText* player1_gun2_text =
    new MenuText(314, 105, "Gun 2\n\nDAM:2\nROF:100\nSPE:10\n\nCost: 100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover12(bool dir) {
  player1_gun2_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    player1_selector = 2;
    player1_gun2_text->Show();
  }
}
MenuButton* player1_gun2 =
    new MenuButton({274, 139, 30, 30}, NULL, Hover12,
                   new MenuText(0, 0, "2", {255, 255, 255, 255}, 24));

// p1 gun 3
MenuText* player1_gun3_text =
    new MenuText(314, 105, "Gun 3\n\nDAM:2\nROF:100\nSPE:10\n\nCost: 100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover13(bool dir) {
  player1_gun3_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    player1_selector = 3;
    player1_gun3_text->Show();
  }
}
MenuButton* player1_gun3 =
    new MenuButton({274, 179, 30, 30}, NULL, Hover13,
                   new MenuText(0, 0, "3", {255, 255, 255, 255}, 24));

// p1 gun 4
MenuText* player1_gun4_text =
    new MenuText(314, 105, "Gun 4\n\nDAM:2\nROF:100\nSPE:10\n\nCost: 100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover14(bool dir) {
  player1_gun4_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    player1_selector = 4;
    player1_gun4_text->Show();
  }
}
MenuButton* player1_gun4 =
    new MenuButton({274, 219, 30, 30}, NULL, Hover14,
                   new MenuText(0, 0, "4", {255, 255, 255, 255}, 24));

// p1 gun 5
MenuText* player1_gun5_text =
    new MenuText(314, 105, "Gun 5\n\nDAM:2\nROF:100\nSPE:10\n\nCost: 100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover15(bool dir) {
  player1_gun5_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    player1_selector = 5;
    player1_gun5_text->Show();
  }
}
MenuButton* player1_gun5 =
    new MenuButton({274, 258, 30, 30}, NULL, Hover15,
                   new MenuText(0, 0, "5", {255, 255, 255, 255}, 24));

// hiding of p1 overlay components
void Overlay1Hide() {
  player1_overlay->Hide();
  player1_upgrade_weapon->Hide();
  player1_gun1_text->Hide();
  player1_gun2_text->Hide();
  player1_gun3_text->Hide();
  player1_gun4_text->Hide();
  player1_gun5_text->Hide();
  player1_selector = NULL;
}

// p1 upgrades
MenuText* p1_speed = new MenuText(274, 75, "S: 500", {0,0,0,255}, 20);
MenuText* p1_armour = new MenuText(360, 75, "A: 500", {0, 0, 0, 255}, 20);

void ShowPriceP1Speed(bool dir);
MenuButton* p1_upgrade_speed = new MenuButton(
    {274, 299, 80, 35}, NULL, ShowPriceP1Speed, new MenuText("Speed+", {255, 255, 255, 255}, 15));
void ShowPriceP1Speed(bool dir){
  MenuText* text = dynamic_cast<MenuText*>(p1_upgrade_speed->GetDisplay());
  if (dir) {
    text->SetText("¢1000");
  } else {
    text->SetText("Speed+");
  }
}

void ShowPriceP1Armour(bool dir);
MenuButton* p1_upgrade_armour =
    new MenuButton({357, 299, 80, 35}, NULL, ShowPriceP1Armour,
                   new MenuText("Armor+", {255, 255, 255, 255}, 15));
void ShowPriceP1Armour(bool dir) {
  MenuText* text = dynamic_cast<MenuText*>(p1_upgrade_armour->GetDisplay());
  if (dir) {
    text->SetText("¢1000");
  } else {
    text->SetText("Armor+");
  }
}

void ShowPriceP1Repair(bool dir);
MenuButton* p1_repair =
    new MenuButton({274, 339, 165, 35}, NULL, ShowPriceP1Repair,
                   new MenuText("Repair", {255, 255, 255, 255}, 15));
void ShowPriceP1Repair(bool dir) {
  MenuText* text = dynamic_cast<MenuText*>(p1_repair->GetDisplay());
  if (dir) {
    text->SetText("¢1000");
  } else {
    text->SetText("Repair");
  }
}










// p2
int player2_selector = NULL;
MenuItem* player2_overlay =
    new MenuItem({554, 100, 132, 188}, SDL_Color{30, 30, 30, 120});
void UpgradeWeapon2() {}
MenuButton* player2_upgrade_weapon =
    new MenuButton({564, 253, 112, 30}, UpgradeWeapon2, NULL,
                   new MenuText("upgrade", {255, 255, 255, 255}, 19));
void Overlay2Show(bool dir) {
  if (dir) {
    player2_overlay->Show();
    player2_upgrade_weapon->Show();
  }
}
// player 2 menu image
MenuImage* player2_image = new MenuImage(564, 100, "player");

// p2 gun 1
MenuText* player2_gun1_text =
    new MenuText(564, 105, "Gun 1\n\nDAM:10\nROF:10\nSPE:1\n\nCost: 100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover21(bool dir) {
  player2_gun1_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    player2_selector = 1;
    player2_gun1_text->Show();
  }
}
MenuButton* player2_gun1 =
    new MenuButton({524, 100, 30, 30}, NULL, Hover21,
                   new MenuText(0, 0, "1", {255, 255, 255, 255}, 24));

// 21 gun 2
MenuText* player2_gun2_text =
    new MenuText(564, 105, "Gun 2\n\nDAM:2\nROF:100\nSPE:10\n\nCost: 100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover22(bool dir) {
  player2_gun2_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    player2_selector = 2;
    player2_gun2_text->Show();
  }
}
MenuButton* player2_gun2 =
    new MenuButton({524, 139, 30, 30}, NULL, Hover22,
                   new MenuText(0, 0, "2", {255, 255, 255, 255}, 24));

// p2 gun 3
MenuText* player2_gun3_text =
    new MenuText(564, 105, "Gun 3\n\nDAM:2\nROF:100\nSPE:10\n\nCost: 100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover23(bool dir) {
  player2_gun3_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    player2_selector = 3;
    player2_gun3_text->Show();
  }
}
MenuButton* player2_gun3 =
    new MenuButton({524, 179, 30, 30}, NULL, Hover23,
                   new MenuText(0, 0, "3", {255, 255, 255, 255}, 24));

// p2 gun 4
MenuText* player2_gun4_text =
    new MenuText(564, 105, "Gun 4\n\nDAM:2\nROF:100\nSPE:10\n\nCost: 100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover24(bool dir) {
  player2_gun4_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    player2_selector = 4;
    player2_gun4_text->Show();
  }
}
MenuButton* player2_gun4 =
    new MenuButton({524, 219, 30, 30}, NULL, Hover24,
                   new MenuText(0, 0, "4", {255, 255, 255, 255}, 24));

// p1 gun 5
MenuText* player2_gun5_text =
    new MenuText(564, 105, "Gun 5\n\nDAM:2\nROF:100\nSPE:10\n\nCost: 100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover25(bool dir) {
  player2_gun5_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    player2_selector = 5;
    player2_gun5_text->Show();
  }
}
MenuButton* player2_gun5 =
    new MenuButton({524, 258, 30, 30}, NULL, Hover25,
                   new MenuText(0, 0, "5", {255, 255, 255, 255}, 24));

// hiding of p2 overlay components
void Overlay2Hide() {
  player2_overlay->Hide();
  player2_upgrade_weapon->Hide();
  player2_gun1_text->Hide();
  player2_gun2_text->Hide();
  player2_gun3_text->Hide();
  player2_gun4_text->Hide();
  player2_gun5_text->Hide();
  player2_selector = NULL;
}

