#pragma once
#ifndef LOAD_H
#define LOAD_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "GL/glew.h"

std::vector<unsigned char> loadFileToCharBuffer(const char* filename);
std::string loadFileToString(const char* file_path);

#endif