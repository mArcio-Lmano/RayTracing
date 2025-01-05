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

TEST(Vec3, OperatorPlusEquals) {
  vec3 v1(1, 2, 3);
  vec3 v2(4, 5, 6);
  v1 += v2;
  EXPECT_DOUBLE_EQ(v1.x(), 5);
  EXPECT_DOUBLE_EQ(v1.y(), 7);
  EXPECT_DOUBLE_EQ(v1.z(), 9);
}

TEST(Vec3, OperatorTimesEquals) {
  vec3 v(1, 2, 3);
  double t = 4.0;
  v *= t;
  EXPECT_DOUBLE_EQ(v.x(), 4);
  EXPECT_DOUBLE_EQ(v.y(), 8);
  EXPECT_DOUBLE_EQ(v.z(), 12);
}

TEST(Vec3, OperatorDividesEquals) {
  vec3 v(4, 8, 12);
  double t = 4.0;
  v /= t;
  EXPECT_DOUBLE_EQ(v.x(), 1);
  EXPECT_DOUBLE_EQ(v.y(), 2);
  EXPECT_DOUBLE_EQ(v.z(), 3);
}

TEST(Vec3, SquareLength) {
  vec3 v(3, 4, 5);
  EXPECT_DOUBLE_EQ(v.sqr_length(), 3 * 3 + 4 * 4 + 5 * 5);
}

TEST(Vec3, Length) {
  vec3 v(3, 4, 5);
  EXPECT_DOUBLE_EQ(v.length(), std::sqrt(3 * 3 + 4 * 4 + 5 * 5));
}

TEST(Vec3, OperatorPlus) {
  vec3 v1(1, 2, 3);
  vec3 v2(4, 5, 6);
  vec3 result = v1 + v2;
  EXPECT_DOUBLE_EQ(result.x(), 5);
  EXPECT_DOUBLE_EQ(result.y(), 7);
  EXPECT_DOUBLE_EQ(result.z(), 9);
}

TEST(Vec3, OperatorMinus) {
  vec3 v1(1, 2, 3);
  vec3 v2(4, 5, 6);
  vec3 result = v1 - v2;
  EXPECT_DOUBLE_EQ(result.x(), -3);
  EXPECT_DOUBLE_EQ(result.y(), -3);
  EXPECT_DOUBLE_EQ(result.z(), -3);
}

TEST(Vec3, OperatorTimes) {
  vec3 v(1, 2, 3);
  double t = 4;
  vec3 result = v * t;
  EXPECT_DOUBLE_EQ(result.x(), 4);
  EXPECT_DOUBLE_EQ(result.y(), 8);
  EXPECT_DOUBLE_EQ(result.z(), 12);
}

TEST(Vec3, OperatorDivides) {
  vec3 v(1, 2, 3);
  double t = 4;
  vec3 result = v / t;
  EXPECT_DOUBLE_EQ(result.x(), 0.25);
  EXPECT_DOUBLE_EQ(result.y(), 0.5);
  EXPECT_DOUBLE_EQ(result.z(), 0.75);
}

TEST(DotProduct, NormalCase) {
  vec3 v1 = vec3(1, 2, 3);
  vec3 v2 = vec3(4, 5, 6);
  EXPECT_DOUBLE_EQ(dot(v1, v2), 32);
}

TEST(DotProduct, EdgeCase) {
  vec3 v1 = vec3(0, 0, 0);
  vec3 v2 = vec3(0, 0, 0);
  EXPECT_DOUBLE_EQ(dot(v1, v2), 0);
}

TEST(CrossProduct, NormalCase) {
  vec3 v1 = vec3(1, 2, 3);
  vec3 v2 = vec3(4, 5, 6);
  vec3 result = cross(v1, v2);
  EXPECT_DOUBLE_EQ(result.x(), -3);
  EXPECT_DOUBLE_EQ(result.y(), 6);
  EXPECT_DOUBLE_EQ(result.z(), -3);
}

TEST(CrossProduct, EdgeCase) {
  vec3 v1 = vec3(0, 0, 0);
  vec3 v2 = vec3(0, 0, 0);
  vec3 result = cross(v1, v2);
  EXPECT_DOUBLE_EQ(result.x(), 0);
  EXPECT_DOUBLE_EQ(result.y(), 0);
  EXPECT_DOUBLE_EQ(result.z(), 0);
}

TEST(UnitVector, NormalCase) {
  vec3 v = vec3(3, 2, -1);
  vec3 result = unit_vector(v);
  EXPECT_DOUBLE_EQ(result.x(), v.x() / v.length());
  EXPECT_DOUBLE_EQ(result.y(), v.y() / v.length());
  EXPECT_DOUBLE_EQ(result.z(), v.z() / v.length());
}

TEST(UnitVector, NormalCase_x) {
  vec3 v = vec3(3, 0, 0);
  vec3 result = unit_vector(v);
  EXPECT_DOUBLE_EQ(result.x(), 1);
  EXPECT_DOUBLE_EQ(result.y(), 0);
  EXPECT_DOUBLE_EQ(result.z(), 0);
}

TEST(UnitVector, NormalCase_y) {
  vec3 v = vec3(0, 5, 0);
  vec3 result = unit_vector(v);
  EXPECT_DOUBLE_EQ(result.x(), 0);
  EXPECT_DOUBLE_EQ(result.y(), 1);
  EXPECT_DOUBLE_EQ(result.z(), 0);
}

TEST(UnitVector, NormalCase_z) {
  vec3 v = vec3(0, 0, 9);
  vec3 result = unit_vector(v);
  EXPECT_DOUBLE_EQ(result.x(), 0);
  EXPECT_DOUBLE_EQ(result.y(), 0);
  EXPECT_DOUBLE_EQ(result.z(), 1);
}

TEST(UnitVector, EdgeCase) {
  vec3 v = vec3(0, 0, 0);
  vec3 result = unit_vector(v);
  EXPECT_DOUBLE_EQ(result.x(), 0);
  EXPECT_DOUBLE_EQ(result.y(), 0);
  EXPECT_DOUBLE_EQ(result.z(), 0);
}
