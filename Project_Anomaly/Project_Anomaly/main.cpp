#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>

#include "gfx_utils.h"
#include "gfx_map.h"

#include "lighting.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int init();
void close();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Event e;

bool quit = false;

int main(int argc, char* args[])
{
	int initErr = init();
	if (initErr)
	{
		return initErr;
	}

	int mX = 0;
	int mY = 0;

	// CREATE A DEVTEST MAP FOR LIGHTING TESTS

	LightMap m;
	m.walls.push_back(seg2(100, 100, 200, 100));
	m.walls.push_back(seg2(200, 100, 200, 200));
	m.walls.push_back(seg2(200, 200, 100, 200));

	// CREATE A DEVTEST MAP FOR LIGHTING TESTS

	// TEST RAYCAST
	seg2 testWall = seg2(100, 100, 100, 500);
	vec2 rayPos = vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	vec2 rayDir = vec2(-10, -10);
	vec2 collPos;
	SDL_FRect collPosDrawRect = {0, 0, 5, 5};
	// TEST RAYCAST

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			if (e.type == SDL_MOUSEMOTION) 
			{
				SDL_GetMouseState(&mX, &mY);
			}
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0xFF);

		// TEST RAYCAST CODE
		SDL_RenderDrawLine(renderer,
			testWall.start.x, testWall.start.y,
			testWall.end.x, testWall.end.y);

		rayDir.x = mX - rayPos.x; rayDir.y = mY - rayPos.y;
		if (raycastIntersection(rayPos, rayDir, testWall, &collPos))
		{
			collPosDrawRect.x = collPos.x - 2;
			collPosDrawRect.y = collPos.y - 2;
			SDL_RenderDrawLineF(renderer, rayPos.x, rayPos.y, collPos.x, collPos.y);
			SDL_RenderFillRectF(renderer, &collPosDrawRect);
		}
		// TEST RAYCAST CODE

		//renderLightMapOutline(renderer, m);
		//filledTrigon(renderer, 100, 100, 200, 100, mX, mY);



		
		SDL_RenderPresent(renderer);

	}

	close();
	return 0;
}

int init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow("Project_Anomaly", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer could not be created. SDL Error: %s\n", SDL_GetError());
		return -1;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize. SDL_image Error: %s\n", IMG_GetError());
		return -1;
	}



	return 0;
}

void close()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}