#include "ray_tracer.h"
#include "material.h"

color ray_color(
	const ray& r,
	const color& background,
	const hittable& world,
	shared_ptr<hittable> pdf_area,
	int depth
) {
	hit_record rec;

	// If we've exceeded the ray bounce limit, no more light is gathered
	if (depth <= 0)
		return color(0, 0, 0);

	// If the ray hits nothing, return the background color
	if (!world.hit(r, 0.001, infinity, rec))
		return background;

	scatter_record srec;
	color emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);
	if (!rec.mat_ptr->scatter(r, rec, srec))
		return emitted;

	if (srec.is_specular) {
		return srec.attenuation
			* ray_color(srec.scatter_ray, background, world, pdf_area, depth - 1);
	}

	auto pdf_area_ptr = make_shared<hittable_pdf>(pdf_area, rec.p);
	mixture_pdf p(pdf_area_ptr, srec.pdf_ptr);

	ray scattered = ray(rec.p, p.generate(), r.time());
	auto pdf_val = p.value(scattered.direction());

	return emitted + srec.attenuation * rec.mat_ptr->scattering_pdf(r, rec, scattered)
		* ray_color(scattered, background, world, pdf_area, depth - 1) / pdf_val;
}