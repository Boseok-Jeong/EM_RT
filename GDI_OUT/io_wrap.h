#pragma once

#include "framework.h"

#include <vector>

#include "RT/rtweekend.h"

using std::vector;

COLORREF color2ref(const color& pixel_color, int samples_per_pixel);
void rt2pixel(CDC* out_img, int img_width, int img_height, const vector<vector<color>>& in_img, int samples_per_pixel);
UINT MFC_RT_CORE(LPVOID pParam);

struct MFC_RT_CORE_PARAM {
	wchar_t* fname;
	HWND hWnd;
};

using RT_PARAM = MFC_RT_CORE_PARAM;