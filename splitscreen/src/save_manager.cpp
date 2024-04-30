// Copyright 2024 Hugh Thompson

#include "save_manager.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

SaveManager::SaveManager() {
  // open file
  std::ifstream data("assets/save.txt");
  if (!data.good()) {
    std::cout << "save file not found, please copy the backup save form "
                 "assets/backup into the assets folder"
              << std::endl;
  }
  std::string line;
  // read data into data variable line by line
  while (getline(data, line)) {
    data_.push_back(std::stoi(line));
  }
  if (data_.size() != 12) {
    std::cout << "save file corrupted, please copy the backup save from "
                 "assets/backup into the assets folder"
              << std::endl;
    std::abort();
  }
  // close file
  data.close();
}

SaveManager::~SaveManager() {
  // delete old save
  std::remove("assets/save.txt");
  // create and open new save file
  std::ofstream data("assets/save.txt");
  // input data into file from data_
  for (int i : data_) {
    data << std::to_string(i) << "\n";
  }
  // clsoe file
  data.close();
}

unsigned int SaveManager::GetCredits() { return data_[0]; }

unsigned int SaveManager::Reward() {
  // calculation of reward based on player level
  float avrgae_level = (data_[2] + data_[3] + data_[5] + data_[6]) / 4.0f;
  int reward = avrgae_level * 100.0f;
  data_[0] += reward;
  return reward;
}

std::vector<int> SaveManager::GetGunStats(int type) {
  float level = data_[7 + type];
  float multiplier = level / 10;
  // exponential cost based off level
  int cost = 10 * pow(1.1, level);
  // linear incrase in upgrdae
  std::vector<int> stats = {
      static_cast<int>(static_cast<float>(kBaseGuns[type][0]) *
                       (1.0f + multiplier)),
      kBaseGuns[type][1], kBaseGuns[type][2], cost};
  return stats;
}

bool SaveManager::UpgradeWeapon(int type) {
  int cost = GetGunStats(type)[3];
  bool bought = false;
  // if suffuicent funds
  if (cost <= data_[0]) {
    data_[7 + type] += 1;
    data_[0] -= cost;
    bought = true;
  }
  return bought;
}

std::vector<int> SaveManager::GetPlayerStats(int player) {
  // setting index base off robot inputted
  int index = 2;
  if (player == 2) {
    index = 5;
  }
  float speed_mul = static_cast<float>(data_[index]) / 100.0f;
  float armour_mul = static_cast<float>(data_[index + 1]) / 10.0f;
  int speed_cost = 100 * pow(1.1, data_[index]);
  int armour_cost = 100 * pow(1.1, data_[index + 1]);
  return {
      static_cast<int>(static_cast<float>(kBasePlayer[0]) * (1.0f + speed_mul)),
      static_cast<int>(static_cast<float>(kBasePlayer[1]) *
                       (1.0f + armour_mul)),
      speed_cost, armour_cost};
}

bool SaveManager::UpgradePlayer(bool upgrade, int player) {
  // setting index base off robot inputted
  int index = 2;
  if (player == 2) {
    index = 5;
  }
  int cost = GetPlayerStats(player)[2 + upgrade];
  bool bought = false;
  if (cost <= data_[0]) {
    data_[index + upgrade] += 1;
    data_[0] -= cost;
    bought = true;
  }
  return bought;
}

int SaveManager::Repair(int player) {
  // setting index base off robot inputted
  int index = 1;
  if (player == 2) {
    index = 4;
  }
  int cost = GetRepairCost(player);
  int bought = 0;
  if (cost <= data_[0]) {
    bought = 2;
    if (data_[index] >= 5) {
      data_[index] -= 5;
      data_[0] -= cost;
      bought = 1;
    }
  }
  return bought;
}

void SaveManager::SetMenuDamage(int player, int damage) {
  // setting index base off robot inputted
  int index = 1;
  if (player == 2) {
    index = 4;
  }
  data_[index] = damage;
}

int SaveManager::GetRepairCost(int player) {
  // setting index base off robot inputted
  int index = 1;
  if (player == 2) {
    index = 4;
  }
  int avg_level = (data_[index + 1] + data_[index + 2]) / 2;
  int cost = 10 * pow(1.1, avg_level);
  if (data_[index] == 0) {
    cost *= 10;
  }
  return cost;
}

int SaveManager::GetDamage(int player) {
  // setting index base off robot inputted
  int index = 1;
  if (player == 2) {
    index = 4;
  }
  return data_[index];
}

int SaveManager::GetLevel() {
  // calculates the mean level of the robots
  return (data_[2] + data_[3] + data_[5] + data_[6]) / 4;
}
