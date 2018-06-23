/*
 * LabMesh.cpp
 *
 *  Created on: 16 авг. 2017 г.
 *      Author: kived
 */

#include "LabMesh.h"

static void north_wall(MeshBuilder & mb, float x, float y,float z, float Depth);
static void west_wall(MeshBuilder & mb, float x, float y,float z, float Depth);
static void floor(MeshBuilder & mb, float x, float y,float z, float Depth);

void MeshBuilder::addVertex(float x, float y, float z, float u, float v)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);

	vertices.push_back(u);
	vertices.push_back(v);
}

void BuildLabirintMesh(MeshBuilder & mb, Map& map, float StartX, float StartY, float Depth )
{
	float x=StartX;
	float y=StartY;
	float z=-0.5f*Depth;


	for(int j=0; j<map.Height();j++) {
		for (int i=0; i<map.Width();i++) {
			map.MoveTo(i,j);


	       if (map.Wall(NORTH)){
	    	   north_wall(mb,x,y,z,Depth);
	       }


	       if (map.Wall(WEST)){
	    	   west_wall(mb,x,y,z,Depth);
	       }

	       floor(mb,x,y,z,0.0f);

	       x+=CELL_SIDE;
		}
		x=StartX;
		y+=CELL_SIDE;
	}

	x=StartX;

	y=StartY+map.Height() * CELL_SIDE;

	for (int i=0; i<map.Width(); i++){
		north_wall(mb,x,y,z,Depth);
		x+=CELL_SIDE;
	}


	x=StartX + map.Width() * CELL_SIDE;
	y=StartY;

	for (int i=0; i<map.Height(); i++){
		west_wall(mb,x,y,z,Depth);
		y+=CELL_SIDE;
	}
}

static void floor(MeshBuilder & mb, float x, float y,float z, float Depth)

{
     /*glBegin(GL_QUADS);
     glVertex3f(x,z+Depth_,y);
     glVertex3f(x, z+Depth_, y+CELL_SIDE);
     glVertex3f(x+CELL_SIDE,z+Depth_, y+CELL_SIDE);
     glVertex3f(x+CELL_SIDE, z+Depth_, y);

     glEnd();*/
	mb.addVertex(x, z+Depth, y+CELL_SIDE, 0.5f, 1.0f);
    mb.addVertex(x, z+Depth, y, 0.5f, 0.5f);
	mb.addVertex(x+CELL_SIDE,z+Depth,y+CELL_SIDE, 1.0f, 1.0f);

	mb.addVertex(x+CELL_SIDE,z+Depth,y+CELL_SIDE, 1.0f, 1.0f);
	mb.addVertex(x, z+Depth, y, 0.5f, 0.5f);
	mb.addVertex(x+CELL_SIDE,z+Depth,y,1.0f, 0.5f);
}



static void north_wall(MeshBuilder & mb, float x, float y,float z, float Depth)
{
	mb.addVertex(x, z+Depth, y, 0.5f, 0.0f);
	mb.addVertex(x, z, y, 0.5f, 0.5f);
	mb.addVertex(x+CELL_SIDE,z+Depth,y, 0.0f, 0.0f);

	mb.addVertex(x+CELL_SIDE,z+Depth,y, 0.0f, 0.0f);
	mb.addVertex(x, z, y, 0.5f, 0.5f);
	mb.addVertex(x+CELL_SIDE,z,y,0.0f, 0.5f);
}

/*
 *
 *
 *          (y,z)     (y+CELL_SIDE,z)
                 ++++++
                 +*   +
                 + *  +
                 +  * +
                 ++++++
            (y,z+Depth)     (y+CELL_SIDE,z+Depth)

            в данном представление

            1) (y,z+Depth), (y,z), (y+CELL_SIDE,z+Depth)
            2) (y+CELL_SIDE,z+Depth), (y,z), (y+CELL_SIDE,z)

            в реальности
            1)
            (x, z+Depth,y)
            (x,z,y),
            (x,z+Depth, y+CELL_SIDE)
            2) (x,z+Depth, y+CELL_SIDE)
             (x,z,y),
             (x,z,y+CELL_SIDE)

 *
 */


static void west_wall(MeshBuilder & mb, float x, float y,float z, float Depth)
{


	mb.addVertex(x, z+Depth,y, 0.5f, 0.0f);
	mb.addVertex(x, z, y, 0.5f, 0.5f);
	mb.addVertex(x,z+Depth, y+CELL_SIDE, 0.0f, 0.0f);

	mb.addVertex(x,z+Depth, y+CELL_SIDE, 0.0f, 0.0f);
	mb.addVertex(x, z, y, 0.5f, 0.5f);
	mb.addVertex(x,z,y+CELL_SIDE,0.0f, 0.5f);

}
