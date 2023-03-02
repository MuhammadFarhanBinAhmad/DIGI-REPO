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
#include "Collision.h"
/******************************************************************************/
/*!
	Defines
*/
/******************************************************************************/
#define POOL 25
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
const unsigned int	COLLISION_TOP			= 0x00000004;	//0100|
const unsigned int	COLLISION_BOTTOM		= 0x00000008;	//1000


enum TYPE_OBJECT
{
	TYPE_OBJECT_EMPTY,			//0
	TYPE_OBJECT_COLLISION,		//1
	TYPE_OBJECT_HERO,			//2
	TYPE_OBJECT_ENEMY1,			//3
	TYPE_OBJECT_COIN,			//4
	TYPE_OBJECT_PARTICLE
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
struct Particle
{
	AEVec2	posCurr;
	AEVec2	velCurr;
	AEMtx33	transform;
	AEGfxVertexList* pMesh;

	float speed;
	float lifetime;
	float scale;

	bool is_Alive;
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
int				CurrentScene;
const float				Camera_View_Size = 20.f;
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
const float				BOUNDING_RECT_SIZE = .5f;         // this is the normalized bounding rectangle (width and height) sizes - AABB collision data

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

float Current_EmmisionTime = 0;;
float EmmisionTime = 0.1f;
Particle Master_Particle;
Particle part[POOL];


bool can_WallJump;
bool has_WallJump;
float time_WallJump = 1.f;
float currenttime_WallJump = 0.f;

void CreateMasterParticle(float lt, float sp, float scale_);
void CreateParticle(Particle& par);
void ParticleUpdate();
void ResetParticle(Particle& par);
/******************************************************************************/
/*!

*/
/******************************************************************************/
void CreateMasterParticle(float lt,float sp,float scale_)
{
	Master_Particle.lifetime = lt;
	Master_Particle.speed = sp;
	Master_Particle.scale = scale_;
	//Creating the Particle object


	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFF00FF00, 0.0f, 0.0f,
		-0.5f, 0.5f, 0xFF00FF, 0.0f, 0.0f);

	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFF00FF00, 0.0f, 0.0f,
		0.5f, 0.5f, 0xFF0000FF, 0.0f, 0.0f);

