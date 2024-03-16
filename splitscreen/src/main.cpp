#include <SDL.h>

#include <iostream>
#include <vector>
#include <stack>

#include "game_object.h"
#include "player.h"
#include "screen.h"
#include "wall.h"
#include "room.h"
#include "ui_bar.h"
#include "gun.h"


int main(int argc, char* args[]) {
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
  Player* player1 = new Player;
  Player* player2 = new Player;
  player1->SetPos(256, 256);
  player2->SetPos(256, 256);


  // testing code
  Room room;
  Gun gun1(0, player1);

  // adding objects to lists
  std::vector<GameObject*> game_objects = {player1, player2};
  std::vector<Wall*> walls = room.GetWalls();
  for (int i = 0; i < walls.size() - 1; i++) {
    game_objects.push_back(walls[i]);
  }
  std::vector<Bullet*> bullets;

  // assign players to screens
  screen2.Attach(player2);
  screen1.Attach(player1);
  // game vars 
  Screen* controlling = &screen1;   
  int swich_cooldown = 0;

  const Uint8* key_state = SDL_GetKeyboardState(NULL);

  // delta time vars
  int delta_time = 0;
  int last = 0;
  const int frame_cap = 30;

  // mian game loop
  while (run) {
    // inputs
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        run = false;
      }
      if (e.type == SDL_KEYDOWN) {
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
        bullets.push_back(bullet);
        game_objects.push_back(bullet);
      }
    }
    if (key_state[SDL_SCANCODE_V] == 1) {
      if (swtich_bar) {
        swtich_bar->ChangeValue(2 * (delta_time / 10));
        if (swtich_bar->Full()) {
          swtich_bar->SetValue(0);
          controlling->RemoveBar(swtich_bar);
          swtich_bar = nullptr;
          swich_cooldown = 1000;
          if (controlling == &screen1) {
            controlling = &screen2;
          } else {
            controlling = &screen1;
          }
        }
      } else if(swich_cooldown <= 0) {
        swtich_bar = controlling->AddBar(
            100, {45, 136, 255}, {150, 225, 200, 50}, 3 * (delta_time / 10));
      }
    }


    // game logic
    for (Wall* wall : walls) {
      wall->Collision(controlling->GetAttached());
      wall->rendered_ = false;
    }
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

    std::stack<Bullet*> to_remove;
    for (Bullet* bullet : bullets) {
      if (bullet->Update(game_objects)) {
        to_remove.push(bullet);
        game_objects.erase(
            std::remove(game_objects.begin(), game_objects.end(), bullet),
            game_objects.end());
      }
    }
    while (!to_remove.empty()) {
      bullets.erase(
          std::remove(bullets.begin(), bullets.end(), to_remove.top()),
          bullets.end());
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
  // destruct to avoid memory leaks and uninitlise
  for (GameObject* obj : game_objects) {
    delete obj;
  }
  screen1.~Screen();
  screen2.~Screen();
  SDL_Quit();
  return 0;
}