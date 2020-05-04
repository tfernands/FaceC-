#ifndef ANCHORSHPP
#define ANCHORSHPP

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

using namespace xt::placeholders;

class Anchors{
	private:
		static xt::xarray<float> create_anchors(float size, xt::xarray<float> aspect_ratios, xt::xarray<float> scales);
		static xt::xarray<float> replicate_anchors(xt::xarray<float> anchors, Vec2 dimensions, Vec2 fmap_size);
		
	public:
		xt::xarray<float> anchors;
		Anchors(float size, xt::xarray<float> aspect_ratios, xt::xarray<float> scales, Vec2 dimensions, Vec2 fmap_size);

		//TODO: corrigir erros numericos
		std::tuple<xt::xarray<float>, xt::xarray<float>> compute_activation(xt::xarray<float> bboxes, float pos_thresh=.5, float neg_thresh=.3);
		
		// Testar (provavelmente contem muitos erros)
		std::tuple<xt::xarray<float>, xt::xarray<float>> compute_bboxes(xt::xarray<float> scores, xt::xarray<float> deltas, float score_threshold=0.5);
};


#endif