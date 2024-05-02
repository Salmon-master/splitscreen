// Copyright 2024 Hugh Thompson

#ifndef SPLITSCREEN_GAME_OBJECT_H_
#define SPLITSCREEN_GAME_OBJECT_H_

#include <iostream>
#include <string>
#include <vector>

#include "SDL2/include/SDL.h"
#include "SDL2_image/include/SDL_image.h"

#include "vector.h"

// Base class for all and any objects which are rendered to a screen, used
// mainly as an interface with the screens so that one one type has to be
// rendered, and most functionalty concerning loading of images and posistion
// manipulation is also included.
class GameObject {
 public:
  // true if rendered on a screen, if not false
  bool rendered_ = false;

 protected:
  // rect of the object(in game space)
  SDL_FRect rect_ = {0, 0, 0, 0};
  // rotation of that object, from 0 to 2PI
  float rotation_ = 0;
  // the center about which that object is rotated
  SDL_Point rotation_center_ = {0, 0};
  // a reference of the pervious movment off the object
  Vector velocity_ = {0, 0};
  // all frames of all animations indexed by animation and frame number
  std::vector<std::vector<SDL_Surface*>> surfaces_;
  // current animation the object doing
  int state_ = 0;
  // current frame of current animation
  int frame_ = 0;
  // the fps of the animation
  int fps_ = 0;
  // the last time, in ms since sld2 libary initisation, that the render wanted
  // the current frame of the object
  int last_step_ = 0;
  // a vector of the next animations to play after the current animation has
  // finished playing.
  std::vector<int> state_que_ = {};
  // a redundant virtual function that allows of dynmic casting to distuingish
  // between types of child objects
  virtual void Cast();

 public:
  // a location and a name for filesystem purposes
  GameObject(int x, int y, std::string name);
  ~GameObject();
  // set the positin of the object in gamespace
  void SetPos(int x, int y);
  // translate the object in gamespace by the inputted amounts
  void Move(float x, float y);
  // calculate animation and retrun frame that needs to be rendered, used by
  // screen class to get surfaces to render.
  SDL_Surface* GetSurface();
  // used to set the current animation, intreupting the current one playing.
  void Setstate(int state);
  // aslo used to set the current amination, but ques the animation to run after
  // the current animation is finished playing.
  void QueState(int state);
  // retuns the rect(x, y, width, height) of the game object
  SDL_FRect GetRect();
  // retuns the roataion, in radians, of the game object
  float GetRotation();
  // retuns the center of the robot relivte to the top left corner
  SDL_Point* GetCenter();
  // retuns the velocity vector of the game object
  Vector GetVelocity();
};

#endif  // !SPLITSCREEN_GAME_OBJECT_H_
