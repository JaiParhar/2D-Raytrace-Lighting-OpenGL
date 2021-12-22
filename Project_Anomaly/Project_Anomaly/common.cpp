#include "common.h"


bool raycastIntersection(glm::vec2 rayPos, glm::vec2 rayDir, seg2 seg, glm::vec2* collisionPoint, float* rayDist, float* segDist)
{
	// Convert segment into form of segPos + segDir * T (0 <= T <= 1)
	glm::vec2 segPos = seg.start;
	glm::vec2 segDir = seg.end - seg.start;

	// Check if rayDir and segDir aren't parallel, because then they won't intersect and this will crash
	if (rayDir == segDir || rayDir == (-1.0f * segDir)) { return false; }

	// Need to find T1, T2 that solves segPos + segDir * T1 = rayPos + rayDir * T2 (0 <= T2 <= 1, T1 >= 0)

	// I copied this code from somewhere else cuz I'm way too fucking lazy for this shit, eat my entire asshole if you judge me for this
	float T2 = (rayDir.x * (segPos.y - rayPos.y) + rayDir.y * (rayPos.x - segPos.x)) / (segDir.x * rayDir.y - segDir.y * rayDir.x);
	float T1 = (segPos.x + segDir.x * T2 - rayPos.x) / rayDir.x;

	// Collision occured
	if (T1 >= 0 && T2 >= 0 && T2 <= 1)
	{
		(*collisionPoint) = rayPos + (T1 * rayDir);
		(*rayDist) = T1 / glm::length(rayDir);
		(*segDist) = T2 / glm::length(segDir);
		return true;
	}

	return false;
}

bool raycastIntersection(glm::vec2 rayPos, glm::vec2 rayDir, seg2 seg, glm::vec2* collisionPoint)
{
	float rd, sd;
	return raycastIntersection(rayPos, rayDir, seg, collisionPoint, &rd, &sd);
}

bool raycastIntersection(glm::vec2 rayPos,glm::vec2 rayDir, seg2 seg)
{
	glm::vec2 collisionPoint;
	return raycastIntersection(rayPos, rayDir, seg, &collisionPoint); 
}
