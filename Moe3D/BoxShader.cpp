#include "BoxShader.h"



BoxShader::BoxShader()
{
}


BoxShader::~BoxShader()
{
}

void BoxShader::SetWorldViewProj(const MMatrix& worldViewProj)
{
	m_worldViewProj = worldViewProj;
}

void BoxShader::SetTexture(const Texture2D& tex)
{
	m_tex = tex;
}

void BoxShader::SetWorld(const MMatrix& world)
{
	m_world = world;
}

void BoxShader::SetWorldInvTranspose(const MMatrix& worldInvTrans)
{
	m_worldInvTranspose = worldInvTrans;
}

void BoxShader::SetEyePos(const MVector& eyePos)
{
	m_eyePos = eyePos;
}

void BoxShader::SetMaterial(const Lights::Material& material)
{
	m_material.ambient = material.ambient;
	m_material.diffuse = material.diffuse;
	m_material.reflect = material.reflect;
	m_material.specular = material.specular;
}

void BoxShader::SetDirLight(const Lights::DirectionalLight& dirLight)
{
	m_dirLight.ambient = dirLight.ambient;
	m_dirLight.diffuse = dirLight.diffuse;
	m_dirLight.direction = dirLight.direction;
	m_dirLight.specular = dirLight.specular;
}

VertexOut BoxShader::VS(const VertexIn& vin)
{
	VertexOut out;
	out.posH = vin.pos * m_worldViewProj;
	
	out.posTrans = vin.pos * m_world;
	out.normal = out.normal * m_worldInvTranspose;

 	out.color = vin.color;
 	out.tex = vin.tex;

	return out;
}

MVector BoxShader::PS(VertexOut& pin)
{
	//单位化法线
	pin.normal.Normalize();

	//纹理采样
	MVector texColor = m_tex.Sample(pin.tex);

	//顶点到观察点向量
	MVector toEye = (m_eyePos - pin.posTrans).Normalize();

	//初始化颜色值全部为0
	MVector ambient(0.f, 0.f, 0.f, 0.f);
	MVector diffuse(0.f, 0.f, 0.f, 0.f);
	MVector specular(0.f, 0.f, 0.f, 0.f);

	//光源计算后得到的环境光、漫反射 、高光
	MVector A, D, S;

	Lights::ComputeDirectionalLight(m_material, m_dirLight, pin.normal, toEye, A, D, S);

	ambient = ambient + A;
	diffuse = diffuse + D;
	specular = specular + S;


	//纹理+光照计算公式： 纹理*(环境光+漫反射光)+高光
	MVector litColor = texColor * (ambient + diffuse) + specular;

	//最终颜色透明度使用漫反射光的透明度
	litColor.w = m_material.diffuse.w * texColor.w;

	return litColor;
}
