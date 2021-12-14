#pragma once
#ifndef GFX_UTILS_H
#define GFX_UTILS_H

#include <stdio.h>
#include <cmath>  
#include <vector>

#include <SDL.h>

#include "common.h"

// Draws a filled triangle
int renderFilledTri(SDL_Renderer* renderer, Triangle t);
int renderFilledTri(SDL_Renderer* renderer, vec2 p0, vec2 p1, vec2 p2);
int renderFilledTri(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2, int y2);

// Draws the outline of a triangle
int renderOutlineTri(SDL_Renderer* renderer, Triangle t);
int renderOutlineTri(SDL_Renderer* renderer, vec2 p0, vec2 p1, vec2 p2);
int renderOutlineTri(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2, int y2);

// Gives back an array of x values dependent on the y values - CANNOT INTERPOLATE IF y0 == y1 AS THAT IS IMPOSSIBLE
std::vector<int> interpolateInts(int y0, int x0, int y1, int x1);

#endif