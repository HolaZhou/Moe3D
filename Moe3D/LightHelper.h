#pragma once

#include <windows.h>
#include <algorithm>
#include "../Math/MMath.h"

namespace Lights {
	//平行光
	struct DirectionalLight
	{
		DirectionalLight() { ZeroMemory(this, sizeof(this)); }

		MVector ambient;	//环境光
		MVector diffuse;	//漫反射光
		MVector specular;	//高光
		MVector direction;	//光照方向
	};
	
	//点光源
	struct PointLight
	{
		PointLight() { ZeroMemory(this, sizeof(this)); }

		MVector ambient;
		MVector diffuse;
		MVector specular;

		MVector position;//光源位置

		MVector att;     //衰减系数

		float range;      //光照范围
	};
	//聚光灯
	struct SpotLight
	{
		SpotLight() { ZeroMemory(this, sizeof(this)); }

		MVector ambient;
		MVector diffuse;
		MVector specular;

		MVector position;	//光照位置
		
		MVector direction;	//光照方向
		
		MVector att;		//衰减系数
		float range;			//光照范围
		float spot;			//光照强度系数   
		
	};
	
	//材质
	struct Material
	{
		Material() { ZeroMemory(this, sizeof(this)); }

		MVector ambient;
		MVector diffuse;
		MVector specular;//w表示高光强度
		MVector reflect;
	};

	//计算平行光
	inline void ComputeDirectionalLight(
		const Material& mat,				//材质
		const DirectionalLight& L,		//平行光
		MVector normal,					//顶点法线
		MVector toEye,					//顶点到眼睛的向量
		MVector & ambient,				//计算结果:环境光
		MVector & diffuse,				//计算结果:漫反射光
		MVector & spec)					//计算结果:高光
	{
		// 结果初始化为0
		ambient = MVector( 0.0f, 0.0f, 0.0f, 0.0f );
		diffuse = MVector(0.0f, 0.0f, 0.0f, 0.0f);
		spec = MVector(0.0f, 0.0f, 0.0f, 0.0f);

		// 光线方向
		MVector lightVec = -L.direction;
		// 环境光直接计算
		ambient = mat.ambient * L.ambient;

		// 计算漫反射系数
		//光线、法线方向归一化
		lightVec.Normalize();
		float diffuseFactor = lightVec.Dot(normal);
		// 顶点背向光源不再计算

		if (diffuseFactor > 0.0f)
		{
			//入射光线关于法线的反射向量
			MVector v = MathUtil::Reflect(-lightVec, normal);

			float specFactor = pow(max(v.Dot(toEye), 0.0f), mat.specular.w);

			//计算漫反射光
			diffuse = mat.diffuse * L.diffuse * diffuseFactor;
			//计算高光
			spec = mat.specular * L.specular * specFactor;
		}
	}

	//计算点光源
	inline void ComputePointLight(
		const Material& mat,        //材质
		PointLight L,				//点光源
		MVector pos,				//顶点位置
		MVector normal,				//顶点法线
		MVector toEye,				//顶点到眼睛的向量
		MVector& ambient,			//计算结果:环境光
		MVector& diffuse,			//计算结果:漫反射光
		MVector& spec)				//计算结果:高光
	{
		ambient = MVector(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = MVector(0.0f, 0.0f, 0.0f, 0.0f);
		spec = MVector(0.0f, 0.0f, 0.0f, 0.0f);

		//光照方向：顶点到光源
		MVector lightVec = L.position - pos;

		//顶点到光源距离
		float d = MathUtil::Length(lightVec);

		//超过范围不再计算
		if (d > L.range)
			return;

		//归一化光照方向
		lightVec = lightVec * (1.f / d);

		//计算环境光
		ambient = mat.ambient * L.ambient;

		//漫反射系数
		float diffuseFactor = lightVec.Dot(normal);

		if (diffuseFactor > 0.0f)
		{
			MVector v = MathUtil::Reflect(-lightVec, normal);
			float specFactor = pow(max(v.Dot(toEye), 0.0f), mat.specular.w);
			//计算漫反射光
			diffuse = mat.diffuse * L.diffuse * diffuseFactor;
			//计算高光
			spec = mat.specular * L.specular * specFactor;
		}

		// 计算衰减
		float att = 1.f / L.att.Dot(MVector(1.f, d, d*d));
		diffuse = diffuse * att;
		spec = diffuse * att;
	}

	//计算聚光灯
	inline void  ComputeSpotLight(
		const Material& mat,            //材质
		const SpotLight& L,				//聚光灯
		MVector pos,					//顶点位置
		MVector normal,					//顶点法线
		MVector toEye,					//顶点到眼睛向量
		MVector& ambient,				//计算结果:环境光
		MVector& diffuse,				//计算结果:漫反射光
		MVector& spec)					//计算结果:高光
	{
		//初始化结果
		ambient = MVector(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = MVector(0.0f, 0.0f, 0.0f, 0.0f);
		spec = MVector(0.0f, 0.0f, 0.0f, 0.0f);

		//光照方向：顶点到光源
		MVector lightVec = L.position - pos;

		//顶点到光源距离
		float d = MathUtil::Length(lightVec);

		//距离大于光照方向不再计算
		if (d > L.range)
			return;

		//归一化光照方向
		lightVec = lightVec * (1.f / d);

		//计算环境光
		ambient = mat.ambient * L.ambient;
		//计算漫反射系数
		float diffuseFactor = lightVec.Dot(normal);

		if (diffuseFactor > 0.0f)
		{
			MVector v = MathUtil::Reflect(-lightVec, normal);
			float specFactor = pow(max(v.Dot(toEye), 0.0f), mat.specular.w);
			//漫反射光
			diffuse = mat.diffuse * L.diffuse * diffuseFactor;
			//高光
			spec = mat.specular * L.specular * specFactor;
		}

		//聚光衰减系数
		float spot = pow(max(-lightVec.Dot(L.direction), 0.0f), L.spot);
		//衰减系数
		float att = spot / L.att.Dot(MVector(1.0f, d, d*d));
		ambient = ambient * spot;
		diffuse = diffuse * att;
		spec = spec * att;
	}
}


