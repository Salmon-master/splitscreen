// Copyright 2024 Hugh Thompson

#pragma once

#include <SDL.h>
// enumerated indexes of the game object types in gameobjects
enum Types { kPlayers = 0, kWalls = 1, kEnemies = 2, kBullets = 3, kDoors = 4 };

const SDL_Color kNullColor = {NULL, NULL, NULL};
