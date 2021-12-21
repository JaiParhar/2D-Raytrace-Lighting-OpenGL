#pragma once
#ifndef LIGHTING_H
#define LIGHTING_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "common.h"

struct LightMap
{
	std::vector<seg2> walls;
};

std::vector<GLfloat> trisToMeshData(std::vector <Triangle> tris);

// Vision tris seem to break occasionally, but seems to be a small issue, shouldn't affect gameplay
std::vector<Triangle> getVisionTris(LightMap m, glm::vec2 pos, float boundW, float boundH);
std::vector<Triangle> getVisionTris(LightMap m, glm::vec2 pos, glm::vec2 boundPos, float boundW, float boundH);

// Gets the rays (What a shitty name for a function jesus christ)
std::vector<glm::vec2> getSortedUniqueRaysToEndpoints(std::vector<seg2> segs, glm::vec2 pos);

#endif