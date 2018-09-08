#pragma once
#include "ShaderBase.h"
#include "MMath.h"

class BoxShader : public ShaderBase
{
public:
	BoxShader();
	~BoxShader();

private:
 	MMatrix						m_worldViewProj;		//�����ӽ�ͶӰ����	
	Texture2D					m_tex;				//����
 	MMatrix						m_world;				//�������
 	MMatrix						m_worldInvTranspose;	//�������������ת�ã����ڵ�������
 	Lights::Material				m_material;			//����
	Lights::DirectionalLight		m_dirLight;			//ƽ�й�
	MVector						m_eyePos;			//�۲��

public:
	void SetWorldViewProj(const MMatrix& worldViewProj);
	void SetTexture(const Texture2D& tex);
	void SetWorld(const MMatrix& world);
	void SetWorldInvTranspose(const MMatrix& worldInvTrans);
	void SetEyePos(const MVector& eyePos);
	void SetMaterial(const Lights::Material& material);
	void SetDirLight(const Lights::DirectionalLight& dirLight);
public:
	VertexOut VS(const VertexIn& vin);	//������ɫ��
	MVector PS(VertexOut& pin);
};

