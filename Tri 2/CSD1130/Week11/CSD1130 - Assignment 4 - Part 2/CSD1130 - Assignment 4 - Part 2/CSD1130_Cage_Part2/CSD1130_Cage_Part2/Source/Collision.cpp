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

	//set start and end point
	lineSegment.m_pt0 = p0;
	lineSegment.m_pt1 = p1;

	CSD1130::Vector2D pos_Start(p0);
	CSD1130::Vector2D pos_End(p1);

	//get distance and generate normalise normal
	CSD1130::Vector2D distance = pos_End - pos_Start;
	CSD1130::Vector2D normal_Normalize{};

	CSD1130::Vector2DNormalize(normal_Normalize, distance);

	lineSegment.m_normal.x = normal_Normalize.x;
	lineSegment.m_normal.y = normal_Normalize.y;

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
	//CIRCLE STATS
	CSD1130::Vector2D Bs = circle.m_center;
	CSD1130::Vector2D normalize_Bs;
	CSD1130::Vector2DNormalize(normalize_Bs, Bs);

	CSD1130::Vector2D p0 = lineSeg.m_pt0;
	CSD1130::Vector2D p1 = lineSeg.m_pt1;
	CSD1130::Vector2D normalize_Vector = lineSeg.m_normal;

	//(^𝑵.Bs - ^𝑵.P0 <= -R)
	if ((CSD1130::Vector2DDotProduct(normalize_Vector, Bs) - CSD1130::Vector2DDotProduct(normalize_Vector, p0)) <= -circle.m_radius)
	{
		//(𝑀⃗ .BsP0' * 𝑀⃗ .BsP1' < 0)
		//How to get V
	}
	//(^𝑵.Bs - ^𝑵.P0 >= R)
	else if ((CSD1130::Vector2DDotProduct(normalize_Vector, Bs) - CSD1130::Vector2DDotProduct(normalize_Vector, p0)) >= circle.m_radius)
	{

	}
	else
	{
		CheckMovingCircleToLineEdge(true, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
	}

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
	
	CSD1130::Vector2D intersection = ptInter;
	CSD1130::Vector2D Normal = normal;
	CSD1130::Vector2D point_End = ptEnd;
	CSD1130::Vector2D reflec = reflected;

	CSD1130::Vector2D temp;
	//return Bi + penetration - 2(penetration . normal) * normal;
	temp = point_End + ptInter - (2 * (CSD1130::Vector2DDotProduct(ptInter, normal))) * reflec;
	ptEnd.x = temp.x;
	ptEnd.y = temp.y;


}



