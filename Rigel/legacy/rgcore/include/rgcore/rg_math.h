#pragma once
#if defined(min)
#undef min
#endif
#if defined(max)
#undef max
#endif
#include <math.h>
#include <limits>
namespace rg {
	typedef float RgFloat;
	struct RgVec2{
		RgFloat x, y;
		RgVec2(const int _x,const int _y) :x((float)_x), y((float)_y) {}
		RgVec2(const RgFloat _x,const RgFloat _y):x(_x),y(_y){}
		RgVec2():x(0),y(0){}
		RgVec2(const RgVec2& v) :x(v.x), y(v.y) {}

		RgVec2& operator +=(RgFloat s) {
			x += s;
			y += s;
			return *this;
		}
		RgVec2& operator -=(RgFloat s) {
			x -= s;
			y -= s;
			return *this;
		}
		RgVec2& operator *=(RgFloat s) {
			x *= s;
			y *= s;
			return *this;
		}
		RgVec2& operator /=(RgFloat s) {
			if (s != 0) {
				x /= s;
				y /= s;
				return *this;
			}
			return *this;
		}
		RgVec2& operator +=(const RgVec2& v){
			x += v.x;
			y += v.y;
			return *this;
		}
		RgVec2& operator -=(const RgVec2& v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}
		RgVec2& operator *=(const RgVec2& v) {
			x *= v.x;
			y *= v.y;
			return *this;
		}
		//等等等等，一脸懵逼
		RgVec2& operator /=(const RgVec2& v) {
			x /= v.x;
			y /= v.y;
			return *this;
		}
		RgFloat dot(const RgVec2& v) {
			return x*v.x + y*v.y;
		}
		RgFloat length(){
			return sqrt(this->dot(*this));
		}

		inline bool operator==(const RgVec2& v) {
			if (v.x == x && v.y == y) return true;
			return false;
		}
		inline bool operator!=(const RgVec2& v) {
			return (v.x != x || v.y != y);
		}

		std::string toStr() const;

		static const RgVec2 Zero;
	};

