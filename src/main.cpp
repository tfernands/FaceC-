#include <iostream>
#include "util.hpp"
#include "anchors.hpp"

int main(){
	Anchors abc(32, xt::xarray<float>({1, 0.5}), xt::xarray<float>({1, 0.5}), Vec2(2, 2), Vec2(2,2));
	xt::xarray<float> a = {{1,4,6,7},{0.8,0.4,2,3}};
	xt::xarray<float> b = {{1,5,2,6},{3,2,4,3}};
	std::cout<<iou(a, b)<<std::endl;
	std::cout<<xt::zeros<float>({2, 3, 4})<<std::endl;
	return 0;
}