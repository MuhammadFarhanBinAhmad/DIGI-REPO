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


/******************************************************************************/
/*!
 */
/******************************************************************************/
struct LineSegment
{
	AEVec2	m_pt0;
	AEVec2	m_pt1;
	AEVec2	m_normal;
};

void BuildLineSegment(LineSegment &lineSegment,								//Line segment reference - input
						const AEVec2& p0,									//Point P0 - input
						const AEVec2& p1);									//Point P1 - input

/******************************************************************************/
/*!
 */
/******************************************************************************/
struct Circle
{
	AEVec2  m_center;
	float	m_radius;
};


// INTERSECTION FUNCTIONS
int CollisionIntersection_CircleLineSegment(const Circle &circle,			//Circle data - input
	const AEVec2 &ptEnd,													//End circle position - input
	const LineSegment &lineSeg,												//Line segment - input
	AEVec2 &interPt,														//Intersection point - output
	AEVec2 &normalAtCollision,												//Normal vector at collision time - output
	float &interTime,														//Intersection time ti - output
	bool & checkLineEdges);													//The last parameter is for Extra Credits: when true => check collision with line segment edges



// For Extra Credits
int CheckMovingCircleToLineEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
	const Circle &circle,													//Circle data - input
	const AEVec2 &ptEnd,													//End circle position - input
	const LineSegment &lineSeg,												//Line segment - input
	AEVec2 &interPt,														//Intersection point - output
	AEVec2 &normalAtCollision,												//Normal vector at collision time - output
	float &interTime);														//Intersection time ti - output



// RESPONSE FUNCTIONS
void CollisionResponse_CircleLineSegment(const AEVec2 &ptInter,				//Intersection position of the circle - input
	const AEVec2 &normal,													//Normal vector of reflection on collision time - input
	AEVec2 &ptEnd,															//Final position of the circle after reflection - output
	AEVec2 &reflected);														//Normalized reflection vector direction - output




#endif // CSD1130_COLLISION_H_