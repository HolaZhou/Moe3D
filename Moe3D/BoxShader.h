#pragma once
#include "ShaderBase.h"
#include "MMath.h"

class BoxShader : public ShaderBase
{
public:
	BoxShader();
	~BoxShader();

private:
 	MMatrix						m_worldViewProj;		//世界视角投影矩阵	
	Texture2D					m_tex;				//纹理
 	MMatrix						m_world;				//世界矩阵
 	MMatrix						m_worldInvTranspose;	//世界矩阵逆矩阵的转置，用于调整法线
 	Lights::Material				m_material;			//材质
	Lights::DirectionalLight		m_dirLight;			//平行光
	MVector						m_eyePos;			//观察点

public:
	void SetWorldViewProj(const MMatrix& worldViewProj);
	void SetTexture(const Texture2D& tex);
	void SetWorld(const MMatrix& world);
	void SetWorldInvTranspose(const MMatrix& worldInvTrans);
	void SetEyePos(const MVector& eyePos);
	void SetMaterial(const Lights::Material& material);
	void SetDirLight(const Lights::DirectionalLight& dirLight);
public:
	VertexOut VS(const VertexIn& vin);	//顶点着色器
	MVector PS(VertexOut& pin);
};