	inline const RgFloat abs(RgFloat s) {
		return abs((float)s);
	}
	inline const RgVec2 operator+(const RgVec2& v1, const RgFloat& s) {
		return{ v1.x + s,v1.y + s };
	}
	inline const RgVec2 operator-(const RgVec2& v1, const RgFloat& s) {
		return{ v1.x - s,v1.y - s };
	}
	inline const RgVec2 operator*(const RgVec2& v1, const RgFloat& s) {
		return{ v1.x * s,v1.y * s };
	}
	inline const RgVec2 operator/(const RgVec2& v1, const RgFloat& s) {
		if (s != 0) {
			return{ v1.x / s,v1.y / s };
		}
		else{
			return v1;
		}
	}
	inline const RgVec2 operator+(const RgVec2& v1, const RgVec2& v2) {
		return{ v1.x + v2.x,v1.y + v2.y };
	}
	inline const RgVec2 operator-(const RgVec2& v1, const RgVec2& v2) {
		return{ v1.x - v2.x,v1.y - v2.y };
	}
	inline const RgVec2 operator*(const RgVec2& v1, const RgVec2& v2) {
		return{ v1.x * v2.x,v1.y * v2.y };
	}
	//等等
	inline const RgVec2 operator/(const RgVec2& v1, const RgVec2& v2) {
		return{ v1.x / v2.x,v1.y / v2.y };
	}
	inline const RgFloat dot(const RgVec2& v1, const RgVec2& v2) {
		return v1.x*v2.x + v1.y*v2.y;
	}
	inline const RgVec2 inverse(RgVec2 const& v){
		return { -v.x,-v.y };
	}
	inline const RgFloat length(RgVec2 const& v) {
		return sqrt(dot(v, v));
	}
	inline const RgVec2 min(RgVec2 const& v1, RgVec2 const& v2) {
		return RgVec2(v1.x < v2.x ? v1.x : v2.x, v1.y < v2.y ? v1.y : v2.y);
	}
	inline const RgVec2 max(RgVec2 const& v1, RgVec2 const& v2) {
		return RgVec2(v1.x > v2.x ? v1.x : v2.x, v1.y > v2.y ? v1.y : v2.y);
	}
	inline const RgVec2 abs(RgVec2 const& v){
		return { abs(v.x),abs(v.y) };
	}
	struct RgVec3 {
		RgFloat x = 0;
		RgFloat y = 0;
		RgFloat z = 0;
		RgVec3(int _x, int _y, int _z) :x((float)_x), y((float)_y), z((float)_z) {}
		RgVec3() :x(0), y(0), z(0) {}
		RgVec3(RgFloat _x, RgFloat _y, RgFloat _z) :x(_x), y(_y), z(_z){}
		inline RgVec3(const RgVec2& v) : x(v.x), y(v.y), z(0){}
		std::string toStr() const;
		RgVec3& operator +=(RgFloat s) {
			x += s;
			y += s;
			z += s;
			return *this;
		}
		RgVec3& operator -=(RgFloat s) {
			x -= s;
			y -= s;
			z -= s;
			return *this;
		}
		RgVec3& operator *=(RgFloat s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}
		RgVec3& operator /=(RgFloat s) {
			if (s != 0)
			{
				x /= s;
				y /= s;
				z /= s;
				return *this;
			}
			return *this;
		}
		RgVec3& operator +=(RgVec3 v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		RgVec3& operator -=(RgVec3 v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		RgVec3& operator *=(RgVec3 v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}
		RgVec3& operator /=(RgVec3 v) {
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}
		RgFloat dot(const RgVec3& v) {
			return x*v.x + y*v.y + z*v.z;
		}
		RgFloat length() {
			return sqrt(this->dot(*this));
		}
	};
	struct RgVec4 {
		RgFloat x, y, z, w;
		RgVec4(int _x, int _y, int _z, int _w) :x((float)_x), y((float)_y), z((float)_z), w((float)_w) {};
		RgVec4(RgFloat _x, RgFloat _y, RgFloat _z, RgFloat _w) :x(_x), y(_y), z(_z), w(_w) {};
		RgVec4() :x(0), y(0), z(0), w(0) {};
		RgVec4(float v) :x(v), y(v), z(v), w(v) {};
		RgVec4(const RgVec2& v1, const RgVec2& v2) :x(v1.x), y(v1.y), z(v2.x), w(v2.y) {};
		RgVec4(const RgVec2& v1, float _z, float _w) :x(v1.x), y(v1.y), z(_z), w(_w) {};
		std::string toStr() const;

		inline const RgVec3 xyz() const{
			return RgVec3(x, y, z);
		}

		RgVec4& operator=(const RgVec2& v) {
			this->x = v.x;
			this->y = v.y;
			this->z = 0;
			this->w = 0;
			return *this;
		}

		inline const RgVec2 xy() const {
			return RgVec2(x, y);
		}
		inline const RgVec2 zw() const {
			return RgVec2(z, w);
		}

		inline void setxy(const RgVec2& xy) {
			x = xy.x;
			y = xy.y;
		}
		inline void setzw(const RgVec2& zw) {
			z = zw.x;
			w = zw.y;
		}

		bool rect_contain(const RgVec2& pos);

		const static RgVec4 Zero;
	};


	inline const RgVec3 operator+(const RgVec3& v1, const RgVec3& v2) {
		return { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
	}

	inline const RgVec4 operator+(const RgVec4& v1, const RgVec4& v2) {
		return{ v1.x + v2.x,v1.y + v2.y,v1.z + v2.z,v1.z+v2.z};
	}

	
	inline const RgVec3 operator-(const RgVec3& v1, const RgVec3& v2) {
		return{ v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
	}
	inline const RgVec4 operator-(const RgVec4& v1, const RgVec4& v2) {
		return{ v1.x - v2.x,v1.y - v2.y,v1.z - v2.z,v1.z - v2.z };
	}
	
	inline const RgFloat operator*(const RgVec3& v1, const RgVec3& v2) {
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}
	inline const RgFloat operator*(const RgVec4& v1, const RgVec4& v2) {
		return v1.w*v2.w + v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}

	inline const RgVec4 operator*(const RgVec4& v, const float d) {
		return RgVec4(v.x*d, v.y*d, v.z*d, v.w*d);
	}
	inline const RgVec4 operator/(const RgVec4& v, const float d) {
		return v*(1.0f / d);
	}


	struct RgMatrix3x3 {
		RgVec3 m1;
		RgVec3 m2;
		RgVec3 m3;
	};
	
	struct RgMatrix4x4 {
		RgVec4 m1;
		RgVec4 m2;
		RgVec4 m3;
		RgVec4 m4;
	};

	const RgFloat RgEpsilon = std::numeric_limits<float>::epsilon();

	inline const RgFloat RgMathClampMin(float v, float min) {
		return v < min ? min : v;
	}
}