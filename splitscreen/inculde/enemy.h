#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>

#include "game_object.h"
#include "vector.h"
#include "ui_bar.h"

//  a class represneting the enmeyies in the game
class Enemy : public GameObject {
 public:
  Enemy(int x, int y, int type);
  // subtract from health, retuns true if health is below 0, false if not
  bool Damage(int amount);
  // calclate the direction the enemy wants to go in, interpritation of alorightm
  // at https://kidscancode.org/godot_recipes/3.x/ai/context_map/
  void AI(std::vector<GameObject*> game_objects, int delta);
  UIBar* GetBar();
  UIBar* CreateBar();
  ~Enemy();

 private:
  // helper function to AI, caculates the interest array and returns it given a
  // direction of interest
  std::vector<float> SetInterest(Vector direction);
  // helper function to AI, caculates the danger array and returns it given a
  // list of game objects that are dangerous
  std::vector<float> SetDanger(std::vector<GameObject*> objects);
  // checks if two line segments intersect, used mainly for ray casting , line
  // segments are given by two sets points(start and end) of each line
  // line 1 = p1-q1
  // line 2 = p2-q2
  bool Intersect(SDL_Point p1, SDL_Point q1, SDL_Point p2, SDL_Point q2);
  int health_ = 100;
  int max_health_ = 100;
  int speed_ = 60;
  static const int num_rays_ = 16;
  Vector ray_directions_[num_rays_];
  int search_range_ = 128;
  float steer_force_ = 0.2;
  int Orientation(SDL_Point p1, SDL_Point p2, SDL_Point p3);
  UIBar* health_bar_ = nullptr;
  bool dead_= false;
};

#endif  // !ENEMY_H_