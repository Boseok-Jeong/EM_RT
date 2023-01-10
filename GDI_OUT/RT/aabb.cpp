#include "aabb.h"

bool aabb::hit(const ray& r, double t_min, double t_max) const {
	for (int a = 0; a < 3; a++) {
		auto invD = 1.0f / r.direction()[a];
		auto t0 = (mini()[a] - r.origin()[a]) * invD;
		auto t1 = (maxi()[a] - r.origin()[a]) * invD;
		if (invD < 0.0f)
			std::swap(t0, t1);
		t_min = t0 > t_min ? t0 : t_min;
		t_max = t1 < t_max ? t1 : t_max;
		if (t_max <= t_min)
			return false;
	}
	return true;
}

aabb surrounding_box(aabb box0, aabb box1) {
	point3 small(fmin(box0.mini().x(), box1.mini().x()),
		fmin(box0.mini().y(), box1.mini().y()),
		fmin(box0.mini().z(), box1.mini().z()));

	point3 big(fmax(box0.maxi().x(), box1.maxi().x()),
		fmax(box0.maxi().y(), box1.maxi().y()),
		fmax(box0.maxi().z(), box1.maxi().z()));
	return aabb(small, big);
}