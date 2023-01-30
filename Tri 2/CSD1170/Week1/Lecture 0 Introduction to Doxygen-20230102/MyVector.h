#pragma once

#include <iostream>

struct PointInfo
{
	int point_x;
	int point_y;
};
struct VectorInfo
{
	struct PointInfo StartPoint;
	struct PointInfo EndPoint;

	int x_Distance;
	int y_Distance;
};

class Vector
{
private:
	struct PointInfo v_Point[3];
	struct VectorInfo v_Vector[3];
	//V3 - V1 = 0
	//V3 - V2 = 1
	//V3 - V2 = 2
	int Distance[3];
public:
	void SetPoint(int x,int y,int point);
	void SetVector(struct PointInfo s_point, struct PointInfo e_point, int point);

	struct PointInfo GetPoint(int point);
	struct VectorInfo GetVector(int point);

	struct PointInfo ResetPoint(int point);
	struct VectorInfo ResetVector(int point);

	~Vector();
};

int v_DistanceX(struct VectorInfo v);
int v_DistanceY(struct VectorInfo v);

void ScalingImage(Vector* Image, int s);
void TrasformImage(Vector* Image, int t);
void RotateImage(Vector* Image, int r);
//void ShearImage(Vector* Image, int sh, int point);


