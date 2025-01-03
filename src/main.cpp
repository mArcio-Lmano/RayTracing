#include <iostream>
#include <ostream>

int main() {
  // Image size
  int image_width = 256;
  int image_height = 256;

  // Render
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {

    std::clog << "\rScan lines Remaining: " << (image_height - j) << ' '
              << std::flush;

    for (int i = 0; i < image_width; i++) {
      double r = 0;
      double g = double(i) / (image_width - 1);
      double b = 0;

      int red = int(255 * r);
      int green = int(255 * g);
      int blue = int(255 * b);

      std::cout << red << ' ' << green << ' ' << blue << '\n';
    }
  }
  std::clog << "\r DONE.             \n";
}