	Master_Particle.pMesh = AEGfxMeshEnd();
	Master_Particle.posCurr.x = 0;
	Master_Particle.posCurr.y = 0;
	Master_Particle.velCurr.x = 0;
	Master_Particle.velCurr.y = 0;
	Master_Particle.transform = MapTransform;
}
void CreateParticle(Particle& par)
{
	par.is_Alive = false;
	par.lifetime = Master_Particle.lifetime;
	par.speed = Master_Particle.speed / 100.f;
	par.transform = Master_Particle.transform;
	par.posCurr = Master_Particle.posCurr;
	par.velCurr = Master_Particle.velCurr;
	par.scale = Master_Particle.scale;

}
void ParticleUpdate()
{
	for (int i = 0; i < POOL; i++)
	{
		if (!part[i].is_Alive)
		{
			continue;
		}
		else
		{
			part[i].velCurr.y += (part[i].speed);
			part[i].posCurr.y = part[i].velCurr.y + pHero->posCurr.y + 0.75f;
			part[i].posCurr.x = pHero->posCurr.x;
			part[i].scale -= g_dt;
			
			part[i].lifetime -= g_dt;
			if (part[i].lifetime <= 0)
			{
				ResetParticle(part[i]);
			}
		}
	}
}
void ResetParticle(Particle& par)
{
	par.is_Alive = false;
	par.lifetime = Master_Particle.lifetime;
	par.speed = Master_Particle.speed / 100.f;
	par.transform = Master_Particle.transform;
	par.posCurr = Master_Particle.posCurr;
	par.velCurr = Master_Particle.velCurr;
	par.scale = Master_Particle.scale;

}
void ParticleDraw()
{
	AEMtx33 scale, trans, matrix;

	for (int i = 0; i < POOL; i++)
	{
		if (!part[i].is_Alive)
			continue;

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);//Setcolour
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(part[i].lifetime);//SetTransperancy

		AEMtx33Scale(&scale, part[i].scale, part[i].scale);
		AEMtx33Trans(&trans, part[i].posCurr.x, part[i].posCurr.y);
		AEMtx33Concat(&matrix, &trans, &scale);
		AEMtx33Concat(&matrix, &MapTransform, &matrix);
		AEGfxSetTransform(matrix.m);


		AEGfxMeshDraw(Master_Particle.pMesh, AE_GFX_MDM_TRIANGLES);

	}
}
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
	switch (gGameStateCurr)
	{
		case GS_PLATFORM_LVL_1:
		{
			if (!ImportMapDataFromFile("..//Resources//Levels//Exported.txt"))
				gGameStateNext = GS_QUIT;

			break;
		}
		case GS_PLATFORM_LVL_2:
		{
			if (!ImportMapDataFromFile("..//Resources//Levels//Exported2.txt"))
				gGameStateNext = GS_QUIT;

			break;
		}

	}


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
	AEMtx33Scale(&scale, (float) (AEGetWindowWidth() / Camera_View_Size), (float)(AEGetWindowHeight() / Camera_View_Size));
	AEMtx33Trans(&trans, -(Camera_View_Size/2.f), -(Camera_View_Size / 2.f));
	AEMtx33Concat(&MapTransform, &scale, &trans);
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

	//Pass base data to all particle

	//Setting the inital number of hero lives
	HeroLives = HERO_LIVES;


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
			switch (MapData[y][x])
			{
				case TYPE_OBJECT_HERO:
				{
					AEVec2 pos = { (f32)x+0.5f,(f32)y+0.5f};
					pHero = gameObjInstCreate(TYPE_OBJECT_HERO, 1.0f, &pos, 0, 0.0f, STATE_NONE);
					Hero_Initial_X = x;
					Hero_Initial_Y = y;
 					break;
				}
				case TYPE_OBJECT_ENEMY1:
				{
					AEVec2 pos = { (f32)x+0.5f,(f32)y+0.5f};
					gameObjInstCreate(TYPE_OBJECT_ENEMY1, 1.0f, &pos, 0, 0.0f, STATE_GOING_LEFT);
					break;
				}
				case TYPE_OBJECT_COIN:
				{
					AEVec2 pos = { (f32)x+0.5f,(f32)y+0.5f};
					gameObjInstCreate(TYPE_OBJECT_COIN, 1.0f, &pos, 0, 0.0f, STATE_NONE);
					TotalCoins++;
					break;
				}
			}
		}

	//PARTICLE
	CreateMasterParticle(1.f, 5.f, 1.f);
	for (int i = 0; i < POOL; i++)
	{
		CreateParticle(part[i]);
	}
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void GameStatePlatformUpdate(void)
{
	int i;
	GameObjInst *pInst ;

	if (AEInputCheckCurr(AEVK_RIGHT))
	{
		pHero->velCurr.x = MOVE_VELOCITY_HERO;
	}
	else if (AEInputCheckCurr(AEVK_LEFT))
	{
		pHero->velCurr.x = -MOVE_VELOCITY_HERO;
	}
	else
		pHero->velCurr.x = 0;

	if (AEInputCheckTriggered(AEVK_SPACE) && (pHero->gridCollisionFlag & COLLISION_BOTTOM) ||
		AEInputCheckTriggered(AEVK_SPACE) && (pHero->gridCollisionFlag & COLLISION_RIGHT) && can_WallJump && !has_WallJump||
		AEInputCheckTriggered(AEVK_SPACE) && (pHero->gridCollisionFlag & COLLISION_LEFT) && can_WallJump && !has_WallJump)
	{
		pHero->velCurr.y = JUMP_VELOCITY;
		if (can_WallJump)
		{
			has_WallJump = true;
			currenttime_WallJump = 0;
		}
	}
	if (AEInputCheckTriggered(AEVK_ESCAPE))
	{
		gGameStateNext = GS_MENU;
	}
	if (pHero->gridCollisionFlag & COLLISION_RIGHT || pHero->gridCollisionFlag & COLLISION_LEFT )
	{
		if (!can_WallJump && !has_WallJump)
		{
			can_WallJump = true;
			currenttime_WallJump = time_WallJump;
		}
	}

	if (currenttime_WallJump > 0.1f)
	{
		currenttime_WallJump -= g_dt;
	}
	//else
	{
		pHero->velCurr.y = (GRAVITY * g_dt) + pHero->velCurr.y;
	}
	if (currenttime_WallJump <= 0)
	{
		can_WallJump = false;
	}
	if ((pHero->gridCollisionFlag & COLLISION_BOTTOM) && has_WallJump)
	{
		has_WallJump = false;
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


	//pHero->velCurr.y = (GRAVITY * g_dt) + pHero->velCurr.y;

	//Update object instances physics and behavior
	for(i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
		pInst = sGameObjInstList + i;

		// skip non-active object
		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;

		if (pInst->pObject->type == TYPE_OBJECT_ENEMY1)
		{
			EnemyStateMachine(pInst);
		}
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

		pInst->posCurr.x += pInst->velCurr.x * g_dt;
		pInst->posCurr.y += pInst->velCurr.y * g_dt;

		pInst->boundingBox.min.x = -BOUNDING_RECT_SIZE * pInst->scale + pInst->posCurr.x;
		pInst->boundingBox.min.y = -BOUNDING_RECT_SIZE * pInst->scale + pInst->posCurr.y;
		pInst->boundingBox.max.x = BOUNDING_RECT_SIZE * pInst->scale + pInst->posCurr.x;
		pInst->boundingBox.max.y = BOUNDING_RECT_SIZE * pInst->scale + pInst->posCurr.y;

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

		pInst->gridCollisionFlag = CheckInstanceBinaryMapCollision(pInst->posCurr.x, pInst->posCurr.y, pInst->scale,pInst->scale);

		// skip non-active object instances
		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;
		//& - BITWISE AND comparison
		if (pInst->gridCollisionFlag & COLLISION_RIGHT)
		{
			SnapToCell(&pInst->posCurr.x);
			pInst->velCurr.x = 0;
		}
		if (pInst->gridCollisionFlag & COLLISION_LEFT)
		{
			SnapToCell(&pInst->posCurr.x);
			pInst->velCurr.x = 0;

		}
		if (pInst->gridCollisionFlag & COLLISION_BOTTOM)
		{
			SnapToCell(&pInst->posCurr.y);
			pInst->velCurr.y = 0;
		}
		if (pInst->gridCollisionFlag & COLLISION_TOP)
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
	if (AEInputCheckTriggered(AEVK_R))
	{
		gGameStateNext = GS_RESTART;
	}
	for(i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
		pInst = sGameObjInstList + i;

		// skip non-active object
		if (!(pInst->flag & FLAG_ACTIVE) || pInst->flag & FLAG_NON_COLLIDABLE)
			continue;

		if (pInst->pObject->type == TYPE_OBJECT_ENEMY1)
		{
			if (CollisionIntersection_RectRect(pHero->boundingBox, pHero->velCurr,
				pInst->boundingBox, pInst->velCurr))
			{
				if (HeroLives > 0)
				{
					HeroLives--;
					AEVec2Set(&pHero->posCurr, (f32)Hero_Initial_X, (f32)Hero_Initial_Y);
				}
				else
				{

					gGameStateNext = GS_RESTART;
				}
			}
		}
		if (pInst->pObject->type == TYPE_OBJECT_COIN)
		{
			if (CollisionIntersection_RectRect(pHero->boundingBox, pHero->velCurr,
				pInst->boundingBox, pInst->velCurr))
			{
				gameObjInstDestroy(pInst);
				TotalCoins--;
			}
			if (TotalCoins == 0)
			{
				switch (gGameStateCurr)
				{
					case GS_PLATFORM_LVL_1:
						gGameStateNext = GS_PLATFORM_LVL_2;
						break;
					case GS_PLATFORM_LVL_2:
						gGameStateNext = GS_MENU;
						break;
				}
			}
		}
	}

	
	//Computing the transformation matrices of the game object instances
	for (unsigned long j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
	{
		GameObjInst* pInst = sGameObjInstList + j;
		AEMtx33		 trans, rot, scale;

		// skip non-active object
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;


		scale = { 0 };
		AEMtx33Scale(&scale, pInst->scale, pInst->scale);
		// Create a rotation matrix that rotates by 45 degrees
		rot = { 0 };
		AEMtx33Rot(&rot, pInst->dirCurr);
		// Create a translation matrix that translates by
		trans = { 0 };
		AEMtx33Trans(&trans, pInst->posCurr.x, pInst->posCurr.y);
		// Concat the matrices (TRS)
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&pInst->transform, &rot, &scale);
		AEMtx33Concat(&pInst->transform, &trans, &pInst->transform);
	}
	if (gGameStateCurr == GS_PLATFORM_LVL_2)
	{
		AEVec2 cam_Pos{0,0};

		cam_Pos.x = AEClamp(pHero->posCurr.x,  Camera_View_Size / 2.f, BINARY_MAP_WIDTH - Camera_View_Size /2.f );
		cam_Pos.y = AEClamp(pHero->posCurr.y, Camera_View_Size/ 2.f, BINARY_MAP_HEIGHT - Camera_View_Size /2.f);
		AEMtx33MultVec(&cam_Pos, &MapTransform, &cam_Pos);

		AEGfxSetCamPosition(cam_Pos.x, cam_Pos.y);
	}
	// Update Camera position, for Level2
		// To follow the player's position
		// To clamp the position at the level's borders, between (0,0) and and maximum camera position
			// You may use an alpha engine helper function to clamp the camera position: AEClamp()
	if (Current_EmmisionTime > 0)
	{
		Current_EmmisionTime -= g_dt;
	}
	else
	{
		for (int j = 0; j < POOL; j++)
		{
			if (!part[j].is_Alive)
			{
				part[j].is_Alive = true;
				Current_EmmisionTime = EmmisionTime;
				break;
			}
		}
	}
	ParticleUpdate();

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
	for(x = 0; x < BINARY_MAP_WIDTH; x++)
		for(y = 0; y < BINARY_MAP_HEIGHT; y++)
		{
			if (GetCellValue(x, y) == TYPE_OBJECT_EMPTY)
			{
				AEGfxSetRenderMode(AE_GFX_RM_COLOR);
				AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);//Setcolour
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetTransparency(1);//SetTransperancy

				// Create a translation matrix that translates by
				AEMtx33Trans(&cellTranslation, x+0.5f, y+0.5f);
				// Concat the matrices (TRS)
				AEMtx33Concat(&cellFinalTransformation, &MapTransform, &cellTranslation);
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

				// Create a translation matrix that translates by
				AEMtx33Trans(&cellTranslation, x+0.5f, y+0.5f);
				// Concat the matrices (TRS)
				AEMtx33Concat(&cellFinalTransformation, &MapTransform, &cellTranslation);
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
			AEGfxSetPosition(0,0);
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);//Setcolour
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
			AEGfxSetTransparency(1);//SetTransperancy

			// Create a translation matrix that translates by
			// Concat the matrices (TRS)
			AEMtx33Concat(&pInst->transform, &MapTransform, &pInst->transform);
			// Choose the transform to use
			AEGfxSetTransform(pInst->transform.m);
			AEGfxMeshDraw(pInst->pObject->pMesh, AE_GFX_MDM_TRIANGLES);
			
		//Don't forget to concatenate the MapTransform matrix with the transformation of each game object instance

	}
	ParticleDraw();

	char strBuffer[100];
	memset(strBuffer, 0, 100*sizeof(char));
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	sprintf_s(strBuffer, "Lives:  %i", HeroLives);
	AEGfxPrint(font, strBuffer, 0.6f, 0.9f, 1.0f, 0.0f, 0.0f, 1.0f);
	sprintf_s(strBuffer, "Coins:  %i", TotalCoins);
	AEGfxPrint(font, strBuffer, -.8f, 0.9f, 1.0f, 0.0f, 0.0f, 1.0f);
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
	// kill all object in the list
	for (u32 i = 0; i < sGameObjNum; i++)
		AEGfxMeshFree(sGameObjList[i].pMesh);


	free(sGameObjList);
	free(sGameObjInstList);

	AEGfxMeshFree(Master_Particle.pMesh);

	FreeMapData();
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
void EnemyStateMachine(GameObjInst* pInst)
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
	switch (pInst->state)
	{
		case STATE_GOING_LEFT:
		{
			switch (pInst->innerState)
			{
				case INNER_STATE_ON_ENTER:
				{
					pInst->velCurr.x = -MOVE_VELOCITY_ENEMY;
					pInst->innerState = INNER_STATE_ON_UPDATE;
					break;
				}
				case INNER_STATE_ON_UPDATE:
				{
					if (GetCellValue((int)(pInst->posCurr.x - 0.5f), (int)(pInst->posCurr.y - 1)) == TYPE_OBJECT_EMPTY || pInst->gridCollisionFlag & COLLISION_LEFT)
					{
						pInst->innerState = INNER_STATE_ON_EXIT;
						pInst->velCurr.x = 0;
						pInst->counter = ENEMY_IDLE_TIME;
					}
					break;
				}
				case INNER_STATE_ON_EXIT:
				{
					pInst->counter -= g_dt;
					if (pInst->counter <= 0)
					{
						pInst->state = STATE_GOING_RIGHT;
						pInst->innerState = INNER_STATE_ON_ENTER;
					}
					break;
				}
			}
		}
		break;
		case STATE_GOING_RIGHT:
		{
			switch (pInst->innerState)
			{
			case INNER_STATE_ON_ENTER:
				{
					pInst->velCurr.x = MOVE_VELOCITY_ENEMY;
					pInst->innerState = INNER_STATE_ON_UPDATE;
					break;
				}
				case INNER_STATE_ON_UPDATE:
				{
					if (GetCellValue((int)(pInst->posCurr.x + 0.5f), (int)(pInst->posCurr.y - 1)) == TYPE_OBJECT_EMPTY || pInst->gridCollisionFlag & COLLISION_RIGHT)
					{
						pInst->innerState = INNER_STATE_ON_EXIT;
						pInst->velCurr.x = 0;
						pInst->counter = ENEMY_IDLE_TIME;
					}
					break;
				}
				case INNER_STATE_ON_EXIT:
				{
					pInst->counter -= g_dt;
					if (pInst->counter <= 0)
					{
						pInst->state = STATE_GOING_LEFT;
						pInst->innerState = INNER_STATE_ON_ENTER;
					}
					break;
				}
			}
		}
		break;
	}
}