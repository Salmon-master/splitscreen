// Copyright 2024 Hugh Thompson

#ifndef SPLITSCREEN_MENU_BUTTON_H_
#define SPLITSCREEN_MENU_BUTTON_H_

#include "menu_item.h"

// a class used to represnt a button in a menu, add to a menu's list of menu
// objects and the button will appear on that menu
class MenuButton : public MenuItem {
 public:
  // inputs are: a rect descibing the position and size of the button, what code
  // to execute when the button is clicked, then what code to execucte when the
  // button is hovered, and a pointer to a menuobject so that text or images my
  // be reneder as part of the button.
  MenuButton(SDL_Rect rect, void (*Click)(), void (*Hover)(bool dir),
             MenuItem* display);
  ~MenuButton();
  //  called by the menu's renderer evey frame to update the buttons asthetics
  //  and to check for hovering and clicking
  void Update();
  // retuns the menuitem bound to the display 
  MenuItem* GetDisplay();
  // sets the default color of the button when not hoverd over
  void SetColorDef(SDL_Color color);

 private:
  // a function pointer to what code the button will execute when clicked.
  // initised in constructor
  void (*OnClick)() = NULL;
  // a function pointer to what code should be executed when hoverd over, and an
  // input to reverse this action. the function will be called with dir being
  // true if the button is currently being over over and fasle if not. initised
  // in constructor
  void (*OnHover)(bool dir) = NULL;
  // a pointer to an optional menuitem rendered as part of the button so that it
  // may display text or images initised in constructor
  MenuItem* display_ = nullptr;
  // the default color of the button when not hoverd over
  SDL_Color color_def_ = {60, 60, 60, 255};
};

#endif  // !SPLITSCREEN_MENU_BUTTON_H_
