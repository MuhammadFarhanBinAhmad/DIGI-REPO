/******************************************************************************/
/*!
\file		Collision.cpp
\author 	Muhammad Farhan Bin Ahmad(ID: 2200544)
\par    	email: b.muhammadfarhan@digipen.edu
\date   	March 03, 2023
\brief

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "main.h"

/**************************************************************************/
/*!

	*/
/**************************************************************************/
bool CollisionIntersection_RectRect(const AABB &aabb1, const AEVec2 &vel1, 
									const AABB &aabb2, const AEVec2 &vel2)
{
	//Static check
	if (aabb1.max.x < aabb2.min.x || aabb1.max.y < aabb2.min.y || aabb1.min.x > aabb2.max.x || aabb1.min.y > aabb2.max.y)
	{
		//Dynamic check
		float tFirst = 0;
		float tLast = g_dt;

		//Relative velocity (B relative to A)

		AEVec2 vRel;
		vRel.x = vel2.x - vel1.x;
		vRel.y = vel2.y - vel1.y;

		if (vRel.x == 0 || vRel.y == 0)
			return false;

		//x-axis
		if (vRel.x < 0)
		{
			//Case 1
			if (aabb1.min.x > aabb2.max.x)
			{
				return false;
			}

			//Case 4
			if (aabb1.max.x < aabb2.min.x)
			{
				tFirst = AEMax((aabb1.max.x - aabb2.min.x) / vRel.x, tFirst);
			}

			if (aabb1.min.x < aabb2.max.x)
			{
				tLast = AEMin((aabb1.min.x - aabb2.max.x) / vRel.x, tLast);
			}
		}
		else if (vRel.x > 0)
		{
			//Case 3
			if (aabb1.max.x < aabb2.min.x)
			{
				return false;
			}

			//Case 2
			if (aabb1.min.x > aabb2.max.x)
			{
				tFirst = AEMax((aabb1.min.x - aabb2.max.x) / vRel.x, tFirst);
			}

			if (aabb1.max.x > aabb2.min.x)
			{
				tLast = AEMin((aabb1.max.x - aabb2.min.x) / vRel.x, tLast);
			}
		}

		if (tFirst > tLast)
		{
			return false;
		}

		//y-axis
		if (vRel.y < 0)
		{
			//Case 1
			if (aabb1.min.y > aabb2.max.y)
			{
				return false;
			}

			//Case 4
			if (aabb1.max.y < aabb2.min.y)
			{
				tFirst = AEMax((aabb1.max.y - aabb2.min.y) / vRel.y, tFirst);
			}

			if (aabb1.min.y < aabb2.max.y)
			{
				tLast = AEMin((aabb1.min.y - aabb2.max.y) / vRel.y, tLast);
			}
		}
		else if (vRel.y > 0)
		{
			//Case 2
			if (aabb1.min.y > aabb2.max.y)
			{
				tFirst = AEMax((aabb1.min.y - aabb2.max.y) / vRel.y, tFirst);
			}

			if (aabb1.max.y > aabb2.min.y)
			{
				tLast = AEMin((aabb1.max.y - aabb2.min.y) / vRel.y, tLast);
			}

			//Case 3
			if (aabb1.max.y < aabb2.min.y)
			{
				return false;
			}
		}

		if (tFirst > tLast)
		{
			return false;
		}

		return true;
	}
	else
	{
		return true;
	}
}