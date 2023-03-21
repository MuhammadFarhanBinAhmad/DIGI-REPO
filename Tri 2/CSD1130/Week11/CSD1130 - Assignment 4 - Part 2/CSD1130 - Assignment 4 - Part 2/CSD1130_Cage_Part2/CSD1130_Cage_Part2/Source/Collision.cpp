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
	const CSD1130::Vector2D& p0,
	const CSD1130::Vector2D& p1)
{

	//set start and end point
	lineSegment.m_pt0 = p0;
	lineSegment.m_pt1 = p1;

	CSD1130::Vector2D temp = p1 - p0;
	CSD1130::Vector2D normal{};

	normal.x = temp.y;
	normal.y = -temp.x;

	CSD1130::Vector2D N_normal{};

	CSD1130::Vector2DNormalize(N_normal, normal);
	lineSegment.m_normal = N_normal;

	//CSD1130::Vector2DNormalize(lineSegment.m_normal, rotMatrix * (p1 - p0));

	//CSD1130::Matrix3x3 rotmatrix{};
	//CSD1130::Mtx33RotRad(rotmatrix, -PI / 2);

	//CSD1130::Vector2DNormalize(lineSegment.m_normal, rotmatrix * (p1 - p0));
}

/******************************************************************************/
/*!
 */
