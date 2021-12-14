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

// Vision tris seem to break occasionally, but seems to be a small issue, shouldn't affect gameplay
std::vector<Triangle> getVisionTris(LightMap m, vec2 pos, int boundW, int boundH);
std::vector<Triangle> getVisionTris(LightMap m, vec2 pos, vec2 boundPos, int boundW, int boundH);

std::vector<vec2> getSortedUniqueRaysToEndpoints(std::vector<seg2> segs, vec2 pos);

#endif