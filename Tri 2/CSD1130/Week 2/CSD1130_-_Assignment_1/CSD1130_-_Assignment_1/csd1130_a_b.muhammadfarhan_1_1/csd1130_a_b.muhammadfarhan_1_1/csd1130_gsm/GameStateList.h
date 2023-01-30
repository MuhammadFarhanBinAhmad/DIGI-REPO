/* Start Header ************************************************************************/
/*!
\file <csd1130_gsm.cpp>
\author <Muhammad Farhan Bin Ahmad,b.muhammadfarhan,2200544>
\par <b.muhammadfarhan@digipen.edu>
\date <Jan 13,2023> 
\brief
/// <Function Brief>
//GS_STATES - Handle all current Game states
/// <Function Brief>
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
#pragma once
enum GS_STATES
{
	GS_LEVEL1 = 0,
	GS_LEVEL2 = 1,

	GS_QUIT,
	GS_RESTART
};