#pragma once
#include "Moe3D.h"
#include "BoxShader.h"
#include "MMath.h"
#include "GeometryGenerator.h"

class BoxDemo
{
public:
	BoxDemo();
	~BoxDemo();
public:
	bool Init(HINSTANCE hInstance, HWND hWnd);
	void Update(float dt);
	void Render();
	void Clear();	

	//����¼�����
	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);
public:
	inline Moe3DDevice*& GetDevice() { return m_pDevice; }
private:
	int							m_width, m_height;
	HINSTANCE					m_hInstance;
	HWND							m_hWnd;

	Moe3DDevice*				m_pDevice;
	Moe3DDeviceContext*			m_pImmediateContext;
	BoxShader*					m_pShader;

	MMatrix						m_worldViewProj;			//�����ӽ�ͶӰ����
	MMatrix						m_world;					//����任����
	MMatrix						m_worldInvTranspose;		//����任������ת�� ���ڵ�������

	std::vector<VertexIn>		m_vertices;				//���㻺��
	std::vector<UINT>			m_indices;				//��������

	GeometryGenerator::MeshData	m_box;

	Texture2D					m_tex;					//����

	Lights::Material				m_material;				//����
	Lights::DirectionalLight		m_dirLight;				//ƽ�й�Դ

	//���������λ�ýǶȵ�
	float						m_theta;
	float						m_phi;
	float						m_radius;
	POINT						m_lastMousePos;
};

