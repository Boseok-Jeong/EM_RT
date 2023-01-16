#pragma once

#include "vec3.h"

struct image_config
{
	int image_width;
	int image_height;
	int samples_per_pixel;
};

struct camera_config
{
	point3 lookfrom;
	point3 lookat;
	vec3 vup;
	double dist_to_focus;
	double aperture;
	double vfov;
	double time0;
	double time1;
};

struct rt_config
{
	double aspect_ratio;
	int max_depth;

	image_config img;
	camera_config cmr;
	
};