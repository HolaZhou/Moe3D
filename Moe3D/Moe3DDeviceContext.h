#pragma once
#include "Moe3DDevice.h"
#include "Vertex.h"
#include <vector>
#include "ShaderBase.h"

enum MOE3D_FILL_MODE//��Ⱦģʽ
{
	MOE3D_FILL_WIREFRAME,//�߿�ģʽ
	MOE3D_FILL_SOLIDE	  //ʵ��ģʽ
};

class Moe3DDeviceContext
{
public:
	Moe3DDeviceContext();
	~Moe3DDeviceContext();
public:
	void Init(Moe3DDevice* pDevice);										//��ʼ��
	void SetRenderMode(MOE3D_FILL_MODE mode);								//������Ⱦģʽ
	void SetVertexBuffer(std::vector<VertexIn> vertices);					//���ö��㻺��
	void SetCameraPos(const MVector& pos);									//�������λ��
	void SetIndexBuffer(std::vector<UINT> indices);							//������������
	void SetShader(ShaderBase* base);										//������ɫ��
	void DrawIndexed(UINT indexCount,UINT startIndexLocation,UINT startVertexLocation);																//����ͼ��
private:
	void ToCVV(VertexOut& v);																	//ͶӰ�������ת��Ϊcvv
	bool Clip(const VertexOut& v);																//cvv�ü�
	VertexOut TransformToProj(const VertexIn& v);													//ת����βü��ռ�
	void TransformToScreen(const MMatrix& m,VertexOut& v);										//ת������Ļ����
	bool BackFaceCulling(const VertexIn& v1, const VertexIn& v2, const VertexIn& v3);			//������������
	void BresenhamDrawLine(int x1, int y1, int x2, int y2);										//����
	void ScanlineFill(const VertexOut& left, const VertexOut& right, int yIndex);				//ɨ����
	void DrawTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);			//��������
	void DrawTriangleTop(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);			//��ƽ��������
	void DrawTriangleBottom(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3); 		//��ƽ��������
	void TriangleRasterization(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);	//��դ��������
private:
	Moe3DDevice* m_pDevice;													//�豸
	MOE3D_FILL_MODE m_renderMode;											//��Ⱦ״̬
	std::vector<VertexIn> m_vertices;										//���㻺��
	std::vector<UINT> m_indices;												//��������
	ShaderBase* m_pShader;													//��ɫ��
	MVector m_cameraPos;													//���λ�� ���ڱ�������
};

