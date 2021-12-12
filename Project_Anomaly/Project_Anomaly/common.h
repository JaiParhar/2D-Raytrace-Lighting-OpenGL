#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

struct vec2
{
	float x, y;
	
	vec2() { x = 0; y = 0; }

	vec2(float X, float Y)
	{
		x = X; y = Y;
	}

	vec2 operator=(vec2 b) { x = b.x; y = b.y; return *this; }
};

bool operator==(vec2 a, vec2 b) { return (a.x == b.x && a.y == b.y); }
vec2 operator*(vec2 v, float a) { return vec2(int(a * v.x), int(a * v.y)); }
vec2 operator*(float a, vec2 v) { return vec2(int(a * v.x), int(a * v.y)); }
vec2 operator+(vec2 a, vec2 b) { return vec2(a.x + b.x, a.y + b.y); }
vec2 operator-(vec2 a, vec2 b) { return vec2(a.x - b.x, a.y - b.y); }

struct seg2
{
	vec2 start;
	vec2 end;

	seg2(float x0, float y0, float x1, float y1)
	{
		start.x = x0; start.y = y0;
		end.x = x1; end.y = y1;
	}

	seg2(vec2 s, vec2 e)
	{
		start = s; end = e;
	}

	float length() 
	{ 
		return sqrt( pow(start.x - end.x, 2) + pow(start.x - end.x, 2));
	}
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

bool raycastIntersection(vec2 rayPos, vec2 rayDir, seg2 seg, vec2* collisionPoint)
{
	// Convert segment into form of segPos + segDir * T (0 <= T <= 1)
	vec2 segPos = seg.start;
	vec2 segDir = seg.start - seg.end;

	// Check if rayDir and segDir aren't parallel, because then they won't intersect and this will crash
	if (rayDir == segDir || rayDir == (-1 * segDir)) { return false; }
 
	// Need to find T1, T2 that solves segPos + segDir * T1 = rayPos + rayDir * T2 (0 <= T2 <= 1, T1 >= 0)

	// I copied this code from somewhere else cuz I'm way too fucking lazy for this shit, eat my entire asshole if you judge me for this
	float T2 = (rayDir.x * (segPos.y - rayPos.y) + rayDir.y * (rayPos.x - segPos.x)) / (segDir.x * rayDir.y - segDir.y * rayDir.x);
	float T1 = (segPos.x + segDir.x * T2 - rayPos.x) / rayDir.x;

	// FOR SOME FUCKING REASON (PROBABLY A MISSING - SIGN, WE GOTTA FLIP THE SIGN OF T2)
	T2 = -T2;

	// Collision occured
	if (T1 >= 0 && T2 >= 0 && T2 <= 1)
	{
		(*collisionPoint) = rayPos + (rayDir * T1);
		return true;
	}

	return false;
}