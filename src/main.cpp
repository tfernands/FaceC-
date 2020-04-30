#include <iostream>
#include "util.hpp"
#include "anchors.hpp"

int main(){
	Anchors anchor(32, xt::xarray<float>({1, 0.5}), xt::xarray<float>({1, 0.5}), Vec2(2, 2), Vec2(2,2));
	//anchor.compute_bboxes(xt::xarray<float>({1, 0.5}))
	float pos_thresh=.5;
	float neg_thresh=.3;
	xt::xarray<float> bboxes = {{-8,-6,8,10}, {0,0,3,2}, {0.5,0.8,3, 4}};
	auto label_deltas = anchor.compute_activation(bboxes);
	std::cout <<std::get<0>(label_deltas)<<std::endl;
	std::cout <<std::get<1>(label_deltas)<<std::endl;
	return 0;
}