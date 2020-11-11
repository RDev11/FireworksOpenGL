#pragma once

#include "GL/freeglut.h" 
#include <iostream>
#include <string_view>
#include <random>
#include <cassert>
#include "SOIL/SOIL.h"
#include <functional>

#define _USE_MATH_DEFINES
#include <math.h>
#ifndef M_PI //is _USE_MATH_DEFINES compiler specific?
constexpr double M_PI = 3.14159265358979323846;
#endif

using std::cout;
using std::endl;

inline GLuint LoadTexture(const char* name) {
	//int width, height;//SOIL_LOAD_RGBA
	//unsigned char* image = SOIL_load_image("qwerty.png", &width, &height, 0, SOIL_LOAD_AUTO);

	using namespace std; 
	//std::cout <<"W,H="<< width << ", " << height << "\n";
	auto h = SOIL_load_OGL_texture(name, SOIL_LOAD_RGBA, 0, 0);
	assert(h);
	return h;

	//char cn[256];
	//wcstombs(cn, name, wcslen(name) + 1),
	//	std::cout << ">>texture:" << cn << "::";
//	/ILuint devilID;
//	ilGenImages(1, &devilID);
//	ilBindImage(devilID);
//	ILboolean res =   ilLoadImage(name);
//	std::cout << "ilLoadImage:" << res;  // Loads into the current bound image
//	if (!res)
//		return 0;
//
//	GLsizei  width = ilGetInteger(IL_IMAGE_WIDTH);
//	GLsizei  height = ilGetInteger(IL_IMAGE_HEIGHT);
//	//		int  depth  = ilGetInteger ( IL_IMAGE_DEPTH  );
//	int  type = ilGetInteger(IL_IMAGE_TYPE);//RGB
//	int  fmt = ilGetInteger(IL_IMAGE_FORMAT);//UNSIGNED BYTE
////		int  dxtc   = ilGetInteger ( IL_DXTC_DATA_FORMAT );
////		bool comp  = (dxtc == IL_DXT1) || (dxtc == IL_DXT2) || (dxtc == IL_DXT3) || (dxtc == IL_DXT4) || (dxtc == IL_DXT5);
////		if ( mipmap )
////		{
////			glTexParameteri ( GL_TEXTURE_3D_EXT, GL_GENERATE_MIPMAP_SGIS, GL_TRUE );
////			glTexParameteri ( GL_TEXTURE_3D_EXT, GL_TEXTURE_MIN_FILTER,   GL_LINEAR_MIPMAP_LINEAR );
////		}
//	GLuint tex;
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glGenTextures(1, &tex);
//	glBindTexture(GL_TEXTURE_2D, tex);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);//GL_REPEAT
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_LINEAR
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//GL_NEAREST
//	//glTexImage2D(GL_TEXTURE_2D, 0, 3,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,ilGetData ());
//	glTexImage2D(GL_TEXTURE_2D, 0, type == GL_RGB ? 3 : 4, width, height, 0, fmt, type, ilGetData());
//	//	glDeleteTextures(1, &openglID);
//	ilDeleteImages(1, &devilID);
//	std::cout << "tex" << tex << "w" << width << "h" << height << "-OK;" << std::endl;
//	return tex;

}

inline  double random(double from = .0, double to = 1.0) {
	static std::random_device rd;
	static std::mt19937 e2(rd());
	static std::uniform_real_distribution<> dist(0.0, 1.0);
	//static std::normal_distribution<float> dist(0, 1);
	return from + dist(e2) * (to - from);
}