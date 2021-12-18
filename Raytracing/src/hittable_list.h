#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>

#include "hittable.h"

class hittable_list : public hittable{
public:
	std::vector<hittable *> objects;


	hittable_list() {}
	hittable_list(hittable *object) { add(object); }

	void clear() {
		for(auto p : objects){
			delete p;
		}
		objects.clear();
	}
	void add(hittable *object) { objects.push_back(object); }

	virtual bool hit(const ray &r, double t_min, double t_max, hit_record &out_hit) const override;
};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &out_hit) const{
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;

	for(const auto &object : objects){
		if(object->hit(r, t_min, closest_so_far, temp_rec)){
			hit_anything = true;
			closest_so_far = temp_rec.t;
			out_hit = temp_rec;
		}
	}
	return hit_anything;
}

#endif