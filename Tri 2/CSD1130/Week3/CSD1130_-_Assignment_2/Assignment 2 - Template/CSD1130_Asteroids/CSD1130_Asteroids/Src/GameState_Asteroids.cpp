/******************************************************************************/
/*!
\file		GameState_Asteroids.cpp
\author 	DigiPen
\par    	email: digipen\@digipen.edu
\date   	January 01, 20xx
\brief		ToDo: give a brief explanation here

Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/
#include "main.h"
#include <iostream>
/******************************************************************************/
#define SMALL 20.f
#define MEDIUM 40.f
#define LARGE 100.f
#define GIGANTIC 150.f
/******************************************************************************/
/******************************************************************************/
//MY HEADERS:
#include "GameObject.h"
/******************************************************************************/
const unsigned int	GAME_OBJ_NUM_MAX		= 32;			// The total number of different objects (Shapes)
const unsigned int	GAME_OBJ_INST_NUM_MAX	= 2048;			// The total number of different game object instances


const unsigned int	SHIP_INITIAL_NUM		= 3;			// initial number of ship lives
const float			SHIP_SIZE				= 5.0f;		// ship size
const float			SHIP_ACCEL_FORWARD		= 40.0f;		// ship forward acceleration (in m/s^2)
const float			SHIP_ACCEL_BACKWARD		= 40.0f;		// ship backward acceleration (in m/s^2)
const float			SHIP_ROT_SPEED			= (2.0f * PI);	// ship rotation speed (degree/second)

const float			BULLET_SPEED			= 100.0f;		// bullet speed (m/s)

const float         BOUNDING_RECT_SIZE      = 1.0f;         // this is the normalized bounding rectangle (width and height) sizes - AABB collision data


// -----------------------------------------------------------------------------
enum TYPE
{
	// list of game object types
	TYPE_SHIP = 0, 
	TYPE_BULLET,
	TYPE_ASTEROID,

	TYPE_NUM
};

// -----------------------------------------------------------------------------
// object flag definition

const unsigned long FLAG_ACTIVE				= 0x00000001;

/******************************************************************************/
/*!
	Struct/Class Definitions
*/

/******************************************************************************/

//Game object structure
struct GameObj
{
	unsigned long		type;		// object type
	AEGfxVertexList *	pMesh;		// This will hold the triangles which will form the shape of the object
};

// ---------------------------------------------------------------------------

//Game object instance structure
struct GameObjInst
{
	GameObj *			pObject;	// pointer to the 'original' shape
	unsigned long		flag;		// bit flag or-ed together
	float				scale;		// scaling value of the object instance
	AEVec2				posCurr;	// object current position(ORIGIN)
	AEVec2				velCurr;	// object current velocity(DIRECTION)
	float				dirCurr;	// object current direction(DEGREE)
	AABB				boundingBox;// object bouding box that encapsulates the object
	AEMtx33				transform;	// object transformation matrix: Each frame, 
									// calculate the object instance's transformation matrix and save it here

	//void				(*pfUpdate)(void);
	//void				(*pfDraw)(void);
};

/******************************************************************************/
/*!
	Static Variables
*/
/******************************************************************************/

// list of original object
static GameObj				sGameObjList[GAME_OBJ_NUM_MAX];				// Each element in this array represents a unique game object (shape)
static unsigned long		sGameObjNum;								// The number of defined game objects

// list of object instances
static GameObjInst			sGameObjInstList[GAME_OBJ_INST_NUM_MAX];	// Each element in this array represents a unique game object instance (sprite)
static unsigned long		sGameObjInstNum;							// The number of used game object instances

// pointer to the ship object
static GameObjInst	*		player_Ship;										// Pointer to the "Ship" game object instance
static GameObjInst	*		player_Bullet;
static GameObjInst	*		hazard_Asteroid_Small;
static GameObjInst	*		hazard_Asteroid_Medium;
static GameObjInst	*		hazard_Asteroid_Large;
static GameObjInst	*		hazard_Asteroid_Gigantic;


// number of ship available (lives 0 = game over)
static long					sShipLives;									// The number of lives left

// the score = number of asteroid destroyed
static unsigned long		sScore;										// Current score

// ---------------------------------------------------------------------------

