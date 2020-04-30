#ifndef VEC2HPP
#define VEC2HPP

class Vec2{
	
	public:
		float e[2];
		Vec2(float x, float y){
			e[0] = x;
			e[1] = y;
		}

		virtual ~Vec2(){}

		inline Vec2& set(float e0, float e1){
			e[0] = e0;
			e[1] = e1;
			return *this;
		}

		inline float operator[](int i) const {
			return e[i];
		}

		inline float& operator[](int i) {
			return e[i];
		}

		inline float x() const {
			return e[0];
		}

		inline float y() const {
			return e[1];
		}

		inline Vec2& operator+=(const Vec2 &v){
			e[0] += v.e[0];
			e[1] += v.e[1];
			return *this;
		}

		inline Vec2& operator-=(const Vec2 &v){
			e[0] -= v.e[0];
			e[1] -= v.e[1];
			return *this;
		}

		friend inline Vec2 operator+(const Vec2 &v1, const Vec2 &v2){
			return Vec2(v1.e[0]+v2.e[0], v1.e[1]+v2.e[1]);
		}

		friend inline Vec2 operator-(const Vec2 &v1, const Vec2 &v2){
			return Vec2(v1.e[0]-v2.e[0], v1.e[1]-v2.e[1]);
		}

		friend inline Vec2 operator-(const Vec2 &v){
			return Vec2(-v.e[0], -v.e[1]);
		}

		friend std::ostream& operator<<(std::ostream &out, Vec2 &v){
			out << "[" << v.e[0] << ", " << v.e[1] << "]";
			return out;
		}
};


#endif

