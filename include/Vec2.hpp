#ifndef VEC2HPP
#define VEC2HPP

#include <fstream>

class Vec2{
	
	public:
		float e[2];

		Vec2(float x, float y);
		virtual ~Vec2();

		Vec2& set(float e0, float e1);
		float operator[](int i) const;
		float& operator[](int i);
		float x() const;
		float y() const;
		Vec2& operator+=(const Vec2 &v);
		Vec2& operator-=(const Vec2 &v);
};

Vec2 operator+(const Vec2 &v1, const Vec2 &v2);
Vec2 operator-(const Vec2 &v1, const Vec2 &v2);
Vec2 operator-(const Vec2 &v);
std::ostream& operator<<(std::ostream &out, Vec2 &v);

#endif

