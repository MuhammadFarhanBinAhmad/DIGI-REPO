/******************************************************************************/
/*!
\file		Collision.h
\author 	DigiPen
\par    	email: digipen\@digipen.edu
\date   	January 01, 20xx
\brief

Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#ifndef CSD1130_COLLISION_H_
#define CSD1130_COLLISION_H_

#include "Vector2D.h"
#include "Collision.h"

/******************************************************************************/
/*!
 */
/******************************************************************************/
struct LineSegment
{
	CSD1130::Vector2D	m_pt0;
	CSD1130::Vector2D	m_pt1;
	CSD1130::Vector2D	m_normal;
};

void BuildLineSegment(LineSegment &lineSegment,								//Line segment reference - input
						const CSD1130::Vector2D& p0,									//Point P0 - input
						const CSD1130::Vector2D& p1);									//Point P1 - input

/******************************************************************************/
/*!
 */
/******************************************************************************/
struct Circle
{
	CSD1130::Vector2D  m_center;
	float	m_radius;
};


// INTERSECTION FUNCTIONS
int CollisionIntersection_CircleLineSegment(const Circle &circle,			//Circle data - input
	const CSD1130::Vector2D &ptEnd,													//End circle position - input
	const LineSegment &lineSeg,												//Line segment - input
	CSD1130::Vector2D& interPt,														//Intersection point - output // BI
	CSD1130::Vector2D& normalAtCollision,												//Normal vector at collision time - output //
	float &interTime,														//Intersection time ti - output // Ti
	bool & checkLineEdges);													//The last parameter is for Extra Credits: when true => check collision with line segment edges



// For Extra Credits
int CheckMovingCircleToLineEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
	const Circle &circle,													//Circle data - input
	const CSD1130::Vector2D&ptEnd,													//End circle position - input
	const LineSegment&lineSeg,												//Line segment - input
	CSD1130::Vector2D& interPt,														//Intersection point - output
	CSD1130::Vector2D& normalAtCollision,												//Normal vector at collision time - output
	float &interTime);														//Intersection time ti - output



// RESPONSE FUNCTIONS
void CollisionResponse_CircleLineSegment(const CSD1130::Vector2D&ptInter,				//Intersection position of the circle - input
	const CSD1130::Vector2D&normal,													//Normal vector of reflection on collision time - input
	CSD1130::Vector2D &ptEnd,															//Final position of the circle after reflection - output
	CSD1130::Vector2D &reflected);														//Normalized reflection vector direction - output

#endif // CSD1130_COLLISION_H_