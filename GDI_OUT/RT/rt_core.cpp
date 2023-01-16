#include "rtweekend.h"

#include "aarect.h"
#include "box.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include "ray_tracer.h"
#include "world.h"

#include <omp.h>

#include "rt_core.h"

using namespace std;

using std::vector;

#include <iostream>


#define STBIW_WINDOWS_UTF8

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../external/stb_image_write.h"

//#include "../external/stb_image.h"


int rt_core(const wstring fname) {

	string fname_in;
	fname_in.assign(fname.begin(), fname.end());

	// char* fname_in = new char[fname.length()];
	//stbiw_convert_wchar_to_utf8(fname_in, fname.length(), fname.c_str());
	// delete[] fname_in;

	// Parallel Setting

	omp_set_num_threads(omp_get_num_procs());
	omp_set_nested(1);

	// Image
	const auto aspect_ratio = 1.0 / 1.0;
	const int image_width = 200;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	// World
	auto pdf_area = make_shared<hittable_list>();
	pdf_area->add(make_shared<xz_rect>(213, 343, 227, 332, 554, shared_ptr<material>()));
	pdf_area->add(make_shared<sphere>(point3(190, 90, 190), 90, shared_ptr<material>()));
	//shared_ptr<hittable> pdf_area =
		//make_shared<xz_rect>(213, 343, 227, 332, 554, shared_ptr<material>());
		//make_shared<sphere>(point3(190, 90, 190), 90, shared_ptr<material>());

	auto world = cornell_box();

	color background(0, 0, 0);

	// Camera
	point3 lookfrom(273 + 10. * random_double(), 273 + 10. * random_double(), -805 + 10. * random_double());
	point3 lookat(278, 278, 0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.;
	auto aperture = 0.0;
	auto vfov = 40.0;
	auto time0 = 0.0;
	auto time1 = 1.0;

	camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, time0, time1);

	// Image data
	const int bytes_per_pixel = 3;
	uint8_t* data = new uint8_t[bytes_per_pixel * image_width * image_height];

	// Render

	//cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	vector<vector<vector<color>>>str_color(image_height, vector<vector<color>>(image_width, vector<color>(samples_per_pixel, color(0, 0, 0))));

	//cerr << "\rLoop Start " << flush;

	int j(0), i(0), s(0);// , cnt(0);

	#pragma omp parallel for private(i, s)//collapse(3)
	for (j = image_height - 1; j >= 0; --j) {
				
		for (i = 0; i < image_width; ++i)
		{
			//color pixel_color(0, 0, 0);

			for (s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				
				//pixel_color += ray_color(r, background, world, pdf_area, max_depth);
				str_color[j][i][s] = ray_color(r, background, world, pdf_area, max_depth);
			}
			//write_color(std::cout, pixel_color, samples_per_pixel);
		}

	}

	//std::cerr << "\nRT Done.\n";

	vector<vector<color>> pixel_img(image_height, vector<color>(image_width, color(0, 0, 0)));


	int j2 = image_height - 1;

	//#pragma omp parallel for
	for (j = image_height - 1; j >= 0; --j) {
		
		for (i = 0; i < image_width; ++i)
		{
			//color pixel_color(0, 0, 0);

			for (s = 0; s < samples_per_pixel; ++s)
				pixel_img[j2 - j][i] += str_color[j][i][s];
			//write_color(cout, pixel_img[j][i], samples_per_pixel);
		}
	}



	for (j = 0; j < image_height; j++)
		for (i = 0; i < image_width; i++)
			write_color(data, j * image_width + i, pixel_img[j][i], samples_per_pixel);


	stbi_write_jpg(fname_in.c_str(), image_width, image_height, bytes_per_pixel, data, 95);

	delete[] data;

	// Progress Indicator
	//std::cerr << "\nDone.\n";

	return 0;
}
