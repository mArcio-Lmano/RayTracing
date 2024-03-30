#ifndef CAMERA_H
#define CAMERA_H

#include "constUtilFuncs.h"

#include "color.h"
#include "hittable.h"
#include "material.h"

#include <algorithm>
#include <execution>
#include <thread>
#include <iostream>
#include <iomanip>




class camera {
public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int    image_width  = 100;  // Rendered image width in pixel count
    int    samples_per_pixel = 10;   // Count of random samples for each pixel
    int    max_depth         = 10;   // Maximum number of ray bounces into scene
    color  background;               // Scene background color


    double vfov = 90;  // Vertical view angle (field of view)
    point3 lookfrom = point3(0,0,-1);  // Point camera is looking from
    point3 lookat   = point3(0,0,0);   // Point camera is looking at
    vec3   vup      = vec3(0,1,0);     // Camera-relative "up" direction


    double defocus_angle = 0;  // Variation angle of rays through each pixel
    double focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus

    void render(const hittable& world) {
        initialize();


        // Assuming image_width and image_height are the dimensions of the image
        std::vector<std::vector<color>> image(image_height, std::vector<color>(image_width));

        // Mutex for synchronization
        std::mutex mtx;
        
        std::clog << "[" << std::string(progress_bar_width, ' ') << "] 0.00%\r";
        std::clog.flush();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        std::for_each(std::execution::par, image_vertical_iterator.begin(), image_vertical_iterator.end(),
            [this, &world, &mtx, &image](int j)
        {
            std::for_each(std::execution::par_unseq, image_horizontal_iterator.begin(), image_horizontal_iterator.end(),
                [this, j, &world, &mtx, &image](int i)
            {
                color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_pixel; ++sample) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                mtx.lock();
                image[j][i] = pixel_color;
                mtx.unlock();
            });

            // Comment this for no progress bar (The code should run faster)
            mtx.lock();
            progress_counter++;
            progress = static_cast<float>(progress_counter) / static_cast<float>(image_height);
            int filled_width = static_cast<int>(progress * progress_bar_width);
            std::clog << "\r[" << std::string(filled_width, '=') << std::string(progress_bar_width - filled_width, ' ') << "] " << std::fixed << std::setprecision(2) << (progress * 100.0) << "%";
            std::clog.flush();
            mtx.unlock();

        });

        // Print the image in the correct order
        for (int j = 0; j < image_height; ++j) {
            for (int i = 0; i < image_width; ++i) {
                write_color(std::cout, image[j][i], samples_per_pixel);
            }
        }
        std::clog << "\rDone.                 \n";
    }

private:
    int    image_height;   // Rendered image height
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below
    vec3   u, v, w;        // Camera frame basis vectors
    vec3   defocus_disk_u; // Defocus disk horizontal radius
    vec3   defocus_disk_v; // Defocus disk vertical radius

    std::vector<int> image_horizontal_iterator; //
    std::vector<int> image_vertical_iterator;   //

    int progress_bar_width; // Width of the progress bar
    int progress_counter;
    float progress;     // Current progress

    void initialize() {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        image_horizontal_iterator.resize(image_width);
        image_vertical_iterator.resize(image_height);

        for(int i=0; i<image_width; i++)
            image_horizontal_iterator[i] = i;
        for(int i=0; i<image_height; i++)
            image_vertical_iterator[i]=i;
        

        center = lookfrom;

        // Determine viewport dimensions.
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

        // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
        vec3 viewport_v = viewport_height * -v;  // Vector down viewport vertical edge


        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // Calculate the camera defocus disk basis vectors.
        auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;

        progress_bar_width = 50;
        progress_counter = 0;
        progress = 0.0;

    }

    ray get_ray(int i, int j) const {
        // Get a randomly-sampled camera ray for the pixel at location i,j, originating from
        // the camera defocus disk.

        auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto pixel_sample = pixel_center + pixel_sample_square();


        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;

        auto ray_time = random_double();

        return ray(ray_origin, ray_direction, ray_time);
    }

    vec3 pixel_sample_square() const {
        // Returns a random point in the square surrounding a pixel at the origin.
        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }

    point3 defocus_disk_sample() const {
        // Returns a random point in the camera defocus disk.
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
        hit_record rec;

        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return color(0,0,0);

        // If the ray hits nothing, return the background color.
        if (!world.hit(r, interval(0.001, infinity), rec))
            return background;

        ray scattered;
        color attenuation;
        color color_from_emission = rec.mat->emitted(rec.u, rec.v, rec.p);

        if (!rec.mat->scatter(r, rec, attenuation, scattered))
            return color_from_emission;

        color color_from_scatter = attenuation * ray_color(scattered, depth-1, world);

        return color_from_emission + color_from_scatter;
    }
};

#endif