#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <iostream>

#include "GL/glew.h"

#include "glm/glm.hpp"
#include "glm/vec2.hpp"

static const GLfloat QUAD_VERTEX_DATA[] = {
	-1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,

	1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f
};

static const GLuint QUAD_VERTEX_NUMBER = 6; // 3 vertices per triangle * 2 triangles

struct seg2
{
	glm::vec2 start;
	glm::vec2 end;

	seg2(float x0, float y0, float x1, float y1)
	{
		start.x = x0; start.y = y0;
		end.x = x1; end.y = y1;
	}

	seg2(glm::vec2 s, glm::vec2 e) { start = s; end = e; }

	float length() { return sqrt( pow(start.x - end.x, 2) + pow(start.y - end.y, 2)); }
};


struct Triangle 
{
	glm::vec2 p0;
	glm::vec2 p1;
	glm::vec2 p2;

	Triangle(glm::vec2 P0, glm::vec2 P1, glm::vec2 P2)
	{
		p0 = P0; p1 = P1; p2 = P2;
	}
};

inline bool operator==(seg2 a, seg2 b) { return (a.start == b.start && a.end == b.end); }

bool raycastIntersection(glm::vec2 rayPos, glm::vec2 rayDir, seg2 seg, glm::vec2* collisionPoint, float* rayDist, float* segDist);
bool raycastIntersection(glm::vec2 rayPos, glm::vec2 rayDir, seg2 seg, glm::vec2* collisionPoint);
bool raycastIntersection(glm::vec2 rayPos, glm::vec2 rayDir, seg2 seg);

#endif