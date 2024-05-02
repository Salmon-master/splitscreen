// Copyright 2024 Hugh Thompson

#include "main.h"

#include <iostream>
#include <stack>
#include <vector>

#include "SDL2/include/SDL.h"
#include "SDL2_ttf/include/SDL_TTF.h"

#include "door.h"
#include "enemy.h"
#include "game_object.h"
#include "gun.h"
#include "menu.h"
#include "menu_button.h"
#include "menu_image.h"
#include "menu_text.h"
#include "robot.h"
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
  // adding menuitems from menu_items.h
  menu->menu_items_ = {robot1_image,
                       robot2_image,
                       robot1_gun1,
                       robot1_gun2,
                       robot1_gun3,
                       robot1_gun4,
                       robot1_gun5,
                       robot2_gun1,
                       robot2_gun2,
                       robot2_gun3,
                       robot2_gun4,
                       robot2_gun5,
                       robot1_overlay,
                       robot1_upgrade_weapon,
                       robot1_gun1_text,
                       robot1_gun2_text,
                       robot1_gun3_text,
                       robot1_gun4_text,
                       robot1_gun5_text,
                       robot2_overlay,
                       robot2_upgrade_weapon,
                       robot2_gun1_text,
                       robot2_gun2_text,
                       robot2_gun3_text,
                       robot2_gun4_text,
                       robot2_gun5_text,
                       r1_speed,
                       r1_armour,
                       r1_upgrade_speed,
                       r1_upgrade_armour,
                       r1_repair,
                       r1_damagebar_bkg,
                       r1_damagebar,
                       r2_speed,
                       r2_armour,
                       r2_upgrade_speed,
                       r2_upgrade_armour,
                       r2_repair,
                       r2_damagebar_bkg,
                       r2_damagebar,
                       play,
                       title,
                       quit,
                       how,
                       credits};
  // setting speicilsed things about the items in menu_items.h
  title->SetWrap(200);
  robot1_gun1->SetColorDef({200, 0, 0, 255});
  robot2_gun1->SetColorDef({200, 0, 0, 255});
  menu->ChangeVisability();
  SDL_Event e;
  // full game loop
  while (run) {
    // menu
    // show menu
    menu->ChangeVisability();
    menu->Render();
    // updating bars
    r1_damagebar->GetRect()->w = static_cast<int>(save.GetDamage(1) * 1.65f);
    r2_damagebar->GetRect()->w = static_cast<int>(save.GetDamage(2) * 1.65f);
    if (death_menu) {
      // death popup
      MenuText* dead = new MenuText(120, 25, "You Died", {255, 0, 0, 255}, 30);
      death_menu->menu_items_ = {dead};
      death_menu->Render();
      SDL_Delay(3000);
      delete death_menu;
      death_menu = nullptr;
    }
    if (reward_menu) {
      // reward pop up
      reward_menu->Render();
      SDL_Delay(3000);
      delete reward_menu;
      reward_menu = nullptr;
      credits->SetText("Cr: \u00A2" + std::to_string(save.GetCredits()));
    }
    menu_run = true;
    while (menu_run) {
      if (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          // quit
          menu_run = false;
          game_run = false;
          run = false;
        }
        if (e.type == SDL_KEYDOWN) {
          if (e.key.keysym.sym == SDLK_ESCAPE) {
            // quit
            menu_run = false;
            game_run = false;
            run = false;
          }
        }
      }
      // hovering over the overlays
      SDL_Rect rect = *robot1_overlay->GetRect();
      int x, y;
      SDL_GetMouseState(&x, &y);
      if (!(x > rect.x && x < rect.x + rect.w && y > rect.y &&
            y < rect.y + rect.h)) {
        Overlay1Hide();
      }
      SDL_Rect rect2 = *robot2_overlay->GetRect();
      if (!(x > rect2.x && x < rect2.x + rect2.w && y > rect2.y &&
            y < rect2.y + rect2.h)) {
        Overlay2Hide();
      }
      // render
      menu->Render();
    }
    menu->ChangeVisability();

    if (game_run) {
      // creating windows
      Screen screen1(100, SDL_WINDOWPOS_CENTERED);
      Screen screen2(600, SDL_WINDOWPOS_CENTERED);
      UIBar* swtich_bar = nullptr;

      // robot intitilastion
      Robot::new_id_ = 1;
      Robot robot1(&save, robot_1_gun);
      Robot robot2(&save, robot_2_gun);
      robot1.SetPos(256, 256);
      robot2.SetPos(256, 256);

      // game objects list, indexed by type
      std::vector<std::vector<GameObject*>> game_objects = {{}, {}, {}, {}, {}};
      // adding objects to lists
      game_objects[kRobots].push_back(&robot1);
      game_objects[kRobots].push_back(&robot2);

      // ship
      Ship shir1(&game_objects, &save);

      // assign robots to screens
      screen2.Attach(&robot2);
      screen1.Attach(&robot1);
      // game vars
      Screen* controlling = &screen1;
      int swich_cooldown = 0;

      // keyboard inputs
      const Uint8* key_state = SDL_GetKeyboardState(NULL);

      // delta time vars
      int delta_time = 0;
      int last = SDL_GetTicks64();
      const int frame_cap = 30;
      // game loop
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
          // shoot
          if (controlling->GetAttached()->active_) {
            Bullet* bullet = controlling->GetAttached()->GetGun()->Shoot();
            if (bullet) {
              game_objects[kBullets].push_back(bullet);
            }
          }
        }
        if (key_state[SDL_SCANCODE_V] == 1) {
          // switching robots
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
        if (!robot1.active_ && !robot2.active_) {
          game_run = false;
          death_menu = new Menu(400, 80);
        }
        // room advancing / ship completion / fleeing
        for (GameObject* obj : game_objects[kRobots]) {
          Robot* robot = dynamic_cast<Robot*>(obj);
          if (robot) {
            SDL_FRect rect = robot->GetRect();
            if (rect.x < 0 || rect.y < 0) {
              if (!shir1.MoveRoom(false)) {
                robot1.SetPos(shir1.GetDimensions().first - 256,
                               shir1.GetDimensions().second - 256);
                robot2.SetPos(shir1.GetDimensions().first - 256,
                               shir1.GetDimensions().second - 256);
              } else {
                game_run = false;
                save.SetMenuDamage(1, robot1.GetDamage());
                save.SetMenuDamage(2, robot2.GetDamage());
              }
              break;
            }
            if (rect.x > shir1.GetDimensions().first + 64 ||
                rect.y > shir1.GetDimensions().second + 64) {
              if (!shir1.MoveRoom(true)) {
                robot1.SetPos(256, 256);
                robot2.SetPos(256, 256);
              } else {
                game_run = false;
                int amount = save.Reward();
                MenuText* dead = new MenuText(
                    25, 25, "Reward: \u00A2" + std::to_string(amount),
                    {255, 0, 0, 255}, 30);
                reward_menu = new Menu(dead->GetRect()->w + 50, 80);
                reward_menu->menu_items_ = {dead};
                save.SetMenuDamage(1, robot1.GetDamage());
                save.SetMenuDamage(1, robot2.GetDamage());
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
        // switching robots
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
      // clean up
      for (GameObject* bullet : game_objects[kBullets]) {
        delete bullet;
      }
    }
  }
  SDL_Quit();
  delete menu;
  return 0;
}
