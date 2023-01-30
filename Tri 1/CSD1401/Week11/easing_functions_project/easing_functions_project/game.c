#include "cprocessing.h"
#include "easing.h"

#define ArrayCount(arr) sizeof(arr)/(sizeof(arr[0]))

float timer;
float duration;
float min_x;
float max_x;

float min_size;
float max_size;

int current_easing_function_index;


typedef float (*EasingFunctionType)(float, float, float);

typedef struct {
	EasingFunctionType function;
	const char* name;
} EasingFunctionInfo;

#define DECLARE_EASING_INFO(name) { name, #name },
static EasingFunctionInfo easing_function_table[] = {
	DECLARE_EASING_INFO(Linear)
	DECLARE_EASING_INFO(EaseInQuad)
	DECLARE_EASING_INFO(EaseOutQuad)
	DECLARE_EASING_INFO(EaseInOutQuad)
	DECLARE_EASING_INFO(EaseInCubic)
	DECLARE_EASING_INFO(EaseOutCubic)
	DECLARE_EASING_INFO(EaseInOutCubic)
	DECLARE_EASING_INFO(EaseInQuart)
	DECLARE_EASING_INFO(EaseOutQuart)
	DECLARE_EASING_INFO(EaseInOutQuart)
	DECLARE_EASING_INFO(EaseInQuint)
	DECLARE_EASING_INFO(EaseOutQuint)
	DECLARE_EASING_INFO(EaseInOutQuint)
	DECLARE_EASING_INFO(EaseInSine)
	DECLARE_EASING_INFO(EaseOutSine)
	DECLARE_EASING_INFO(EaseInOutSine)
	DECLARE_EASING_INFO(EaseInExpo)
	DECLARE_EASING_INFO(EaseOutExpo)
	DECLARE_EASING_INFO(EaseInOutExpo)
	DECLARE_EASING_INFO(EaseInCirc)
	DECLARE_EASING_INFO(EaseOutCirc)
	DECLARE_EASING_INFO(EaseInOutCirc)
	DECLARE_EASING_INFO(EaseOutBounce)
	DECLARE_EASING_INFO(EaseInBounce)
	DECLARE_EASING_INFO(EaseInOutBounce)
	DECLARE_EASING_INFO(EaseInBack)
	DECLARE_EASING_INFO(EaseOutBack)
	DECLARE_EASING_INFO(EaseInOutBack)
	DECLARE_EASING_INFO(EaseInElastic)
	DECLARE_EASING_INFO(EaseOutElastic)
	DECLARE_EASING_INFO(EaseInOutElastic)
};
#undef DECLARE_EASING_FUNC


#pragma once

#include <stdlib.h>
#include <math.h>
#define NATURAL_LOG_OF_2    0.693147181f
#define PI                3.14159265358979323846f  /* pi */

#define SWAP(type, lhs, rhs) { \
	type temp = lhs; \
	lhs = rhs; \
    rhs = temp; \
}


typedef enum {
	FORWARD,
	BACKWARD,
} Direction;
Direction direction;

void GameInit(void)
{
	direction = FORWARD;
	timer = 0.f;
	duration = 2.f;
	min_x = 150.f;
	max_x = 650.f;
	min_size = 50;
	max_size = 130.f;

	current_easing_function_index = 0;
}
void GameUpdate(void)
{
	timer += CP_System_GetDt();
	if (timer >= duration) {
		timer = 0.f;
		SWAP(float, min_x, max_x);
		SWAP(float, min_size, max_size);
	}


	if (CP_Input_KeyTriggered(KEY_RIGHT))
	{
		++current_easing_function_index;
		if (current_easing_function_index >= ArrayCount(easing_function_table)) {
			current_easing_function_index = 0;
		}
	}

	if (CP_Input_KeyTriggered(KEY_LEFT))
	{
		--current_easing_function_index;
		if (current_easing_function_index < 0) {
			current_easing_function_index = ArrayCount(easing_function_table) - 1;
		}
	}


	EasingFunctionInfo* current_easing_function = easing_function_table + current_easing_function_index;
	float circle_x = current_easing_function->function(min_x, max_x, timer / duration);
	float circle_size = current_easing_function->function(min_size, max_size, timer / duration);

	CP_Color background_color = { 125, 125, 125, 255 };
	CP_Graphics_ClearBackground(background_color);

	CP_Color text_color = { 255, 255, 255, 255 };
	CP_Settings_Fill(text_color);
	CP_Settings_TextSize(30.f);
	CP_Font_DrawText(current_easing_function->name, 10.f, 30.f);

	CP_Color circle_color = { 255, 255, 255, 255 };
	CP_Settings_Fill(circle_color);
	CP_Graphics_DrawCircle(circle_x, 150.f, circle_size);
}


void GameExit(void)
{
	
}
