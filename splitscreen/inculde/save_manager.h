// Copyright 2024 Hugh Thompson

#ifndef SPLITSCREEN_SAVE_MANAGER_H_
#define SPLITSCREEN_SAVE_MANAGER_H_

#include <vector>

class SaveManager {
 public:
  // unitialse
  SaveManager();
  // uninitalise and destruct in mem safe way
  ~SaveManager();
  // retuns the number of credits the robot has
  unsigned int GetCredits();
  // called if the robot clears the enitre ship, gives the robot a reward in
  // credits based on the avarege level of the robot's robots
  unsigned int Reward();
  // returns a 4 element vector of the guns stats given a type(0 based):
  // element 1 [0] - damage,
  // element 2 [1] - rate of fire,
  // element 3 [2] - bullet speed,
  // element 4 [3] - cost of upgrade.
  std::vector<int> GetGunStats(int type);
  // upgrade the weapon of the given type, retuns false if the robot does not
  // have enough credits to make the purchase, retuns true the the purcahes was
  // made sucessfully
  bool UpgradeWeapon(int type);
  // returns a 4 element vector of the robots stats given a robots id(1 based):
  // element 1 [0] - robot translational speed,
  // element 2 [1] - robot armour,
  // element 3 [2] - cost of speed upgrade,
  // element 4 [3] - cost of armour upgrade.
  std::vector<int> GetRobotStats(int robot);
  // upgrades a robot given the robot's id(1 based), and the elemet to upgarde,
  // with fasle for speed upgarde and true for armour upgrade.
  bool UpgradeRobot(bool upgrade, int robot);
  // money, bought full health
  // Repairs (decreses taken damge) of a robot gievn its id(1 based) if
  // condtions are met. if conditions (has sufficient funds and not going to
  // take the robot to negitiave damage) are met:
  // returns 0 for a sucessful transaction.
  // if not met:
  // returns 1 for insufficent funds present,
  // returns 2 for damage being too low
  int Repair(int robot);
  // writes the damage attined by the robot to the save, used by the mainb game
  // loop to save the robot's progress after completing or fleeing a ship
  void SetMenuDamage(int robot, int damage);
  // retuns the repair cost given a givens robot's id(1 based)
  int GetRepairCost(int robot);
  // retuns the damage of a givens robot's id(1 based)
  int GetDamage(int robot);
  // returns the mean level of both robot's upgrades, used as a multiplier to
  // increase difficulty
  int GetLevel();

 private:
  // The constants of the base guns, multipled by their respective levels to
  // attain the gun's stats. in the from of a 3 element array where:
  // [0] is the gun's base damage,
  // [1] is the gun's base rate of fire,
  // [2] is the gun's base bullet speed.
  const int kBaseGuns[5][3] = {
      {10, 500, 5}, {4, 200, 20}, {1, 100, 20}, {10, 600, 50}, {5, 300, 20}};
  // The constants of the base robots, multipled by their respective levels to
  // attain the robots's stats. in the from of a 2 element array where:
  // [0] is the robot's base speed,
  // [1] is the robot's base armour.
  const int kBaseRobot[2] = {200, 2};

  // 12 element vector of data loaded in from the save file where:
  // [0] is the amount of credits,
  // [1] is the damage of robot 1,
  // [2] is the level of robot 1's speed,
  // [3] is the level of robot 1's armour,
  // [4] is the damage of robot 2,
  // [5] is the level of robot 2's speed,
  // [6] is the level of robot 2's armour,
  // [7] is the level of gun 0,
  // [8] is the level of gun 1,
  // [9] is the level of gun 2,
  // [10] is the level of gun 3,
  // [11] is the level of gun 4.
  std::vector<int> data_;
};
#endif  // !SPLITSCREEN_SAVE_MANAGER_H_
