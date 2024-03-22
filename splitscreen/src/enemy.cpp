#include "enemy.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "wall.h"

Enemy::Enemy(int x, int y, int type)
    : GameObject(x, y, "enemy_" + std::to_string(type)) {
  SetPos(x, y);
  for (size_t i = 0; i < num_rays_; i++) {
    float angle = (i * 2 * M_PI) / num_rays_;
    ray_directions_[i] = {cos(angle), sin(angle)};
  }
  rotation_center_.y = (rect_.h - 28);
}

bool Enemy::Damage(int amount) {
  bool rv = false;
  health_ -= amount;
  if (health_ <= 0) {
    rv = true;
    dead_ = true;
    health_bar_->SetValue(0);
  } else {
    health_bar_->SetValue(health_);
  }
  return rv;
}

void Enemy::AI(std::vector<GameObject*> game_objects, int delta) {
  if (!dead_) {
    if (delta == 0) {
      delta = 1;
    }
    std::vector<GameObject*> danger_objects;
    std::vector<GameObject*> interest_objects;
    for (GameObject* obj : game_objects) {
      Player* player_type = dynamic_cast<Player*>(obj);
      Bullet* bullet_type = dynamic_cast<Bullet*>(obj);
      Wall* wall_type = dynamic_cast<Wall*>(obj);
      Enemy* enemy_type = dynamic_cast<Enemy*>(obj);
      if (wall_type) {
        if (Vector{(obj->GetRect().x + obj->GetCenter()->x) -
                       (rect_.x + rotation_center_.x),
                   (obj->GetRect().y + obj->GetCenter()->y) -
                       (rect_.y + rotation_center_.y)}
                .Norm() < search_range_) {
          danger_objects.push_back(obj);
        }
      }
      if (player_type) {
        if (Vector{obj->GetRect().x - rect_.x, obj->GetRect().y - rect_.y}
                .Norm() <= search_range_ * 4) {
          interest_objects.push_back(obj);
        }
      }
    }
    std::vector<float> interest(num_rays_);
    if (!interest_objects.empty()) {
      interest =
          SetInterest(Vector{interest_objects[0]->GetRect().x - rect_.x,
                             interest_objects[0]->GetRect().y - rect_.y});
    }
    std::vector<float> danger = SetDanger(danger_objects);
    for (int i = 0; i < num_rays_; i++) {
      if (danger[i] != 0.0f) {
        interest[i] = danger[i];
      }
    }
    Vector chosen_dir = {0, 0};
    for (int i = 0; i < num_rays_; i++) {
      chosen_dir.x += interest[i] * ray_directions_[i].x;
      chosen_dir.y += interest[i] * ray_directions_[i].y;
    }
    Vector steer = {((chosen_dir.Normalised().x) - velocity_.x) * steer_force_,
                    ((chosen_dir.Normalised().y) - velocity_.y) * steer_force_};
    Vector chosen_direction = {velocity_.x + steer.x, velocity_.y + steer.y};
    Move(((chosen_direction.Normalised().x * speed_ * delta) / 1000),
         ((chosen_direction.Normalised().y * speed_ * delta) / 1000));
    velocity_ = {(chosen_direction.Normalised().x * speed_ * delta) / 1000,
                 (chosen_direction.Normalised().y * speed_ * delta) / 1000};

    float new_rotation = atan(velocity_.y / velocity_.x);
    if (chosen_direction.y > 0) {
      if (chosen_direction.x < 0) {
        new_rotation += M_PI;
      } else {
        new_rotation += M_PI * 2;
      }
    } else {
      if (chosen_direction.x < 0) {
        new_rotation += M_PI;
      }
    }
    if (new_rotation < 0) {
      new_rotation += M_PI * 2;
    }
    new_rotation += M_PI / 2;
    if (new_rotation >= 2 * M_PI) {
      new_rotation -= 2 * M_PI;
    }
    if (abs(new_rotation - rotation_) > M_PI) {
      float amount =
          ((2 * M_PI) - abs(new_rotation - rotation_)) * steer_force_ / 5;
      if (rotation_ > new_rotation) {
        rotation_ += amount;
      } else {
        rotation_ -= amount;
      }
    } else {
      rotation_ += ((new_rotation - rotation_) * steer_force_ / 5);
    }
    if (rotation_ >= 2 * M_PI) {
      rotation_ -= 2 * M_PI;
    }
    if (rotation_ <= 0) {
      rotation_ += 2 * M_PI;
    }
  }
}

