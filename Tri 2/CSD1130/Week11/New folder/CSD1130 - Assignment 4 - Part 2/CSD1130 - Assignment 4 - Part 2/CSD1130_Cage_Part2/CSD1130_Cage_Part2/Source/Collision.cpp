/******************************************************************************/
/*!
\file		Collision.cpp
\author 	DigiPen
\par    	email: digipen\@digipen.edu
\date   	January 01, 20xx
\brief

Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#include "main.h"

/******************************************************************************/
/*!
 */
/******************************************************************************/
void BuildLineSegment(LineSegment &lineSegment,
	const AEVec2& p0,
	const AEVec2& p1)
{
	// your code goes here
	UNREFERENCED_PARAMETER(lineSegment);
	UNREFERENCED_PARAMETER(p0);
	UNREFERENCED_PARAMETER(p1);
}

/******************************************************************************/
/*!
 */
/******************************************************************************/
int CollisionIntersection_CircleLineSegment(const Circle &circle,
	const AEVec2 &ptEnd,
	const LineSegment &lineSeg,
	AEVec2 &interPt,
	AEVec2 &normalAtCollision,
	float &interTime,
	bool & checkLineEdges)
{
	// your code goes here
	UNREFERENCED_PARAMETER(circle);
	UNREFERENCED_PARAMETER(ptEnd);
	UNREFERENCED_PARAMETER(lineSeg);
	UNREFERENCED_PARAMETER(normalAtCollision);
	UNREFERENCED_PARAMETER(interPt);
	UNREFERENCED_PARAMETER(interTime);
	UNREFERENCED_PARAMETER(checkLineEdges);

	return 0; // no intersection
}

/******************************************************************************/
/*!
*/
/******************************************************************************/
int CheckMovingCircleToLineEdge(bool withinBothLines,
	const Circle &circle,
	const AEVec2 &ptEnd,
	const LineSegment &lineSeg,
	AEVec2 &interPt,
	AEVec2 &normalAtCollision,
	float &interTime)
{
	// your code goes here
	UNREFERENCED_PARAMETER(withinBothLines);
	UNREFERENCED_PARAMETER(circle);
	UNREFERENCED_PARAMETER(ptEnd);
	UNREFERENCED_PARAMETER(lineSeg);
	UNREFERENCED_PARAMETER(interPt);
	UNREFERENCED_PARAMETER(normalAtCollision);
	UNREFERENCED_PARAMETER(interTime);

	return 0;//no collision
}





/******************************************************************************/
/*!
 */
/******************************************************************************/
void CollisionResponse_CircleLineSegment(const AEVec2 &ptInter,
	const AEVec2 &normal,
	AEVec2 &ptEnd,
	AEVec2 &reflected)
{
	// your code goes here
	UNREFERENCED_PARAMETER(ptInter);
	UNREFERENCED_PARAMETER(normal);
	UNREFERENCED_PARAMETER(ptEnd);
	UNREFERENCED_PARAMETER(reflected);
}



