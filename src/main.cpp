
#include "constUtilFuncs.h"

#include "bvh.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "texture.h"

#include <chrono>
#include <tbb/parallel_for.h>
#include <cassert>

hittable_list random_spheres(){
    hittable_list world;
  

    auto checker = make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));

    auto ground_material =  make_shared<lambertian>(checker);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));


    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;


                if (choose_mat < 0.05){
                    auto eart_texture = make_shared<image_texture>("../images/earthmap.jpg");
                    sphere_material = make_shared<lambertian>(eart_texture);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));

                    // Add  Movement
                    // auto center2 = center + vec3(0, random_double(0,.5), 0);
                    // world.add(make_shared<sphere>(center, center2, 0.2, sphere_material));

                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto eart_texture = make_shared<image_texture>("../images/earthmap.jpg");
    auto material1 = make_shared<lambertian>(eart_texture);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material2));
    world.add(make_shared<sphere>(point3(4, 1, 0), -0.95, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material3));


    world = hittable_list(make_shared<bvh_node>(world));

    return world;
};


hittable_list two_spheres() {
    hittable_list world;

    auto checker = make_shared<checker_texture>(0.3, color(.2, .3, .1), color(.9, .9, .9));

    world.add(make_shared<sphere>(point3(0,-10, 0), 10, make_shared<lambertian>(checker)));
    world.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));
    
    return world;
}


hittable_list earth() {
    auto earth_texture = make_shared<image_texture>("../images/earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<sphere>(point3(0,0,0), 2, earth_surface);

    return hittable_list(globe);
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    hittable_list world;
    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1920;
    cam.samples_per_pixel = 250;
    cam.max_depth         = 100;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.02;
    cam.focus_dist    = 10.0;

    switch (1)  {
        case 1: world = random_spheres(); break;
        case 2: world = two_spheres();    break;
        case 3: world = earth();          break;
    }

    cam.render(world);


    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Output the duration
    std::clog << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}