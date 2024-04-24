// Copyright 2024 Hugh Thompson

#pragma once

#include "SDL2/include/SDL.h"

// enumerated indexes of the game object types in gameobjects
enum Types { kPlayers = 0, kWalls = 1, kEnemies = 2, kBullets = 3, kDoors = 4 };

// a constasnt for the use of setting a null color
const SDL_Color kNullColor = {NULL, NULL, NULL, NULL};
