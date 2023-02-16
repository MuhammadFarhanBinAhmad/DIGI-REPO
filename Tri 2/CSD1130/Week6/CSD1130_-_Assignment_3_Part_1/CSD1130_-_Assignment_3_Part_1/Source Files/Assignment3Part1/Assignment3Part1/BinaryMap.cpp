/******************************************************************************/
/*!
\file		BinaryMap.cpp
\author 	MuhammadFarhanBinAhmad(2200544)
\par    	email: b.muhammadfarhan@digipen.edu
\date   	February 1, 2023
\brief	
		int		GetCellValue(int,int) - Get Cellvalue of current cell(Use BinaryCollisionArray)
		int		CheckInstanceBinaryMapCollision(float,float,float,float) -	Check for collision
		void	SnapToCell(float*)- Snap back the object to the center of the cell
		int		ImportMapDataFromFile(const char*) - Import data from file(pretty self-explanatory)
		void	FreeMapData() - Free(dom) data
		void	PrintRetrievedInformation() - Print data

*NOTE:ITS BOTTOM LEFT NOT TOP RIGHT(YX. NOT XY)
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior 
written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/


#include "BinaryMap.h"
#include <iostream>
#include <fstream>

/*The number of horizontal elements*/
static int BINARY_MAP_WIDTH;

/*The number of vertical elements*/
static int BINARY_MAP_HEIGHT;

/*This will contain all the data of the map, which will be retreived from a file
when the "ImportMapDataFromFile" function is called*/
static int **MapData;

/*This will contain the collision data of the binary map. It will be filled in the 
"ImportMapDataFromFile" after filling "MapData". Basically, if an array element 
in MapData is 1, it represents a collision cell, any other value is a non-collision
cell*/
static int **BinaryCollisionArray;

std::string length, height;

/******************************************************************************/
/*!
	This function opens the file name "FileName" and retrieves all the map data.
	It allocates memory for the 2 arrays: MapData & BinaryCollisionArray
	The first line in this file is the width of the map.
	The second line in this file is the height of the map.
	The remaining part of the file is a series of numbers
	Each number represents the ID (or value) of a different element in the 
	double dimensionaly array.

	Example:

	Width 5
	Height 5
	1 1 1 1 1
	1 1 1 3 1
	1 4 2 0 1
	1 0 0 0 1
	1 1 1 1 1


	After importing the above data, "MapData" and " BinaryCollisionArray" 
	should be

	1 1 1 1 1
	1 1 1 3 1
	1 4 2 0 1
	1 0 0 0 1
	1 1 1 1 1

	and

	1 1 1 1 1
	1 1 1 0 1
	1 0 0 0 1
	1 0 0 0 1
	1 1 1 1 1

	respectively.
	
	Finally, the function returns 1 if the file named "FileName" exists, 
	otherwise it returns 0
 */
/******************************************************************************/
int ImportMapDataFromFile(const char *FileName)
{
	std::ifstream read_File;
	read_File.open(FileName);

	//Be a good citizen
	//Check file if it exist
	if (!read_File)
	{
		return 0;
	}

	read_File >> length >> BINARY_MAP_WIDTH >> height >> BINARY_MAP_HEIGHT;

	//Allocate mem
	MapData = new int* [BINARY_MAP_HEIGHT];
	BinaryCollisionArray = new int* [BINARY_MAP_HEIGHT];
	//Allocate memory for the MapData and BinaryCollisionArray 2D arrays
	for (int i = 0; i < BINARY_MAP_HEIGHT; i++)
	{
		MapData[i] = new int[BINARY_MAP_WIDTH];
		BinaryCollisionArray[i] = new int[BINARY_MAP_WIDTH];
	}

	//Get data from file
	for (int i = 0; i < BINARY_MAP_HEIGHT;i++)
	{
		for (int j = 0; j < BINARY_MAP_WIDTH; j++)
		{
			read_File >> MapData[i][j];
		}
	}
	//Set binarymap base
	for (int i = 0; i < BINARY_MAP_HEIGHT; i++)
	{
		for (int j = 0; j < BINARY_MAP_WIDTH; j++)
		{
			//anything that is not 1 = clear space
			if (MapData[i][j] == 1)
			{
				BinaryCollisionArray[i][j] = 1;
			}
			else
			{
				BinaryCollisionArray[i][j] = 0;
			}
		}
	}
	read_File.close();

	return 1;
}

/******************************************************************************/
/*!
	This function frees the memory that was allocated for the 2 arrays MapData 
	& BinaryCollisionArray which was allocated in the "ImportMapDataFromFile" 
	function
 */
/******************************************************************************/
void FreeMapData(void)
{
	//FREE(DOM) ALL MEMORY
	for (int i = 0; i < BINARY_MAP_HEIGHT; i++)
	{
		//Delete the rows of MapData and BinaryCollisionArray
		delete[] MapData[i];
		delete[] BinaryCollisionArray[i];
	}
	//Deleting remaining alllocated memory
	delete[] MapData;
	delete[] BinaryCollisionArray;
}

