// Copyright 2024 Hugh Thompson

#include "door.h"

Door::Door(int x, int y) : GameObject(x, y, "door") { open_ = false; }

bool Door::Open() {
  // reverse the open_ var 
  open_ = !open_;
  return open_;
}

bool Door::Collide(GameObject* obj) {
  bool rv = false;
  // if not rendered, no point in wasting memory, and if closed
  if (rendered_ && !open_) {
    std::pair<bool, bool> move = {false, false};
    Vector diff = {(obj->GetCenter()->x + obj->GetRect().x) -
                       (rect_.x + rotation_center_.x),
                   (obj->GetCenter()->y + obj->GetRect().y) -
                       (rect_.y + rotation_center_.y)};
    float circle_distance_x = abs(diff.x);
    float circle_distance_y = abs(diff.y);
    int r = obj->GetCenter()->x;

    // checking if the obj is overlapping
    if (circle_distance_x < (rect_.w / 2 + r)) {
      if (circle_distance_y < (rect_.h / 2 + r)) {
        if (circle_distance_x <= (rect_.w / 2)) {
          // on y axis
          rv = true;
          move.second = true;
        }
        if (circle_distance_y <= (rect_.h / 2)) {
          // on x axis
          rv = true;
          move.first = true;
        }
        float cornerdistance_sq = pow((circle_distance_x - rect_.w / 2), 2) +
                                  pow((circle_distance_y - rect_.h / 2), 2);
        // checking overlapping on corner
        if (cornerdistance_sq <= pow(r, 2)) {
          rv = true;
          // only cancel out velocity moving towards object
          move.first = (obj->GetVelocity().x / abs(obj->GetVelocity().x) !=
                        diff.x / abs(diff.x));
          move.second = (obj->GetVelocity().y / abs(obj->GetVelocity().y) !=
                         diff.y / abs(diff.y));
        }
      }
    }
    // canceling out motion according to collision
    obj->Move(obj->GetVelocity().x * -1 * move.first,
              obj->GetVelocity().y * -1 * move.second);
  }
  return rv;
}

bool Door::GetState() { return open_; }
