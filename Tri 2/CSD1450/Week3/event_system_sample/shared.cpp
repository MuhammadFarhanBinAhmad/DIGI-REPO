#pragma once

// Helper function to find point within circle
int is_point_in_circle(float circle_center_x, float circle_center_y, float diameter, float point_x, float point_y)
{
	float local_x = point_x - circle_center_x;
	float local_y = point_y - circle_center_y;
	float radius = diameter / 2.f;
	return (local_x * local_x + local_y * local_y) <= (radius * radius);
}

int is_circle_in_circle(float lhs_center_x, float lhs_center_y, float lhs_diameter, float rhs_center_x, float rhs_center_y, float rhs_diameter)
{
	float local_x = rhs_center_x - lhs_center_x;
	float local_y = rhs_center_y - lhs_center_y;
	float lhs_radius = lhs_diameter / 2.f;
	float rhs_radius = rhs_diameter / 2.f;

	float total_radius = lhs_radius + rhs_radius;

	return (local_x * local_x + local_y * local_y) <= (total_radius * total_radius);
}
