#pragma once
#ifndef GFX_MAP_H
#define GFX_MAP_H

#include <SDL.h>

#include "lighting.h"

int renderLightMapOutline(SDL_Renderer* renderer, LightMap lm);

#endif