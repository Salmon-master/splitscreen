// Copyright 2024 Hugh Thompson

#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>

#include "bullet.h"
#include "game_object.h"
#include "gun.h"
#include "room.h"
#include "screen.h"
#include "ui_bar.h"
#include "vector.h"
#include "save_manager.h"

class Room;

//  a class represneting the enemies in the game
class Enemy : public GameObject {
 public:
  Enemy(int x, int y, int type, Room* room, SaveManager* save);
  // subtract from health, retuns true if health is below 0, false if not
  bool Damage(int amount);
  // calclate the direction the enemy wants to go in, interpritation of
  // alorightm at https://kidscancode.org/godot_recipes/3.x/ai/context_map/
  void AI(std::vector<std::vector<GameObject*>>* game_objects, int delta);
  UIBar* GetBar();
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
  // the health of teh enemy
  int health_ = 10;
  // the staring health of the enemy
  int max_health_ = 10;
  // movement speed
  float speed_ = 80;
  // range of attack
  int attack_range_ = 128;
  // Used in AI and associated functions to do AI
  static const int kNumRays = 8;
  Vector ray_directions_[kNumRays];
  int search_range_ = 128;
  float steer_force_ = 0.35;
  // retuns the orenatation of three points, could be either colcokwise(1),
  // anitclockwise(2) or colinear(0)
  int Orientation(SDL_Point p1, SDL_Point p2, SDL_Point p3);
  // a pointer to the enemies health bar, initiaised in constructor
  UIBar* health_bar_ = nullptr;
  // wether or not the enenmy is alive
  bool dead_ = false;
  // Deals with the enemies attack mechanics
  Bullet* Attack(Vector location);
  // reference to the wepon used by this enemy, initiased in constructor
  Gun* gun_ = nullptr;
  // returns a rotation is radians from the vertical (from 0 to 2PI Rad) given a
  // vector.
  float SetRotationFromVector(Vector rotation);
  // a pointer to the room which the enemy is in, initised in consctor
  Room* room_ = nullptr;
  // base enemy stats
  const int kEnemyStats[5][3] = {
      {30, 64, 20}, {60, 128, 10}, {85, 96, 5}, {50, 256, 10}, {60, 128, 10}};
  int type_;
};

#endif  // !ENEMY_H_
