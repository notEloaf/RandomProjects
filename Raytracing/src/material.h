#ifndef MATERIAL_H
#define MATERIAL_H

#include "global.h"

struct hit_record;

class material{
public:
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3<double> &attenuation, ray &scattered) const = 0;
};


class lambertian : public material{
public:
	vec3<double> color;

	lambertian(vec3<double> c) : color(c) {}

	bool scatter(const ray &r_in, const hit_record &rec, vec3<double> &attenuation, ray &scattered) const override{
		vec3<double> scatter_dir = rec.normal + random_unit_vector();
		if(scatter_dir.near_zero()){
			scatter_dir = rec.normal;
		}
		scattered = ray(rec.point, scatter_dir);
		attenuation = color;
		log(color)
		return true;
	}
};

class metal : public material{
public:
	vec3<double> color;
	double fuzz;

	metal(vec3<double> c, double f) : color(c), fuzz(f < 1 ? f : 1) {}

	bool scatter(const ray &r_in, const hit_record &rec, vec3<double> &attenuation, ray &scattered) const override{
		vec3<double> reflected = reflect(normalise(r_in.dir), rec.normal);
		scattered = ray(rec.point, reflected + fuzz*random_in_unit_sphere());
		attenuation = color;
		return (dot(scattered.dir, rec.normal) > 0);
	}
};


#endif