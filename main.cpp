#include "geometry.h"
#include <fstream>
#include <iostream>
#include <vector>

struct Sphere {
  Vec3f center;
  float radius;

  Sphere(const Vec3f &c, const float &r) : center(c), radius(r) {}
};

Vec3f cast_ray(const Vec3f &origin, const Vec3f &direction,
               const Sphere &sphere) {
  return Vec3f(0.4, 0.2, 0.1);
}

void render(const Sphere &sphere) {
  const int width = 1024;
  const int height = 768;
  const int fov = M_PI / 2.0;
  std::vector<Vec3f> framebuffer(width * height);

  for (size_t j = 0; j < height; j++) {
    for (size_t i = 0; i < width; i++) {
      float x = (2 * (i + 0.5) / (float)width - 1) * tan(fov / 2.) * width /
                (float)height;
      float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
      Vec3f dir = Vec3f(x, y, -1).normalize();
      framebuffer[i + j * width] = cast_ray(Vec3f(0, 0, 0), dir, sphere);
    }
  }

  std::ofstream ofs; // save the framebuffer to file
  ofs.open("./out.ppm");
  ofs << "P6\n" << width << " " << height << "\n255\n";
  for (size_t i = 0; i < height * width; ++i) {
    for (size_t j = 0; j < 3; j++) {
      ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
    }
  }
  ofs.close();
}

int main() {
  Sphere sphere(Vec3f(-13, 20, -2), 20);
  render(sphere);
  return 0;
}
