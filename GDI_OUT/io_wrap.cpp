#include "io_wrap.h"

#include "RT/aarect.h"
#include "RT/box.h"
#include "RT/camera.h"
#include "RT/color.h"
#include "RT/hittable_list.h"
#include "RT/material.h"
#include "RT/sphere.h"

#include "RT/ray_tracer.h"
#include "RT/world.h"

#include "RT/rt_core.h"

#include "GDI_OUTDoc.h"

COLORREF color2ref(const color& pixel_color, int samples_per_pixel)
{
	double r = pixel_color.x();
	double g = pixel_color.y();
	double b = pixel_color.z();

	COLORREF ans(0x0);

	// Replace NaN components with zero. See explanation in Ray Tracing: The Rest of Your Life.
	if (r != r) r = 0.0;
	if (g != g) g = 0.0;
	if (b != b) b = 0.0;

	// Divide the color by the number of samples.
	double scale = 1.0 / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	// Write the translated [0,255] value of each color component.
	ans = static_cast<int>(256 * clamp(r, 0.0, 0.999));
	ans <<= 8;
	ans |= static_cast<int>(256 * clamp(g, 0.0, 0.999));
	ans <<= 8;
	ans |= static_cast<int>(256 * clamp(b, 0.0, 0.999));

	return ans;
}

void rt2pixel(CDC* out_img, int img_width, int img_height, const vector<vector<color>>& in_img, int samples_per_pixel)
{
	for (int i = 0; i < img_width; i++)
	{
		for (int j = 0; j < img_height; j++)
		{
			out_img->SetPixel(i, j, color2ref(in_img[i][j], samples_per_pixel));

		}

	}
}

UINT MFC_RT_CORE(LPVOID pParam)
{
	RT_PARAM* pRtParam = (RT_PARAM*)pParam;
	rt_core(pRtParam->fname);

	//delete pRtParam->fname;

	InvalidateRect(pRtParam->hWnd, NULL, TRUE);
	UpdateWindow(pRtParam->hWnd);

	delete pRtParam;

	return 0;
}