// functions to create/destroy a game object instance
GameObjInst *		gameObjInstCreate (unsigned long type, float scale, 
											   AEVec2 * pPos, AEVec2 * pVel, float dir);
void					gameObjInstDestroy(GameObjInst * pInst);
/******************************************************************************/
/*!
	TEXTURE
*/
/******************************************************************************/
AEGfxTexture* pTex;

/******************************************************************************/
/*!
	MY VARIABLES
*/
/******************************************************************************/
float ship_CurrentSpeed;
bool is_accelarating;

/******************************************************************************/
/*!
	"Load" function of this state
*/
/******************************************************************************/
ObjectNormalValue obj_NormalValue;
bool shootbullet;
void GameStateAsteroidsLoad(void)
{
	// zero the game object array
	memset(sGameObjList, 0, sizeof(GameObj) * GAME_OBJ_NUM_MAX);
	// No game objects (shapes) at this point
	sGameObjNum = 0;

	// zero the game object instance array
	memset(sGameObjInstList, 0, sizeof(GameObjInst) * GAME_OBJ_INST_NUM_MAX);
	// No game object instances (sprites) at this point
	sGameObjInstNum = 0;

	// The ship object instance hasn't been created yet, so this "spShip" pointer is initialized to 0
	player_Ship = nullptr;
	player_Bullet = nullptr;
	//Asteroid
	hazard_Asteroid_Small = nullptr;
	hazard_Asteroid_Medium = nullptr;
	hazard_Asteroid_Large = nullptr;
	hazard_Asteroid_Gigantic = nullptr;

	// =========================
	// Texture
	// =========================
	char strBuffer[1024];
	pTex = AEGfxTextureLoad("Asteroid.png");
	if (!pTex)
	{
		sprintf_s(strBuffer,"fail");
	}
	//AE_ASSERT_MESG(pTex, "fail to create object!!");

	// load/create the mesh data (game objects / Shapes)
	GameObj * obj_Player;
	GameObj * obj_Bullet;
	GameObj * obj_Asteroid;

	// =====================
	// create the ship shape
	// =====================

	obj_Player = sGameObjList + sGameObjNum++;
	obj_Player->type	= TYPE_SHIP;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f,  0.5f, 0xFFFF0000, 0.0f, 0.0f, 
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 0.0f,
		 0.5f,  0.0f, 0xFFFFFFFF, 0.0f, 0.0f );  

	obj_Player->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(obj_Player->pMesh, "fail to create object!!");


	// =======================
	// create the bullet shape
	// =======================

	obj_Bullet = sGameObjList + sGameObjNum++;
	obj_Bullet->type = TYPE_BULLET;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.f, -1.f, 0x00FF00FF, 0.f, 0.f,
		1.f, -1.f, 0x00FFFF00, 1.f, 0.f,
		-1.f, 1.f, 0x0000FFFF, 0.f, 1.f);
	AEGfxTriAdd(
		1.f, -1.f, 0x00FFFFFF, 1.f, 0.f,
		1.f, 1.f, 0x00FFFFFF, 1.f, 1.f,
		-1.f, 1.f, 0x00FFFFFF, 0.f, 1.0f);

	obj_Bullet->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(obj_Bullet->pMesh, "fail to create object!!");


	// =========================
	// create the asteroid shape
	// =========================
	obj_Asteroid = sGameObjList + sGameObjNum++;
	obj_Asteroid->type = TYPE_ASTEROID;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.f, -1.f, 0x00FF00FF, 0.f, 0.f,
		1.f, -1.f, 0x00FFFF00, 1.f, 0.f,
		-1.f, 1.f, 0x0000FFFF, 0.f, 1.f);
	AEGfxTriAdd(
		1.f, -1.f, 0x00FFFFFF, 1.f, 0.f,
		1.f, 1.f, 0x00FFFFFF, 1.f, 1.f,
		-1.f, 1.f, 0x00FFFFFF, 0.f, 1.0f);

	obj_Asteroid->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(obj_Asteroid->pMesh, "fail to create object!!");

	// =========================
	// Set all normal
	// =========================
	

}

