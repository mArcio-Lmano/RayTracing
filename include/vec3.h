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
/// Inline functions
inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
  return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}
inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

inline vec3 operator*(const vec3 &v, double t) {
  return vec3(v.x() * t, v.y() * t, v.z() * t);
}

inline vec3 operator/(const vec3 &v, double t) {
  return vec3(v.x() / t, v.y() / t, v.z() / t);
}

inline double dot(const vec3 &v1, const vec3 &v2) {
  return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.y() * v2.z() - v1.z() * v2.y(),
              v1.z() * v2.x() - v1.x() * v2.z(),
              v1.x() * v2.y() - v1.y() * v2.x());
}

inline vec3 unit_vector(const vec3 &v) {
  if (v.length() == 0) {
    return vec3(0, 0, 0);
  }
  return v / v.length();
}
#endif
