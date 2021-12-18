#ifndef HITTABLE_H
#define HITTABLE_H

#include "global.h"

class material;

struct hit_record{
	vec3<double> point;
	vec3<double> normal;
	double t;
	bool front_face;

	material *mat;

	inline void set_face_normal(const ray &r, const vec3<double> &outward_normal){
		front_face = dot(r.dir, outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable{
public:
	virtual bool hit(const ray &r, double t_min, double t_max, hit_record &out_hit) const = 0;
};

#endif