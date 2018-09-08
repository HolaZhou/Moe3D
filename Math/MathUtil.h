#pragma once
#include "MVector.h"
#include "MMatrix.h"
#include "Vertex.h"
#include <windows.h>
#include <cmath>
#include <vector>

namespace MathUtil
{
	extern const float PI;
	//线性插值 t位于[0,1]
	float Lerp(float x1, float x2, float t);

	//矢量插值
	MVector Lerp(const MVector& v1, const MVector& v2, float t);

	//ZCFLOAT2 插值
	MFLOAT2 Lerp(const MFLOAT2& v1, const MFLOAT2& v2, float t);

	//ZCFLOAT3插值
	MFLOAT3 Lerp(const MFLOAT3& v1, const MFLOAT3& v2, float t);

	//VertexOut插值
	VertexOut Lerp(const VertexOut& v1, const VertexOut& v2, float t);

	//clamp
	float Clamp(float x, float min, float max);

	//角度转弧度
	inline float MConvertToRadians(float fDegrees) { return fDegrees * (PI / 180.0f); }

	//向量长度
	float Length(const MVector& v);

	//单位矩阵
	MMatrix MMatrixIdentity();

	//矩阵转置
	MMatrix MMatrixTranspose(const MMatrix& mat);

	//矩阵对应行列式	
	float MMatrixDet(const MMatrix& mat);

	//伴随矩阵中的每一项 3*3矩阵对应的行列式值
	float MMatrixAdjElem(
		float a1, float a2, float a3,
		float b1, float b2, float b3,
		float c1, float c2, float c3);

	//伴随矩阵 代数余子式组成的矩阵的转置
	MMatrix MMatrixAdj(const MMatrix& mat);

	//逆矩阵 = 伴随矩阵/(行列式值的绝对值)
	MMatrix MMatrixInverse(const MMatrix& mat);

	//缩放矩阵
	MMatrix MMatrixScaling(float scaleX, float scaleY, float scaleZ);

	//平移矩阵
	MMatrix MMatrixTranslate(float offsetX, float offsetY, float offsetZ);

	//绕x轴旋转矩阵
	MMatrix MMatrixRotationX(float angle);

	//绕y轴旋转矩阵
	MMatrix MMatrixRotationY(float angle);

	//绕z轴旋转矩阵
	MMatrix MMatrixRotationZ(float angle);

	//获取视角矩阵
	MMatrix MMatrixLookAtLH(MVector eyePos, MVector lookAt, MVector up);

	//获取投影矩阵 同dx中的XMMatrixPerspectiveFovLH
	//									    观察角            宽高比       近裁剪平面   远裁剪平面       
	MMatrix MMatrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ);
	
	//投影出来的坐标到屏幕坐标变换矩阵
	MMatrix MMatrixScreenTransform(int clientWidth, int clientHeight);

	//颜色ZCVector(r,b,g,a)转化为UINT
	UINT ColorToUINT(const MVector& color);

	//求入射向量关于法线的反射向量
	MVector Reflect(const MVector& vin, const MVector& normal);
}