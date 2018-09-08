#include "MVector.h"

float MVector::Length() const
{
	float sq = x*x + y*y + z*z;
	return static_cast<float>(sqrt(sq));
}

// normalize a vector
MVector MVector::Normalize()
{
	float length = Length();
	if (length != 0.0f)
	{
		float inv = 1.0f / length;
		x *= inv;
		y *= inv;
		z *= inv;
	}
	return *this;
}

// dot product
float MVector::Dot(MVector v) const
{
	return x * v.x + y*v.y + z*v.z;
}

// cross product
MVector MVector::Cross(MVector rhs) const
{
	float m1 = y * rhs.z - z * rhs.y;
	float m2 = z * rhs.x - x * rhs.z;
	float m3 = x * rhs.y - y * rhs.x;
	return MVector(m1, m2, m3, 0.0f);
}

// vector1 == vector2 
bool MVector::operator==(const MVector& rhs) const
{
	if (abs(x - rhs.x) <= 0.000001f 
		&& abs(y - rhs.y) <= 0.000001f 
		&& abs(z - rhs.z) <= 0.000001f 
		&& abs(w - rhs.w) <= 0.000001f)
		return true;
	else
		return false;
}

// verctor * matrix
MVector MVector::operator* (const MMatrix& rhs) const
{
	return MVector(x*rhs._11 + y*rhs._21 + z*rhs._31 + w*rhs._41,
					x*rhs._12 + y*rhs._22 + z*rhs._32 + w*rhs._42,
					x*rhs._13 + y*rhs._23 + z*rhs._33 + w*rhs._43,
					x*rhs._14 + y*rhs._24 + z*rhs._34 + w*rhs._44);
}

// vector * vetcor
MVector MVector::operator*(const MVector& rhs) const
{
	return MVector(
		x * rhs.x,
		y * rhs.y,
		z * rhs.z,
		w * rhs.w
	);
}

// vector * float
MVector MVector::operator*(float factor) const
{
	return MVector(
		x * factor,
		y * factor,
		z * factor,
		w
	);
}

// vector1 + vector2
MVector MVector::operator+(const MVector& rhs) const
{
	return MVector(x + rhs.x, y + rhs.y, z + rhs.z, 0.0f);
}

// vector1 - vector2
MVector MVector::operator-(const MVector& rhs) const
{
	return MVector(x - rhs.x, y - rhs.y, z - rhs.z, 0.0f);
}

// vector -> -vector
MVector MVector::operator-() const
{
	return MVector(-x, -y - z, w);
}
