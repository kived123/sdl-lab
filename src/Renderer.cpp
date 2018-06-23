/*
 * Renderer.cpp
 *
 *  Created on: 2 июля 2017 г.
 *      Author: kived
 */
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL/SOIL.h>
#include "Renderer.h"
#include "LabMesh.h"


using namespace std;





const char * vertex_shader =
			     "#version 130\n"
				"in vec3 vert;"
				"in vec2 texcoord;"
				"out vec2 Texcoord;"
				"uniform mat4 mvp;"
		        "void main(void) {"
		        "gl_Position = mvp * vec4(vert,1.0);"
		        " Texcoord = texcoord;"
		        "}";



const char * fragment_shader =
			       "#version 130\n"
		       "in vec2 Texcoord;"
		        "uniform sampler2D ourTexture;"
				"out vec4 color;"


				"void main(void) {"
				"  color = texture(ourTexture, Texcoord);"
				"}";



void renderer::init(Map &m)
{
	glClearColor(0.0f,0.0f,1.0f,0.0f);


	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	unsigned int bufid;

	glGenBuffers(1, &bufid);

	MeshBuilder mb;

	BuildLabirintMesh(mb, m, 0.0f,0.0f,3.0f);
	int size = mb.vertices.size();

	VerticesCount = size/5;

	cout << size << endl;

	cout << "Vertices Count =" << VerticesCount << endl;



	glBindBuffer(GL_ARRAY_BUFFER, bufid);
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(GLfloat), &mb.vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	GLuint vs,fs;


    vs = glCreateShader( GL_VERTEX_SHADER );
	fs = glCreateShader( GL_FRAGMENT_SHADER );


	glShaderSource( vs, 1, &vertex_shader, NULL);
    glShaderSource( fs, 1, &fragment_shader, NULL);



	glCompileShader(vs);
	glCompileShader(fs);

	GLuint prg = glCreateProgram();

	glBindAttribLocation(prg, 0,	"vert");
	glBindAttribLocation(prg, 1,	"texcoord");


        glAttachShader(prg, vs);
        glAttachShader(prg, fs);

        glLinkProgram(prg);

	glUseProgram(prg);


	int width, height;
	unsigned char* image;

	glGenTextures(1, &texture);


	glBindTexture(GL_TEXTURE_2D, texture);
	image = SOIL_load_image("Data/tex.png", &width, &height, 0, SOIL_LOAD_RGB);
	cout << (void*)image << endl;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		              GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // We want to repeat this pattern so we set kept it at GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   // We want to repeat this pattern so we set kept it at GL_REPEAT


	glBindTexture(GL_TEXTURE_2D, 0);


	MVPLoc = glGetUniformLocation(prg,"mvp");
	cout << "MVPLoc = " << MVPLoc << endl;
	TexLoc = glGetUniformLocation(prg, "ourTexture");
	cout << "ourTexture = " << TexLoc << endl;
}


void renderer::frame()
{

	float aspect = float(WINDOW_WIDTH)/WINDOW_HEIGHT;
	glm::mat4 proj = glm::perspective(45.0f, aspect, 1.0f, 100.0f);

		glm::mat4 view = glm::lookAt(glm::vec3(PosX,0.0f,PosY),
					glm::vec3(AtX,0.0f,AtY),
					glm::vec3(0.0f,1.0f,0.0f));


		glm::mat4 MVP = proj*view;

		glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));



		glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, texture);
	    glUniform1i(TexLoc, 0);


		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, VerticesCount);

}
