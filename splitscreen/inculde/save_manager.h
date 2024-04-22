#ifndef SAVE_MANAGER_H_
#define SAVE_MANAGER_H_

#include <vector>

class SaveManager {
 public:
  SaveManager();
  ~SaveManager();
  unsigned int GetCredits();
  unsigned int Reward();
  // DAM, ROF, SPE, cost
  std::vector<int> GetGunStats(int type);
  bool UpgradeWeapon(int type);
  // speed, Armour, cost
  std::vector<int> GetPlayerStats(int player);
  // false for speed, true for armour
  bool UpgradePlayer(bool upgrade, int player);
  // money, bought full health
  int Repair(int player);
  void SetMenuDamage(int player, int damage);
  int GetRepairCost(int player);
  int GetDamage(int player);
  int GetLevel();

 private:
  // DAM, ROF, SPE
  const int kBaseGuns[5][3] = {{10, 500, 5}, {4, 200, 20}, {1, 100, 20}, {10, 600, 50}, {5, 300, 20}};
  // speed, Armour
  const int kBasePlayer[2] = {200, 2};
  std::vector<int> data_;

};
#endif  // !SAVE_MANAGER_H_
