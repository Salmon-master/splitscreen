// Copyright 2024 Hugh Thompson

#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>

struct Vector {
  float x = 0;
  float y = 0;

  float Norm() {
    float norm = sqrt(pow(x, 2) + pow(y, 2));
    return norm;
  }
  Vector Normalised() {
    Vector normlisied = {this->x / this->Norm(), this->y / this->Norm()};
    return normlisied;
  }
  float Dot(Vector other) { return (this->x * other.x) + (this->y * other.y); }
  Vector Scaled(float scalar) {
    return {this->x * scalar, this->y * scalar};
  }
};

#endif  // !VECTOR_H_