/******************************************************************************/
/*!
	"Initialize" function of this state
*/
/******************************************************************************/
void GameStateAsteroidsInit(void)
{
	// create the main ship
	player_Ship = gameObjInstCreate(TYPE_SHIP, SHIP_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(player_Ship);

	// CREATE THE INITIAL ASTEROIDS INSTANCES USING THE "gameObjInstCreate" FUNCTION
	player_Bullet = gameObjInstCreate(TYPE_BULLET,SMALL,nullptr,nullptr,0.0f);
	AE_ASSERT(player_Bullet);

	hazard_Asteroid_Small = gameObjInstCreate(TYPE_ASTEROID, SMALL, nullptr, nullptr, 0.0f);
	AE_ASSERT(hazard_Asteroid_Small);
	hazard_Asteroid_Medium = gameObjInstCreate(TYPE_ASTEROID, MEDIUM, nullptr, nullptr, 0.0f);
	AE_ASSERT(hazard_Asteroid_Medium);
	hazard_Asteroid_Large = gameObjInstCreate(TYPE_ASTEROID, LARGE, nullptr, nullptr, 0.0f);
	AE_ASSERT(hazard_Asteroid_Large);
	hazard_Asteroid_Gigantic = gameObjInstCreate(TYPE_ASTEROID, GIGANTIC, nullptr, nullptr, 0.0f);
	AE_ASSERT(hazard_Asteroid_Gigantic);
	// reset the score and the number of ships
	sScore      = 0;
	sShipLives  = SHIP_INITIAL_NUM;

	//SET DIRECTION  VECTOR FOR SHIP
	ResetPostion(&player_Ship->posCurr, &player_Ship->velCurr);
	SetNormal(&player_Ship->velCurr, &obj_NormalValue, PLAYERSHIP);

	//SetPool()
}

/******************************************************************************/
/*!
	"Update" function of this state
*/
/******************************************************************************/
void GameStateAsteroidsUpdate(void)
{



	// =========================
	// update according to input
	// =========================

	// This input handling moves the ship without any velocity nor acceleration
	// It should be changed when implementing the Asteroids project
	//
	// Updating the velocity and position according to acceleration is 
	// done by using the following:
	// Pos1 = 1/2 * a*t*t + v0*t + Pos0
	//
	// In our case we need to divide the previous equation into two parts in order 
	// to have control over the velocity and that is done by:
	//
	// v1 = a*t + v0		//This is done when the UP or DOWN key is pressed 
	// Pos1 = v1*t + Pos0
	

	if (AEInputCheckCurr(AEVK_UP))
	{
		//SetNormal(&player_Ship->posCurr, &player_Ship->velCurr, &obj_NormalValue, PLAYERSHIP);
		TransformFoward(&player_Ship->posCurr,  &obj_NormalValue, PLAYERSHIP, SHIP_ACCEL_FORWARD);
		is_accelarating = true;
		//UpdateSpeed(&ship_CurrentSpeed, SHIP_ACCEL_FORWARD, is_accelarating);

		// Find the velocity according to the acceleration
		// Limit your speed over here
	}
	else
	{
		is_accelarating = false;
	}
	if (AEInputCheckCurr(AEVK_DOWN))
	{
		TransformFoward(&player_Ship->posCurr, &obj_NormalValue, PLAYERSHIP,-SHIP_ACCEL_BACKWARD);

		// Find the velocity according to the decceleration
		// Limit your speed over here
	}

	if (AEInputCheckCurr(AEVK_LEFT))
	{
		player_Ship->dirCurr += SHIP_ROT_SPEED * (float)(AEFrameRateControllerGetFrameTime());
		ObjectRotate(&player_Ship->velCurr, player_Ship->dirCurr);
		SetNormal(&player_Ship->velCurr, &obj_NormalValue, PLAYERSHIP);
	}

	if (AEInputCheckCurr(AEVK_RIGHT))
	{

		player_Ship->dirCurr -= SHIP_ROT_SPEED * (float)(AEFrameRateControllerGetFrameTime());
		ObjectRotate(&player_Ship->velCurr, player_Ship->dirCurr);
		SetNormal(&player_Ship->velCurr, &obj_NormalValue, PLAYERSHIP);
	}


	// Shoot a bullet if space is triggered (Create a new object instance)
	if (AEInputCheckTriggered(AEVK_SPACE))
	{
		SetPosition(&player_Bullet->posCurr, player_Ship->posCurr);
		obj_NormalValue.player_Bullet_x = obj_NormalValue.player_Ship_x;
		obj_NormalValue.player_Bullet_y = obj_NormalValue.player_Ship_y;

		//ObjectRotate(&player_Ship->velCurr, player_Ship->dirCurr);
		//SetNormal(&player_Ship->velCurr, &obj_NormalValue, PLAYERBULLET);
		shootbullet = true;
		// Get the bullet's direction according to the ship's direction
		// Set the velocity
		// Create an instance
	}
	if (shootbullet)
	{
		TransformFoward(&player_Bullet->posCurr, &obj_NormalValue, PLAYERBULLET, 2);
	}
	// ======================================================
	// update physics of all active game object instances
	//  -- Get the AABB bounding rectangle of every active instance:
	//		boundingRect_min = -(BOUNDING_RECT_SIZE/2.0f) * instance->scale + instance->pos
	//		boundingRect_max = +(BOUNDING_RECT_SIZE/2.0f) * instance->scale + instance->pos
	//
	//	-- Positions of the instances are updated here with the already computed velocity (above)
	// ======================================================
	
	//AEGfxMeshFree(sGameObjList[0].pMesh);



	// ====================
	// check for collision
	// ====================

	/*
	for each object instance: oi1
		if oi1 is not active
			skip

		if oi1 is an asteroid
			for each object instance oi2
				if(oi2 is not active or oi2 is an asteroid)
					skip

				if(oi2 is the ship)
					Check for collision between ship and asteroids (Rectangle - Rectangle)
					Update game behavior accordingly
					Update "Object instances array"
				else
				if(oi2 is a bullet)
					Check for collision between bullet and asteroids (Rectangle - Rectangle)
					Update game behavior accordingly
					Update "Object instances array"
	*/





	// ===================================
	// update active game object instances
	// Example:
	//		-- Wrap specific object instances around the world (Needed for the assignment)
	//		-- Removing the bullets as they go out of bounds (Needed for the assignment)
	//		-- If you have a homing missile for example, compute its new orientation 
	//			(Homing missiles are not required for the Asteroids project)
	//		-- Update a particle effect (Not required for the Asteroids project)
	// ===================================
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst * pInst = sGameObjInstList + i;

		// skip non-active object
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;
		
		// check if the object is a ship
		if (pInst->pObject->type == TYPE_SHIP)
		{
			// warp the ship from one end of the screen to the other
			pInst->posCurr.x = AEWrap(pInst->posCurr.x, AEGfxGetWinMinX() - SHIP_SIZE, 
														AEGfxGetWinMaxX() + SHIP_SIZE);
			pInst->posCurr.y = AEWrap(pInst->posCurr.y, AEGfxGetWinMinY() - SHIP_SIZE, 
														AEGfxGetWinMaxY() + SHIP_SIZE);
		}

		// Wrap asteroids here
		

		// Remove bullets that go out of bounds
		
	}


	

	// =====================================
	// calculate the matrix for all objects
	// =====================================

	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst * pInst = sGameObjInstList + i;
		AEMtx33		 trans, rot, scale;

		UNREFERENCED_PARAMETER(trans);
		UNREFERENCED_PARAMETER(rot);
		UNREFERENCED_PARAMETER(scale);

		// skip non-active object
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;


		// Compute the scaling matrix
		// Compute the rotation matrix 
		// Compute the translation matrix
		// Concatenate the 3 matrix in the correct order in the object instance's "transform" matrix
	}
}

