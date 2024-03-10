#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <vector>

#include "SDL.h"
#include "game_object.h"

// object to control a window on screen, used by the main.cc to create a window,
// so use instantiate the object with a screen position (top left corner) and
// and then render objects to the screen using the render function that takes a
// vector of game objects as an argument. the screen camrea postion can be set
// to the location of a game object using the attach method.
class Screen {
 public:
 private:
  // window data
  SDL_Window* win_;
  SDL_Renderer* renderer_;
  int window_id_;
  // camera pos
  float x_ = 0;
  float y_ = 0;
  // object following
  GameObject* following_ = nullptr;
  std::pair<int, int> offset_ = {0, 0};

 public:
  Screen(int x, int y);
  ~Screen();
  // render all objects in veiw of camrea on screen, called in main method every
  // frame
  void Render(std::vector<GameObject*> game_ojbects);
  // bind camrea position of object position
  void Attach(GameObject* target);

 private:
};

#endif  // !SCREEN_H_