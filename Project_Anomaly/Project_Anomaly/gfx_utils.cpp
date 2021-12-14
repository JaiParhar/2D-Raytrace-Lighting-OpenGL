#include "gfx_utils.h"

int renderFilledTri(SDL_Renderer* renderer, Triangle t)
{
	return renderFilledTri(renderer, t.p0, t.p1, t.p2);
}

int renderFilledTri(SDL_Renderer* renderer, vec2 p0, vec2 p1, vec2 p2)
{
	return renderFilledTri(renderer,
		p0.x, p0.y,
		p1.x, p1.y,
		p2.x, p2.y);
}

int renderFilledTri(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2, int y2)
{
	// Ordering the points properly
	int tempY, tempX;
	if (y1 < y0) /* swap(P1, P0) */
	{
		tempY = y0; tempX = x0;
		y0 = y1; x0 = x1;
		y1 = tempY; x1 = tempX;
	}
	if (y2 < y0) /* swap(P2, P0) */
	{
		tempY = y0; tempX = x0;
		y0 = y2; x0 = x2;
		y2 = tempY; x2 = tempX;
	}
	if (y2 < y1) /* swap(P2, P1) */
	{
		tempY = y1; tempX = x1;
		y1 = y2; x1 = x2;
		y2 = tempY; x2 = tempX;
	}

	// Getting x coords of triangle edges
	std::vector<int> x01 = interpolateInts(y0, x0, y1, x1);
	std::vector<int> x12 = interpolateInts(y1, x1, y2, x2);
	std::vector<int> x02 = interpolateInts(y0, x0, y2, x2);

	// Remove one of the duplicate points
	x01.pop_back();

	// Concatenate short edges into one long array
	std::vector<int> x012;
	x012.reserve(x01.size() + x12.size());
	x012.insert(x012.end(), x01.begin(), x01.end());
	x012.insert(x012.end(), x12.begin(), x12.end());

	// Determine which is left and which is right
	std::vector<int> x_left;
	std::vector<int> x_right;
	int m = std::floor(x012.size() / 2);
	if (x02[m] < x012[m])
	{
		x_left = x02;
		x_right = x012;
	}
	else {
		x_left = x012;
		x_right = x02;
	}

	// Draw the triangle
	for (int y = y0; y <= y2; y++)
	{
		SDL_RenderDrawLine(renderer, x_left[y - y0], y, x_right[y - y0], y);
	}

	return 0;

}

int renderOutlineTri(SDL_Renderer* renderer, Triangle t)
{
	return renderOutlineTri(renderer, t.p0, t.p1, t.p2);
}

int renderOutlineTri(SDL_Renderer* renderer, vec2 p0, vec2 p1, vec2 p2)
{
	return renderOutlineTri(renderer,
		p0.x, p0.y,
		p1.x, p1.y,
		p2.x, p2.y);
}

int renderOutlineTri(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2, int y2)
{
	return SDL_RenderDrawLine(renderer, x0, y0, x1, y1)
		+ SDL_RenderDrawLine(renderer, x1, y1, x2, y2) 
		+ SDL_RenderDrawLine(renderer, x2, y2, x0, y0);
}

std::vector<int> interpolateInts(int y0, int x0, int y1, int x1)
{
	// Make sure y1 >= y0, if not, swap
	if (y0 > y1)
	{
		int yTemp = y0; int xTemp = x0;
		y0 = y1; x0 = x1; y1 = yTemp; x1 = xTemp;
	}

	std::vector<int> interpolatedInts;

	// Adding case for if y1 == y0 (just return the average, as theoretically x0 and x1 should be the same unless something has gone very wrong)
	if (y1 == y0)
	{
		interpolatedInts.push_back((x0 + x1) / 2);
		return interpolatedInts;
	}

	for (int y = y0; y <= y1; y++)
	{
		int x = (((y - y0) * (x1 - x0) / (y1 - y0))) + x0;

		// For debugging
		//printf("y = %i, x = %i \n", y, x);

		interpolatedInts.push_back(x);
	}

	return interpolatedInts;
}

Uint32 getUint32RGBA8888(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	Uint32 col = 0;
	col += r; col = col << 8;
	col += g; col = col << 8;
	col += b; col = col << 8;
	col += a;
	return col;
}