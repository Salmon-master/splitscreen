// Copyright 2024 Hugh Thompson

#include "main.h"

#include <SDL.h>
#include <SDL_TTF.h>

#include <iostream>
#include <stack>
#include <vector>

#include "door.h"
#include "enemy.h"
#include "game_object.h"
#include "gun.h"
#include "menu.h"
#include "menu_button.h"
#include "menu_image.h"
#include "menu_text.h"
#include "player.h"
#include "room.h"
#include "save_manager.h"
#include "screen.h"
#include "ship.h"
#include "ui_bar.h"
#include "wall.h"

bool run = true;
bool menu_run = true;
bool game_run = true;
SaveManager save;

#include "menu_items.h"

int main(int argc, char* args[]) {
  srand(time(0));
  // intlising SDL with window and renderer, errors are thrown if initilaides
  // incorrectly
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("error initializing SDL: %s\n", SDL_GetError());
  }
  menu->menu_items_ = {player1_image,
                       player2_image,
                       player1_gun1,
                       player1_gun2,
                       player1_gun3,
                       player1_gun4,
                       player1_gun5,
                       player2_gun1,
                       player2_gun2,
                       player2_gun3,
                       player2_gun4,
                       player2_gun5,
                       player1_overlay,
                       player1_upgrade_weapon,
                       player1_gun1_text,
                       player1_gun2_text,
                       player1_gun3_text,
                       player1_gun4_text,
                       player1_gun5_text,
                       player2_overlay,
                       player2_upgrade_weapon,
                       player2_gun1_text,
                       player2_gun2_text,
                       player2_gun3_text,
                       player2_gun4_text,
                       player2_gun5_text,
                       p1_speed,
                       p1_armour,
                       p1_upgrade_speed,
                       p1_upgrade_armour,
                       p1_repair,
                       p1_damagebar_bkg,
                       p1_damagebar,
                       p2_speed,
                       p2_armour,
                       p2_upgrade_speed,
                       p2_upgrade_armour,
                       p2_repair,
                       p2_damagebar_bkg,
                       p2_damagebar,
                       play,
                       title,
                       quit,
                       how,
                       credits};
  title->SetWrap(200);
  player1_gun1->SetColorDef({200, 0, 0, 255});
  player2_gun1->SetColorDef({200, 0, 0, 255});
  SDL_Event e;
  while (run) {
    // menu
    menu->Render();
    p1_damagebar->GetRect()->w = static_cast<int>(save.GetDamage(1) * 1.65f);
    p2_damagebar->GetRect()->w = static_cast<int>(save.GetDamage(2) * 1.65f);
    if (death_menu) {
      MenuText* dead = new MenuText(120, 25, "You Died", {255, 0, 0, 255}, 30);
      death_menu->menu_items_ = {dead};
      death_menu->Render();
      SDL_Delay(3000);
      delete death_menu;
      death_menu = nullptr;
    }
    if (reward_menu) {
      reward_menu->Render();
      SDL_Delay(3000);
      delete reward_menu;
      reward_menu = nullptr;
      credits->SetText("Cr: ¢" + std::to_string(save.GetCredits()));
    }
    menu_run = true;
    while (menu_run) {
      if (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          menu_run = false;
        }
        if (e.type == SDL_KEYDOWN) {
          if (e.key.keysym.sym == SDLK_ESCAPE) {
            menu_run = false;
          }
        }
      }
      SDL_Rect rect = *player1_overlay->GetRect();
      int x, y;
      SDL_GetMouseState(&x, &y);
      if (!(x > rect.x && x < rect.x + rect.w && y > rect.y &&
            y < rect.y + rect.h)) {
        Overlay1Hide();
      }
      SDL_Rect rect2 = *player2_overlay->GetRect();
      if (!(x > rect2.x && x < rect2.x + rect2.w && y > rect2.y &&
            y < rect2.y + rect2.h)) {
        Overlay2Hide();
      }
      menu->Render();
    }
    menu->ChangeVisability();

    if (game_run) {
      // creating windows
      Screen screen1(100, 250);
      Screen screen2(600, 250);
      UIBar* swtich_bar = nullptr;

      // game object intitilastion
      Player::new_id_ = 1;
      Player player1(&save, player_1_gun);
      Player player2(&save, player_2_gun);
      player1.SetPos(256, 256);
      player2.SetPos(256, 256);

      // adding objects to lists
      std::vector<std::vector<GameObject*>> game_objects = {{}, {}, {}, {}, {}};
      game_objects[kPlayers].push_back(&player1);
      game_objects[kPlayers].push_back(&player2);

      // ship
      Ship ship1(&game_objects, &save);

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
      int last = SDL_GetTicks64();
      const int frame_cap = 30;
      // main game loop
      while (game_run) {
        // inputs
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
          if (controlling->GetAttached()->active_) {
            Bullet* bullet = controlling->GetAttached()->GetGun()->Shoot();
            if (bullet) {
              game_objects[kBullets].push_back(bullet);
            }
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
            swtich_bar =
                controlling->AddBar(100, {45, 136, 255}, {150, 225, 200, 50},
                                    3 * (delta_time / 10));
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
        // death
        if (!player1.active_ && !player2.active_) {
          game_run = false;
          death_menu = new Menu(400, 80);
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
                game_run = false;
                save.SetMenuDamage(1, player1.GetDamage());
                save.SetMenuDamage(2, player2.GetDamage());
              }
              break;
            }
            if (rect.x > ship1.GetDimensions().first + 64 ||
                rect.y > ship1.GetDimensions().second + 64) {
              if (!ship1.MoveRoom(true)) {
                player1.SetPos(256, 256);
                player2.SetPos(256, 256);
              } else {
                game_run = false;
                int amount = save.Reward();
                MenuText* dead =
                    new MenuText(25, 25, "Reward: ¢" + std::to_string(amount), {255, 0, 0, 255}, 30);
                reward_menu = new Menu(dead->GetRect()->w + 50, 80);
                reward_menu->menu_items_ = {dead};
                save.SetMenuDamage(1, player1.GetDamage());
                save.SetMenuDamage(1, player2.GetDamage());
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
      for (GameObject* bullet : game_objects[kBullets]) {
        delete bullet;
      }
    }
    menu->ChangeVisability();
  }
  SDL_Quit();
  delete menu;
  return 0;
}
