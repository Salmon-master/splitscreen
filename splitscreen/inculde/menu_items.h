// Copyright 2024 Hugh Thompson

#pragma once

#include <vector>

#include "menu.h"
#include "menu_button.h"
#include "menu_image.h"
#include "menu_item.h"
#include "menu_text.h"

// menus and popups
Menu* menu = new Menu;
Menu* death_menu = nullptr;
Menu* reward_menu = nullptr;

// run the game
void Play() {
  menu_run = false;
  game_run = true;
}

// play button
MenuButton* play =
    new MenuButton({25, 210, 200, 70}, Play, NULL,
                   new MenuText("Play", {255, 255, 255, 255}, 60));
// quit the game
void Quit() {
  run = false;
  menu_run = false;
  game_run = false;
}
// quit button
MenuButton* quit =
    new MenuButton({25, 340, 200, 50}, Quit, NULL,
                   new MenuText("Quit", {255, 255, 255, 255}, 40));
// popup tutorial 
void Tutorial() {
  Menu* popup = new Menu(600, 430);
  bool popup_run = true;
  SDL_Event e;
  MenuText* text = new MenuText(
      25, 25,
      "Naviagte your way though enemy spaceships using your two robots, if an "
      "eniter ship is cleared, you will receive a reward! The catch is however "
      "that you may only control one of your robots at a time.\n\n To switch "
      "between which robot you are controlling press v.\n to control your "
      "currently selected robot, use a and d to rotate the robot and w to move "
      "fowards and space to shoot\n\n to clear a ship, you will need to "
      "progress through a number of rooms, to do this you must defeat all "
      "enemies in that room, and then navigate through to the bottom right "
      "hand corner of the room to progress to the next stage.\n\n press escape "
      "to exit",
      {0, 0, 0, 255}, 16);
  text->SetWrap(550);
  popup->menu_items_ = {text};
  while (popup_run) {
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        popup_run = false;
      }
      if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_ESCAPE) {
          popup_run = false;
        }
      }
    }
    popup->Render();
  }
  delete popup;
}
// tutorial button
MenuButton* how =
    new MenuButton({25, 285, 200, 50}, Tutorial, NULL,
                   new MenuText("How To", {255, 255, 255, 255}, 40));
// tile of the game
MenuText* title = new MenuText(25, 75, "Conscience", {255, 0, 0, 255}, 26);

// amount of credits the player currently possesses
MenuText* credits =
    new MenuText(25, 174, "Cr: \u00A2" + std::to_string(save.GetCredits()),
                 {0, 0, 0, 255}, 26);

// player 1 GUI vars
// which gun the player has selected
int player_1_gun = 0;
void reset1();
// overlay for p1 gun menu
void Overlay1Hide();
// the currenyt hoverd over gun
int player1_selector = NULL;
// p1 overlay
MenuItem* player1_overlay =
    new MenuItem({304, 100, 132, 188}, SDL_Color{30, 30, 30, 120});
