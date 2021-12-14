#include "lighting.h"

std::vector<Triangle> getVisionTris(LightMap m, vec2 pos, int boundW, int boundH)
{
	return getVisionTris(m, pos, pos, boundW, boundH);
}

std::vector<Triangle> getVisionTris(LightMap m, vec2 pos, vec2 boundPos, int boundW, int boundH)
{
	// Added check to make sure that view source is in bounds
	if (pos.x <= (boundPos.x - (boundW / 2)) || pos.x >= (boundPos.x + (boundW / 2)) || 
		pos.y <= (boundPos.y - (boundH / 2)) || pos.y >= (boundPos.y + (boundH / 2)))
	{
		std::vector<Triangle> noTris;
		return noTris;
	}

	// Add the screen edges to the walls list
	// (NOTE: for some fucking reason, the = operator just copies it? doesnt do shit with pointers)
	// (NOTE: whoever designed that can eat my entire asshole, wish this shit was fucking consistant)
	std::vector<seg2> allWalls = m.walls;

	vec2 topLeftCorner(boundPos.x - (boundW / 2), boundPos.y - (boundH / 2));
	vec2 topRightCorner(boundPos.x + (boundW / 2), boundPos.y - (boundH / 2));
	vec2 botLeftCorner(boundPos.x - (boundW / 2), boundPos.y + (boundH / 2));
	vec2 botRightCorner(boundPos.x + (boundW / 2), boundPos.y + (boundH / 2));

	allWalls.push_back(seg2(topLeftCorner, topRightCorner));
	allWalls.push_back(seg2(topRightCorner, botRightCorner));
	allWalls.push_back(seg2(botRightCorner, botLeftCorner));
	allWalls.push_back(seg2(botLeftCorner, topLeftCorner));

	// Gets the rays that need to be cast
	std::vector<vec2> orderedRays = getSortedUniqueRaysToEndpoints(allWalls, pos);

	// Actually cast the fuckers
	std::vector<vec2> orderedCollisions;
	double idontcare; // Stores segDist, which i dont care about here, and i didnt feel like adding another implementation
	for (int r = 0; r < orderedRays.size(); r++)
	{
		int closestIndex = 0;
		double closestDist = -1;
		vec2 closestPoint;
		for (int w = 0; w < allWalls.size(); w++) 
		{
			vec2 collPoint;
			double rayDist;
			if (raycastIntersection(pos, orderedRays[r], allWalls[w], &collPoint, &rayDist, &idontcare)) // Dont combine with inner if, for clarity mainly
			{
				if (rayDist < closestDist || closestDist == -1)
				{
					closestIndex = w;
					closestDist = rayDist;
					closestPoint = collPoint;
				}
			}
		}

		// Error handling - If this prints something has gone horribly wrong
		// if (closestDist == -1) { printf("Something has gone wrong in finding the closest intersection, which shouldn't even be possible. Fix this!\n"); }
		// ^^^^^^^^ Actually happens (probably due to precision issues in niche cases), but doesn't seem to crash so we good.


		orderedCollisions.push_back(closestPoint);
	}
	
	// Build the fucking triangles (finally, after all this shit)
	std::vector<Triangle> visionTris;
	for (int i = 0; i < orderedCollisions.size() - 1; i++) // - 1 cuz we are accessing this element and next element
	{
		visionTris.push_back(Triangle(orderedCollisions[i], orderedCollisions[i+1], pos));
	}
	visionTris.push_back(Triangle(orderedCollisions[0], orderedCollisions[orderedCollisions.size()-1], pos)); // Handles last triangle

	return visionTris;
}

std::vector<vec2> getSortedUniqueRaysToEndpoints(std::vector<seg2> segs, vec2 pos)
{
	// Gets unique angles into the array
	std::vector<double> rayAngles;
	for (int i = 0; i < segs.size(); i++)
	{
		vec2 posToStart = segs[i].start - pos;
		vec2 posToEnd = segs[i].end - pos;

		double angleStart = atan2(posToStart.y, posToStart.x);
		double angleEnd = atan2(posToEnd.y, posToEnd.x);

		double offset = 0.00001;

		// Makes sure to add if not doubled up
		if (std::find(rayAngles.begin(), rayAngles.end(), angleStart) == rayAngles.end())
		{
			rayAngles.push_back(angleStart);
			rayAngles.push_back(angleStart + offset);
			rayAngles.push_back(angleStart - offset);
		}
		
		// Makes sure to add if not doubled up
		if (std::find(rayAngles.begin(), rayAngles.end(), angleEnd) == rayAngles.end())
		{
			rayAngles.push_back(angleEnd);
			rayAngles.push_back(angleEnd + offset);
			rayAngles.push_back(angleEnd - offset);
		}

	}

	// Sorts the angles of the rays
	sort(rayAngles.begin(), rayAngles.end());
	
	// Converts the ray angles into (normalized but doesn't need to be) vectors
	std::vector<vec2> rays;
	for (int i = 0; i < rayAngles.size(); i++)
	{
		rays.push_back(vec2(cos(rayAngles[i]), sin(rayAngles[i])));
	}

	return rays;
}

SDL_Texture* generateLightFadeTexture(SDL_Renderer* renderer, int pixelW, int pixelH, double lightMag, double lightFade)
{
	// SDL_PIXELFORMAT_RGBA8888 means 1 byte red, 1 byte green, 1 byte blue, 1 byte alpha
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, pixelW, pixelH);

	Uint32* pixels;
	int pitch; // width in bytes

	SDL_LockTexture(texture, NULL, (void**) &pixels, &pitch);

	int bytesPerPixel = pitch / pixelW;

	for (int y = 0; y < pixelH; y++)
	{
		for (int x = 0; x < pixelW; x++)
		{
			// Goes from -1 to 1
			double dx = ((double)x - ((double)pixelW / 2.0)) / ((double)pixelW / 2.0);
			double dy = ((double)y - ((double)pixelH / 2.0)) / ((double)pixelH / 2.0);

			double r = sqrt(dx * dx + dy * dy);
			
			unsigned int mag = (unsigned int) (lightMag * 255.0 * (pow(lightFade, -r)));
			if (mag > 255)
			{
				mag = 255;
			}
			unsigned char chmag = (unsigned char) mag;
			pixels[(pixelW * y) + (x)] = getUint32RGBA8888(chmag, chmag, chmag, 255);
		}
	}

	SDL_UnlockTexture(texture);

	return texture;
}
