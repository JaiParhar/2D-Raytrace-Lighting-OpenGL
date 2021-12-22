#pragma once
#ifndef GFX_RENDER_H
#define GFX_RENDER_H

#include "GL/glew.h"

#include "common.h"
#include "gfx_utils.h"

void renderBlankVAO(GLuint VAO_ID, GLuint num_vertices);
void renderTexturedVAO(GLuint VAO_ID, GLuint num_vertices);

#endif