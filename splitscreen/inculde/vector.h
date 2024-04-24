// Copyright 2024 Hugh Thompson

#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>
// a structure containing a 2d vector mathmatical/physics sense.
struct Vector {
  // x componet of the vector
  float x = 0;
  // y component of the vector
  float y = 0;
  // retuns the length or normal of the vector
  float Norm() {
    float norm = sqrt(pow(x, 2) + pow(y, 2));
    return norm;
  }
  // retuns the vector, but scaled so that the normal is a length of 1
  Vector Normalised() {
    Vector normlisied = {this->x / this->Norm(), this->y / this->Norm()};
    return normlisied;
  }
  // retuns the dot product of this vector and another inputted vector
  float Dot(Vector other) { return (this->x * other.x) + (this->y * other.y); }
  // retuns this vector, but scaled by the input
  Vector Scaled(float scalar) {
    return {this->x * scalar, this->y * scalar};
  }
};

#endif  // !VECTOR_H_
