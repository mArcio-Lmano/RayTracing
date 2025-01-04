#ifndef VEC3_H
#define VEC3_H
#include <ostream>

class vec3 {
public:
  double cords[3];

  vec3();
  vec3(double v1, double v2, double v3);

  double x() const;
  double y() const;
  double z() const;

  vec3 operator-() const;

  double operator[](int i) const;
  double &operator[](int i);

  vec3 &operator+=(const vec3 &v);

  vec3 &operator*=(const double scaler);
  vec3 &operator/=(const double scaler);
  // operator + * /

  double sqr_length() const;
  double length() const;
};
//////////////////////
// Utility function //
//////////////////////
// Print vector
inline std::ostream &operator<<(std::ostream &out, const vec3 &v);
// Sum of vectors
inline vec3 operator+(const vec3 &v1, const vec3 &v2);
#endif
