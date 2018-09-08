#include "Moe3DDevice.h"
#include "MathUtil.h"
using namespace MathUtil;

Moe3DDevice::Moe3DDevice(int width, int height)
{
	m_width = width;
	m_height = height;
	m_zBuffer = new float*[width];
	for (int i = 0; i < width; ++i)
	{
		m_zBuffer[i] = new float[height];
	}
}


Moe3DDevice::~Moe3DDevice()
{
	if (m_pFramebuffer)
		delete m_pFramebuffer;
	if (m_zBuffer)
		for (int i = 0; i < m_width; ++i)
		{
			delete[] m_zBuffer[i];
		}
}

//»­ÏñËØ
void Moe3DDevice::DrawPixel(int x, int y, MVector color)
{
	m_pFramebuffer[m_width*y + x] = MathUtil::ColorToUINT(color);
}

float Moe3DDevice::GetZ(int x, int y) const
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		return m_zBuffer[x][y];
	else
		return 1.f;
}

void Moe3DDevice::SetZ(int x, int y, float z)
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
	{
		m_zBuffer[x][y] = z;
	}
}

void Moe3DDevice::ClearBuffer(MVector color)
{
	for (int x = 0; x < m_width; ++x)
	{
		for (int  y = 0; y < m_height; ++y)
		{
			m_pFramebuffer[m_width*y + x] = MathUtil::ColorToUINT(color);
			m_zBuffer[x][y] = 0;
		}
	}
}

