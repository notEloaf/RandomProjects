#ifndef SPHERE_H
#define SPHERE_H


#include "global.h"
#include "hittable.h"


class sphere : public hittable{
public:
	vec3<double> center;
	double radius;

	material *mat;

	sphere() {}
	sphere(vec3<double> cen, double r) : center(cen), radius(r) {}
	sphere(vec3<double> cen, double r, material *m) : center(cen), radius(r), mat(m) {}

	virtual bool hit(const ray &r, double t_min, double t_max, hit_record &out_hit) const override;
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &out_hit) const{
	vec3<double> oc = r.origin - center;
	double a = r.dir.length_squared();
	double half_b = dot(oc, r.dir);
	double c = oc.length_squared() - radius * radius;
	double discriminant = half_b*half_b - a*c;

	if(discriminant < 0) return false;

	double sqrtd = sqrt(discriminant);
	
	double root = (-half_b - sqrtd) / a;
	if(root < t_min || t_max < root){
		root = (-half_b + sqrtd) / a;
		if(root < t_min || t_max < root){
			return false;
		}
	}

	out_hit.t = root;
	out_hit.point = r.at(root);
	vec3<double> outward_normal = (out_hit.point - center) / radius;
	out_hit.set_face_normal(r, outward_normal);
	out_hit.mat = mat;
	return true;
}

#endif