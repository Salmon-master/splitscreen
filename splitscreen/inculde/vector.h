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
};

#endif  // !VECTOR_H_
