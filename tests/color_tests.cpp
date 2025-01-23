#include "../include/color.h"
#include <gtest/gtest.h>

TEST(WriteColorTest, Basic) {
  // Set up the input and expected output
  color pixel_color = {1.0f, 0.5f, 0.25f};
  std::ostringstream out;
  write_color(out, pixel_color);
  std::string expected_output = "255 127 63\n";

  EXPECT_EQ(expected_output, out.str());
}

TEST(WriteColorTest, EdgeCaseZero) {
  // Set up the input and expected output
  color pixel_color = {0.0f, 0.0f, 0.0f};
  std::ostringstream out;
  write_color(out, pixel_color);
  std::string expected_output = "0 0 0\n";

  EXPECT_EQ(expected_output, out.str());
}

TEST(WriteColorTest, EdgeCaseUnit) {
  // Set up the input and expected output
  color pixel_color = {1.0f, 1.0f, 1.0f};
  std::ostringstream out;
  write_color(out, pixel_color);
  std::string expected_output = "255 255 255\n";

  EXPECT_EQ(expected_output, out.str());
}
