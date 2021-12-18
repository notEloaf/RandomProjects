#ifndef CTEST_H
#define CTEST_H

#include <iostream>
#include <thread>

typedef std::chrono::high_resolution_clock::time_point time_var;

class ctest{
public:
	time_var t1;
	time_var t2;

	void start(){
		t1 = std::chrono::high_resolution_clock::now();
	}


	double stop(){
		t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms_double = t2 - t1;
		return ms_double.count();
	}
};

#endif