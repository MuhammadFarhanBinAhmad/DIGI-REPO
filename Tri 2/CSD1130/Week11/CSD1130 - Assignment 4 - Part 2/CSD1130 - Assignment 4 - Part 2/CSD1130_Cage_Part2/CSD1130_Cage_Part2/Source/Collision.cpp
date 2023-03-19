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
#include "Vector2D.h"
#include "Matrix3x3.h"

/******************************************************************************/
/*!
 */
/******************************************************************************/
void BuildLineSegment(LineSegment &lineSegment,
	const AEVec2& p0,
	const AEVec2& p1)
{

	lineSegment.m_pt0 = p0;
	lineSegment.m_pt1 = p1;

	CSD1130::Vector2D length = lineSegment.m_pt1 - lineSegment.m_pt0;

	CSD1130::Vector2DNormalize

	float length_x = lineSegment.m_pt1.x - lineSegment.m_pt0.x;
	float length_y = lineSegment.m_pt1.y - lineSegment.m_pt0.y;

	float normal_x = length_y;
	float normal_y = -length_x;

	float distance = sqrt((normal_x * normal_x) + (normal_y * normal_y));

	lineSegment.m_normal.x = normal_x / distance;
	lineSegment.m_normal.y = normal_y / distance;

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
	
	AEVec2 normalize_Normal = lineSeg.m_normal;

	if ()
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