UIBar* Enemy::GetBar() { return health_bar_; }

UIBar* Enemy::CreateBar() {
  health_bar_ =
      new UIBar(max_health_, {135, 211, 124},
                SDL_Rect{(int)rect_.x, ((int)rect_.y - 10), (int)rect_.w, 10});
  health_bar_->SetValue(max_health_);
  return health_bar_;
}

Enemy::~Enemy() { delete health_bar_; }

std::vector<float> Enemy::SetInterest(Vector direction) {
  std::vector<float> interest_aray(num_rays_);
  for (int i = 0; i < num_rays_; i++) {
    float interest =
        ray_directions_[i].Normalised().Dot(direction.Normalised());
    interest_aray[i] = std::max(0.0f, interest);
  }
  return interest_aray;
}

std::vector<float> Enemy::SetDanger(std::vector<GameObject*> objects) {
  std::vector<float> danger_aray(num_rays_);
  for (int i = 0; i < num_rays_; i++) {
    // calculating cast ray
    std::pair<SDL_Point, SDL_Point> ray = {
        SDL_Point{(int)ray_directions_[i].Scaled(search_range_).x +
                      (int)rect_.x + rotation_center_.x,
                  (int)ray_directions_[i].Scaled(search_range_).y +
                      (int)rect_.y + rotation_center_.y},
        SDL_Point{(int)rect_.x + rotation_center_.y,
                  (int)rect_.y + rotation_center_.y}};
    // iterates through all given game objects and checks for dangerous objects
    // in ray path
    for (GameObject* obj : objects) {
      // r is shorthand for the rect, not called rect as this uses too much
      // horizontal space
      SDL_Rect r = {obj->GetRect().x, obj->GetRect().y, obj->GetRect().w,
                    obj->GetRect().h};
      // division of that rectangle into its component line segments
      std::vector<std::pair<SDL_Point, SDL_Point>> lines = {
          {SDL_Point{r.x, r.y}, SDL_Point{r.x + r.w, r.y}},
          {SDL_Point{r.x + r.w, r.y}, SDL_Point{r.x + r.w, r.y + r.h}},
          {SDL_Point{r.x + r.w, r.y + r.h}, SDL_Point{r.x, r.y + r.h}},
          {SDL_Point{r.x, r.y + r.h}, SDL_Point{r.x, r.y}}};
      // checks each line segmemt of intercetions with the cast ray
      for (std::pair<SDL_Point, SDL_Point> line : lines) {
        float danger = 0;
        if (Intersect(line.first, line.second, ray.first, ray.second)) {
          // if there is an intersection set the danger equal to the inverse
          // distance between the enemy and that object, times a constant
          float diffrence;
          if (line.first.x == line.second.x) {
            diffrence = abs(line.first.x - (rect_.x + rotation_center_.x));
          } else {
            diffrence = abs(line.first.y - (rect_.y + rotation_center_.y));
          }
          danger = ((search_range_ - r.w) - diffrence) * 0.03;
          // danger = pow(diffrence.Norm(), -0.5) * 100;
          // danger = 1;
        }
        danger_aray[i] = danger;
        if (danger != 0.0f) {
          break;
        }
      }
      if (danger_aray[i] != 0.0f) {
        break;
      }
    }
  }
  return danger_aray;
}

bool Enemy::Intersect(SDL_Point p1, SDL_Point q1, SDL_Point p2, SDL_Point q2) {
  // algorithm from:
  // https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/,
  // checks orientation of the two tragnes formed by the lines, if diffrent the
  // the lines intersect
  int o1 = Orientation(p1, q1, p2);
  int o2 = Orientation(p1, q1, q2);
  int o3 = Orientation(p2, q2, p1);
  int o4 = Orientation(p2, q2, q1);
  if (o1 != o2 && o3 != o4) {
    return true;
  };
  return false;
}

int Enemy::Orientation(SDL_Point p1, SDL_Point p2, SDL_Point p3) {
  int val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
  if (val == 0) return 0;    // collinear
  return (val > 0) ? 1 : 2;  // clock or counterclock wise
}