#include "hittable.h"


bool translate::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	ray moved_r(r.origin() - offset, r.direction(), r.time());
	if (!ptr->hit(moved_r, t_min, t_max, rec))
		return false;

	rec.p += offset;
	rec.set_face_normal(moved_r, rec.normal);

	return true;
}

bool translate::bounding_box(double time0, double time1, aabb& output_box) const {
	if (!ptr->bounding_box(time0, time1, output_box))
		return false;

	output_box = aabb(
		output_box.mini() + offset,
		output_box.maxi() + offset);

	return true;
}