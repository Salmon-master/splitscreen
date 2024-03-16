#include "game_object.h"

#include <filesystem>

void GameObject::Cast() {}

GameObject::GameObject(int x, int y, std::string name) {
  // setting posistion
  rect_.x = x;
  rect_.y = y;

  // image loader, finds folder based off _name, loads the assets into a 2d aray
  // of frames in animations and frame numbers.
  std::string path = "assets/" + name + "/";
  int index_pointer = 0;
  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    std::string animation_path = (entry.path()).string() + "/";
    std::vector<SDL_Surface*> empty;
    surfaces_.emplace_back(empty);
    for (const auto& animation_entry :
         std::filesystem::directory_iterator(animation_path)) {
      SDL_Surface* surface_buffer =
          IMG_Load(((animation_entry.path()).string()).c_str());
      surfaces_[index_pointer].emplace_back(surface_buffer);
    }
    index_pointer += 1;
  }

  // setting dimensions
  rect_.w = surfaces_[0][0]->w;
  rect_.h = surfaces_[0][0]->h;

  // rotation center default
  rotation_center_.x = (rect_.w / 2);
  rotation_center_.y = (rect_.h / 2);
}

void GameObject::SetPos(int x, int y) {
  // update postion
  rect_.x = x;
  rect_.y = y;
  // set velocity
  velocity_ = {0, 0};
}

void GameObject::Move(float x, float y) {
  // update postion
  rect_.x += x;
  rect_.y += y;
}

SDL_Surface* GameObject::GetSurface() {
  // animation calcuation, if there is an animation update it based off the del
  // t since last this function called, and chages animation to next in que if
  // applicple when animaion repeats.
  if (surfaces_[state_].size() != 1) {
    int ticks = (int)SDL_GetTicks64();
    int delta_time = ticks - last_step_;
    if (delta_time != 0) {
      int mspf = std::pow(((float)fps_ / 1000), -1);
      int step = delta_time / mspf;
      if (step >= 1) {
        frame_ += step;
        if (step > surfaces_[state_].size() - 1) {
          frame_ = 0;
          if (state_que_.size() != 0) {
            state_ = state_que_.back();
            state_que_.pop_back();
          }
        }
      }
    }
  }
  return surfaces_[state_][frame_];
}

void GameObject::Setstate(int state) { state_ = state; }

void GameObject::QueState(int state) {
  state_que_.insert(state_que_.begin(), state);
}

SDL_FRect GameObject::GetRect() { return rect_; }

float GameObject::GetRotation() { return rotation_; }

SDL_Point* GameObject::GetCenter() { return &rotation_center_; }

Vector GameObject::GetVelocity() { return velocity_; }