// upgrde the weapon of player 1
void UpgradeWeapon1() {
  if (save.UpgradeWeapon(player1_selector)) {
    Overlay1Hide();
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
  } else {
    Menu* popup = new Menu(410, 80);
    MenuText* text =
        new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    delete popup;
  }
}
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
    new MenuText(314, 105, "Gun 1\n\nDAM:10\nROF:10\nSPE:1\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover11(bool dir) {
  player1_gun1_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    player1_selector = 0;
    player1_gun1_text->Show();
    std::vector<int> stats = save.GetGunStats(0);
    player1_gun1_text->SetText("Gun 1\n\nDAM:" + std::to_string(stats[0]) +
                               "\nROF:" + std::to_string(stats[1] / 10) +
                               "\nSPE:1" + std::to_string(stats[2] / 10) +
                               "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
void Click11();
MenuButton* player1_gun1 =
    new MenuButton({274, 100, 30, 30}, Click11, Hover11,
                   new MenuText(0, 0, "1", {255, 255, 255, 255}, 24));
void Click11() {
  reset1();
  player1_gun1->SetColorDef({200, 0, 0, 255});
  player_1_gun = 0;
}


// p1 gun 2
MenuText* player1_gun2_text =
    new MenuText(314, 105, "Gun 2\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover12(bool dir) {
  player1_gun2_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    player1_selector = 1;
    player1_gun2_text->Show();
    std::vector<int> stats = save.GetGunStats(1);
    player1_gun2_text->SetText("Gun 2\n\nDAM:" + std::to_string(stats[0]) +
                               "\nROF:" + std::to_string(stats[1] / 10) +
                               "\nSPE:1" + std::to_string(stats[2] / 10) +
                               "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
void Click12();
MenuButton* player1_gun2 =
    new MenuButton({274, 139, 30, 30}, Click12, Hover12,
                   new MenuText(0, 0, "2", {255, 255, 255, 255}, 24));
void Click12() {
  reset1();
  player1_gun2->SetColorDef({200, 0, 0, 255});
  player_1_gun = 1;
}



// p1 gun 3
MenuText* player1_gun3_text =
    new MenuText(314, 105, "Gun 3\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover13(bool dir) {
  player1_gun3_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    player1_selector = 2;
    player1_gun3_text->Show();
    std::vector<int> stats = save.GetGunStats(2);
    player1_gun3_text->SetText("Gun 3\n\nDAM:" + std::to_string(stats[0]) +
                               "\nROF:" + std::to_string(stats[1] / 10) +
                               "\nSPE:1" + std::to_string(stats[2] / 10) +
                               "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
void Click13();
MenuButton* player1_gun3 =
    new MenuButton({274, 179, 30, 30}, Click13, Hover13,
                   new MenuText(0, 0, "3", {255, 255, 255, 255}, 24));
void Click13() {
  reset1();
  player1_gun3->SetColorDef({200, 0, 0, 255});
  player_1_gun = 2;
}



// p1 gun 4
MenuText* player1_gun4_text =
    new MenuText(314, 105, "Gun 4\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover14(bool dir) {
  player1_gun4_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    player1_selector = 3;
    player1_gun4_text->Show();
    std::vector<int> stats = save.GetGunStats(3);
    player1_gun4_text->SetText("Gun 4\n\nDAM:" + std::to_string(stats[0]) +
                               "\nROF:" + std::to_string(stats[1] / 10) +
                               "\nSPE:1" + std::to_string(stats[2] / 10) +
                               "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
void Click14();
MenuButton* player1_gun4 =
    new MenuButton({274, 219, 30, 30}, Click14, Hover14,
                   new MenuText(0, 0, "4", {255, 255, 255, 255}, 24));
void Click14() {
  reset1();
  player1_gun4->SetColorDef({200, 0, 0, 255});
  player_1_gun = 3;
}



// p1 gun 5
MenuText* player1_gun5_text =
    new MenuText(314, 105, "Gun 5\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover15(bool dir) {
  player1_gun5_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    player1_selector = 4;
    player1_gun5_text->Show();
    std::vector<int> stats = save.GetGunStats(4);
    player1_gun5_text->SetText("Gun 5\n\nDAM:" + std::to_string(stats[0]) +
                               "\nROF:" + std::to_string(stats[1] / 10) +
                               "\nSPE:1" + std::to_string(stats[2] / 10) +
                               "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
void Click15();
MenuButton* player1_gun5 =
    new MenuButton({274, 258, 30, 30}, Click15, Hover15,
                   new MenuText(0, 0, "5", {255, 255, 255, 255}, 24));
void Click15() {
  reset1();
  player1_gun5->SetColorDef({200, 0, 0, 255});
  player_1_gun = 4;
}

// hiding of p1 overlay components
void reset1() {
  player1_gun1->SetColorDef({60, 60, 60, 255});
  player1_gun2->SetColorDef({60, 60, 60, 255});
  player1_gun3->SetColorDef({60, 60, 60, 255});
  player1_gun4->SetColorDef({60, 60, 60, 255});
  player1_gun5->SetColorDef({60, 60, 60, 255});
}

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

// p1 speed
MenuText* p1_speed = new MenuText(
    274, 75, "S: " + std::to_string(save.GetPlayerStats(1)[0] / 10),
    {0, 0, 0, 255}, 20);
MenuText* p1_armour =
    new MenuText(360, 75, "A: " + std::to_string(save.GetPlayerStats(1)[1]),
                 {0, 0, 0, 255}, 20);

void ShowPriceP1Speed(bool dir);
void UpgradeP1Speed() {
  if (save.UpgradePlayer(false, 1)) {
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
    p1_speed->SetText("S: " + std::to_string(save.GetPlayerStats(1)[0] / 10));
  } else {
    Menu* popup = new Menu(410, 80);
    MenuText* text =
        new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    delete popup;
  }
}
MenuButton* p1_upgrade_speed =
    new MenuButton({274, 299, 80, 35}, UpgradeP1Speed, ShowPriceP1Speed,
                   new MenuText("Speed+", {255, 255, 255, 255}, 15));
void ShowPriceP1Speed(bool dir) {
  MenuText* text = dynamic_cast<MenuText*>(p1_upgrade_speed->GetDisplay());
  if (dir) {
    text->SetText("\u00A2" + std::to_string(save.GetPlayerStats(1)[2]));
  } else {
    text->SetText("Speed+");
  }
}



// p1 armour
void ShowPriceP1Armour(bool dir);
void UpgradeP1Armour() {
  if (save.UpgradePlayer(true, 1)) {
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
    p1_armour->SetText("A: " + std::to_string(save.GetPlayerStats(1)[1]));
  } else {
    Menu* popup = new Menu(410, 80);
    MenuText* text =
        new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    delete popup;
  }
}
MenuButton* p1_upgrade_armour =
    new MenuButton({357, 299, 80, 35}, UpgradeP1Armour, ShowPriceP1Armour,
                   new MenuText("Armor+", {255, 255, 255, 255}, 15));
void ShowPriceP1Armour(bool dir) {
  MenuText* text = dynamic_cast<MenuText*>(p1_upgrade_armour->GetDisplay());
  if (dir) {
    text->SetText("\u00A2" + std::to_string(save.GetPlayerStats(1)[3]));
  } else {
    text->SetText("Armor+");
  }
}


// p1 damage / repair
MenuItem* p1_damagebar =
    new MenuItem({274, 379, static_cast<int>(save.GetDamage(1) * 1.65f), 11},
                 {110, 59, 173, 255});
MenuItem* p1_damagebar_bkg =
    new MenuItem({274, 379, 165, 11}, {26, 34, 38, 255});

void Repairp1() {
  int code = save.Repair(1);
  if (code != 1) {
    Menu* popup = new Menu(410, 80);
    MenuText* text;
    if (code == 0) {
      text = new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    } else {
      text = new MenuText(93, 25, "Health full!", {0, 0, 0, 255}, 30);
    }
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    delete popup;
  } else {
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
    p1_damagebar->GetRect()->w = static_cast<int>(save.GetDamage(1) * 1.65f);
  }
}
void ShowPriceP1Repair(bool dir);
MenuButton* p1_repair =
    new MenuButton({274, 339, 165, 35}, Repairp1, ShowPriceP1Repair,
                   new MenuText("Repair", {255, 255, 255, 255}, 15));
void ShowPriceP1Repair(bool dir) {
  MenuText* text = dynamic_cast<MenuText*>(p1_repair->GetDisplay());
  if (dir) {
    text->SetText("\u00A2" + std::to_string(save.GetRepairCost(1)));
  } else {
    text->SetText("Repair");
  }
}

// player two
int player_2_gun = NULL;
void reset2();
void Overlay2Hide();
int player2_selector = NULL;
MenuItem* player2_overlay =
    new MenuItem({554, 100, 132, 188}, SDL_Color{30, 30, 30, 120});
void UpgradeWeapon2() {
  if (save.UpgradeWeapon(player2_selector)) {
    Overlay2Hide();
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
  } else {
    Menu* popup = new Menu(410, 80);
    MenuText* text =
        new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    delete popup;
  }
}
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
    new MenuText(564, 105, "Gun 1\n\nDAM:10\nROF:10\nSPE:1\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover21(bool dir) {
  player2_gun1_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    player2_selector = 0;
    player2_gun1_text->Show();
    std::vector<int> stats = save.GetGunStats(0);
    player2_gun1_text->SetText("Gun 1\n\nDAM:" + std::to_string(stats[0]) +
                               "\nROF:" + std::to_string(stats[1] / 10) +
                               "\nSPE:1" + std::to_string(stats[2] / 10) +
                               "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
void Click21();
MenuButton* player2_gun1 =
    new MenuButton({524, 100, 30, 30}, Click21, Hover21,
                   new MenuText(0, 0, "1", {255, 255, 255, 255}, 24));
void Click21() {
  reset2();
  player2_gun1->SetColorDef({200, 0, 0, 255});
  player_2_gun = 0;
}



// 21 gun 2
MenuText* player2_gun2_text =
    new MenuText(564, 105, "Gun 2\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover22(bool dir) {
  player2_gun2_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    player2_selector = 1;
    player2_gun2_text->Show();
    std::vector<int> stats = save.GetGunStats(1);
    player2_gun2_text->SetText("Gun 2\n\nDAM:" + std::to_string(stats[0]) +
                               "\nROF:" + std::to_string(stats[1] / 10) +
                               "\nSPE:1" + std::to_string(stats[2] / 10) +
                               "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
void Click22();
MenuButton* player2_gun2 =
    new MenuButton({524, 139, 30, 30}, Click22, Hover22,
                   new MenuText(0, 0, "2", {255, 255, 255, 255}, 24));
void Click22() {
  reset2();
  player2_gun2->SetColorDef({200, 0, 0, 255});
  player_2_gun = 1;
}



// p2 gun 3
MenuText* player2_gun3_text =
    new MenuText(564, 105, "Gun 3\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover23(bool dir) {
  player2_gun3_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    player2_selector = 2;
    player2_gun3_text->Show();
    std::vector<int> stats = save.GetGunStats(2);
    player2_gun3_text->SetText("Gun 3\n\nDAM:" + std::to_string(stats[0]) +
                               "\nROF:" + std::to_string(stats[1] / 10) +
                               "\nSPE:1" + std::to_string(stats[2] / 10) +
                               "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
void Click23();
MenuButton* player2_gun3 =
    new MenuButton({524, 179, 30, 30}, Click23, Hover23,
                   new MenuText(0, 0, "3", {255, 255, 255, 255}, 24));
void Click23() {
  reset2();
  player2_gun3->SetColorDef({200, 0, 0, 255});
  player_2_gun = 2;
}



// p2 gun 4
MenuText* player2_gun4_text =
    new MenuText(564, 105, "Gun 4\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover24(bool dir) {
  player2_gun4_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    player2_selector = 3;
    player2_gun4_text->Show();
    std::vector<int> stats = save.GetGunStats(3);
    player2_gun4_text->SetText("Gun 4\n\nDAM:" + std::to_string(stats[0]) +
                               "\nROF:" + std::to_string(stats[1] / 10) +
                               "\nSPE:1" + std::to_string(stats[2] / 10) +
                               "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
void Click24();
MenuButton* player2_gun4 =
    new MenuButton({524, 219, 30, 30}, Click24, Hover24,
                   new MenuText(0, 0, "4", {255, 255, 255, 255}, 24));
void Click24() {
  reset2();
  player2_gun4->SetColorDef({200, 0, 0, 255});
  player_2_gun = 3;
}



// p1 gun 5
MenuText* player2_gun5_text =
    new MenuText(564, 105, "Gun 5\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
void Hover25(bool dir) {
  player2_gun5_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    player2_selector = 4;
    player2_gun5_text->Show();
    std::vector<int> stats = save.GetGunStats(4);
    player2_gun5_text->SetText("Gun 5\n\nDAM:" + std::to_string(stats[0]) +
                               "\nROF:" + std::to_string(stats[1] / 10) +
                               "\nSPE:1" + std::to_string(stats[2] / 10) +
                               "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
void Click25();
MenuButton* player2_gun5 =
    new MenuButton({524, 258, 30, 30}, Click25, Hover25,
                   new MenuText(0, 0, "5", {255, 255, 255, 255}, 24));
void Click25() {
  reset2();
  player2_gun5->SetColorDef({200, 0, 0, 255});
  player_2_gun = 4;
}

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
void reset2() {
  player2_gun1->SetColorDef({60, 60, 60, 255});
  player2_gun2->SetColorDef({60, 60, 60, 255});
  player2_gun3->SetColorDef({60, 60, 60, 255});
  player2_gun4->SetColorDef({60, 60, 60, 255});
  player2_gun5->SetColorDef({60, 60, 60, 255});
}

// p2 speed
MenuText* p2_speed = new MenuText(
    524, 75, "S: " + std::to_string(save.GetPlayerStats(2)[0] / 10),
    {0, 0, 0, 255}, 20);
MenuText* p2_armour =
    new MenuText(610, 75, "A: " + std::to_string(save.GetPlayerStats(2)[1]),
                 {0, 0, 0, 255}, 20);

void ShowPriceP2Speed(bool dir);
void UpgradeP2Speed() {
  if (save.UpgradePlayer(false, 2)) {
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
    p2_speed->SetText("S: " + std::to_string(save.GetPlayerStats(2)[0] / 10));
  } else {
    Menu* popup = new Menu(410, 80);
    MenuText* text =
        new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    delete popup;
  }
}
MenuButton* p2_upgrade_speed =
    new MenuButton({524, 299, 80, 35}, UpgradeP2Speed, ShowPriceP2Speed,
                   new MenuText("Speed+", {255, 255, 255, 255}, 15));
void ShowPriceP2Speed(bool dir) {
  MenuText* text = dynamic_cast<MenuText*>(p2_upgrade_speed->GetDisplay());
  if (dir) {
    text->SetText("\u00A2" + std::to_string(save.GetPlayerStats(2)[2]));
  } else {
    text->SetText("Speed+");
  }
}


// p2 armour
void ShowPriceP2Armour(bool dir);
void UpgradeP2Armour() {
  if (save.UpgradePlayer(true, 2)) {
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
    p2_armour->SetText("A: " + std::to_string(save.GetPlayerStats(2)[1]));
  } else {
    Menu* popup = new Menu(410, 80);
    MenuText* text =
        new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    delete popup;
  }
}
MenuButton* p2_upgrade_armour =
    new MenuButton({607, 299, 80, 35}, UpgradeP2Armour, ShowPriceP2Armour,
                   new MenuText("Armor+", {255, 255, 255, 255}, 15));
void ShowPriceP2Armour(bool dir) {
  MenuText* text = dynamic_cast<MenuText*>(p2_upgrade_armour->GetDisplay());
  if (dir) {
    text->SetText("\u00A2" + std::to_string(save.GetPlayerStats(2)[3]));
  } else {
    text->SetText("Armor+");
  }
}


// p2 repair / damage
void ShowPriceP2Repair(bool dir);
MenuItem* p2_damagebar =
    new MenuItem({524, 379, static_cast<int>(save.GetDamage(2) * 1.65f), 11},
                 {110, 59, 173, 255});
MenuItem* p2_damagebar_bkg =
    new MenuItem({524, 379, 165, 11}, {26, 34, 38, 255});
void Repairp2() {
  int code = save.Repair(2);
  if (code != 1) {
    Menu* popup = new Menu(410, 80);
    MenuText* text;
    if (code == 0) {
      text = new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    } else {
      text = new MenuText(93, 25, "Health full!", {0, 0, 0, 255}, 30);
    }
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    delete popup;
  } else {
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
    p2_damagebar->GetRect()->w = static_cast<int>(save.GetDamage(2) * 1.65f);
  }
}
MenuButton* p2_repair =
    new MenuButton({524, 339, 165, 35}, Repairp2, ShowPriceP2Repair,
                   new MenuText("Repair", {255, 255, 255, 255}, 15));
void ShowPriceP2Repair(bool dir) {
  MenuText* text = dynamic_cast<MenuText*>(p2_repair->GetDisplay());
  if (dir) {
    text->SetText("\u00A2" + std::to_string(save.GetRepairCost(2)));
  } else {
    text->SetText("Repair");
  }
}
