/*
 * Renderer.h
 *
 *  Created on: 2 июля 2017 г.
 *      Author: kived
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#include "Map.h"

class renderer
{
public:
	renderer():texture(0),MVPLoc(0),
	vao(0),
	VerticesCount(0),
	TexLoc(0),
	PosX(0.0f),
	PosY(0.0f),
	AtX(1.0f),
	AtY(0.0f){}
	void init(Map &m);
	void Pos(float posx, float posy)
	{
		PosX=posx;
		PosY=posy;
	}

	void LookAt(float atx, float aty)
	{
		AtX=atx;
	    AtY=aty;
	}


	void frame();
private:
	unsigned int texture;
	unsigned int MVPLoc;
	unsigned int vao;
	int VerticesCount;
	unsigned int TexLoc;


	float PosX, PosY;
	float AtX, AtY;
};



#endif /* RENDERER_H_ */
