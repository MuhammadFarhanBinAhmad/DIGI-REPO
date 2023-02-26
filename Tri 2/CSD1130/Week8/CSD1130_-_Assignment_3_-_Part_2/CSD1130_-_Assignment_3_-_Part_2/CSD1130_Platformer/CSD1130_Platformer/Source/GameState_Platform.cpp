/******************************************************************************/
/*!
\file		GameState_Asteroids.cpp
\author 	DigiPen
\par    	email: digipen\@digipen.edu
\date   	February 01, 20xx
\brief

Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#include "main.h"
#include <iostream>
#include <fstream>
/******************************************************************************/
/*!
	Defines
*/
/******************************************************************************/
const unsigned int	GAME_OBJ_NUM_MAX		= 32;	//The total number of different objects (Shapes)
const unsigned int	GAME_OBJ_INST_NUM_MAX	= 2048;	//The total number of different game object instances

//Gameplay related variables and values
const float			GRAVITY					= -20.0f;
const float			JUMP_VELOCITY			= 11.0f;
const float			MOVE_VELOCITY_HERO		= 4.0f;
const float			MOVE_VELOCITY_ENEMY		= 7.5f;
const double		ENEMY_IDLE_TIME			= 2.0;
const int			HERO_LIVES				= 3;

//Flags
const unsigned int	FLAG_ACTIVE				= 0x00000001;
const unsigned int	FLAG_VISIBLE			= 0x00000002;
const unsigned int	FLAG_NON_COLLIDABLE		= 0x00000004;

//Collision flags
const unsigned int	COLLISION_LEFT			= 0x00000001;	//0001
const unsigned int	COLLISION_RIGHT			= 0x00000002;	//0010
const unsigned int	COLLISION_TOP			= 0x00000004;	//0100
const unsigned int	COLLISION_BOTTOM		= 0x00000008;	//1000


enum TYPE_OBJECT
{
	TYPE_OBJECT_EMPTY,			//0
	TYPE_OBJECT_COLLISION,		//1
	TYPE_OBJECT_HERO,			//2
	TYPE_OBJECT_ENEMY1,			//3
	TYPE_OBJECT_COIN			//4
	
};

//State machine states
enum STATE
{
	STATE_NONE,
	STATE_GOING_LEFT,
	STATE_GOING_RIGHT
};

//State machine inner states
enum INNER_STATE
{
	INNER_STATE_ON_ENTER,
	INNER_STATE_ON_UPDATE,
	INNER_STATE_ON_EXIT
};

/******************************************************************************/
/*!
	Struct/Class Definitions
*/
/******************************************************************************/
struct GameObj
{
	unsigned int		type;		// object type
	AEGfxVertexList *	pMesh;		// pbject
};


struct GameObjInst
{
	GameObj *		pObject;	// pointer to the 'original'
	unsigned int	flag;		// bit flag or-ed together
	float			scale;
	AEVec2			posCurr;	// object current position
	AEVec2			velCurr;	// object current velocity
	float			dirCurr;	// object current direction

	AEMtx33			transform;	// object drawing matrix
	
	AABB			boundingBox;// object bouding box that encapsulates the object

	//Used to hold the current 
	int				gridCollisionFlag;

	// pointer to custom data specific for each object type
	void*			pUserData;

	//State of the object instance
	enum			STATE state;
	enum			INNER_STATE innerState;

	//General purpose counter (This variable will be used for the enemy state machine)
	double			counter;
};


/******************************************************************************/
/*!
	File globals
*/
/******************************************************************************/
static int				HeroLives;
static int				Hero_Initial_X;
static int				Hero_Initial_Y;
static int				TotalCoins;

// list of original objects
static GameObj			*sGameObjList;
static unsigned int		sGameObjNum;

// list of object instances
static GameObjInst		*sGameObjInstList;
static unsigned int		sGameObjInstNum;

