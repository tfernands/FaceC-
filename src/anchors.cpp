#include "anchors.hpp"

using namespace xt::placeholders;
xt::xarray<float> Anchors::create_anchors(float size, xt::xarray<float> aspect_ratios, xt::xarray<float> scales){
	xt::xarray<float> anchors = xt::zeros<float>({(int)aspect_ratios.shape()[0]*(int)scales.shape()[0], 4});
	xt::view(anchors, xt::all(), xt::range(2,_)) = xt::transpose(xt::tile(scales.reshape({1,-1}), {2,2}));
	xt::xarray<float> aspect_pow = xt::pow(aspect_ratios,.5);
	xt::xarray<float> aspect = xt::repeat(aspect_pow, 2, 0);
	xt::view(anchors, xt::all(), 2) *= aspect/2;
	xt::view(anchors, xt::all(), 3) /= aspect*2;
	xt::view(anchors, xt::all(), 0) -= xt::view(anchors, xt::all(), 2);
	xt::view(anchors, xt::all(), 1) -= xt::view(anchors, xt::all(), 3);
	return size*anchors;
}

xt::xarray<float> Anchors::replicate_anchors(xt::xarray<float> anchors, Vec2 dimensions, Vec2 fmap_size){
	float h = dimensions[0];
	float w = dimensions[1];
	float fh = fmap_size[0];
	float fw = fmap_size[1];
	xt::xarray<float> linspace1 = xt::linspace<float>(0.f, fw, w);
	xt::xarray<float> linspace2 = xt::linspace<float>(0.f, fh, h);
	auto shift_xy = xt::meshgrid(linspace1, linspace2);
	xt::xarray<float> shift_x = xt::ravel(std::get<0>(shift_xy));
	xt::xarray<float> shift_y = xt::ravel(std::get<1>(shift_xy));
	xt::xarray<float> shifts = xt::transpose(xt::vstack(xt::xtuple(shift_x, shift_y, shift_x, shift_y)));
	xt::xarray<float> output = xt::expand_dims(shifts, 1) + xt::expand_dims(anchors, 0);
	output = output.reshape({-1, 4});
	return output;
}

Anchors::Anchors(float size, xt::xarray<float> aspect_ratios, xt::xarray<float> scales, Vec2 dimensions, Vec2 fmap_size){
	xt::xarray<float> temp_anchors = create_anchors(size, aspect_ratios, scales);
	this->anchors = replicate_anchors(temp_anchors, dimensions, fmap_size);
}

//TODO: corrigir erros numericos
std::tuple<xt::xarray<float>, xt::xarray<float>> Anchors::compute_activation(xt::xarray<float> bboxes, float pos_thresh, float neg_thresh){
	xt::xarray<float> labels = -xt::zeros<float>({(int)this->anchors.shape()[0]});
	xt::xarray<float> ious = util::iou(this->anchors, bboxes);
	auto max_overlap_idx = xt::argmax(ious, 1);
	using index_type = std::array<std::size_t, 2>;
	std::vector<index_type> indices;
	for (unsigned int i = 0; i < (unsigned int)ious.shape()[0]; i++)
		indices.push_back({i, max_overlap_idx[i]});
	xt::xarray<float> max_overlaps = xt::index_view(ious, indices);
	xt::filter(labels, max_overlaps < neg_thresh) = 0;
	xt::filter(labels, max_overlaps > pos_thresh) = 1;
	xt::xarray<float> deltas = xt::zeros<float>({(int)labels.shape()[0], 5});
	xt::xarray<float> temp_bboxes = xt::index_view(bboxes, max_overlap_idx);
	xt::xarray<float> w = xt::view(this->anchors, xt::all(), 2)-xt::view(this->anchors, xt::all(), 0);
	xt::xarray<float> h = xt::view(this->anchors, xt::all(), 3)-xt::view(this->anchors, xt::all(), 1);
	xt::view(deltas, xt::all(), 0) = (xt::view(temp_bboxes, xt::all(), 0)-xt::view(this->anchors, xt::all(), 0))/w;
	xt::view(deltas, xt::all(), 1) = (xt::view(temp_bboxes, xt::all(), 1)-xt::view(this->anchors, xt::all(), 1))/h;
	xt::view(deltas, xt::all(), 2) = (xt::view(temp_bboxes, xt::all(), 2)-xt::view(this->anchors, xt::all(), 2))/w;
	xt::view(deltas, xt::all(), 3) = (xt::view(temp_bboxes, xt::all(), 3)-xt::view(this->anchors, xt::all(), 3))/h;
	xt::view(xt::filter(deltas, max_overlaps > pos_thresh), xt::all(), 4) = 1;
	return std::tuple<xt::xarray<float>, xt::xarray<float>>(labels, deltas);
}

//Testar (provavelmente contem muitos erros)
std::tuple<xt::xarray<float>, xt::xarray<float>> Anchors::compute_bboxes(xt::xarray<float> scores, xt::xarray<float> deltas, float score_threshold){
	xt::xarray<float> positives = scores > score_threshold;
	xt::xarray<float> w = xt::view(xt::filter(this->anchors, positives), 2) - xt::view(xt::filter(this->anchors, positives), 0);
	xt::xarray<float> h = xt::view(xt::filter(this->anchors, positives), 3) - xt::view(xt::filter(this->anchors, positives), 1);
	xt::xarray<float> bboxes = xt::filter(this->anchors, positives) + xt::filter(deltas, positives)*xt::stack(xt::xtuple(w, h, w, h), 1);
	xt::xarray<float> temp_scores = xt::filter(scores, positives);
	return std::tuple<xt::xarray<float>, xt::xarray<float>>(bboxes, temp_scores);
}