/******************************************************************************/
/*!
\file		Matrix3x3.cpp
\author 	muhammad farhan bin ahmad(2200544)
\par    	email: b.muhammadfarhan@digipen.edu
\date   	March 11, 2023
\brief		
			3 Constructor:
			Default constructor
			Copy assignment
			Copy constructor
			1 Assigment operator:
			Matrix3x3& operator *=

			2 Non-member operator:
			Matrix3x3 operator * - This operator multiplies 2 matrix and returna matrix
			Vector2D  operator * - This operator multiplies a matrix pMtx with the vector and returns the result as a vector
			7 Non-member function:
			void Mtx33Identity - Set Identity matrix
			void Mtx33Translate - Translate matrix
			void Mtx33Scale - Scale up/down matrix
			void Mtx33RotRad - Rotate matrix in radian value
			void Mtx33RotDeg - Rotate matrix in degree value
			void Mtx33Transpose - Transpose the matrix
			void Mtx33Inverse - Inverse the matrix


Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "Matrix3x3.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define M_PI 3.14159265358979323846

namespace CSD1130
{

	Matrix3x3::Matrix3x3(const float* pArr)
	{
		m[0] = pArr[0];
		m[1] = pArr[1];
		m[2] = pArr[2];
		m[3] = pArr[3];
		m[4] = pArr[4];
		m[5] = pArr[5];
		m[6] = pArr[6];
		m[7] = pArr[7];
		m[8] = pArr[8];
	}
	Matrix3x3::Matrix3x3(float _00, float _01, float _02,
		float _10, float _11, float _12,
		float _20, float _21, float _22)
	{
		m[0] = _00;
		m[1] = _01;
		m[2] = _02;
		m[3] = _10;
		m[4] = _11;
		m[5] = _12;
		m[6] = _20;
		m[7] = _21;
		m[8] = _22;
	}
	Matrix3x3& Matrix3x3::operator=(const Matrix3x3& rhs)
	{
		m[0] = rhs.m[0];
		m[1] = rhs.m[1];
		m[2] = rhs.m[2];
		m[3] = rhs.m[3];
		m[4] = rhs.m[4];
		m[5] = rhs.m[5];
		m[6] = rhs.m[6];
		m[7] = rhs.m[7];
		m[8] = rhs.m[8];

		return *this;
	}

	// Assignment operators
	Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& rhs)
	{

		Matrix3x3 temp;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				float sum = 0.0f;
				for (int k = 0; k < 3; k++)
				{
					sum += m2[i][k] * rhs.m2[k][j];
				}
				temp.m2[i][j] = sum;
			}
		}

		// Copy the elements of the temporary matrix into the left-hand side matrix.
		memcpy(m, temp.m, sizeof(float) * 9);

		return *this;
	}

	Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		Matrix3x3 result;

		result.m00 = lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20;
		result.m01 = lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21;
		result.m02 = lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22;

		result.m10 = lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20;
		result.m11 = lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21;
		result.m12 = lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22;

		result.m20 = lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20;
		result.m21 = lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21;
		result.m22 = lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22;

		return result;
	}

	/**************************************************************************/
	/*!
		This operator multiplies the matrix pMtx with the vector rhs
		and returns the result as a vector
	 */
	 /**************************************************************************/
	Vector2D  operator*(const Matrix3x3& pMtx, const Vector2D& rhs)
	{
		float x = pMtx.m00 * rhs.x + pMtx.m01 * rhs.y + pMtx.m02;
		float y = pMtx.m10 * rhs.x + pMtx.m11 * rhs.y + pMtx.m12;
		return Vector2D(x, y);
	}

	/**************************************************************************/
	/*!
		This function sets the matrix pResult to the identity matrix
	 */
	 /**************************************************************************/
	void Mtx33Identity(Matrix3x3& pResult)
	{
		pResult.m00 = 1;
		pResult.m11 = 1;
		pResult.m22 = 1;

		pResult.m01 = 0;
		pResult.m02 = 0;
		pResult.m10 = 0;
		pResult.m12 = 0;
		pResult.m20 = 0;
		pResult.m21 = 0;

	}

	/**************************************************************************/
	/*!
		This function creates a translation matrix from x & y
		and saves it in pResult
	 */
	 /**************************************************************************/
	void Mtx33Translate(Matrix3x3& pResult, float x, float y)
	{
		// Start with an identity matrix
		Mtx33Identity(pResult);

		// Update the third column to contain the translation offset
		pResult.m02 = x;
		pResult.m12 = y;
	}

	/**************************************************************************/
	/*!
		This function creates a scaling matrix from x & y
		and saves it in pResult
	 */
	 /**************************************************************************/
	void Mtx33Scale(Matrix3x3& pResult, float x, float y)
	{
		Mtx33Identity(pResult);

		pResult.m00 = x;
		pResult.m11 = y;
		pResult.m22 = 1.0f;
	}

	/**************************************************************************/
	/*!
		This matrix creates a rotation matrix from "angle" whose value
		is in radian. Save the resultant matrix in pResult.
	 */
	 /**************************************************************************/
	void Mtx33RotRad(Matrix3x3& pResult, float angle)
	{
		Mtx33Identity(pResult);
		float cosVal = cos(angle);
        float sinVal = sin(angle);
		pResult = Matrix3x3(cosVal, -sinVal, 0.0f,
                            sinVal, cosVal, 0.0f,
                            0.0f, 0.0f, 1.0f);
	}

	/**************************************************************************/
	/*!
		This matrix creates a rotation matrix from "angle" whose value
		is in degree. Save the resultant matrix in pResult.
	 */
	 /**************************************************************************/
	void Mtx33RotDeg(Matrix3x3& pResult, float angle)
	{
		// Convert angle from degrees to radians
		float angleRad = angle * M_PI / 180.0f;

		// Calculate the rotation matrix
		Mtx33RotRad(pResult, angleRad);
	}

	/**************************************************************************/
	/*!
		This functions calculated the transpose matrix of pMtx
		and saves it in pResult
	 */
	 /**************************************************************************/
	void Mtx33Transpose(Matrix3x3& pResult, const Matrix3x3& pMtx)
	{
		pResult.m00 = pMtx.m00;
		pResult.m01 = pMtx.m10;
		pResult.m02 = pMtx.m20;

		pResult.m10 = pMtx.m01;
		pResult.m11 = pMtx.m11;
		pResult.m12 = pMtx.m21;

		pResult.m20 = pMtx.m02;
		pResult.m21 = pMtx.m12;
		pResult.m22 = pMtx.m22;
	}

	/**************************************************************************/
	/*!
		This function calculates the inverse matrix of pMtx and saves the
		result in pResult. If the matrix inversion fails, pResult
		would be set to NULL.
	*/
	/**************************************************************************/
	void Mtx33Inverse(Matrix3x3* pResult, float* determinant, const Matrix3x3& pMtx)
	{
		// Step 1: Calculate the determinant of pMtx
		float det = pMtx.m00 * (pMtx.m11 * pMtx.m22 - pMtx.m12 * pMtx.m21) -
			pMtx.m01 * (pMtx.m10 * pMtx.m22 - pMtx.m12 * pMtx.m20) +
			pMtx.m02 * (pMtx.m10 * pMtx.m21 - pMtx.m11 * pMtx.m20);
		*determinant = det;

		// Step 2: Check if the determinant is zero
		if (det == 0)
		{
			pResult = NULL; // matrix has no inverse
			return;
		}

		// Step 3: Calculate the adjoint matrix of pMtx
		Matrix3x3 adjoint;
		adjoint.m00 = pMtx.m11 * pMtx.m22 - pMtx.m12 * pMtx.m21;
		adjoint.m01 = -(pMtx.m01 * pMtx.m22 - pMtx.m02 * pMtx.m21);
		adjoint.m02 = pMtx.m01 * pMtx.m12 - pMtx.m02 * pMtx.m11;
		adjoint.m10 = -(pMtx.m10 * pMtx.m22 - pMtx.m12 * pMtx.m20);
		adjoint.m11 = pMtx.m00 * pMtx.m22 - pMtx.m02 * pMtx.m20;
		adjoint.m12 = -(pMtx.m00 * pMtx.m12 - pMtx.m02 * pMtx.m10);
		adjoint.m20 = pMtx.m10 * pMtx.m21 - pMtx.m11 * pMtx.m20;
		adjoint.m21 = -(pMtx.m00 * pMtx.m21 - pMtx.m01 * pMtx.m20);
		adjoint.m22 = pMtx.m00 * pMtx.m11 - pMtx.m01 * pMtx.m10;

		float inv_det = 1.0f / det;

		pResult->m00 = adjoint.m00 * inv_det;
		pResult->m01 = adjoint.m10 * inv_det;
		pResult->m02 = adjoint.m20 * inv_det;
		pResult->m10 = adjoint.m01 * inv_det;
		pResult->m11 = adjoint.m11 * inv_det;
		pResult->m12 = adjoint.m21 * inv_det;
		pResult->m20 = adjoint.m02 * inv_det;
		pResult->m21 = adjoint.m12 * inv_det;
		pResult->m22 = adjoint.m22 * inv_det;
	}
}
