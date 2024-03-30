
#include "constUtilFuncs.h"

#include "bvh.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "quad.h"
#include "texture.h"

#include <cmath>
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

hittable_list two_perlin_spheres() {
    hittable_list world;

    auto pertext = make_shared<noise_texture>(1);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
    world.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(pertext)));

    return world;
};

hittable_list quads(){
    hittable_list world;

    // Materials
    auto left_red     = make_shared<lambertian>(color(1.0, 0.2, 0.2));
    auto back_green   = make_shared<lambertian>(color(0.2, 1.0, 0.2));
    auto right_blue   = make_shared<lambertian>(color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<lambertian>(color(1.0, 0.5, 0.0));
    auto lower_teal   = make_shared<lambertian>(color(0.2, 0.8, 0.8));

    // Quads
    world.add(make_shared<quad>(point3(-3,-2, 5), vec3(0, 0,-4), vec3(0, 4, 0), left_red));
    world.add(make_shared<quad>(point3(-2,-2, 0), vec3(4, 0, 0), vec3(0, 4, 0), back_green));
    world.add(make_shared<quad>(point3( 3,-2, 1), vec3(0, 0, 4), vec3(0, 4, 0), right_blue));
    world.add(make_shared<quad>(point3(-2, 3, 1), vec3(4, 0, 0), vec3(0, 0, 4), upper_orange));
    world.add(make_shared<quad>(point3(-2,-3, 5), vec3(4, 0, 0), vec3(0, 0,-4), lower_teal));

    return world;
}

hittable_list cube_big_ligth(){
    hittable_list world;

    // Materials
    auto left_red     = make_shared<lambertian>(color(1.0, 0.2, 0.2));
    auto back_green   = make_shared<lambertian>(color(0.2, 1.0, 0.2));
    auto right_blue   = make_shared<lambertian>(color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<lambertian>(color(1.0, 0.5, 0.0));
    auto lower_teal   = make_shared<lambertian>(color(0.2, 0.8, 0.8));
    
    auto earth_texture = make_shared<image_texture>("../images/earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);

    auto ligth_material = make_shared<diffuse_light>(color(1,1,1));

    // Earth
    world.add(make_shared<sphere>(point3(0, 0, 2), 1, earth_surface));


    // Quads
    world.add(make_shared<quad>(point3(-2,-2, 4), vec3(0, 0,-4), vec3(0, 4, 0), left_red));
    world.add(make_shared<quad>(point3(-2,-2, 0), vec3(4, 0, 0), vec3(0, 4, 0), back_green));
    world.add(make_shared<quad>(point3( 2,-2, 0), vec3(0, 0, 4), vec3(0, 4, 0), right_blue));
    world.add(make_shared<quad>(point3(-2, 2, 0), vec3(4, 0, 0), vec3(0, 0, 4), ligth_material));
    world.add(make_shared<quad>(point3(-2,-2, 4), vec3(4, 0, 0), vec3(0, 0,-4), lower_teal));

    return world;
}


hittable_list cube_small_ligth(){
    hittable_list world;

    // Materials
    auto left_red     = make_shared<lambertian>(color(1.0, 0.2, 0.2));
    auto back_green   = make_shared<lambertian>(color(0.2, 1.0, 0.2));
    auto right_blue   = make_shared<lambertian>(color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<lambertian>(color(1.0, 0.5, 0.0));
    auto lower_teal   = make_shared<lambertian>(color(0.2, 0.8, 0.8));
    
    auto earth_texture = make_shared<image_texture>("../images/earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);

    auto ligth_material = make_shared<diffuse_light>(color(15,15,15));

    // Earth
    world.add(make_shared<sphere>(point3(0, 0, 2), 1, earth_surface));
    
    // Ligth
    world.add(make_shared<quad>(point3(-1.0, 1.9, 1.0), vec3(2, 0, 0), vec3(0, 0, 2), ligth_material));

    // Quads
    world.add(make_shared<quad>(point3(-2,-2, 4), vec3(0, 0,-4), vec3(0, 4, 0), left_red));
    world.add(make_shared<quad>(point3(-2,-2, 0), vec3(4, 0, 0), vec3(0, 4, 0), back_green));
    world.add(make_shared<quad>(point3( 2,-2, 0), vec3(0, 0, 4), vec3(0, 4, 0), right_blue));
    world.add(make_shared<quad>(point3(-2, 2, 0), vec3(4, 0, 0), vec3(0, 0, 4), upper_orange));
    world.add(make_shared<quad>(point3(-2,-2, 4), vec3(4, 0, 0), vec3(0, 0,-4), lower_teal));

    return world;
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    hittable_list world;
    camera cam;

    // cam.aspect_ratio      = 16.0 / 9.0;
    cam.aspect_ratio      = 1.0;
    cam.image_width       = 200;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = color(0.70, 0.80, 1.00);
    // cam.background        = color(0, 0, 0);

    cam.vfov     = 80;
    cam.lookfrom = point3(0,0,6);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.02;
    cam.focus_dist    = 10.0;

    switch (7)  {
        case 1: world = random_spheres();     break;
        case 2: world = two_spheres();        break;
        case 3: world = earth();              break;
        case 4: world = two_perlin_spheres(); break;
        case 5: world = quads();              break;
        case 6: world = cube_big_ligth();     break;
        case 7: world = cube_small_ligth();   break;
    }

    cam.render(world);


    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Output the duration
    std::clog << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}