// Copyright 2024 Hugh Thompson

#ifndef SPLITSCREEN_ROBOT_H_
#define SPLITSCREEN_ROBOT_H_

#include "game_object.h"
#include "gun.h"
#include "save_manager.h"
#include "ui_bar.h"

// foward declations
class Gun;
// robot class, used by the game to represnt a robot within the game
class Robot : public GameObject {
 private:
  // translation speed, set in constructor
  int speed_ = 200;
  // rotation speed of the robot, always 1/100000 of the translational speed
  float rotation_speed_ = 0.002;
  // the gun the robot is holding, assigned in constructor
  Gun* gun_ = nullptr;
  // how much damage the robot has incured
  int damage_ = 0;
  // the UI bar of how mcuh damage this robot has taken, assigned in consturctor
  UIBar* damage_bar_ = nullptr;
  // armour value, reduces damage taken, from 0 to 100 as a percentage of damage
  // reduced
  int armour_ = 0;
  // unique identification number used to load in stats, based off what order
  // the objects are constructed in. e.g first robot has id of 1, next intilise
  // has id of 2 ect...
  // initilised in constructor
  int id_;

 public:
  // initise the robot with what gun they are holding and a reference to the
  // current save.
  Robot(SaveManager* save, int gun);
  // destruct and unitilise in memory safe way.
  ~Robot();
  // convert the speed(magnitude) and rotation(angle) into x and y components to
  // feed to parent move function, and then move the robot.(smoothed with delta
  // time)
  void Step(int delta_time);
  // change the rotation of the robot, true is colcokwise, false is
  // anticlockwise, will rotate the robot based upon the rotation speed and is
  // smoothed by delta time.
  void Rotate(bool direction, int delta_time);
  // retuns a pointer to the current gun the robot is weilding
  Gun* GetGun();
  // called when the robot receives damage, retuns wether or not the robot is
  // alive.
  bool Damage(int amount);
  UIBar* GetBar();
  // if the robot has been disabled(damgage == 100), then it will not be active
  // (fasle), so it cannot move or shoot
  bool active_ = true;
  // statitc variable used to assign ids to robots
  inline static int new_id_;
  int GetDamage();
};

#endif  // !SPLITSCREEN_ROBOT_H_
