#pragma once
#include "MVector.h"


//info of a vertex
class VertexIn
{
public:
	// position 
	MVector pos;
	// color
	MVector color;
	// texture
	MFLOAT2 tex;
	// normal
	MVector normal;

	VertexIn() = default;
	VertexIn(MVector pos, MVector color, MFLOAT2 tex, MVector normal)
		:pos(pos), color(color), tex(tex), normal(normal) {}

	VertexIn(const VertexIn& rhs):pos(rhs.pos),color(rhs.color),tex(rhs.tex),normal(rhs.normal){}
};

// VertexIn -> vertex shader -> VertexOut
class VertexOut
{
public:
	// pos -> world transformation -> posTrans
	MVector posTrans;
	// pos -> projection transformation -> posH
	MVector posH;
	// texture
	MFLOAT2 tex;
	// normal
	MVector normal;
	// color
	MVector color;
	// 1/z depth testing
	float oneDivZ;

	VertexOut() = default;
	VertexOut(MVector posT, MVector posH, MFLOAT2 tex, MVector normal, MVector color, float oneDivZ)
		:posTrans(posT), posH(posH), tex(tex), normal(normal), color(color), oneDivZ(oneDivZ) {}

	VertexOut(const VertexOut& rhs) :posTrans(rhs.posTrans), posH(rhs.posH), tex(rhs.tex), normal(rhs.normal),
	color(rhs.color),oneDivZ(rhs.oneDivZ){}

	VertexOut& operator= (const VertexOut& rhs)
	{
		if (this == &rhs)
			return *this;
		this->normal = rhs.normal;
		this->posH = rhs.posH;
		this->posTrans = rhs.posTrans;
		this->tex = rhs.tex;
		this->color = rhs.color;
		this->oneDivZ = rhs.oneDivZ;
		return *this;
	}
};

