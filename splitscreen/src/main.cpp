#include <SDL.h>

#include <iostream>
#include <vector>

#include "game_object.h"
#include "player.h"
#include "screen.h"
#include "wall.h"
#include "room.h"

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

  // game object intitilastion
  Player* player1 = new Player;
  Player* player2 = new Player;
  player1->SetPos(256, 256);
  player2->SetPos(256, 256);

  // testing code
  Room room;

  // adding objects to lists
  std::vector<GameObject*> game_objects = {player1, player2};
  std::vector<Wall*> walls = room.GetWalls();
  for (int i = 0; i < walls.size() - 1; i++) {
    game_objects.push_back(walls[i]);
  }

  // assign players to screens
  screen2.Attach(player2);
  screen1.Attach(player1);
  // game vars 
  Player* controlling = player1; 

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
        if (e.key.keysym.sym == SDLK_v) {
          if (controlling == player1) {
            controlling = player2;
          } else {
            controlling = player1;
          }
        }
      }
    }
    SDL_PumpEvents();
    if (key_state[SDL_SCANCODE_W] == 1) {
      controlling->Step(delta_time);
    }
    if (key_state[SDL_SCANCODE_A] == 1) {
      controlling->Rotate(0, delta_time);
    }
    if (key_state[SDL_SCANCODE_D] == 1) {
      controlling->Rotate(1, delta_time);
    }


    // game logic
    for (Wall* wall : walls) {
      wall->Collision(controlling);
      wall->rendered_ = false;
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