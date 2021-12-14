#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

struct vec2
{
	double x, y;
	
	vec2() { x = 0; y = 0; }
	vec2(double X, double Y) { x = X; y = Y; }

	double magnitude() { return sqrt((x * x) + (y * y)); }
	vec2 operator=(vec2 b) { x = b.x; y = b.y; return *this; }
};

inline bool operator==(vec2 a, vec2 b) { return (a.x == b.x && a.y == b.y); }
inline vec2 operator*(vec2 v, double a) { return vec2(int(a * v.x), int(a * v.y)); }
inline vec2 operator*(double a, vec2 v) { return vec2(int(a * v.x), int(a * v.y)); }
inline vec2 operator+(vec2 a, vec2 b) { return vec2(a.x + b.x, a.y + b.y); }
inline vec2 operator-(vec2 a, vec2 b) { return vec2(a.x - b.x, a.y - b.y); }

struct seg2
{
	vec2 start;
	vec2 end;

	seg2(double x0, double y0, double x1, double y1)
	{
		start.x = x0; start.y = y0;
		end.x = x1; end.y = y1;
	}

	seg2(vec2 s, vec2 e) { start = s; end = e; }

	double length() { return sqrt( pow(start.x - end.x, 2) + pow(start.y - end.y, 2)); }
};


struct Triangle 
{
	vec2 p0;
	vec2 p1;
	vec2 p2;

	Triangle(vec2 P0, vec2 P1, vec2 P2)
	{
		p0 = P0; p1 = P1; p2 = P2;
	}
};

inline bool operator==(seg2 a, seg2 b) { return (a.start == b.start && a.end == b.end); }

bool raycastIntersection(vec2 rayPos, vec2 rayDir, seg2 seg, vec2* collisionPoint, double* rayDist, double* segDist);
bool raycastIntersection(vec2 rayPos, vec2 rayDir, seg2 seg, vec2* collisionPoint);
bool raycastIntersection(vec2 rayPos, vec2 rayDir, seg2 seg);

#endif