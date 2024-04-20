// Copyright 2024 Hugh Thompson

#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "vector.h"

// Base class for all and any objects which are rendered to a screen, used
// mainly as an interface with the screens so that one one type has to be
// rendered, and most functionalty concerning loading of images and posistion
// manipulation is also included.
class GameObject {
 public:
  // ture if rendered on a screen, if not false
  bool rendered_ = false;

 protected:
  // cartesian control variables
  SDL_FRect rect_ = {0, 0, 0, 0};
  float rotation_ = 0;
  SDL_Point rotation_center_ = {0, 0};
  // still cartesian control, but is a reference of the pervious movment off the
  // object
  Vector velocity_ = {0, 0};
  // all frames of all animations indexed by animation and frame number
  std::vector<std::vector<SDL_Surface*>> surfaces_;
  // animation control vars
  int state_ = 0;
  int frame_ = 0;
  int fps_ = 0;
  int last_step_ = 0;
  std::vector<int> state_que_ = {};
  virtual void Cast();

 public:
  GameObject(int x, int y, std::string name);
  ~GameObject();
  // location modiying and setting
  void SetPos(int x, int y);
  void Move(float x, float y);
  // calculate animation and retrun frame that needs to be rendered, used by
  // screen class to get surfaces to render
  SDL_Surface* GetSurface();
  // both below functions used by the main game loop in the input sections to
  // update what animation needs to be run, animations can either be run
  // immedatly(SetState()) and interupt the current one, or run after the
  // current animation is finished playing (QueState()).
  void Setstate(int state);
  void QueState(int state);
  // private acessors
  SDL_FRect GetRect();
  float GetRotation();
  SDL_Point* GetCenter();
  Vector GetVelocity();

 private:
};

#endif  // !GAME_OBJECT_H_
