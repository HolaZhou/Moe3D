#pragma once
#include <cmath>
#include "MMatrix.h"

class MVector
{
public:
	float x;
	float y;
	float z;
	float w;	//homogeneous coordinates£¬0->vector, 1->dot

public:
	MVector() = default;
	MVector(float x1, float y1, float z1, float w1 = 0) :x(x1), y(y1), z(z1), w(w1) {}
	MVector(const MVector& rhs) :x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
	MVector& operator= (const MVector& rhs)
	{
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

public:
	// length of the vector
	float Length() const;	
	// normalize a vector
	MVector Normalize();
	// dot product
	float Dot(MVector v) const;
	// cross product
	MVector Cross(MVector rhs) const;
	// vector1 == vector2
	bool operator==(const MVector& rhs) const;
	// vertor * matrix
	MVector operator* (const MMatrix& rhs) const;
	// verctor * vector
	MVector operator* (const MVector& rhs) const;
	// vector * float
	MVector operator*(float factor) const;
	// + 
	MVector operator+ (const MVector& rhs) const;
	// - 
	MVector operator- (const MVector& rhs) const;
	// negate
	MVector operator-() const;
	
};


class MFLOAT3
{
public:
	float x;
	float y;
	float z;
public:
	MFLOAT3() = default;
	MFLOAT3(float r,float b,float g):x(r),y(b),z(g){}
	MFLOAT3(const MFLOAT3& rhs) :x(rhs.x), y(rhs.y), z(rhs.z) {}
	MFLOAT3& operator= (const MFLOAT3& rhs)
	{
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
};


// to show texture
class MFLOAT2
{
public:
	float u;
	float v;
public:
	MFLOAT2() = default;
	MFLOAT2(float x, float y) :u(x), v(y) {}
	MFLOAT2(const MFLOAT2& rhs):u(rhs.u),v(rhs.v){}
	MFLOAT2& operator= (const MFLOAT2& rhs)
	{
		if (this == &rhs)
			return *this;
		u = rhs.u;
		v = rhs.v;
		return *this;
	}
};