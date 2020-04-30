#include <iostream>
#include "util.hpp"
#include "anchors.hpp"

int main(){
	//Anchors a(32, xt::xarray<float>{1, 0.5}, xt::xarray<float>{1, 0.5}, (2, 2))
	xt::xarray<float> a = {{1,4,6,7},{0.8,0.4,2,3}};
	xt::xarray<float> b = {{1,5,2,6},{3,2,4,3}};
	std::cout<<iou(a, b)<<std::endl;
	return 0;
}