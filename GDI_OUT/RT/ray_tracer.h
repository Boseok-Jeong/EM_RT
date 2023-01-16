#pragma once

#include "rtweekend.h"
#include "hittable.h"

color ray_color(
	const ray& r,
	const color& background,
	const hittable& world,
	shared_ptr<hittable>& pdf_area,
	int depth
);