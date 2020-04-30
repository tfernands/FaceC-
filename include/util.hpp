#ifndef UTILHPP
#define UTILHPP

#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include <float.h>

namespace util{
	xt::xarray<float> iou(xt::xarray<float> a, xt::xarray<float> b);
};

#endif