//Binary map data
static int				**MapData;
static int				**BinaryCollisionArray;
static int				BINARY_MAP_WIDTH;
static int				BINARY_MAP_HEIGHT;
static GameObjInst		*pBlackInstance;
static GameObjInst		*pWhiteInstance;
static AEMtx33			MapTransform;

int						GetCellValue(int X, int Y);
int						CheckInstanceBinaryMapCollision(float PosX, float PosY, 
														float scaleX, float scaleY);
void					SnapToCell(float *Coordinate);
int						ImportMapDataFromFile(char *FileName);
void					FreeMapData(void);

// function to create/destroy a game object instance
static GameObjInst*		gameObjInstCreate (unsigned int type, float scale, 
											AEVec2* pPos, AEVec2* pVel, 
											float dir, enum STATE startState);
static void				gameObjInstDestroy(GameObjInst* pInst);

//We need a pointer to the hero's instance for input purposes
static GameObjInst		*pHero;

//State machine functions
void					EnemyStateMachine(GameObjInst *pInst);

std::string length, height;
bool is_grounded;

/******************************************************************************/
/*!

*/
/******************************************************************************/
void GameStatePlatformLoad(void)
{
	sGameObjList = (GameObj *)calloc(GAME_OBJ_NUM_MAX, sizeof(GameObj));
	sGameObjInstList = (GameObjInst *)calloc(GAME_OBJ_INST_NUM_MAX, sizeof(GameObjInst));
	sGameObjNum = 0;


	GameObj* pObj;

	//Creating the black object
	pObj		= sGameObjList + sGameObjNum++;
	pObj->type	= TYPE_OBJECT_EMPTY;


	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFF000000, 0.0f, 0.0f,
		 0.5f,  -0.5f, 0xFF000000, 0.0f, 0.0f, 
		-0.5f,  0.5f, 0xFF000000, 0.0f, 0.0f);
	
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f,
		 0.5f,  -0.5f, 0xFF000000, 0.0f, 0.0f, 
		0.5f,  0.5f, 0xFF000000, 0.0f, 0.0f);

	pObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pObj->pMesh, "fail to create object!!");
		
	
	//Creating the white object
	pObj		= sGameObjList + sGameObjNum++;
	pObj->type	= TYPE_OBJECT_COLLISION;


	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		 0.5f,  -0.5f, 0xFFFFFFFF, 0.0f, 0.0f, 
		-0.5f,  0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f, 
		 0.5f,  -0.5f, 0xFFFFFFFF, 0.0f, 0.0f, 
		0.5f,  0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	pObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pObj->pMesh, "fail to create object!!");


	//Creating the hero object
	pObj		= sGameObjList + sGameObjNum++;
	pObj->type	= TYPE_OBJECT_HERO;


	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFF0000FF, 0.0f, 0.0f, 
		 0.5f,  -0.5f, 0xFF0000FF, 0.0f, 0.0f, 
		-0.5f,  0.5f, 0xFF0000FF, 0.0f, 0.0f);
	
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFF0000FF, 0.0f, 0.0f,
		 0.5f,  -0.5f, 0xFF0000FF, 0.0f, 0.0f, 
		0.5f,  0.5f, 0xFF0000FF, 0.0f, 0.0f);

	pObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pObj->pMesh, "fail to create object!!");


	//Creating the enemey1 object
	pObj		= sGameObjList + sGameObjNum++;
	pObj->type	= TYPE_OBJECT_ENEMY1;


	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 0.0f, 
		 0.5f,  -0.5f, 0xFFFF0000, 0.0f, 0.0f, 
		-0.5f,  0.5f, 0xFFFF0000, 0.0f, 0.0f);
	
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f, 
		 0.5f,  -0.5f, 0xFFFF0000, 0.0f, 0.0f, 
		0.5f,  0.5f, 0xFFFF0000, 0.0f, 0.0f);

	pObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pObj->pMesh, "fail to create object!!");


	//Creating the Coin object
	pObj		= sGameObjList + sGameObjNum++;
	pObj->type	= TYPE_OBJECT_COIN;


	AEGfxMeshStart();
	//Creating the circle shape
	int Parts = 12;
	for(float i = 0; i < Parts; ++i)
	{
		AEGfxTriAdd(
		0.0f, 0.0f, 0xFFFFFF00, 0.0f, 0.0f, 
		cosf(i*2*PI/Parts)*0.5f,  sinf(i*2*PI/Parts)*0.5f, 0xFFFFFF00, 0.0f, 0.0f, 
		cosf((i+1)*2*PI/Parts)*0.5f,  sinf((i+1)*2*PI/Parts)*0.5f, 0xFFFFFF00, 0.0f, 0.0f);
	}

	pObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pObj->pMesh, "fail to create object!!");

	//Setting intital binary map values
	MapData = 0;
	BinaryCollisionArray = 0;
	BINARY_MAP_WIDTH = 0;
	BINARY_MAP_HEIGHT = 0;

	//Importing Data
	if(!ImportMapDataFromFile("..//Resources//Levels//Exported.txt"))
		gGameStateNext = GS_QUIT;


	//Computing the matrix which take a point out of the normalized coordinates system
	//of the binary map
	/***********
	Compute a transformation matrix and save it in "MapTransform".
	This transformation transforms any point from the normalized coordinates system of the binary map.
	Later on, when rendering each object instance, we should concatenate "MapTransform" with the
	object instance's own transformation matrix

	Compute a translation matrix (-Grid width/2, -Grid height/2) and save it in "trans"
	Compute a scaling matrix and save it in "scale". The scale must account for the window width and height.
		Alpha engine has 2 helper functions to get the window width and height: AEGetWindowWidth() and AEGetWindowHeight()
	Concatenate scale and translate and save the result in "MapTransform"
	***********/ 
	AEMtx33 scale, trans;

	MapTransform = { 0 };
	trans = { 0 };
	scale = { 0 };
	AEMtx33Trans(&trans, -AEGetWindowWidth()/2, -AEGetWindowHeight() / 2);
	AEMtx33Scale(&scale, AEGetWindowWidth() / BINARY_MAP_WIDTH, AEGetWindowWidth() / BINARY_MAP_HEIGHT);
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void GameStatePlatformInit(void)
{
	int x{}, y{};

	pHero = 0;
	pBlackInstance = 0;
	pWhiteInstance = 0;
	TotalCoins = 0;

	//Create an object instance representing the black cell.
	//This object instance should not be visible. When rendering the grid cells, each time we have
	//a non collision cell, we position this instance in the correct location and then we render it
	pBlackInstance = gameObjInstCreate(TYPE_OBJECT_EMPTY, 1.0f, 0, 0, 0.0f, STATE_NONE);
	pBlackInstance->flag ^= FLAG_VISIBLE;
	pBlackInstance->flag |= FLAG_NON_COLLIDABLE;

	//Create an object instance representing the white cell.
	//This object instance should not be visible. When rendering the grid cells, each time we have
	//a collision cell, we position this instance in the correct location and then we render it
	pWhiteInstance = gameObjInstCreate(TYPE_OBJECT_COLLISION, 1.0f, 0, 0, 0.0f, STATE_NONE);
	pWhiteInstance->flag ^= FLAG_VISIBLE;
	pWhiteInstance->flag |= FLAG_NON_COLLIDABLE;

	//Setting the inital number of hero lives
	HeroLives = HERO_LIVES;

	GameObjInst *pInst;
	AEVec2 Pos;

	UNREFERENCED_PARAMETER(pInst);
	UNREFERENCED_PARAMETER(Pos);

	// creating the main character, the enemies and the coins according 
	// to their initial positions in MapData

	/***********
	Loop through all the array elements of MapData 
	(which was initialized in the "GameStatePlatformLoad" function
	from the .txt file
		if the element represents a collidable or non collidable area
			don't do anything

		if the element represents the hero
			Create a hero instance
			Set its position depending on its array indices in MapData
			Save its array indices in Hero_Initial_X and Hero_Initial_Y 
			(Used when the hero dies and its position needs to be reset)

		if the element represents an enemy
			Create an enemy instance
			Set its position depending on its array indices in MapData
			
		if the element represents a coin
			Create a coin instance
			Set its position depending on its array indices in MapData
			
	***********/
	for(x = 0; x < BINARY_MAP_WIDTH; ++x)
		for(y = 0; y < BINARY_MAP_HEIGHT; ++y)
		{
			switch (MapData[x][y])
			{
				case TYPE_OBJECT_HERO:
				{
					AEVec2 pos = { (f32)y,(f32)x};
					pHero = gameObjInstCreate(TYPE_OBJECT_HERO, 1.0f, &pos, &pos, 0.0f, STATE_NONE);
					continue;
				}
				case TYPE_OBJECT_ENEMY1:
				{
					AEVec2 pos = { (f32)y,(f32)x };
					gameObjInstCreate(TYPE_OBJECT_ENEMY1, 1.0f, &pos, &pos, 0.0f, STATE_NONE);
					continue;
				}
				case TYPE_OBJECT_COIN:
				{
					AEVec2 pos = { (f32)y,(f32)x };
					gameObjInstCreate(TYPE_OBJECT_COIN, 1.0f, &pos, &pos, 0.0f, STATE_NONE);
					continue;
				}
			}
		}
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void GameStatePlatformUpdate(void)
{
	int i, j;
	GameObjInst *pInst ;

	if (AEInputCheckReleased(AEVK_RIGHT))
	{
		pHero->velCurr.x = MOVE_VELOCITY_HERO;
	}
	else if (AEInputCheckReleased(AEVK_LEFT))
	{
		pHero->velCurr.x = -MOVE_VELOCITY_HERO;
	}
	else
		pHero->velCurr.x = -MOVE_VELOCITY_HERO;

	if (AEInputCheckTriggered(AEVK_SPACE))
	{
		pHero->velCurr.y = JUMP_VELOCITY;
	}
	if (AEInputCheckTriggered(AEVK_ESCAPE))
	{
		gGameStateNext = GS_QUIT;
	}
	//Handle Input
	/***********
	if right is pressed
		Set hero velocity X to MOVE_VELOCITY_HERO
	else
	if left is pressed
		Set hero velocity X to -MOVE_VELOCITY_HERO
	else
		Set hero velocity X to 0

	if space is pressed AND Hero is colliding from the bottom
		Set hero velocity Y to JUMP_VELOCITY

	if Escape is pressed
		Exit to menu
	***********/


	//Update object instances physics and behavior
	for(i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
		pInst = sGameObjInstList + i;

		// skip non-active object
		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;

		pInst->velCurr.y = GRAVITY* g_dt + pInst->velCurr.y;
		/****************
		Apply gravity
			Velocity Y = Gravity * Frame Time + Velocity Y

		If object instance is an enemy
			Apply enemy state machine
		****************/
	}

	//Update object instances positions
	for(i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
		pInst = sGameObjInstList + i;

		// skip non-active object
		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;

		/**********
		update the position using: P1 = V1*dt + P0
		Get the bouding rectangle of every active instance:
			boundingRect_min = -BOUNDING_RECT_SIZE * instance->scale + instance->pos
			boundingRect_max = BOUNDING_RECT_SIZE * instance->scale + instance->pos
		**********/
	}

	//Check for grid collision
	for(i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
		pInst = sGameObjInstList + i;

		// skip non-active object instances
		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;
		if (COLLISION_RIGHT)
		{
			SnapToCell(&pInst->posCurr.x);
			pInst->velCurr.x = 0;
		}
		if (COLLISION_LEFT)
		{
			SnapToCell(&pInst->posCurr.x);
			pInst->velCurr.x = 0;
		}
		if (COLLISION_BOTTOM)
		{
			SnapToCell(&pInst->posCurr.y);
			pInst->velCurr.y = 0;
		}
		if (COLLISION_TOP)
		{
			SnapToCell(&pInst->posCurr.y);
			pInst->velCurr.y = 0;
		}
		/*************
		Update grid collision flag

		if collision from bottom
			Snap to cell on Y axis
			Velocity Y = 0

		if collision from top
			Snap to cell on Y axis
			Velocity Y = 0
	
		if collision from left
			Snap to cell on X axis
			Velocity X = 0

		if collision from right
			Snap to cell on X axis
			Velocity X = 0
		*************/
	}


	//Checking for collision among object instances:
	//Hero against enemies
	//Hero against coins

	/**********
	for each game object instance
		Skip if it's inactive or if it's non collidable

		If it's an enemy
			If collision between the enemy instance and the hero (rectangle - rectangle)
				Decrement hero lives
				Reset the hero's position in case it has lives left, otherwise RESTART the level

		If it's a coin
			If collision between the coin instance and the hero (rectangle - rectangle)
				Remove the coin and decrement the coin counter.
				Go to level2, in case no more coins are left and you are at Level1.
				Quit the game level to the main menu, in case no more coins are left and you are at Level2.
	**********/
	
	for(i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
	}

	
	//Computing the transformation matrices of the game object instances
	for(i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
		AEMtx33 scale, rot, trans;
		pInst = sGameObjInstList + i;

		// skip non-active object
		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;

		AEMtx33Scale(&scale, pInst->scale, pInst->scale);
		AEMtx33Rot(&rot, pInst->dirCurr);
		AEMtx33Trans(&trans, pInst->posCurr.x, pInst->posCurr.y);

		
	}
	
	// Update Camera position, for Level2
		// To follow the player's position
		// To clamp the position at the level's borders, between (0,0) and and maximum camera position
			// You may use an alpha engine helper function to clamp the camera position: AEClamp()
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void GameStatePlatformDraw(void)
{
	//Drawing the tile map (the grid)
	int x, y;
	AEMtx33 cellTranslation, cellFinalTransformation;

	//Drawing the tile map

	/******REMINDER*****
	You need to concatenate MapTransform with the transformation matrix 
	of any object you want to draw. MapTransform transform the instance 
	from the normalized coordinates system of the binary map
	*******************/

	/*********
	for each array element in BinaryCollisionArray (2 loops)
		Compute the cell's translation matrix acoording to its 
		X and Y coordinates and save it in "cellTranslation"
		Concatenate MapTransform with the cell's transformation 
		and save the result in "cellFinalTransformation"
		Send the resultant matrix to the graphics manager using "AEGfxSetTransform"

		Draw the instance's shape depending on the cell's value using "AEGfxMeshDraw"
			Use the black instance in case the cell's value is TYPE_OBJECT_EMPTY
			Use the white instance in case the cell's value is TYPE_OBJECT_COLLISION
	*********/
	for(x = 0; x < BINARY_MAP_WIDTH; ++x)
		for(y = 0; y < BINARY_MAP_HEIGHT; ++y)
		{
			if (GetCellValue(x, y) == TYPE_OBJECT_EMPTY)
			{
				AEGfxSetRenderMode(AE_GFX_RM_COLOR);
				AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);//Setcolour
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetTransparency(1);//SetTransperancy

				AEMtx33 b_scale = { 0 };
				AEMtx33Scale(&b_scale, 10, 10);
				AEMtx33 b_rotate = { 0 };
				AEMtx33Rot(&b_rotate, 0);
				// Create a translation matrix that translates by
				AEMtx33Trans(&cellTranslation, x*10, y*10);
				// Concat the matrices (TRS)
				AEMtx33Concat(&cellFinalTransformation, &b_rotate, &b_scale);
				AEMtx33Concat(&cellFinalTransformation, &cellTranslation, &cellFinalTransformation);
				// Choose the transform to use
				AEGfxSetTransform(cellFinalTransformation.m);
				AEGfxMeshDraw(pBlackInstance->pObject->pMesh, AE_GFX_MDM_TRIANGLES);
			}
			if (GetCellValue(x, y) == TYPE_OBJECT_COLLISION)
			{
				AEGfxSetRenderMode(AE_GFX_RM_COLOR);
				AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);//Setcolour
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetTransparency(1);//SetTransperancy

				AEMtx33 b_scale = { 0 };
				AEMtx33Scale(&b_scale, 1, 1);
				AEMtx33 b_rotate = { 0 };
				AEMtx33Rot(&b_rotate, 0);
				// Create a translation matrix that translates by
				AEMtx33Trans(&cellTranslation, x, y);
				// Concat the matrices (TRS)
				AEMtx33Concat(&cellFinalTransformation, &b_rotate, &b_scale);
				AEMtx33Concat(&cellFinalTransformation, &cellTranslation, &cellFinalTransformation);
				// Choose the transform to use
				AEGfxSetTransform(cellFinalTransformation.m);
				AEGfxMeshDraw(pWhiteInstance->pObject->pMesh, AE_GFX_MDM_TRIANGLES);
			}
		}



	//Drawing the object instances
	/**********
	For each active and visible object instance
		Concatenate MapTransform with its transformation matrix
		Send the resultant matrix to the graphics manager using "AEGfxSetTransform"
		Draw the instance's shape using "AEGfxMeshDraw"
	**********/
	for (x = 0; x < GAME_OBJ_INST_NUM_MAX; x++)
	{
		GameObjInst* pInst = sGameObjInstList + x;

		// skip non-active object
		if (0 == (pInst->flag & FLAG_ACTIVE) || 0 == (pInst->flag & FLAG_VISIBLE))
			continue;
		if (pInst != nullptr)
		{
			//render ship
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);//Setcolour
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetTransparency(1);//SetTransperancy

			AEMtx33 b_scale = { 0 };
			AEMtx33Scale(&b_scale, pInst->scale, pInst->scale);
			AEMtx33 b_rotate = { 0 };
			AEMtx33Rot(&b_rotate, pInst->dirCurr);
			// Create a translation matrix that translates by
			AEMtx33 b_translate = { 0 };
			AEMtx33Trans(&b_translate, pInst->posCurr.x, pInst->posCurr.y);
			// Concat the matrices (TRS)
			AEMtx33 b_transform = { 0 };
			AEMtx33Concat(&b_transform, &b_rotate, &b_scale);
			AEMtx33Concat(&b_transform, &b_translate, &b_transform);
			// Choose the transform to use
			AEGfxSetTransform(b_transform.m);
			//Actually drawing the mesh 
			AEGfxMeshDraw(pInst->pObject->pMesh, AE_GFX_MDM_TRIANGLES);
		}
		
		//Don't forget to concatenate the MapTransform matrix with the transformation of each game object instance

	}

	char strBuffer[100];
	memset(strBuffer, 0, 100*sizeof(char));
	sprintf_s(strBuffer, "Lives:  %i", HeroLives);
	//AEGfxPrint(650, 30, (u32)-1, strBuffer);	
	printf("%s \n", strBuffer);
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void GameStatePlatformFree(void)
{
	// kill all object in the list
	for (unsigned int i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		gameObjInstDestroy(sGameObjInstList + i);
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void GameStatePlatformUnload(void)
{
	// free all CREATED mesh
	for (u32 i = 0; i < sGameObjNum; i++)
		AEGfxMeshFree(sGameObjList[i].pMesh);

	/*********
	Free the map data
	*********/
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
GameObjInst* gameObjInstCreate(unsigned int type, float scale, 
							   AEVec2* pPos, AEVec2* pVel, 
							   float dir, enum STATE startState)
{
	AEVec2 zero;
	AEVec2Zero(&zero);

	AE_ASSERT_PARM(type < sGameObjNum);
	
	// loop through the object instance list to find a non-used object instance
	for (unsigned int i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		// check if current instance is not used
		if (pInst->flag == 0)
		{
			// it is not used => use it to create the new instance
			pInst->pObject			 = sGameObjList + type;
			pInst->flag				 = FLAG_ACTIVE | FLAG_VISIBLE;
			pInst->scale			 = scale;
			pInst->posCurr			 = pPos ? *pPos : zero;
			pInst->velCurr			 = pVel ? *pVel : zero;
			pInst->dirCurr			 = dir;
			pInst->pUserData		 = 0;
			pInst->gridCollisionFlag = 0;
			pInst->state			 = startState;
			pInst->innerState		 = INNER_STATE_ON_ENTER;
			pInst->counter			 = 0;
			
			// return the newly created instance
			return pInst;
		}
	}

	return 0;
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void gameObjInstDestroy(GameObjInst* pInst)
{
	// if instance is destroyed before, just return
	if (pInst->flag == 0)
		return;

	// zero out the flag
	pInst->flag = 0;
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
int GetCellValue(int X, int Y)
{
	if (X >= 0 && X < BINARY_MAP_WIDTH && Y >= 0 && Y < BINARY_MAP_HEIGHT)
	{
		return BinaryCollisionArray[Y][X];
	}
	return 0;
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
int CheckInstanceBinaryMapCollision(float PosX, float PosY, float scaleX, float scaleY)
{
	//At the end of this function, "Flag" will be used to determine which sides
	//of the object instance are colliding. 2 hot spots will be placed on each side.
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

/******************************************************************************/
/*!

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

*/
/******************************************************************************/
int ImportMapDataFromFile(char *FileName)
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
	for (int i = 0; i < BINARY_MAP_HEIGHT; i++)
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

*/
/******************************************************************************/
void EnemyStateMachine(GameObjInst *pInst)
{
	/***********
	This state machine has 2 states: STATE_GOING_LEFT and STATE_GOING_RIGHT
	Each state has 3 inner states: INNER_STATE_ON_ENTER, INNER_STATE_ON_UPDATE, INNER_STATE_ON_EXIT
	Use "switch" statements to determine which state and inner state the enemy is currently in.


	STATE_GOING_LEFT
		INNER_STATE_ON_ENTER
			Set velocity X to -MOVE_VELOCITY_ENEMY
			Set inner state to "on update"

		INNER_STATE_ON_UPDATE
			If collision on left side OR bottom left cell is non collidable
				Initialize the counter to ENEMY_IDLE_TIME
				Set inner state to on exit
				Set velocity X to 0


		INNER_STATE_ON_EXIT
			Decrement counter by frame time
			if counter is less than 0 (sprite's idle time is over)
				Set state to "going right"
				Set inner state to "on enter"

	STATE_GOING_RIGHT is basically the same, with few modifications.

	***********/
	switch (STATE_GOING_LEFT)
	{
		case INNER_STATE_ON_ENTER:
		{
			pInst->posCurr.x += -MOVE_VELOCITY_ENEMY;
			break;
		}
		case INNER_STATE_ON_UPDATE:
		{
			break;
		}
		case INNER_STATE_ON_EXIT:
		{
			break;
		}
	}
	switch (STATE_GOING_RIGHT)
	{
		case INNER_STATE_ON_ENTER:
		{
			break;
		}
		case INNER_STATE_ON_UPDATE:
		{
			break;
		}
		case INNER_STATE_ON_EXIT:
		{
			break;
		}
	}
}