#include "../include/vec3.h"
#include <cmath>

vec3::vec3() : cords{0, 0, 0} {};
vec3::vec3(double v1, double v2, double v3) : cords{v1, v2, v3} {};

double vec3::x() const { return cords[0]; }
double vec3::y() const { return cords[1]; }
double vec3::z() const { return cords[2]; }

vec3 vec3::operator-() const { return vec3(-cords[0], -cords[1], -cords[2]); }

double vec3::operator[](int i) const { return cords[i]; }
double &vec3::operator[](int i) { return cords[i]; }

vec3 &vec3::operator+=(const vec3 &v) {
  cords[0] += v.cords[0];
  cords[1] += v.cords[1];
  cords[2] += v.cords[2];
  return *this;
}

vec3 &vec3::operator*=(const double t) {
  cords[0] *= t;
  cords[1] *= t;
  cords[2] *= t;
  return *this;
}

vec3 &vec3::operator/=(const double t) {
  cords[0] /= t;
  cords[1] /= t;
  cords[2] /= t;
  return *this;
}

double vec3::sqr_length() const {
  return cords[0] * cords[0] + cords[1] * cords[1] + cords[2] * cords[2];
}

double vec3::length() const { return std::sqrt(sqr_length()); }
