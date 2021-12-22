#pragma once
#ifndef GFX_UTILS_H
#define GFX_UTILS_H

#include <string>
#include <vector>

#include "GL/glew.h"
#include "picoPNG.h"

#include "common.h"

GLuint genVAO();
GLuint genVBO();
GLuint genTexture();

void storeVBOData(GLuint vboID, GLuint attrib, const GLfloat* data, int dataSize, int dimension = 3);
void storePNGTextureData(GLuint textureID, std::vector<unsigned char> data, unsigned long* width, unsigned long* height, bool linearInterp = false);

GLuint createShaderProgram(std::string vert, std::string frag);

#endif