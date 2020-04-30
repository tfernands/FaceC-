#ifndef UTILHPP
#define UTILHPP

#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include <float.h>

xt::xarray<float> iou(xt::xarray<float> a, xt::xarray<float> b){
 	xt::xarray<float> x0 = xt::maximum(xt::expand_dims(xt::view(a, xt::all(), 0), 1), xt::view(b, xt::all(), 0));
	xt::xarray<float> y0 = xt::maximum(xt::expand_dims(xt::view(a, xt::all(), 1), 1), xt::view(b, xt::all(), 1));
	xt::xarray<float> x1 = xt::minimum(xt::expand_dims(xt::view(a, xt::all(), 2), 1), xt::view(b, xt::all(), 2));
	xt::xarray<float> y1 = xt::minimum(xt::expand_dims(xt::view(a, xt::all(), 3), 1), xt::view(b, xt::all(), 3));
	xt::xarray<float> iw = xt::clip(x1-x0, 0, FLT_MAX);
	xt::xarray<float> ih = xt::clip(y1-y0, 0, FLT_MAX);
	xt::xarray<float> ab_area = iw*ih;
	xt::xarray<float> b_area = (xt::view(b, xt::all(), 2)-xt::view(b, xt::all(), 0))*(xt::view(b, xt::all(), 3)-xt::view(b, xt::all(), 1));
	xt::xarray<float> a_area = (xt::view(a, xt::all(), 2)-xt::view(a, xt::all(), 0))*(xt::view(a, xt::all(), 3)-xt::view(a, xt::all(), 1));
	return ab_area/(xt::expand_dims(a_area, 1)+b_area-ab_area);
}

#endif