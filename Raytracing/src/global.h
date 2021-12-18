#ifndef GLOBAL_H
#define GLOBAL_H

#include <limits>
#include <cmath>
#include <cstdlib>



//Helpers------------------------------------------------------------------------------------------
const double INF = std::numeric_limits<double>::infinity();
const double pi = 3.141592653589;

inline double degree_to_radius(double degrees){
	return degrees * pi / 180.0;
}

inline double random_double(){
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max){
	return min + (max-min)*random_double();
}

inline double clamp(double x, double min, double max){
	if( x < min ) return min;
	if( x > max ) return max;
	return x;
}

//Common includes------------------------------------------------------------------------------------------
#include "vec3.h"
#include "ray.h"

//Debuf functions------------------------------------------------------------------------------------------
#define DEBUG_LEVEL 0

//Log Message
#if DEBUG_LEVEL > 0
#define log( msg ) std::cerr << "\033[1;36m" << __FILE__ << "{" << __LINE__ << "}: " << msg << "\033[0m" << std::endl;
#endif

//Warning Message
#if DEBUG_LEVEL > 1
#define warn( msg ) std::cerr << "\033[1;33m" << __FILE__ << "{" << __LINE__ << "}: " << msg << "\033[0m" << std::endl;
#endif

//Error Message
#if DEBUG_LEVEL > 2
#define error( msg ) std::cerr << "\033[1;41m" << __FILE__ << "{" << __LINE__ << "}: " << msg << "\033[0m" << std::endl;
#endif

//No debug
#if DEBUG_LEVEL <= 0
#define log( msg )
#define warn( msg )
#define error( msg )
#endif


#endif