#ifndef RAY_H
#define RAY_H

#include "global.h"

class ray{
public:
	vec3<double> origin;
	vec3<double> dir;


	ray(){}
	ray(const vec3<double> &orig, const vec3<double> &direction) : origin(orig), dir(direction) {}

	vec3<double> at(double t) const{
		return origin + t*dir;
	}
};

#endif