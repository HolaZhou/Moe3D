#pragma once
#include <windows.h>
#include "MVector.h"
#include "Vertex.h"

class Moe3DDevice
{
public:
	Moe3DDevice(int width, int height);
	~Moe3DDevice();
public:
	void DrawPixel(int x, int y, MVector color);	
	float GetZ(int x, int y) const;
	void SetZ(int x, int y, float z);
	inline UINT*& GetFrameBuffer() { return m_pFramebuffer; }
	inline int GetClientWidth() { return m_width; }
	inline int getClientHeight() { return m_height; }
	void ClearBuffer(MVector color);
private:
	int m_width;
	int m_height;
	UINT* m_pFramebuffer;
	float **m_zBuffer;		//z»º´æ
};