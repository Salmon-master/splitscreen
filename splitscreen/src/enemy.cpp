#include "enemy.h"

#include <algorithm>
#include <iostream>

#include "wall.h"

Enemy::Enemy(int x, int y, int type) : GameObject(x, y, "enemy_" + type) {
  SetPos(x, y);
  for (size_t i = 0; i < num_rays_; i++) {
    float angle = (i * 2 * M_PI) / num_rays_;
    ray_directions_[i] = {cos(angle), sin(angle)};
  }
}

bool Enemy::Damage(int amount) {
  bool rv = false;
  health_ -= amount;
  if (health_ <= 0) {
    rv = true;
  }
  return rv;
}

void Enemy::AI(std::vector<GameObject*> game_objects) {
  for (GameObject* obj : game_objects) {
    Player* player_type = dynamic_cast<Player*>(obj);
    Bullet* bullet_type = dynamic_cast<Bullet*>(obj);
  }
}

std::vector<float> Enemy::SetInterest(Vector direction) {
  std::vector<float> interest_aray(num_rays_);
  for (int i = 0; i < num_rays_; i++) {
    float interest = ray_directions_->Dot(direction.Normalised());
    interest_aray[i] = std::max(0.0f, interest);
  }
  return interest_aray;
}

std::vector<float> Enemy::SetDanger(std::vector<GameObject*> objects) {
  std::vector<float> danger_aray(num_rays_);
  for (int i = 0; i < num_rays_; i++) {
    // calculating cast ray
    std::pair<SDL_Point, SDL_Point> ray = {
        SDL_Point{(int)ray_directions_[i].Scaled(search_range_).x,
                  (int)ray_directions_[i].Scaled(search_range_).y},
        SDL_Point{(int)rect_.x, (int)rect_.y}};
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
          Vector diffrence = {rect_.x - obj->GetRect().x,
                              rect_.y - obj->GetRect().y};
          danger = pow(diffrence.Norm(), -1) * 10;
        }
        danger_aray[i] = danger;
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
  int o1 = (q1.y - p1.y) * (p2.x - q1.x) - (q1.x - p1.x) * (p2.y - q1.y);
  int o2 = (q1.y - p1.y) * (q2.x - q1.x) - (q1.x - p1.x) * (q2.y - q1.y);
  int o3 = (q2.y - p2.y) * (p1.x - q2.x) - (q2.x - p2.x) * (p1.y - q2.y);
  int o4 = (q2.y - p2.y) * (q1.x - q2.x) - (q2.x - p2.x) * (q1.y - q2.y);
  if (o1 != o2 && o3 != o4) {
    return true;
  };
  return false;
}
