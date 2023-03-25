/******************************************************************************/
/*!
\file		Collision.cpp
\author 	Muhammad Farhan Bin Ahmad (2200544)
\id			b.muhammadfarhan
\par    	email: b.muhammadfarhan@digipen.edu
\date   	March 22, 2023
\brief
			BuildLineSegment - Create line segment 
			CollisionIntersection_CircleLineSegment - Set collision interaction with line
			CheckMovingCircleToLineEdge - Set collision interaction with line edges
			CollisionResponse_CircleLineSegment - Set reflection feedback

Copyright (C) 2023 DigiPen Institute of Technology.
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

	//Set normal
	CSD1130::Vector2D temp = p1 - p0;
	CSD1130::Vector2D normal{};

	normal.x = temp.y;
	normal.y = -temp.x;
	lineSegment.m_normal = normal;

	//Normalize vector
	CSD1130::Vector2DNormalize(lineSegment.m_normal, normal);
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
	
	CSD1130::Pt2 M;

	M.x = Velocity.y;
	M.y = -Velocity.x;
	
	//(^𝑵.Bs - ^𝑵.P0)
	float nbsp0 = CSD1130::Vector2DDotProduct(lineSeg.m_normal, circle.m_center)
		- CSD1130::Vector2DDotProduct(lineSeg.m_normal, lineSeg.m_pt0);

	//(^𝑵.Bs - ^𝑵.P0 <= -R)
	//Check you are within range
	if (nbsp0 <= -circle.m_radius)
	{
		//P0' = P0 – R*𝑵
		CSD1130::Vector2D p0_prime = lineSeg.m_pt0 - (circle.m_radius * lineSeg.m_normal);
		//P1' = P1 – R*𝑵
		CSD1130::Vector2D p1_prime = lineSeg.m_pt1 - (circle.m_radius * lineSeg.m_normal);


		float mBsp0_mBsp1 = CSD1130::Vector2DDotProduct(M, (p0_prime - circle.m_center))
			* CSD1130::Vector2DDotProduct(M, (p1_prime - circle.m_center));

		//Check actual line
		if (mBsp0_mBsp1 < 0)
		{
			//MAKE SURE N(NORMALIZE).V !=0
			float nv = Vector2DDotProduct(lineSeg.m_normal, Velocity);
			if (nv == 0)
			{
				return 0;
			}

			interTime = (CSD1130::Vector2DDotProduct(lineSeg.m_normal,lineSeg.m_pt0 - circle.m_center) 
				- circle.m_radius) / nv;

			//If collide
			if (interTime >= 0 && interTime <= 1)
			{
				CSD1130::Vector2D Bi = circle.m_center + Velocity * interTime;
				interPt = Bi;
				
				normalAtCollision = -lineSeg.m_normal;
				return 1;
			}
			//No collision
			else
			{
				checkLineEdges = true;
				return CheckMovingCircleToLineEdge(false,
					circle,
					ptEnd,
					lineSeg,
					interPt,
					normalAtCollision,
					interTime);
			}
		}
	}
	//Check you are within range
	else if (nbsp0 > circle.m_radius)
	{
		//P0' = P0 – R*𝑵
		CSD1130::Vector2D p0_prime = lineSeg.m_pt0 + (circle.m_radius * lineSeg.m_normal);
		//P1' = P1 – R*𝑵
		CSD1130::Vector2D p1_prime = lineSeg.m_pt1 + (circle.m_radius * lineSeg.m_normal);


		float mBsp0_mBsp1 = CSD1130::Vector2DDotProduct(M, (p0_prime - circle.m_center))
			* CSD1130::Vector2DDotProduct(M, (p1_prime - circle.m_center));


		//(𝑀⃗ .BsP0' * 𝑀⃗ .BsP1' < 0)
		//Check actual line
		if (mBsp0_mBsp1 < 0)
		{
			//Check normalize vec
			float nv = Vector2DDotProduct(lineSeg.m_normal, Velocity);
			if (nv == 0)
			{
				return 0;
			}

			interTime = (CSD1130::Vector2DDotProduct(lineSeg.m_normal, lineSeg.m_pt0 - circle.m_center)
				+ circle.m_radius) / nv;

			//If collide
			if (interTime >=0  && interTime <= 1)
			{
				CSD1130::Vector2D Bi = circle.m_center + Velocity * interTime;
				interPt = Bi;
				normalAtCollision = lineSeg.m_normal;
				return 1;
			}
			//No collision
			else
			{
				checkLineEdges = false;
				return CheckMovingCircleToLineEdge(false,
					circle,
					ptEnd,
					lineSeg,
					interPt,
					normalAtCollision,
					interTime);
			}
		}
	}
	else
	{
		checkLineEdges = true;
		return CheckMovingCircleToLineEdge(true,
			circle,
			ptEnd,
			lineSeg,
			interPt,
			normalAtCollision,
			interTime);
	}
	return 0;
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

	CSD1130::Vector2D Velocity = ptEnd - circle.m_center;

	CSD1130::Vector2D vec_Normalize;
	CSD1130::Vector2DNormalize(vec_Normalize, Velocity);

	CSD1130::Pt2 M;

	M.x = Velocity.y;
	M.y = -Velocity.x;

	CSD1130::Vector2D M_Normalize;
	CSD1130::Vector2DNormalize(M_Normalize, M);

	//When it’s true, is to say that Bs is starting from between both imaginary
	if (withinBothLines)
	{
		//BsP0.P0P1 - P0 side
		float BsP0_P0P1 = CSD1130::Vector2DDotProduct((lineSeg.m_pt0 - circle.m_center), (lineSeg.m_pt1 - lineSeg.m_pt0));
		if (BsP0_P0P1 > 0)//NO COLLISION
		{
			//m = BsP0_V
			float BsP0_V = CSD1130::Vector2DDotProduct((lineSeg.m_pt0 - circle.m_center), vec_Normalize);
			if (BsP0_V > 0)
			{

				float dist0 = CSD1130::Vector2DDotProduct((lineSeg.m_pt0 - circle.m_center), M_Normalize);//Shortest distance from P0 to 𝑉

				if (abs(dist0) > circle.m_radius)
				{
					return 0;//no collision
				}
				//CIRCLE MOVEMENT GOING TOWARDS P0

				//Cicle at collision time with p0
				float s = sqrtf(circle.m_radius * circle.m_radius - dist0 * dist0);
				interTime = (BsP0_V - s) / CSD1130::Vector2DLength(Velocity);

				if (interTime <= 1)
				{
					CSD1130::Vector2D Bi = circle.m_center + Velocity * interTime;
					//Set reflection
					interPt = Bi;
					CSD1130::Vector2DNormalize(normalAtCollision,Bi-lineSeg.m_pt0);
					return 1;
				}
			}
		}
		else
		{
			//m =BsP1_V
			float BsP1_V = CSD1130::Vector2DDotProduct((lineSeg.m_pt1 - circle.m_center), vec_Normalize);

			//NO COLLISION
			if (BsP1_V > 0)
			{
				//CIRCLE MOVEMENT GOING TOWARDS P1

				//Cicle at collision time with p1
				float dist1 = CSD1130::Vector2DDotProduct((lineSeg.m_pt1 - circle.m_center), M_Normalize);

				if (abs(dist1) > circle.m_radius)
				{
					return 0;//no collision
				}
				else
				{
					//circle at collision time with P1
					float s = sqrtf(circle.m_radius * circle.m_radius - dist1 * dist1);
					interTime = (BsP1_V - s) / CSD1130::Vector2DLength(Velocity);

					if (interTime <= 1)
					{
						CSD1130::Vector2D Bi = circle.m_center + Velocity * interTime;
						//Set reflection
						interPt = Bi;
						CSD1130::Vector2DNormalize(normalAtCollision, Bi - lineSeg.m_pt1);
						return 1;
					}
				}
			}
		}
	}
	else
	{

		bool p0Side = false;
		float dist0 = CSD1130::Vector2DDotProduct((lineSeg.m_pt0 - circle.m_center), M_Normalize);
		float dist1 = CSD1130::Vector2DDotProduct((lineSeg.m_pt1 - circle.m_center), M_Normalize);

		float dist0_absVal = abs(dist0);
		float dist1_absVal = abs(dist1);

		if (dist0_absVal > circle.m_radius && dist1_absVal > circle.m_radius)
		{
			return 0;
		}
		else if (dist0_absVal <= circle.m_radius && dist1_absVal <= circle.m_radius)
		{
			float m0 = CSD1130::Vector2DDotProduct(lineSeg.m_pt0 - circle.m_center, vec_Normalize);
			float m1 = CSD1130::Vector2DDotProduct(lineSeg.m_pt1 - circle.m_center, vec_Normalize);

			float m0_absVal = abs(m0);
			float m1_absVal = abs(m1);

			if (m0_absVal < m1_absVal)
			{
				p0Side = true;
			}
			else
			{
				p0Side = false;
			}
		}
		else if (dist0_absVal <= circle.m_radius)
		{
			p0Side = true;
		}
		else
		{
			p0Side = false;
		}

		if (p0Side)
		{
			//m
			float BsP0_V = CSD1130::Vector2DDotProduct((lineSeg.m_pt0 - circle.m_center), vec_Normalize);

			if (BsP0_V < 0)
			{
				//MOVING AWAY
				return 0;
			}
			else
			{
				//CIRCLE MOVING TOWARDS P0
				
				//Circle at collision time p0
				float s = sqrtf(circle.m_radius * circle.m_radius - dist0 * dist0);
				interTime = (BsP0_V - s) / CSD1130::Vector2DLength(Velocity);

				if (interTime <= 1)
				{
					//Set reflection
					CSD1130::Vector2D Bi = circle.m_center + Velocity * interTime;
					interPt = Bi;
					CSD1130::Vector2DNormalize(normalAtCollision, Bi - lineSeg.m_pt0);
					return 1;
				}
			}
		}
		else
		{
			//m
			float BsP1_V = CSD1130::Vector2DDotProduct((lineSeg.m_pt1 - circle.m_center), vec_Normalize);
			if (BsP1_V < 0)
			{
				return 0;
			}
			else
			{
				//CIRCLE MOVING TOWARDS P1

				//Circle at collision time p1
				float s = sqrtf(circle.m_radius * circle.m_radius - dist1 * dist1);
				interTime = (BsP1_V - s) / CSD1130::Vector2DLength(Velocity);

				if (interTime <= 1)
				{
					//Set reflection
					CSD1130::Vector2D Bi = circle.m_center + Velocity * interTime;
					interPt = Bi;
					CSD1130::Vector2DNormalize(normalAtCollision, Bi - lineSeg.m_pt1);
					return 1;
				}
			}
		}

	}
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
	//return Bi + penetration - 2(penetration . normal) * normal;
	CSD1130::Vector2D pt_Penet = ptEnd - ptInter;
	//Set reflection
	ptEnd = ptInter + pt_Penet - 2 * CSD1130::Vector2DDotProduct(pt_Penet, normal) * normal;
	reflected = ptEnd - ptInter;
	//Normalize vector
	CSD1130::Vector2DNormalize(reflected, reflected);
}



