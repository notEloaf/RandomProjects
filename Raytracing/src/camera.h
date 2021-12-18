#ifndef CAMERA_H
#define CAMERA_H

#include "global.h"

class camera{
public:
	camera(){
		const double aspect_ratio = 16.0/9.0;
		double viewport_height = 2.0;
		double viewport_width = aspect_ratio * viewport_height;
		double focal_length = 1.0;

		origin = vec3<double>(0, 0, 0);
		horizontal = vec3<double>(viewport_width, 0, 0);
		vertical = vec3<double>(0, viewport_height, 0);
		lower_left_corner = origin - horizontal/2.0 - vertical/2.0 - vec3<double>(0,0,focal_length);
	}

	ray get_ray(double u, double v) const{
		return ray(origin, lower_left_corner + u * horizontal + v*vertical - origin);
	}

private:
	vec3<double> origin;
	vec3<double> lower_left_corner;
	vec3<double> horizontal;
	vec3<double> vertical;
};

#endif