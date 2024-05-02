// Copyright 2024 Hugh Thompson

#ifndef SPLITSCREEN_MENU_ITEMS_H_
#define SPLITSCREEN_MENU_ITEMS_H_

#include <vector>

#include "menu.h"
#include "menu_button.h"
#include "menu_image.h"
#include "menu_item.h"
#include "menu_text.h"

// main menu
Menu* menu = new Menu;
// reward pop up
Menu* death_menu = nullptr;
// death pop up
Menu* reward_menu = nullptr;

// runs the game
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
// show the tutorial pop up
void Tutorial() {
  Menu* popup = new Menu(600, 430);
  bool popup_run = true;
  SDL_Event e;
  // text for the pop up to display
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
  // menu loop
  while (popup_run) {
    // input for qutiiting the pop up
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
  // clean up
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

// which gun the robot has selected
int robot_1_gun = 0;
// sets the color of all robot 1's gun selctor icons to the defaukt color({60,
// 60, 60, 255})
void reset1();
// hide the overlay for robot 1 gun menu
void Overlay1Hide();
// the current hoverd over gun for robot 1
int robot1_selector = NULL;
// robot 1 overlay
MenuItem* robot1_overlay =
    new MenuItem({304, 100, 132, 188}, SDL_Color{30, 30, 30, 120});
// upgrde the weapon of robot 1
void UpgradeWeapon1() {
  if (save.UpgradeWeapon(robot1_selector)) {
    // upgrade sucessful
    Overlay1Hide();
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
  } else {
    // not enough money
    Menu* popup = new Menu(410, 80);
    MenuText* text =
        new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    delete popup;
  }
}
// weapon upgrade button
MenuButton* robot1_upgrade_weapon =
    new MenuButton({314, 253, 112, 30}, UpgradeWeapon1, NULL,
                   new MenuText("upgrade", {255, 255, 255, 255}, 19));
// shows the overlay for robot 1 gun menu
void Overlay1Show(bool dir) {
  if (dir) {
    robot1_overlay->Show();
    robot1_upgrade_weapon->Show();
  }
}
// robot 1 menu image
MenuImage* robot1_image = new MenuImage(314, 100, "robot");

// text displing the robot 1 gun 1 stats
MenuText* robot1_gun1_text =
    new MenuText(314, 105, "Gun 1\n\nDAM:10\nROF:10\nSPE:1\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
// displays gun 1's stats(damage rate of fire, bullet speed and cost) on the
// robot 1 overlay.
void Hover11(bool dir) {
  robot1_gun1_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    robot1_selector = 0;
    robot1_gun1_text->Show();
    std::vector<int> stats = save.GetGunStats(0);
    // loading in stats from save
    robot1_gun1_text->SetText("Gun 1\n\nDAM:" + std::to_string(stats[0]) +
                              "\nROF:" + std::to_string(stats[1] / 10) +
                              "\nSPE:1" + std::to_string(stats[2] / 10) +
                              "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
// sets robot 1's gun to gun number 1
void Click11();
// robot 1 gun 1's gun selector icon
MenuButton* robot1_gun1 =
    new MenuButton({274, 100, 30, 30}, Click11, Hover11,
                   new MenuText(0, 0, "1", {255, 255, 255, 255}, 24));
void Click11() {
  // visual update
  reset1();
  robot1_gun1->SetColorDef({200, 0, 0, 255});
  // weapon setting
  robot_1_gun = 0;
}

// text displing the robot 1 gun 1 stats
MenuText* robot1_gun2_text =
    new MenuText(314, 105, "Gun 2\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
// displays gun 2's stats(damage rate of fire, bullet speed and cost) on the
// robot 1 overlay.
void Hover12(bool dir) {
  robot1_gun2_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    robot1_selector = 1;
    robot1_gun2_text->Show();
    std::vector<int> stats = save.GetGunStats(1);
    robot1_gun2_text->SetText("Gun 2\n\nDAM:" + std::to_string(stats[0]) +
                              "\nROF:" + std::to_string(stats[1] / 10) +
                              "\nSPE:1" + std::to_string(stats[2] / 10) +
                              "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
// sets robot 1's gun to gun number 2
void Click12();
// robot 1 gun 1's gun selector icon
MenuButton* robot1_gun2 =
    new MenuButton({274, 139, 30, 30}, Click12, Hover12,
                   new MenuText(0, 0, "2", {255, 255, 255, 255}, 24));
void Click12() {
  // visual update
  reset1();
  robot1_gun2->SetColorDef({200, 0, 0, 255});
  // weapon setting
  robot_1_gun = 1;
}

// text displing the robot 1 gun 3 stats
MenuText* robot1_gun3_text =
    new MenuText(314, 105, "Gun 3\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
// displays gun 3's stats(damage rate of fire, bullet speed and cost) on the
// robot 1 overlay.
void Hover13(bool dir) {
  robot1_gun3_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    robot1_selector = 2;
    robot1_gun3_text->Show();
    std::vector<int> stats = save.GetGunStats(2);
    robot1_gun3_text->SetText("Gun 3\n\nDAM:" + std::to_string(stats[0]) +
                              "\nROF:" + std::to_string(stats[1] / 10) +
                              "\nSPE:1" + std::to_string(stats[2] / 10) +
                              "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
// sets robot 1's gun to gun number 3
void Click13();
// robot 1 gun 4's gun selector icon
MenuButton* robot1_gun3 =
    new MenuButton({274, 179, 30, 30}, Click13, Hover13,
                   new MenuText(0, 0, "3", {255, 255, 255, 255}, 24));
void Click13() {
  // visual update
  reset1();
  robot1_gun3->SetColorDef({200, 0, 0, 255});
  // weapon setting
  robot_1_gun = 2;
}

// text displing the robot 1 gun 4 stats
MenuText* robot1_gun4_text =
    new MenuText(314, 105, "Gun 4\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
// displays gun 4's stats(damage rate of fire, bullet speed and cost) on the
// robot 1 overlay.
void Hover14(bool dir) {
  robot1_gun4_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    robot1_selector = 3;
    robot1_gun4_text->Show();
    std::vector<int> stats = save.GetGunStats(3);
    robot1_gun4_text->SetText("Gun 4\n\nDAM:" + std::to_string(stats[0]) +
                              "\nROF:" + std::to_string(stats[1] / 10) +
                              "\nSPE:1" + std::to_string(stats[2] / 10) +
                              "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
// sets robot 1's gun to gun number 4
void Click14();
// robot 1 gun 4's gun selector icon
MenuButton* robot1_gun4 =
    new MenuButton({274, 219, 30, 30}, Click14, Hover14,
                   new MenuText(0, 0, "4", {255, 255, 255, 255}, 24));
// sets robot 1's gun to gun number 1
void Click14() {
  // visual update
  reset1();
  robot1_gun4->SetColorDef({200, 0, 0, 255});
  // setting weapon
  robot_1_gun = 3;
}

// text displing the robot 1 gun 5 stats
MenuText* robot1_gun5_text =
    new MenuText(314, 105, "Gun 5\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
// displays gun 5's stats(damage rate of fire, bullet speed and cost) on the
// robot 1 overlay.
void Hover15(bool dir) {
  robot1_gun5_text->SetWrap(112);
  Overlay1Show(dir);
  if (dir) {
    robot1_selector = 4;
    robot1_gun5_text->Show();
    std::vector<int> stats = save.GetGunStats(4);
    robot1_gun5_text->SetText("Gun 5\n\nDAM:" + std::to_string(stats[0]) +
                              "\nROF:" + std::to_string(stats[1] / 10) +
                              "\nSPE:1" + std::to_string(stats[2] / 10) +
                              "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
// sets robot 1's gun to gun number 5
void Click15();
// robot 1 gun 5's gun selector icon
MenuButton* robot1_gun5 =
    new MenuButton({274, 258, 30, 30}, Click15, Hover15,
                   new MenuText(0, 0, "5", {255, 255, 255, 255}, 24));
void Click15() {
  // visual update
  reset1();
  robot1_gun5->SetColorDef({200, 0, 0, 255});
  // weapon setting
  robot_1_gun = 4;
}

void reset1() {
  // reseting color of all components
  robot1_gun1->SetColorDef({60, 60, 60, 255});
  robot1_gun2->SetColorDef({60, 60, 60, 255});
  robot1_gun3->SetColorDef({60, 60, 60, 255});
  robot1_gun4->SetColorDef({60, 60, 60, 255});
  robot1_gun5->SetColorDef({60, 60, 60, 255});
}

// hiding of r1 overlay components
void Overlay1Hide() {
  // hiding components
  robot1_overlay->Hide();
  robot1_upgrade_weapon->Hide();
  robot1_gun1_text->Hide();
  robot1_gun2_text->Hide();
  robot1_gun3_text->Hide();
  robot1_gun4_text->Hide();
  robot1_gun5_text->Hide();
  robot1_selector = NULL;
}

// text displaying the speed of robot 1
MenuText* r1_speed =
    new MenuText(274, 75, "S: " + std::to_string(save.GetRobotStats(1)[0] / 10),
                 {0, 0, 0, 255}, 20);
// text displaying the armor of robot 1
MenuText* r1_armour =
    new MenuText(360, 75, "A: " + std::to_string(save.GetRobotStats(1)[1]),
                 {0, 0, 0, 255}, 20);
// shows the price for robot 1's speed
void ShowPriceR1Speed(bool dir);
// upgrades the level of robot 1's speed.
void UpgradeR1Speed() {
  if (save.UpgradeRobot(false, 1)) {
    // payment sucessful, visual update
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
    r1_speed->SetText("S: " + std::to_string(save.GetRobotStats(1)[0] / 10));
  } else {
    // payment unsucessful, popup created to display this to the player
    Menu* popup = new Menu(410, 80);
    MenuText* text =
        new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    // clean up
    delete popup;
  }
}
// a button used by the player to upgarde robot 1's speed
MenuButton* r1_upgrade_speed =
    new MenuButton({274, 299, 80, 35}, UpgradeR1Speed, ShowPriceR1Speed,
                   new MenuText("Speed+", {255, 255, 255, 255}, 15));
void ShowPriceR1Speed(bool dir) {
  // cast for acess to call menutext methods
  MenuText* text = dynamic_cast<MenuText*>(r1_upgrade_speed->GetDisplay());
  if (dir) {
    // if hovered over, show price
    text->SetText("\u00A2" + std::to_string(save.GetRobotStats(1)[2]));
  } else {
    // if not hovered over, which upgarde this button is doing
    text->SetText("Speed+");
  }
}

// shows the price to upgrade robot 1's armour
void ShowPriceR1Armour(bool dir);
// ugardes the level of robot 1's armour
void UpgradeR1Armour() {
  if (save.UpgradeRobot(true, 1)) {
    // payment sucessful, visual update
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
    r1_armour->SetText("A: " + std::to_string(save.GetRobotStats(1)[1]));
  } else {
    // payment unsucessful, popup is shown telling the player this.
    Menu* popup = new Menu(410, 80);
    MenuText* text =
        new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    // clean up
    delete popup;
  }
}
// a button used to upgarde the level of robot 1's armour
MenuButton* r1_upgrade_armour =
    new MenuButton({357, 299, 80, 35}, UpgradeR1Armour, ShowPriceR1Armour,
                   new MenuText("Armor+", {255, 255, 255, 255}, 15));
void ShowPriceR1Armour(bool dir) {
  // cast for use of acessing menutext methods
  MenuText* text = dynamic_cast<MenuText*>(r1_upgrade_armour->GetDisplay());
  if (dir) {
    // if hovered over, show the price
    text->SetText("\u00A2" + std::to_string(save.GetRobotStats(1)[3]));
  } else {
    // if not hovered over, show the upgrade which this button is doing
    text->SetText("Armor+");
  }
}

// a bar showing how much damage robot 1 has taken
MenuItem* r1_damagebar =
    new MenuItem({274, 379, static_cast<int>(save.GetDamage(1) * 1.65f), 11},
                 {110, 59, 173, 255});
// a background to the bar showing how much dmage robot 1 has taken
MenuItem* r1_damagebar_bkg =
    new MenuItem({274, 379, 165, 11}, {26, 34, 38, 255});

// reapirs robot 1
void RepairR1() {
  // code telling the program if the purchase is sucessful, and if not why not
  int code = save.Repair(1);
  if (code != 1) {
    // if the pruchase is not sucessful, popup a window
    Menu* popup = new Menu(410, 80);
    MenuText* text;
    // what text to display based or eariler code retreived
    if (code == 0) {
      text = new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    } else {
      text = new MenuText(93, 25, "Health full!", {0, 0, 0, 255}, 30);
    }
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    // clean up
    delete popup;
  } else {
    // if the purchase is sucesful, update visuals.
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
    r1_damagebar->GetRect()->w = static_cast<int>(save.GetDamage(1) * 1.65f);
  }
}
// shows the cost to repair robot 1 5 damage.
void ShowPriceR1Repair(bool dir);
// a button used to repair robot 1
MenuButton* r1_repair =
    new MenuButton({274, 339, 165, 35}, RepairR1, ShowPriceR1Repair,
                   new MenuText("Repair", {255, 255, 255, 255}, 15));
void ShowPriceR1Repair(bool dir) {
  // cast to acess menu text methods
  MenuText* text = dynamic_cast<MenuText*>(r1_repair->GetDisplay());
  if (dir) {
    // if hovered over, display the cost of the repair
    text->SetText("\u00A2" + std::to_string(save.GetRepairCost(1)));
  } else {
    // if not hovered over, display the funcion this button preforms
    text->SetText("Repair");
  }
}

// robot 2's selected gun
int robot_2_gun = NULL;
// sets the color of all robot 2's gun selctor icons to the defaukt color({60,
// 60, 60, 255})
void reset2();
// hides the image overaly for robot 2
void Overlay2Hide();
// the currently hoverd over gun for robot 2
int robot2_selector = NULL;
// the image overlay for robot 2
MenuItem* robot2_overlay =
    new MenuItem({554, 100, 132, 188}, SDL_Color{30, 30, 30, 120});
// upgrade the currently hovered over weapon of robot 2
void UpgradeWeapon2() {
  if (save.UpgradeWeapon(robot2_selector)) {
    // visual updadte if the upgrdade is sucessful
    Overlay2Hide();
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
  } else {
    // if the upgarde is unscessful, then display this to the player though a
    // pop up
    Menu* popup = new Menu(410, 80);
    MenuText* text =
        new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    // clean up
    delete popup;
  }
}
// a button used to upgrade robot 2's currently hovered over weapon
MenuButton* robot2_upgrade_weapon =
    new MenuButton({564, 253, 112, 30}, UpgradeWeapon2, NULL,
                   new MenuText("upgrade", {255, 255, 255, 255}, 19));
// shows the overlay for player 2
void Overlay2Show(bool dir) {
  if (dir) {
    robot2_overlay->Show();
    robot2_upgrade_weapon->Show();
  }
}
// robot 2 menu image
MenuImage* robot2_image = new MenuImage(564, 100, "robot");

// text displaying the stats of gun 1 on the robot 2's overlay
MenuText* robot2_gun1_text =
    new MenuText(564, 105, "Gun 1\n\nDAM:10\nROF:10\nSPE:1\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
// displays gun 1's stats(damage rate of fire, bullet speed and cost) on the
// robot 2 overlay.
void Hover21(bool dir) {
  robot2_gun1_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    robot2_selector = 0;
    robot2_gun1_text->Show();
    std::vector<int> stats = save.GetGunStats(0);
    robot2_gun1_text->SetText("Gun 1\n\nDAM:" + std::to_string(stats[0]) +
                              "\nROF:" + std::to_string(stats[1] / 10) +
                              "\nSPE:1" + std::to_string(stats[2] / 10) +
                              "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
// sets robot 2's gun to gun number 1
void Click21();
// robot 2 gun 1's gun selector icon
MenuButton* robot2_gun1 =
    new MenuButton({524, 100, 30, 30}, Click21, Hover21,
                   new MenuText(0, 0, "1", {255, 255, 255, 255}, 24));
void Click21() {
  reset2();
  robot2_gun1->SetColorDef({200, 0, 0, 255});
  robot_2_gun = 0;
}

// text displing the robot 2 gun 1 stats
MenuText* robot2_gun2_text =
    new MenuText(564, 105, "Gun 2\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
// displays gun 2's stats(damage rate of fire, bullet speed and cost) on the
// robot 2 overlay.
void Hover22(bool dir) {
  robot2_gun2_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    robot2_selector = 1;
    robot2_gun2_text->Show();
    std::vector<int> stats = save.GetGunStats(1);
    robot2_gun2_text->SetText("Gun 2\n\nDAM:" + std::to_string(stats[0]) +
                              "\nROF:" + std::to_string(stats[1] / 10) +
                              "\nSPE:1" + std::to_string(stats[2] / 10) +
                              "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
// sets robot 2's gun to gun number 2
void Click22();
// robot 2 gun 2's gun selector icon
MenuButton* robot2_gun2 =
    new MenuButton({524, 139, 30, 30}, Click22, Hover22,
                   new MenuText(0, 0, "2", {255, 255, 255, 255}, 24));
void Click22() {
  reset2();
  robot2_gun2->SetColorDef({200, 0, 0, 255});
  robot_2_gun = 1;
}

// text displing the robot 2 gun 3 stats
MenuText* robot2_gun3_text =
    new MenuText(564, 105, "Gun 3\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
// displays gun 3's stats(damage rate of fire, bullet speed and cost) on the
// robot 2 overlay.
void Hover23(bool dir) {
  robot2_gun3_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    robot2_selector = 2;
    robot2_gun3_text->Show();
    std::vector<int> stats = save.GetGunStats(2);
    robot2_gun3_text->SetText("Gun 3\n\nDAM:" + std::to_string(stats[0]) +
                              "\nROF:" + std::to_string(stats[1] / 10) +
                              "\nSPE:1" + std::to_string(stats[2] / 10) +
                              "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
// sets robot 2's gun to gun number 3
void Click23();
// robot 2 gun 3's gun selector icon
MenuButton* robot2_gun3 =
    new MenuButton({524, 179, 30, 30}, Click23, Hover23,
                   new MenuText(0, 0, "3", {255, 255, 255, 255}, 24));
void Click23() {
  reset2();
  robot2_gun3->SetColorDef({200, 0, 0, 255});
  robot_2_gun = 2;
}

// text displing the robot 2 gun 4 stats
MenuText* robot2_gun4_text =
    new MenuText(564, 105, "Gun 4\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
// displays gun 4's stats(damage rate of fire, bullet speed and cost) on the
// robot 2 overlay.
void Hover24(bool dir) {
  robot2_gun4_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    robot2_selector = 3;
    robot2_gun4_text->Show();
    std::vector<int> stats = save.GetGunStats(3);
    robot2_gun4_text->SetText("Gun 4\n\nDAM:" + std::to_string(stats[0]) +
                              "\nROF:" + std::to_string(stats[1] / 10) +
                              "\nSPE:1" + std::to_string(stats[2] / 10) +
                              "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
// sets robot 2's gun to gun number 1
void Click24();
// robot 2 gun 4's gun selector icon
MenuButton* robot2_gun4 =
    new MenuButton({524, 219, 30, 30}, Click24, Hover24,
                   new MenuText(0, 0, "4", {255, 255, 255, 255}, 24));
void Click24() {
  reset2();
  robot2_gun4->SetColorDef({200, 0, 0, 255});
  robot_2_gun = 3;
}

// text displing the robot 5 gun 1 stats
MenuText* robot2_gun5_text =
    new MenuText(564, 105, "Gun 5\n\nDAM:2\nROF:100\nSPE:10\n\nCost:\u00A2100",
                 {0xff, 0xff, 0xff, 0xff}, 17);
// displays gun 5's stats(damage rate of fire, bullet speed and cost) on the
// robot 2 overlay.
void Hover25(bool dir) {
  robot2_gun5_text->SetWrap(112);
  Overlay2Show(dir);
  if (dir) {
    robot2_selector = 4;
    robot2_gun5_text->Show();
    std::vector<int> stats = save.GetGunStats(4);
    robot2_gun5_text->SetText("Gun 5\n\nDAM:" + std::to_string(stats[0]) +
                              "\nROF:" + std::to_string(stats[1] / 10) +
                              "\nSPE:1" + std::to_string(stats[2] / 10) +
                              "\n\nCost:\u00A2" + std::to_string(stats[3]));
  }
}
// sets robot 2's gun to gun number 5
void Click25();
// robot 2 gun 5's gun selector icon
MenuButton* robot2_gun5 =
    new MenuButton({524, 258, 30, 30}, Click25, Hover25,
                   new MenuText(0, 0, "5", {255, 255, 255, 255}, 24));
void Click25() {
  reset2();
  robot2_gun5->SetColorDef({200, 0, 0, 255});
  robot_2_gun = 4;
}

void Overlay2Hide() {
  robot2_overlay->Hide();
  robot2_upgrade_weapon->Hide();
  robot2_gun1_text->Hide();
  robot2_gun2_text->Hide();
  robot2_gun3_text->Hide();
  robot2_gun4_text->Hide();
  robot2_gun5_text->Hide();
  robot2_selector = NULL;
}
void reset2() {
  robot2_gun1->SetColorDef({60, 60, 60, 255});
  robot2_gun2->SetColorDef({60, 60, 60, 255});
  robot2_gun3->SetColorDef({60, 60, 60, 255});
  robot2_gun4->SetColorDef({60, 60, 60, 255});
  robot2_gun5->SetColorDef({60, 60, 60, 255});
}

// text displaying the speed of robot 2
MenuText* r2_speed =
    new MenuText(524, 75, "S: " + std::to_string(save.GetRobotStats(2)[0] / 10),
                 {0, 0, 0, 255}, 20);
// text displaying the armour of robot 1
MenuText* r2_armour =
    new MenuText(610, 75, "A: " + std::to_string(save.GetRobotStats(2)[1]),
                 {0, 0, 0, 255}, 20);
// shows the price to upgrade robot 2's speed
void ShowPriceR2Speed(bool dir);
// upgrades the level of robot 1's speed.
void UpgradeR2Speed() {
  if (save.UpgradeRobot(false, 2)) {
    // payment sucessful, visual update
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
    r2_speed->SetText("S: " + std::to_string(save.GetRobotStats(2)[0] / 10));
  } else {
    // payment unsucessful, popup created to display this to the player
    Menu* popup = new Menu(410, 80);
    MenuText* text =
        new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    // clean up
    delete popup;
  }
}
// a button used by the player to upgarde robot 2's speed
MenuButton* r2_upgrade_speed =
    new MenuButton({524, 299, 80, 35}, UpgradeR2Speed, ShowPriceR2Speed,
                   new MenuText("Speed+", {255, 255, 255, 255}, 15));
void ShowPriceR2Speed(bool dir) {
  // cast for acess to call menutext methods
  MenuText* text = dynamic_cast<MenuText*>(r2_upgrade_speed->GetDisplay());
  if (dir) {
    // if hovered over, show price
    text->SetText("\u00A2" + std::to_string(save.GetRobotStats(2)[2]));
  } else {
    // if not hovered over, which upgarde this button is doing
    text->SetText("Speed+");
  }
}

// shows the price to upgarde robot 1's armour
void ShowPriceR2Armour(bool dir);
// upgrades the level of robot 2's armour.
void UpgradeR2Armour() {
  if (save.UpgradeRobot(true, 2)) {
    // payment sucessful, visual update
    credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
    r2_armour->SetText("A: " + std::to_string(save.GetRobotStats(2)[1]));
  } else {
    // payment unsucessful, popup created to display this to the player
    Menu* popup = new Menu(410, 80);
    MenuText* text =
        new MenuText(25, 25, "Insufficent Funds!", {0, 0, 0, 255}, 30);
    popup->menu_items_ = {text};
    popup->Render();
    SDL_Delay(3000);
    // clean up
    delete popup;
  }
}
// a button used by the player to upgarde robot 2's armour
MenuButton* r2_upgrade_armour =
    new MenuButton({607, 299, 80, 35}, UpgradeR2Armour, ShowPriceR2Armour,
                   new MenuText("Armor+", {255, 255, 255, 255}, 15));
void ShowPriceR2Armour(bool dir) {
  // cast for acess to call menutext methods
  MenuText* text = dynamic_cast<MenuText*>(r2_upgrade_armour->GetDisplay());
  if (dir) {
    // if hovered over, show price
    text->SetText("\u00A2" + std::to_string(save.GetRobotStats(2)[3]));
  } else {
    // if not hovered over, which upgarde this button is doing
    text->SetText("Armor+");
  }
}

// r2 repair / damage
void ShowPriceR2Repair(bool dir);
MenuItem* r2_damagebar =
    new MenuItem({524, 379, static_cast<int>(save.GetDamage(2) * 1.65f), 11},
                 {110, 59, 173, 255});
MenuItem* r2_damagebar_bkg =
    new MenuItem({524, 379, 165, 11}, {26, 34, 38, 255});
void Repairr2() {
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
    r2_damagebar->GetRect()->w = static_cast<int>(save.GetDamage(2) * 1.65f);
  }
}
// a button used to repair robot 2
MenuButton* r2_repair =
    new MenuButton({524, 339, 165, 35}, Repairr2, ShowPriceR2Repair,
                   new MenuText("Repair", {255, 255, 255, 255}, 15));
// shows the cost to repair robot 2 5 damage.
void ShowPriceR2Repair(bool dir) {
  // cast for acess to call menutext methods
  MenuText* text = dynamic_cast<MenuText*>(r2_repair->GetDisplay());
  if (dir) {
    // if hovered over, display the cost of the repair
    text->SetText("\u00A2" + std::to_string(save.GetRepairCost(2)));
  } else {
    // if not hovered over, display the funcion this button preforms
    text->SetText("Repair");
  }
}
#endif  // !SPLITSCREEN_MENU_ITEMS_H_
