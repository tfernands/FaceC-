#ifndef ANCHORSHPP
#define ANCHORSHPP

#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include <float.h>
#include "util.hpp"
#include "Vec2.hpp"

class Anchors{
	private:

		static Anchors create_anchors(float size, xt::xarray<float> aspect_ratios, xt::xarray<float> scales){
			xt::xarray<float> anchors = xt::zeros<float>({aspect_ratios.shape()[0], scales.shape()[0], 4});


		}

	public:


		Anchors(float size, xt::xarray<float> aspect_ratios, xt::xarray<float> scales, Vec2 dimensions, Vec2 fmap_size){
			
		}

};


#endif