/******************************************************************************/
/*!
	
*/
/******************************************************************************/
void GameStateAsteroidsDraw(void)
{
	char strBuffer[1024];
	
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);

	// draw all object instances in the list
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst * pInst = sGameObjInstList + i;

		// skip non-active object
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;
		
		// Set the current object instance's transform matrix using "AEGfxSetTransform"
		// Draw the shape used by the current object instance using "AEGfxMeshDraw"
	}

	AEGfxSetBackgroundColor(255.0f, 0.0f, 0.0f);

	//render ship
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);//Setcolour
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);//SetTransperancy
	AEGfxTextureSet(pTex, 0.f, 0.f);

	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, 20.f, 20.f);
	// Create a rotation matrix that rotates by 45 degrees
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, player_Ship->dirCurr);
	// Create a translation matrix that translates by
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, player_Ship->posCurr.x, player_Ship->posCurr.y);
	// Concat the matrices (TRS)
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	// Choose the transform to use
	AEGfxSetTransform(transform.m);
	//Actually drawing the mesh 
	AEGfxMeshDraw(player_Ship->pObject->pMesh, AE_GFX_MDM_TRIANGLES);



	//render ship
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);//Setcolour
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);//SetTransperancy
	AEGfxTextureSet(pTex, 0.f, 0.f);

	AEMtx33 b_scale = { 0 };
	AEMtx33Scale(&b_scale, 5.f, 5.f);
	AEMtx33 b_rotate = { 0 };
	AEMtx33Rot(&b_rotate, player_Bullet ->dirCurr);
	// Create a translation matrix that translates by
	AEMtx33 b_translate = { 0 };
	AEMtx33Trans(&b_translate, player_Bullet->posCurr.x, player_Bullet->posCurr.y);
	// Concat the matrices (TRS)
	AEMtx33 b_transform = { 0 };
	AEMtx33Concat(&b_transform, &b_rotate, &b_scale);
	AEMtx33Concat(&b_transform, &b_translate, &b_transform);
	// Choose the transform to use
	AEGfxSetTransform(b_transform.m);
	//Actually drawing the mesh 
	AEGfxMeshDraw(player_Bullet->pObject->pMesh, AE_GFX_MDM_TRIANGLES);


	//You can replace this condition/variable by your own data.
	//The idea is to display any of these variables/strings whenever a change in their value happens
	static bool onValueChange = true;
	if(onValueChange)
	{
		sprintf_s(strBuffer, "Score: %d", sScore);
		//AEGfxPrint(10, 10, (u32)-1, strBuffer);
		printf("%s \n", strBuffer);

		sprintf_s(strBuffer, "Ship Left: %d", sShipLives >= 0 ? sShipLives : 0);
		//AEGfxPrint(600, 10, (u32)-1, strBuffer);
		printf("%s \n", strBuffer);

		// display the game over message
		if (sShipLives < 0)
		{
			//AEGfxPrint(280, 260, 0xFFFFFFFF, "       GAME OVER       ");
			printf("       GAME OVER       \n");
		}

		onValueChange = false;
	}
}

