#ifndef VEC2HPP
#define VEC2HPP

#include <fstream>

class Vec2{
	
	public:
		float e[2];

		Vec2(float x, float y);
		virtual ~Vec2();

		inline Vec2& set(float e0, float e1);
		inline float operator[](int i) const;
		inline float& operator[](int i);
		inline float x() const;
		inline float y() const;
		inline Vec2& operator+=(const Vec2 &v);
		inline Vec2& operator-=(const Vec2 &v);
};

inline Vec2 operator+(const Vec2 &v1, const Vec2 &v2);
inline Vec2 operator-(const Vec2 &v1, const Vec2 &v2);
inline Vec2 operator-(const Vec2 &v);
std::ostream& operator<<(std::ostream &out, Vec2 &v);

#endif

