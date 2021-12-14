#include "common.h"


bool raycastIntersection(vec2 rayPos, vec2 rayDir, seg2 seg, vec2* collisionPoint, double* rayDist, double* segDist)
{
	// Convert segment into form of segPos + segDir * T (0 <= T <= 1)
	vec2 segPos = seg.start;
	vec2 segDir = seg.end - seg.start;

	// Check if rayDir and segDir aren't parallel, because then they won't intersect and this will crash
	if (rayDir == segDir || rayDir == (-1 * segDir)) { return false; }

	// Need to find T1, T2 that solves segPos + segDir * T1 = rayPos + rayDir * T2 (0 <= T2 <= 1, T1 >= 0)

	// I copied this code from somewhere else cuz I'm way too fucking lazy for this shit, eat my entire asshole if you judge me for this
	double T2 = (rayDir.x * (segPos.y - rayPos.y) + rayDir.y * (rayPos.x - segPos.x)) / (segDir.x * rayDir.y - segDir.y * rayDir.x);
	double T1 = (segPos.x + segDir.x * T2 - rayPos.x) / rayDir.x;

	// Collision occured
	if (T1 >= 0 && T2 >= 0 && T2 <= 1)
	{
		(*collisionPoint) = rayPos + (rayDir * T1);
		(*rayDist) = T1 / rayDir.magnitude();
		(*segDist) = T2 / segDir.magnitude();
		return true;
	}

	return false;
}

bool raycastIntersection(vec2 rayPos, vec2 rayDir, seg2 seg, vec2* collisionPoint)
{
	double rd, sd;
	return raycastIntersection(rayPos, rayDir, seg, collisionPoint, &rd, &sd);
}

bool raycastIntersection(vec2 rayPos, vec2 rayDir, seg2 seg)
{
	vec2 collisionPoint; 
	return raycastIntersection(rayPos, rayDir, seg, &collisionPoint); 
}