/******************************************************************************/
/*!
	
*/
/******************************************************************************/
void GameStateAsteroidsFree(void)
{
	// kill all object instances in the array using "gameObjInstDestroy"
	
}

/******************************************************************************/
/*!
	
*/
/******************************************************************************/
void GameStateAsteroidsUnload(void)
{
	// free all mesh data (shapes) of each object using "AEGfxTriFree"
	
}

/******************************************************************************/
/*!
	
*/
/******************************************************************************/
GameObjInst * gameObjInstCreate(unsigned long type, 
							   float scale, 
							   AEVec2 * pPos, 
							   AEVec2 * pVel, 
							   float dir)
{
	AEVec2 zero;
	AEVec2Zero(&zero);

	AE_ASSERT_PARM(type < sGameObjNum);
	
	// loop through the object instance list to find a non-used object instance
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst * pInst = sGameObjInstList + i;

		// check if current instance is not used
		if (pInst->flag == 0)
		{
			// it is not used => use it to create the new instance
			pInst->pObject	= sGameObjList + type;
			pInst->flag		= FLAG_ACTIVE;
			pInst->scale	= scale;
			pInst->posCurr	= pPos ? *pPos : zero;
			pInst->velCurr	= pVel ? *pVel : zero;
			pInst->dirCurr	= dir;
			
			// return the newly created instance
			return pInst;
		}
	}

	// cannot find empty slot => return 0
	return 0;
}

/******************************************************************************/
/*!
	
*/
/******************************************************************************/
void gameObjInstDestroy(GameObjInst * pInst)
{
	// if instance is destroyed before, just return
	if (pInst->flag == 0)
		return;

	// zero out the flag
	pInst->flag = 0;
}