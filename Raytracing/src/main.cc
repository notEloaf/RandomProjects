#include <iostream>
#include "global.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

#include "ctest.h"

vec3<double> light_pos(10,10,10);

vec3<double> ray_color(const ray &r, const hittable &world, int depth){
	if(depth <= 0){
		return vec3<double>(0,0,0);
	}




	hit_record rec;
	hit_record shadow_rec;
	bool darken = false;
	if(world.hit(r, 0.001, INF, rec)){
		ray shadow_ray(rec.point, normalise(light_pos-rec.point+1.5*random_unit_vector()));
		if(world.hit(shadow_ray, 0.001, INF, shadow_rec)){
			darken = true;
		}
		ray scattered;
		vec3<double> attenuation;
		if(rec.mat->scatter(r, rec, attenuation, scattered)){
			if(darken){
				return 0.5 * attenuation * ray_color(scattered, world, depth-1);
			}
			return attenuation * ray_color(scattered, world, depth-1);
		}
		return vec3<double>(0,0,0);
	}

	vec3<double> unit_dir = normalise(r.dir);
	double t = 0.5 * (unit_dir.y + 1.0);
	return (1.0 - t) * vec3<double>(1.0, 1.0, 1.0) + t * vec3<double>(0.5, 0.7, 1.0);
}

void write_color(vec3<double> pixel_color, int samples_per_pixel){
	double r = pixel_color.x;
	double g = pixel_color.y;
	double b = pixel_color.z;

	double scale = 1.0 / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	std::cout << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' ' << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' ' << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << std::endl;
}

int main(int argc, char const *argv[])
{
	const double aspect_ratio = 16.0/9.0;
	const size_t image_width = 1920;
	const size_t image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 1000;
	const int max_depth = 10;

	std::cerr << "Creating image with dimensions (" << image_width << ", " << image_height << ")" << std::endl;

	material *lam_mat = new lambertian(vec3<double>(0.8, 0.8, 0.0));
	material *lam_mat_g = new lambertian(vec3<double>(0.1, 0.8, 0.0));
	material *metal_mat = new metal(vec3<double>(0.8, 0.8, 0.8), 1);
	material *metal_mat_f = new metal(vec3<double>(0.1, 0.1, 0.1), 0.01);

	hittable_list world;
	world.add(new sphere(vec3<double>(0,0,-1), 0.5, lam_mat));
	world.add(new sphere(vec3<double>(0,-100.5,-1), 100, lam_mat_g));

	world.add(new sphere(vec3<double>(-1,0,-1), 0.5, metal_mat));
	world.add(new sphere(vec3<double>(1,0,-1), 0.5, metal_mat_f));


	camera cam;

	ctest timer;

	timer.start();

	//Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	for(int y = image_height-1; y >= 0 ; y--){
		std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
		for(int x = 0; x < image_width; x++){
			vec3<double> pixel_color(0,0,0);
			for(int s = 0; s < samples_per_pixel; s++){
				double u = (x + random_double())/(image_width-1);
				double v = (y + random_double())/(image_height-1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(pixel_color, samples_per_pixel);
		}
	}

	double t = timer.stop();
	std::cerr << "\nTime taken: " << t << " ms" << std::endl;

	return 0;
}