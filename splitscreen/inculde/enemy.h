#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>

#include "bullet.h"
#include "game_object.h"
#include "gun.h"
#include "ui_bar.h"
#include "vector.h"
#include "room.h"
#include "screen.h"

class Room;

//  a class represneting the enmeyies in the game
class Enemy : public GameObject {
 public:
  Enemy(int x, int y, int type, Room* room);
  // subtract from health, retuns true if health is below 0, false if not
  bool Damage(int amount);
  // calclate the direction the enemy wants to go in, interpritation of
  // alorightm at https://kidscancode.org/godot_recipes/3.x/ai/context_map/
  void AI(std::vector<std::vector<GameObject*>>* game_objects, int delta);
  UIBar* GetBar(Screen* screen);
  UIBar* CreateBar(Screen* screen);
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
  int health_ = 10;
  int max_health_ = 10;
  float speed_ = 80;
  int attack_range_ = 128;
  static const int num_rays_ = 8;
  Vector ray_directions_[num_rays_];
  int search_range_ = 128;
  float steer_force_ = 0.35;
  int Orientation(SDL_Point p1, SDL_Point p2, SDL_Point p3);
  UIBar* health_bar_ = nullptr;
  bool dead_ = false;
  Bullet* Attack(Vector location);
  Gun* gun_ = nullptr;
  float SetRotationFromVector(Vector rotation);
  Room* room_  = nullptr;
  std::vector<Screen*> on_screen_;
};

#endif  // !ENEMY_H_