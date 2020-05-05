#ifndef TRACKINGHPP
#define TRACKINGHPP

#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include "xtensor/xfixed.hpp"
#include "xtensor/xadapt.hpp"
#include "xtensor/xpad.hpp"
#include "xtensor/xstrided_view.hpp"
#include "xtensor/xmanipulation.hpp"
#include "xtensor/xsort.hpp"
#include "xtensor/xindex_view.hpp"
#include <float.h>
#include "util.hpp"
#include "Vec2.hpp"
#include <math.h>

class Focus{
	private:
		float mean_y;
		float mean_x;
		float border;
		float resting_border;
		float resting_center_x;
		float resting_center_y;

	public:
		Focus();
		Focus(xt::xarray<float> frame, float border=0.1);
		virtual ~Focus();

		void update(xt::xarray<float> bboxes, float frameh, float target_ratio=0.55);
		std::tuple<xt::xarray<float>, std::tuple<int, int, int, int>> crop(xt::xarray<float> frame);
};

#endif