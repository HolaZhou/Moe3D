#pragma once
#include "Vertex.h"
#include "MVector.h"
#include "MMath.h"
#include "LightHelper.h"

class ShaderBase
{
public:
	ShaderBase();
	virtual ~ShaderBase();

public:
	virtual VertexOut VS(const VertexIn& vin) = 0;	//顶点着色器
	virtual MVector PS(VertexOut& pin) = 0;	//像素着色器
};

