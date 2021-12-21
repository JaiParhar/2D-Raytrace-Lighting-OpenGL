#pragma once
#ifndef GFX_UTILS_H
#define GFX_UTILS_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "GL/glew.h"

#include "common.h"

GLuint genBlankQuadVAO();

GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);

#endif