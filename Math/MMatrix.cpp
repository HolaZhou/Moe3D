#include "MMatrix.h"


void MMatrix::Identity()
{
	_11 = 1.f; _12 = 0.f; _13 = 0.f; _14 = 0.f;
	_21 = 0.f; _22 = 1.f; _23 = 0.f; _24 = 0.f;
	_31 = 0.f; _32 = 0.f; _33 = 1.f; _34 = 0.f;
	_41 = 0.f; _42 = 0.f; _43 = 0.f; _44 = 1.f;
}

void MMatrix::SetZero()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			m[i][j] = 0.0f;	
}

// M1 == M2 / left hand side = right hand side
bool MMatrix::operator==(const MMatrix& rhs) const
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (abs(m[i][j] - rhs.m[i][j]) >= 0.000001f)
				return false;
	return true;
}

//M1 = M2 + M3
MMatrix MMatrix::operator+(const MMatrix& rhs) const
{
	MMatrix matrix;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			matrix.m[i][j]  = m[i][j] + rhs.m[i][j];
	return matrix;
}

//M1 = M2 - M3
MMatrix MMatrix::operator-(const MMatrix& rhs) const
{
	MMatrix matrix;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			matrix.m[i][j] = m[i][j] - rhs.m[i][j];
	return matrix;
}

//M1 = M2 * M3
MMatrix MMatrix::operator*(const MMatrix& rhs) const
{
	MMatrix matrix;
	for (int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
		{
			matrix.m[j][i] = (m[j][0] * rhs.m[0][i]) +
				          (m[j][1] * rhs.m[1][i]) +
				          (m[j][2] * rhs.m[2][i]) +
				          (m[j][3] * rhs.m[3][i]);
		}
	return matrix;
}
