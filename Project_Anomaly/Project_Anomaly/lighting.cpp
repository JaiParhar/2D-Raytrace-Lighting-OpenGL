#include "lighting.h"

std::vector<GLfloat> trisToMeshData(std::vector<Triangle> tris)
{
	std::vector<GLfloat> meshData;

	for (int i = 0; i < tris.size(); i++) 
	{
		meshData.push_back(tris[i].p0.x); meshData.push_back(tris[i].p0.y); meshData.push_back(0.0f);
		meshData.push_back(tris[i].p1.x); meshData.push_back(tris[i].p1.y); meshData.push_back(0.0f);
		meshData.push_back(tris[i].p2.x); meshData.push_back(tris[i].p2.y); meshData.push_back(0.0f);
	}

	return meshData;
}

std::vector<Triangle> getVisionTris(LightMap m, glm::vec2 pos, float boundW, float boundH)
{
	return getVisionTris(m, pos, pos, boundW, boundH);
}

std::vector<Triangle> getVisionTris(LightMap m, glm::vec2 pos, glm::vec2 boundPos, float boundW, float boundH)
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

	glm::vec2 topLeftCorner(boundPos.x - (boundW / 2), boundPos.y - (boundH / 2));
	glm::vec2 topRightCorner(boundPos.x + (boundW / 2), boundPos.y - (boundH / 2));
	glm::vec2 botLeftCorner(boundPos.x - (boundW / 2), boundPos.y + (boundH / 2));
	glm::vec2 botRightCorner(boundPos.x + (boundW / 2), boundPos.y + (boundH / 2));

	allWalls.push_back(seg2(topLeftCorner, topRightCorner));
	allWalls.push_back(seg2(topRightCorner, botRightCorner));
	allWalls.push_back(seg2(botRightCorner, botLeftCorner));
	allWalls.push_back(seg2(botLeftCorner, topLeftCorner));

	// Gets the rays that need to be cast
	std::vector<glm::vec2> orderedRays = getSortedUniqueRaysToEndpoints(allWalls, pos);

	// Actually cast the fuckers
	std::vector<glm::vec2> orderedCollisions;
	float idontcare; // Stores segDist, which i dont care about here, and i didnt feel like adding another implementation
	for (int r = 0; r < orderedRays.size(); r++)
	{
		int closestIndex = 0;
		float closestDist = -1;
		glm::vec2 closestPoint;
		for (int w = 0; w < allWalls.size(); w++) 
		{
			glm::vec2 collPoint;
			float rayDist;
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

std::vector<glm::vec2> getSortedUniqueRaysToEndpoints(std::vector<seg2> segs, glm::vec2 pos)
{
	// Gets unique angles into the array
	std::vector<float> rayAngles;
	for (int i = 0; i < segs.size(); i++)
	{
		glm::vec2 posToStart = segs[i].start - pos;
		glm::vec2 posToEnd = segs[i].end - pos;

		float angleStart = atan2(posToStart.y, posToStart.x);
		float angleEnd = atan2(posToEnd.y, posToEnd.x);

		float offset = 0.00001;

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
	std::vector<glm::vec2> rays;
	for (int i = 0; i < rayAngles.size(); i++)
	{
		rays.push_back(glm::vec2(cos(rayAngles[i]), sin(rayAngles[i])));
	}

	return rays;
}