#ifndef VEC3_H
#define VEC3_H

#include <iostream>

#include "global.h"



template <typename T>
class vec3{
public:
	T x, y, z;
	vec3(): x(0), y(0), z(0) {}
	vec3(T x_in, T y_in, T z_in): x(x_in), y(y_in), z(z_in) {}

	vec3 operator-() const { return vec3<T>(-x,-y,-z); }

	//Getter and setter
	T operator[](int i) const {
		switch(i){
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				return x;
		}
	}

	T &operator[](int i) {
		switch(i){
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				return x;
		}
	}

	//Vector functions
	vec3 &operator+=(const vec3 &v){
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3 &operator*=(const vec3 &v){
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	vec3 &operator/=(const T n){
		return *this *= 1/n;
	}

	T length() const{
		return sqrt(length_squared());
	}

	T length_squared() const {
		return x*x + y*y + z*z;
	}

	bool near_zero() const{
		const auto s = 1e-8;
		return (fabs(x) < s && fabs(y) < s && fabs(z) < s);
	}

	inline static vec3<double> random(){
		return vec3<double>(random_double(), random_double(), random_double());
	}

	inline static vec3<double> random(double min, double max){
		return vec3<double>(random_double(min, max), random_double(min, max), random_double(min, max));
	}

};



//Helper Functions
template <typename T>
inline std::ostream &operator<<(std::ostream &out, const vec3<T> v){
	return out << "{" << v.x << ", " << v.y << ", " << v.z << "}";
}

template <typename T>
inline vec3<T> operator+(const vec3<T> &v1, const vec3<T> v2){
	return vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <typename T>
inline vec3<T> operator-(const vec3<T> &v1, const vec3<T> v2){
	return vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> &v1, const vec3<T> v2){
	return vec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <typename T>
inline vec3<T> operator*(T n, const vec3<T> v){
	return vec3<T>(n * v.x, n * v.y, n * v.z);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> &v, T n){
	return n * v;
}

template <typename T>
inline vec3<T> operator/(const vec3<T> &v, T n){
	return (1/n) * v;
}

template <typename T>
inline T dot(const vec3<T> &v1, const vec3<T> v2){
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline vec3<T> cross(const vec3<T> &a, const vec3<T> &b) {
    return bec3(a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

template <typename T>
inline vec3<T> normalise(const vec3<T> &v) {
    return v / v.length();
}

vec3<double> random_in_unit_sphere(){
	while(true){
		vec3<double> p = vec3<double>::random(-1, 1);
		if(p.length_squared() >= 1) continue;
		return p;
	}
}

vec3<double> random_in_hemisphere(const vec3<double> &normal){
	vec3<double> in_unit_sphere = random_in_unit_sphere();
	if(dot(in_unit_sphere, normal) > 0.0){
		return in_unit_sphere;
	}

	return -in_unit_sphere;
}

template <typename T>
inline vec3<T> reflect(const vec3<T> &v, const vec3<T> n){
	return v - 2*dot(v,n)*n;
}

inline vec3<double> random_unit_vector(){
	return normalise(random_in_unit_sphere());
}


#endif