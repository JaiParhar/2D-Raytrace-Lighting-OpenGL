#include "gfx_map.h"

int renderLightMapOutline(SDL_Renderer* renderer, LightMap lm)
{
	for (int i = 0; i < lm.walls.size(); i++)
	{
		SDL_RenderDrawLine(renderer,
			lm.walls[i].start.x, lm.walls[i].start.y,
			lm.walls[i].end.x, lm.walls[i].end.y);
	}

	return 0;
}