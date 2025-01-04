#include "../include/vec3.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(Vec3, DefaultConstructor) {
  vec3 v;
  EXPECT_DOUBLE_EQ(v.x(), 0);
  EXPECT_DOUBLE_EQ(v.y(), 0);
  EXPECT_DOUBLE_EQ(v.z(), 0);
}

TEST(Vec3, Constructor) {
  vec3 v(1, 2, 3);
  EXPECT_DOUBLE_EQ(v.x(), 1);
  EXPECT_DOUBLE_EQ(v.y(), 2);
  EXPECT_DOUBLE_EQ(v.z(), 3);
}

TEST(Vec3, OperatorSub) {
  vec3 v(1, 2, 3);
  vec3 w = -v;
  EXPECT_DOUBLE_EQ(w.x(), -1);
  EXPECT_DOUBLE_EQ(w.y(), -2);
  EXPECT_DOUBLE_EQ(w.z(), -3);
}

TEST(Vec3, OperatorIndex) {
  vec3 v(1, 2, 3);
  EXPECT_DOUBLE_EQ(v[0], 1);
  EXPECT_DOUBLE_EQ(v[1], 2);
  EXPECT_DOUBLE_EQ(v[2], 3);
}

// TEST(Vec3, OperatorPlusEquals) {
//   vec3 v1(1, 2, 3);
//   vec3 result = v1 + v2;
//   EXPECT_DOUBLE_EQ(result.x(), 5);
//   EXPECT_DOUBLE_EQ(result.y(), 7);
//   EXPECT_DOUBLE_EQ(result.z(), 9);
// }

TEST(Vec3, OperatorTimesEquals) {
  vec3 v(1, 2, 3);
  double t = 4.0;
  v *= t;
  EXPECT_DOUBLE_EQ(v.x(), 4);
  EXPECT_DOUBLE_EQ(v.y(), 8);
  EXPECT_DOUBLE_EQ(v.z(), 12);
}

TEST(Vec3, OperatorDividesEquals) {
  vec3 v(1, 2, 3);
  double t = 4.0;
  v /= t;
  EXPECT_DOUBLE_EQ(v.x(), 4);
  EXPECT_DOUBLE_EQ(v.y(), 8);
  EXPECT_DOUBLE_EQ(v.z(), 12);
}

TEST(Vec3, SquareLength) {
  vec3 v(3, 4, 5);
  EXPECT_DOUBLE_EQ(v.sqr_length(), 3 * 3 + 4 * 4 + 5 * 5);
}

TEST(Vec3, Length) {
  vec3 v(3, 4, 5);
  EXPECT_DOUBLE_EQ(v.length(), std::sqrt(3 * 3 + 4 * 4 + 5 * 5));
}
