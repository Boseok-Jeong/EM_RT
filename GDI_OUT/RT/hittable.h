#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h" // Ch. 9  added

#include "aabb.h"

class material; // Ch. 9  added


struct hit_record {
	point3 p;
	vec3 normal;
	shared_ptr<material> mat_ptr; // Ch. 9  added
	double t;
	// for texture
	double u;
	double v;
	
	// add for front face
	bool front_face;

	inline void set_face_normal(const ray& r, const vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
	virtual bool bounding_box(double time0, double time1, aabb& output_box) const = 0;
	virtual double pdf_value(const point3& o, const vec3& v) const {
		return 0.0;
	}

	virtual vec3 random(const vec3& o) const {
		return vec3(1, 0, 0);
	}
};


class flip_face : public hittable {
public:
	flip_face(shared_ptr<hittable> p) : ptr(p) {}

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override {
		if (!ptr->hit(r, t_min, t_max, rec))
			return false;

		rec.front_face = !rec.front_face;
		return true;
	}

	virtual bool bounding_box(double time0, double time1, aabb& output_box) const override {
		return ptr->bounding_box(time0, time1, output_box);
	}

public:
	shared_ptr<hittable> ptr;
};


class translate : public hittable {
public:
	translate(shared_ptr<hittable> p, const vec3& displacement)
		: ptr(p), offset(displacement) {}

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;

	virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;


public:
	shared_ptr<hittable> ptr;
	vec3 offset;
};


class rotate_y : public hittable {
public:
	rotate_y(shared_ptr<hittable> p, double angle);

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

	virtual bool bounding_box(double time0, double time1, aabb& output_box) const override {
		output_box = bbox;
		return hasbox;
	}

public:
	shared_ptr<hittable> ptr;
	double sin_theta;
	double cos_theta;
	bool hasbox;
	aabb bbox;
};

inline rotate_y::rotate_y(shared_ptr<hittable> p, double angle) : ptr(p) {
	auto radians = degrees_to_radians(angle);
	sin_theta = sin(radians);
	cos_theta = cos(radians);
	hasbox = ptr->bounding_box(0, 1, bbox);

	point3 mini(infinity, infinity, infinity);
	point3 maxi(-infinity, -infinity, -infinity);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				auto x = i * bbox.maxi().x() + (1 - i) * bbox.mini().x();
				auto y = j * bbox.maxi().y() + (1 - j) * bbox.mini().y();
				auto z = k * bbox.maxi().z() + (1 - k) * bbox.mini().z();

				auto newx = cos_theta * x + sin_theta * z;
				auto newz = -sin_theta * x + cos_theta * z;

				vec3 tester(newx, y, newz);

				for (int c = 0; c < 3; c++) {
					mini[c] = fmin(mini[c], tester[c]);
					maxi[c] = fmax(maxi[c], tester[c]);
				}
			}
		}
	}

	bbox = aabb(mini, maxi);
}

inline bool rotate_y::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	auto origin = r.origin();
	auto direction = r.direction();

	origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
	origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];

	direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
	direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];

	ray rotated_r(origin, direction, r.time());

	if (!ptr->hit(rotated_r, t_min, t_max, rec))
		return false;

	auto p = rec.p;
	auto normal = rec.normal;

	p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
	p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

	normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
	normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

	rec.p = p;
	rec.set_face_normal(rotated_r, normal);

	return true;
}

#endif