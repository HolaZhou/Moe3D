#pragma once

#include <windows.h>
#include <algorithm>
#include "../Math/MMath.h"

namespace Lights {
	//ƽ�й�
	struct DirectionalLight
	{
		DirectionalLight() { ZeroMemory(this, sizeof(this)); }

		MVector ambient;	//������
		MVector diffuse;	//�������
		MVector specular;	//�߹�
		MVector direction;	//���շ���
	};
	
	//���Դ
	struct PointLight
	{
		PointLight() { ZeroMemory(this, sizeof(this)); }

		MVector ambient;
		MVector diffuse;
		MVector specular;

		MVector position;//��Դλ��

		MVector att;     //˥��ϵ��

		float range;      //���շ�Χ
	};
	//�۹��
	struct SpotLight
	{
		SpotLight() { ZeroMemory(this, sizeof(this)); }

		MVector ambient;
		MVector diffuse;
		MVector specular;

		MVector position;	//����λ��
		
		MVector direction;	//���շ���
		
		MVector att;		//˥��ϵ��
		float range;			//���շ�Χ
		float spot;			//����ǿ��ϵ��   
		
	};
	
	//����
	struct Material
	{
		Material() { ZeroMemory(this, sizeof(this)); }

		MVector ambient;
		MVector diffuse;
		MVector specular;//w��ʾ�߹�ǿ��
		MVector reflect;
	};

	//����ƽ�й�
	inline void ComputeDirectionalLight(
		const Material& mat,				//����
		const DirectionalLight& L,		//ƽ�й�
		MVector normal,					//���㷨��
		MVector toEye,					//���㵽�۾�������
		MVector & ambient,				//������:������
		MVector & diffuse,				//������:�������
		MVector & spec)					//������:�߹�
	{
		// �����ʼ��Ϊ0
		ambient = MVector( 0.0f, 0.0f, 0.0f, 0.0f );
		diffuse = MVector(0.0f, 0.0f, 0.0f, 0.0f);
		spec = MVector(0.0f, 0.0f, 0.0f, 0.0f);

		// ���߷���
		MVector lightVec = -L.direction;
		// ������ֱ�Ӽ���
		ambient = mat.ambient * L.ambient;

		// ����������ϵ��
		//���ߡ����߷����һ��
		lightVec.Normalize();
		float diffuseFactor = lightVec.Dot(normal);
		// ���㱳���Դ���ټ���

		if (diffuseFactor > 0.0f)
		{
			//������߹��ڷ��ߵķ�������
			MVector v = MathUtil::Reflect(-lightVec, normal);

			float specFactor = pow(max(v.Dot(toEye), 0.0f), mat.specular.w);

			//�����������
			diffuse = mat.diffuse * L.diffuse * diffuseFactor;
			//����߹�
			spec = mat.specular * L.specular * specFactor;
		}
	}

	//������Դ
	inline void ComputePointLight(
		const Material& mat,        //����
		PointLight L,				//���Դ
		MVector pos,				//����λ��
		MVector normal,				//���㷨��
		MVector toEye,				//���㵽�۾�������
		MVector& ambient,			//������:������
		MVector& diffuse,			//������:�������
		MVector& spec)				//������:�߹�
	{
		ambient = MVector(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = MVector(0.0f, 0.0f, 0.0f, 0.0f);
		spec = MVector(0.0f, 0.0f, 0.0f, 0.0f);

		//���շ��򣺶��㵽��Դ
		MVector lightVec = L.position - pos;

		//���㵽��Դ����
		float d = MathUtil::Length(lightVec);

		//������Χ���ټ���
		if (d > L.range)
			return;

		//��һ�����շ���
		lightVec = lightVec * (1.f / d);

		//���㻷����
		ambient = mat.ambient * L.ambient;

		//������ϵ��
		float diffuseFactor = lightVec.Dot(normal);

		if (diffuseFactor > 0.0f)
		{
			MVector v = MathUtil::Reflect(-lightVec, normal);
			float specFactor = pow(max(v.Dot(toEye), 0.0f), mat.specular.w);
			//�����������
			diffuse = mat.diffuse * L.diffuse * diffuseFactor;
			//����߹�
			spec = mat.specular * L.specular * specFactor;
		}

		// ����˥��
		float att = 1.f / L.att.Dot(MVector(1.f, d, d*d));
		diffuse = diffuse * att;
		spec = diffuse * att;
	}

	//����۹��
	inline void  ComputeSpotLight(
		const Material& mat,            //����
		const SpotLight& L,				//�۹��
		MVector pos,					//����λ��
		MVector normal,					//���㷨��
		MVector toEye,					//���㵽�۾�����
		MVector& ambient,				//������:������
		MVector& diffuse,				//������:�������
		MVector& spec)					//������:�߹�
	{
		//��ʼ�����
		ambient = MVector(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = MVector(0.0f, 0.0f, 0.0f, 0.0f);
		spec = MVector(0.0f, 0.0f, 0.0f, 0.0f);

		//���շ��򣺶��㵽��Դ
		MVector lightVec = L.position - pos;

		//���㵽��Դ����
		float d = MathUtil::Length(lightVec);

		//������ڹ��շ����ټ���
		if (d > L.range)
			return;

		//��һ�����շ���
		lightVec = lightVec * (1.f / d);

		//���㻷����
		ambient = mat.ambient * L.ambient;
		//����������ϵ��
		float diffuseFactor = lightVec.Dot(normal);

		if (diffuseFactor > 0.0f)
		{
			MVector v = MathUtil::Reflect(-lightVec, normal);
			float specFactor = pow(max(v.Dot(toEye), 0.0f), mat.specular.w);
			//�������
			diffuse = mat.diffuse * L.diffuse * diffuseFactor;
			//�߹�
			spec = mat.specular * L.specular * specFactor;
		}

		//�۹�˥��ϵ��
		float spot = pow(max(-lightVec.Dot(L.direction), 0.0f), L.spot);
		//˥��ϵ��
		float att = spot / L.att.Dot(MVector(1.0f, d, d*d));
		ambient = ambient * spot;
		diffuse = diffuse * att;
		spec = spec * att;
	}
}