/******************************************************************************/
int CollisionIntersection_CircleLineSegment(const Circle &circle,
	const CSD1130::Vector2D&ptEnd,
	const LineSegment &lineSeg,
	CSD1130::Vector2D&interPt,
	CSD1130::Vector2D&normalAtCollision,
	float &interTime,
	bool & checkLineEdges)
{

	//NORMAL VECTOR ALREADY NORMALIZE SO DONT NEED TO NORMALIZE

	//LINE SEGMENT
	CSD1130::Vector2D Velocity = ptEnd - circle.m_center;
	CSD1130::Vector2D distance_Vector = lineSeg.m_pt1 - circle.m_center;

	//(^𝑵.Bs - ^𝑵.P0 <= -R)
	//Check you are within range
	//if ( CSD1130::Vector2DDotProduct(distance_Vector,lineSeg.m_normal) <= -circle.m_radius)
	if ((CSD1130::Vector2DDotProduct(lineSeg.m_normal,circle.m_center) 
		- 
		CSD1130::Vector2DDotProduct(lineSeg.m_normal, lineSeg.m_pt0)) 
		<= circle.m_radius)
	{
		//P0' = P0 – R*𝑵
		CSD1130::Vector2D p0_prime = lineSeg.m_pt0 - (circle.m_radius * lineSeg.m_normal);
		//P1' = P1 – R*𝑵
		CSD1130::Vector2D p1_prime = lineSeg.m_pt1 - (circle.m_radius * lineSeg.m_normal);

		//𝑀⃗⃗ is the outward normal to Velocity 𝑉⃗ 
		CSD1130::Vector2D M;

		CSD1130::Matrix3x3 rotMatx{};
		CSD1130::Mtx33RotRad(rotMatx, -PI / 2);

		CSD1130::Vector2DNormalize(M, rotMatx * Velocity);
		
		//(𝑀⃗ .BsP0' * 𝑀⃗ .BsP1' < 0)
		//Check actual line
		if ((CSD1130::Vector2DDotProduct(M, (p0_prime-circle.m_center)) 
			* 
			CSD1130::Vector2DDotProduct(M, (p1_prime-circle.m_center))) 
			< 0)
		{
			interTime = (CSD1130::Vector2DDotProduct(lineSeg.m_normal, lineSeg.m_pt0) - (CSD1130::Vector2DDotProduct(lineSeg.m_normal, circle.m_center) - circle.m_radius)
				/ (CSD1130::Vector2DDotProduct(lineSeg.m_normal, Velocity)));

			if (interTime >= 0 && interTime <= 1)
			{
				CSD1130::Vector2D Bi = circle.m_center + Velocity * (interTime);
				interPt.x = Bi.x;
				interPt.y = Bi.y;

				normalAtCollision = lineSeg.m_normal;
				return 1;
			}
			else
			{
				CheckMovingCircleToLineEdge(false, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
				return 0;
			}
		}
	}
	//else if (CSD1130::Vector2DDotProduct(distance_Vector, lineSeg.m_normal) >= circle.m_radius)
	else if ((CSD1130::Vector2DDotProduct(lineSeg.m_normal, circle.m_center)
		-
		CSD1130::Vector2DDotProduct(lineSeg.m_normal, lineSeg.m_pt0))
		>= circle.m_radius)
	{
		//P0' = P0 – R*𝑵
		CSD1130::Vector2D p0_prime = lineSeg.m_pt0 + (circle.m_radius * lineSeg.m_normal);
		//P1' = P1 – R*𝑵
		CSD1130::Vector2D p1_prime = lineSeg.m_pt1 + (circle.m_radius * lineSeg.m_normal);

		//𝑀⃗⃗ is the outward normal to Velocity 𝑉⃗ 
		CSD1130::Vector2D M;

		CSD1130::Matrix3x3 rotMatx{};
		CSD1130::Mtx33RotRad(rotMatx, -PI / 2);

		CSD1130::Vector2DNormalize(M, rotMatx * Velocity);

		//(𝑀⃗ .BsP0' * 𝑀⃗ .BsP1' < 0)
		//Check actual line
		if ((CSD1130::Vector2DDotProduct(M, (p0_prime - circle.m_center))
			*
			CSD1130::Vector2DDotProduct(M, (p1_prime - circle.m_center)))
			< 0)
		{
			interTime = (CSD1130::Vector2DDotProduct(lineSeg.m_normal, lineSeg.m_pt0) - (CSD1130::Vector2DDotProduct(lineSeg.m_normal, circle.m_center) - circle.m_radius)
				/ (CSD1130::Vector2DDotProduct(lineSeg.m_normal, Velocity)));

			if (interTime >= 0 && interTime <= 1)
			{
				CSD1130::Vector2D Bi = circle.m_center + Velocity * (interTime);
				interPt.x = Bi.x;
				interPt.y = Bi.y;

				normalAtCollision = lineSeg.m_normal;
				return 1;
			}
			else
			{
				CheckMovingCircleToLineEdge(false, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
				return 0;
			}
		}
	}
	else
	{
		CheckMovingCircleToLineEdge(true, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
		return 1;
	}
}

/******************************************************************************/
/*!
*/
/******************************************************************************/
int CheckMovingCircleToLineEdge(bool withinBothLines,
	const Circle &circle,
	const CSD1130::Vector2D& ptEnd,
	const LineSegment &lineSeg,
	CSD1130::Vector2D& interPt,
	CSD1130::Vector2D& normalAtCollision,
	float &interTime)
{
	//CIRCLE
	CSD1130::Vector2D Bs = circle.m_center;

	//LINESEGMENT
	CSD1130::Vector2D p0 = lineSeg.m_pt0;
	CSD1130::Vector2D p1 = lineSeg.m_pt1;

	if (withinBothLines)
	{
		CSD1130::Vector2D BsP0 = p0 - Bs;
		CSD1130::Vector2D BsP1 = p1 - Bs;

		//Check which edge may collide first?
		if (CSD1130::Vector2DDotProduct(BsP0, BsP1) > 0)//P0 side
		{
			//if ()
		}
		else
		{

		}
	}
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
void CollisionResponse_CircleLineSegment(const CSD1130::Vector2D &ptInter,
	const CSD1130::Vector2D &normal,
	CSD1130::Vector2D &ptEnd,
	CSD1130::Vector2D &reflected)
{
	

	CSD1130::Vector2D pt_Penet = ptEnd - ptInter;
	//return Bi + penetration - 2(penetration . normal) * normal;

	ptEnd = ptInter + pt_Penet - (2 * (CSD1130::Vector2DDotProduct(pt_Penet, normal))) * normal;
	CSD1130::Vector2D temp = ptEnd - ptInter;
	CSD1130::Vector2DNormalize(reflected, temp);
}



