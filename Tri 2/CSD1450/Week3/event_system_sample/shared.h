#ifndef __SHARED_H__
#define __SHARED_H__


#define WINDOW_W 1600
#define WINDOW_H 900

// Helper macro to get amount of elements in a static array.
#define array_count(a) sizeof(a)/sizeof(*a)

int is_point_in_circle(float circle_center_x, float circle_center_y, float diameter, float point_x, float point_y);
int is_circle_in_circle(float lhs_center_x, float lhs_center_y, float lhs_diameter, float rhs_center_x, float rhs_center_y, float rhs_diameter);

#endif // __SHARED_H__