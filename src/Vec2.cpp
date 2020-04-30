#include "Vec2.hpp"

Vec2::Vec2(float x, float y){
	e[0] = x;
	e[1] = y;
}

Vec2::~Vec2(){}

Vec2& Vec2::set(float e0, float e1){
	e[0] = e0;
	e[1] = e1;
	return *this;
}

float Vec2::operator[](int i) const {
	return e[i];
}

float& Vec2::operator[](int i) {
	return e[i];
}

float Vec2::x() const {
	return e[0];
}

float Vec2::y() const {
	return e[1];
}

Vec2& Vec2::operator+=(const Vec2 &v){
	e[0] += v.e[0];
	e[1] += v.e[1];
	return *this;
}

Vec2& Vec2::operator-=(const Vec2 &v){
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	return *this;
}

Vec2 operator+(const Vec2 &v1, const Vec2 &v2){
	return Vec2(v1.e[0]+v2.e[0], v1.e[1]+v2.e[1]);
}

Vec2 operator-(const Vec2 &v1, const Vec2 &v2){
	return Vec2(v1.e[0]-v2.e[0], v1.e[1]-v2.e[1]);
}

Vec2 operator-(const Vec2 &v){
	return Vec2(-v.e[0], -v.e[1]);
}

std::ostream& operator<<(std::ostream &out, Vec2 &v){
	out << "[" << v.e[0] << ", " << v.e[1] << "]";
	return out;
}
