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
	//���Բ�ֵ tλ��[0,1]
	float Lerp(float x1, float x2, float t);

	//ʸ����ֵ
	MVector Lerp(const MVector& v1, const MVector& v2, float t);

	//ZCFLOAT2 ��ֵ
	MFLOAT2 Lerp(const MFLOAT2& v1, const MFLOAT2& v2, float t);

	//ZCFLOAT3��ֵ
	MFLOAT3 Lerp(const MFLOAT3& v1, const MFLOAT3& v2, float t);

	//VertexOut��ֵ
	VertexOut Lerp(const VertexOut& v1, const VertexOut& v2, float t);

	//clamp
	float Clamp(float x, float min, float max);

	//�Ƕ�ת����
	inline float MConvertToRadians(float fDegrees) { return fDegrees * (PI / 180.0f); }

	//��������
	float Length(const MVector& v);

	//��λ����
	MMatrix MMatrixIdentity();

	//����ת��
	MMatrix MMatrixTranspose(const MMatrix& mat);

	//�����Ӧ����ʽ	
	float MMatrixDet(const MMatrix& mat);

	//��������е�ÿһ�� 3*3�����Ӧ������ʽֵ
	float MMatrixAdjElem(
		float a1, float a2, float a3,
		float b1, float b2, float b3,
		float c1, float c2, float c3);

	//������� ��������ʽ��ɵľ����ת��
	MMatrix MMatrixAdj(const MMatrix& mat);

	//����� = �������/(����ʽֵ�ľ���ֵ)
	MMatrix MMatrixInverse(const MMatrix& mat);

	//���ž���
	MMatrix MMatrixScaling(float scaleX, float scaleY, float scaleZ);

	//ƽ�ƾ���
	MMatrix MMatrixTranslate(float offsetX, float offsetY, float offsetZ);

	//��x����ת����
	MMatrix MMatrixRotationX(float angle);

	//��y����ת����
	MMatrix MMatrixRotationY(float angle);

	//��z����ת����
	MMatrix MMatrixRotationZ(float angle);

	//��ȡ�ӽǾ���
	MMatrix MMatrixLookAtLH(MVector eyePos, MVector lookAt, MVector up);

	//��ȡͶӰ���� ͬdx�е�XMMatrixPerspectiveFovLH
	//									    �۲��            ��߱�       ���ü�ƽ��   Զ�ü�ƽ��       
	MMatrix MMatrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ);
	
	//ͶӰ���������굽��Ļ����任����
	MMatrix MMatrixScreenTransform(int clientWidth, int clientHeight);

	//��ɫZCVector(r,b,g,a)ת��ΪUINT
	UINT ColorToUINT(const MVector& color);

	//�������������ڷ��ߵķ�������
	MVector Reflect(const MVector& vin, const MVector& normal);
}