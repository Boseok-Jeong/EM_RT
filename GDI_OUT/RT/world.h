#pragma once

#include "hittable_list.h"

hittable_list cornell_box();
hittable_list cornell_box(shared_ptr<hittable_list>& pdf_area);