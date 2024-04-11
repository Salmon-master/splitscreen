// Copyright 2024 Hugh Thompson

#include "main.h"

#include <SDL.h>

#include <iostream>
#include <stack>
#include <vector>

#include "door.h"
#include "enemy.h"
#include "game_object.h"
#include "gun.h"
#include "player.h"
#include "room.h"
#include "screen.h"
#include "ship.h"
#include "ui_bar.h"
#include "wall.h"

int main(int argc, char* args[]) {
  srand(time(0));
  bool run = true;
  // intlising SDL with window and renderer, errors are thrown if initilaides
  // incorrectly
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("error initializing SDL: %s\n", SDL_GetError());
  }
  // creating windows
  Screen screen1(100, 250);
  Screen screen2(600, 250);
  SDL_Event e;
  UIBar* swtich_bar = nullptr;

  // game object intitilastion
  Player player1;
  Player player2;
  player1.SetPos(256, 256);
  player2.SetPos(256, 256);

  // adding objects to lists
  std::vector<std::vector<GameObject*>> game_objects = {{}, {}, {}, {}, {}};
  game_objects[kPlayers].push_back(&player1);
  game_objects[kPlayers].push_back(&player2);

  // testing code
  Ship ship1(&game_objects);
  // eniemies
  // assign players to screens
  screen2.Attach(&player2);
  screen1.Attach(&player1);
  // game vars
  Screen* controlling = &screen1;
  int swich_cooldown = 0;

  const Uint8* key_state = SDL_GetKeyboardState(NULL);

  // delta time vars
  int delta_time = 0;
  int last = 0;
  const int frame_cap = 30;
  // main game loop
  while (run) {
    // inputs
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        run = false;
      }
      if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_SPACE) {
          Bullet* bullet = controlling->GetAttached()->GetGun()->Shoot();
          if (bullet) {
            game_objects[kBullets].push_back(bullet);
          }
        }
      }
    }
    SDL_PumpEvents();
    if (key_state[SDL_SCANCODE_W] == 1) {
      controlling->GetAttached()->Step(delta_time);
    }
    if (key_state[SDL_SCANCODE_A] == 1) {
      controlling->GetAttached()->Rotate(0, delta_time);
    }
    if (key_state[SDL_SCANCODE_D] == 1) {
      controlling->GetAttached()->Rotate(1, delta_time);
    }
    if (key_state[SDL_SCANCODE_SPACE] == 1) {
      Bullet* bullet = controlling->GetAttached()->GetGun()->Shoot();
      if (bullet) {
        game_objects[kBullets].push_back(bullet);
      }
    }
    if (key_state[SDL_SCANCODE_V] == 1) {
      if (swtich_bar) {
        swtich_bar->ChangeValue(2 * (delta_time / 10));
        std::cout << swtich_bar->GetValue() << std::endl;
        if (swtich_bar->Full()) {
          controlling->RemoveBar(swtich_bar);
          swtich_bar = nullptr;
          swich_cooldown = 1000;
          if (controlling == &screen1) {
            controlling = &screen2;
          } else {
            controlling = &screen1;
          }
        }
      } else if (swich_cooldown <= 0) {
        swtich_bar = controlling->AddBar(
            100, {45, 136, 255}, {150, 225, 200, 50}, 3 * (delta_time / 10));
      }
    }

    // game logic

    // unlocking of doors
    if (game_objects[kEnemies].size() == 0) {
      Door* door = dynamic_cast<Door*>(game_objects[kDoors].back());
      if (!door->GetState()) {
        door->Open();
      }
    }

    // level advancing
    for (GameObject* obj : game_objects[kPlayers]) {
      Player* player = dynamic_cast<Player*>(obj);
      if (player) {
        SDL_FRect rect = player->GetRect();
        if (rect.x < 0 || rect.y < 0) {
          if (!ship1.MoveRoom(false)) {
            player1.SetPos(ship1.GetDimensions().first - 256,
                           ship1.GetDimensions().second - 256);
            player2.SetPos(ship1.GetDimensions().first - 256,
                           ship1.GetDimensions().second - 256);
          } else {
            run = false;
          }
          break;
        }
        if (rect.x > ship1.GetDimensions().first + 64 ||
            rect.y > ship1.GetDimensions().second + 64) {
          if (!ship1.MoveRoom(true)) {
            player1.SetPos(256, 256);
            player2.SetPos(256, 256);
          } else {
            run = false;
          }
          break;
        }
      } else {
        std::cout << "incorrect type allocated to list" << std::endl;
      }
    }

    // enemy AI
    for (GameObject* obj : game_objects[kEnemies]) {
      Enemy* enemy = dynamic_cast<Enemy*>(obj);
      if (enemy) {
        enemy->AI(&game_objects, delta_time);
      }
    }
    // wall collision
    for (GameObject* obj : game_objects[kWalls]) {
      Wall* wall = dynamic_cast<Wall*>(obj);
      if (wall) {
        wall->Collision(controlling->GetAttached());
        wall->rendered_ = false;
      } else {
        std::cout << "incorrect type allocated to list" << std::endl;
      }
    }
    // door collision
    for (GameObject* obj : game_objects[kDoors]) {
      Door* door = dynamic_cast<Door*>(obj);
      if (door) {
        bool colliding = door->Collide(controlling->GetAttached());
        door->rendered_ = false;
      } else {
        std::cout << "incorrect type allocated to list" << std::endl;
      }
    }
    // switching players
    if (swich_cooldown > 0) {
      swich_cooldown -= delta_time;
    }
    if (swtich_bar) {
      swtich_bar->ChangeValue(-1 * (delta_time / 10));
      if (swtich_bar->GetValue() <= 0) {
        controlling->RemoveBar(swtich_bar);
        swtich_bar = nullptr;
        swich_cooldown = 1000;
      }
    }
    // bullets
    std::stack<Bullet*> to_remove;
    for (GameObject* obj : game_objects[kBullets]) {
      Bullet* bullet = dynamic_cast<Bullet*>(obj);
      if (bullet) {
        if (bullet->Update(&game_objects)) {
          to_remove.push(bullet);
        }
      } else {
        std::cout << "incorrect type allocated to list" << std::endl;
      }
    }
    while (!to_remove.empty()) {
      std::vector<GameObject*>* bullets = &game_objects[kBullets];
      bullets->erase(
          std::remove(bullets->begin(), bullets->end(), to_remove.top()),
          bullets->end());
      delete to_remove.top();
      to_remove.pop();
    }

    // rendering
    screen1.Render(game_objects);
    screen2.Render(game_objects);

    // delta time calculation
    delta_time = SDL_GetTicks64() - last;
    last = SDL_GetTicks64();

    // frame capping
    if (delta_time < pow(frame_cap * 1000, -1)) {
      SDL_Delay(pow(frame_cap * 1000, -1) - delta_time);
    }
  }
  SDL_Quit();
  return 0;
}