/******************************************************************************/
/*!
	This function prints out the content of the 2D array “MapDataE
	You must print to the console, the same information you are reading from "Exported.txt" file
	Follow exactly the same format of the file, including the print of the width and the height
	Add spaces and end lines at convenient places
 */
/******************************************************************************/
void PrintRetrievedInformation(void)
{
	std::cout << "Width: " << BINARY_MAP_WIDTH << std::endl;
	std::cout << "Height: " << BINARY_MAP_HEIGHT<< std::endl;

	//Print MapData
	for (int i = 0; i < BINARY_MAP_HEIGHT; i++)
	{
		for (int j = 0; j < BINARY_MAP_WIDTH; j++)
		{
			std::cout << MapData[i][j]<< ' ';
		}
		std::cout << '\n';
	}
}

/******************************************************************************/
/*!
	This function retrieves the value of the element (X;Y) in BinaryCollisionArray.
	Before retrieving the value, it should check that the supplied X and Y values
	are not out of bounds (in that case return 0)
 */
/******************************************************************************/
int GetCellValue(int X, int Y)
{
	if (X >=0 && X <BINARY_MAP_WIDTH && Y>=0 && Y<BINARY_MAP_HEIGHT)
	{
		return BinaryCollisionArray[Y][X];
	}
	return 0;
}

/******************************************************************************/
/*!
	This function snaps the value sent as parameter to the center of the cell.
	It is used when a sprite is colliding with a collision area from one 
	or more side.
	To snap the value sent by "Coordinate", find its integral part by type 
	casting it to an integer, then add 0.5 (which is half the cell's width 
	or height)
 */
/******************************************************************************/
void SnapToCell(float *Coordinate)
{
	//Snap back cell
	int temp = (int)(*Coordinate);
	*Coordinate = (float)(temp + 0.5f);
}

/******************************************************************************/
/*!
	This function creates 2 hot spots on each side of the object instance, 
	and checks if each of these hot spots is in a collision area (which means 
	the cell if falls in has a value of 1).
	At the beginning of the function, a "Flag" integer should be initialized to 0.
	Each time a hot spot is in a collision area, its corresponding bit 
	in "Flag" is set to 1.
	Finally, the function returns the integer "Flag"
	The position of the object instance is received as PosX and PosY
	The size of the object instance is received as scaleX and scaleY

	Note: This function assume the object instance's size is 1 by 1 
		  (the size of 1 tile)

	Creating the hotspots:
		-Handle each side separately.
		-2 hot spots are needed for each collision side.
		-These 2 hot spots should be positioned on 1/4 above the center 
		and 1/4 below the center

	Example: Finding the hots spots on the left side of the object instance

	float x1, y1, x2, y2;

	-hotspot 1
	x1 = PosX + scaleX/2	To reach the right side
	y1 = PosY + scaleY/4	To go up 1/4 of the height
	
	-hotspot 2
	x2 = PosX + scaleX/2	To reach the right side
	y2 = PosY - scaleY/4	To go down 1/4 of the height
 */
/******************************************************************************/
int CheckInstanceBinaryMapCollision(float PosX, float PosY, 
									float scaleX, float scaleY)
{

	int flag = 0;

	int x1, x2, y1, y2;
	//CHECK RIGHT
	x1 = (int)(PosX + scaleX / 2);
	y1 = (int)(PosY + scaleY / 4);

	x2 = (int)(PosX + scaleX / 2);
	y2 = (int)(PosY - scaleY / 4);

	if (BinaryCollisionArray[y1][x1] == 1 || BinaryCollisionArray[y2][x2] == 1)
	{
		flag += COLLISION_RIGHT;
	}

	//CHECK LEFT
	x1 = (int)(PosX - scaleX / 2);
	y1 = (int)(PosY - scaleY / 4);

	x2 = (int)(PosX - scaleX / 2);
	y2 = (int)(PosY + scaleY / 4);

	if (BinaryCollisionArray[y1][x1] == 1 || BinaryCollisionArray[y2][x2] == 1)
	{
		flag += COLLISION_LEFT;
	}
	//CHECK UP
	x1 = (int)(PosX - scaleX / 4);
	y1 = (int)(PosY + scaleY / 2);

	x2 = (int)(PosX + scaleX / 4);
	y2 = (int)(PosY + scaleY / 2);

	if (BinaryCollisionArray[y1][x1] == 1 || BinaryCollisionArray[y2][x2] == 1)
	{
		flag += COLLISION_TOP;
	}
	//CHECK DOWN
	x1 = (int)(PosX + scaleX / 4);
	y1 = (int)(PosY - scaleY / 2);

	x2 = (int)(PosX - scaleX / 4);
	y2 = (int)(PosY - scaleY / 2);

	if (BinaryCollisionArray[y1][x1] == 1 || BinaryCollisionArray[y2][x2] == 1)
	{
		flag += COLLISION_BOTTOM;
	}
	return flag;
}