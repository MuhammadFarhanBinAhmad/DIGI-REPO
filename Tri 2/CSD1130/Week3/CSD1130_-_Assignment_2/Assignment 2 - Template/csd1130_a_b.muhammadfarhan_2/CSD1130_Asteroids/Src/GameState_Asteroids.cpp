/******************************************************************************/
/*!
\file		GameObject.cpp
\author 	MuhammadFarhanBinAhmad(2200544)
\par    	email: b.muhammadfarhan@digipen.edu
\date   	February 02, 2023
\brief		Hold all 6 state in the game
			GameStateAsteroidsLoad- Load all needed assets and data
			GameStateAsteroidsInit- Initilize all needed variables and object being use in the game
			GameStateAsteroidsUpdate- Game Update Function. Handles all the physics,input etc.
			GameStateAsteroidsDraw- Game render function. Handles all the rendering
			GameStateAsteroidsFree- Remove all remaining objects instances and freeing their allocated memory.
			GameStateAsteroidsUnload- Unload all memory that was loaded in the game

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
#include "main.h"
#include <iostream>
#include <time.h>
/******************************************************************************/
#define SMALL 5.f

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
static GameObjInst	*		hazard_Asteroid;


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
AEGfxTexture* Asteroid_Tex;
AEGfxTexture* Bullet_Tex;
/******************************************************************************/
/*!
	MY VARIABLES
	*/
float ship_CurrentAcceleration;
float ship_CurrentMagnitude;
bool is_accelarating;

float rate_Spawn = 2;
float rate_spawn_time = 2;
int asteroid_total = 10;
int asteroid_current = 0;
float ship_MaxSpeed = 20;


double finaltime = 0;
//SWITCH WEAPON
int weapon_current=0;
int Combo=0;
bool is_invicible;
float invicibility_Time;
bool game_End;
float fire_Rate = 0.25f;
float next_time_to_fire = 0;
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
	hazard_Asteroid = nullptr;

	// =========================
	// Texture
	// =========================
	char strBuffer[1024];

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
		-0.5f, -0.5f, 0xFFFF0000, 1.0f, 0.0f,
		 0.5f,  0.0f, 0xFFFFFFFF, 0.0f, 1.0f );  

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
		1.f, -1.f, 0x00FFFFFF, 1.f, 0.f,
		-1.f, 1.f, 0xFF00FFFF, 0.f, 1.f);
	AEGfxTriAdd(
		1.f, -1.f, 0x00FF00FF, 1.f, 0.f,
		1.f, 1.f, 0x0000FFFF, 1.f, 1.f,
		-1.f, 1.f, 0x00FF00FF, 0.f, 1.0f);

	obj_Asteroid->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(obj_Asteroid->pMesh, "fail to create object!!");


	Asteroid_Tex = AEGfxTextureLoad("..//Resources//Asteroid.png");
	Bullet_Tex = AEGfxTextureLoad("..//Resources//Bullet.png");
}

/******************************************************************************/
/*!
	"Initialize" function of this state
*/
/******************************************************************************/
void GameStateAsteroidsInit(void)
{

	// =========================
	// INITIALIZE GAME OBJECT
	// =========================
	
	//Create Player ship and place it in sGameObjInstList
	player_Ship = gameObjInstCreate(TYPE_SHIP, SHIP_SIZE * 3, nullptr, nullptr, 0.0f);
	AE_ASSERT(player_Ship);

	//Create Player bullet and place it in sGameObjInstList
	player_Bullet = gameObjInstCreate(TYPE_BULLET,1,nullptr,nullptr,0.0f);
	AE_ASSERT(player_Bullet);
	player_Bullet->flag = 0;

	//Create Asteroid and place it in sGameObjInstList
	hazard_Asteroid = gameObjInstCreate(TYPE_ASTEROID, SMALL, nullptr, nullptr, 0.0f);
	AE_ASSERT(hazard_Asteroid);
	hazard_Asteroid->flag = 0;
	// reset the score and the number of ships
	sScore      = 0;
	sShipLives  = SHIP_INITIAL_NUM;

}

/******************************************************************************/
/*!
	"Update" function of this state
*/
/******************************************************************************/
void GameStateAsteroidsUpdate(void)
{

	if (sShipLives > 0 && sScore < 5000)
	{
		if (ship_CurrentMagnitude > ship_MaxSpeed)
		{
			//ship_CurrentMagnitude = ship_MaxSpeed;
		}
		if (AEInputCheckCurr(AEVK_UP))
		{
			AEVec2 dirvec = { 0,0 };//Direction vector of ship
			AEVec2Set(&dirvec, cosf(player_Ship->dirCurr), sinf(player_Ship->dirCurr));//Set movement direction of ship
			AEVec2Scale(&dirvec, &dirvec, SHIP_ACCEL_FORWARD);//Ship acceleration
			//AEVec2Scale(&dirvec, &dirvec, g_dt);
			AEVec2Add(&player_Ship->velCurr, &player_Ship->velCurr, &dirvec);//Move player foward
			//AEVec2Scale(&player_Ship->velCurr, &player_Ship->velCurr, 0.99f);//Ships "friction"
		}
		if (AEInputCheckCurr(AEVK_DOWN))
		{
			AEVec2 dirvec = { 0,0 };
			AEVec2Set(&dirvec, -cosf(player_Ship->dirCurr), -sinf(player_Ship->dirCurr));//Set movement direction of ship
			AEVec2Scale(&dirvec, &dirvec, SHIP_ACCEL_BACKWARD);//Ship acceleration
			AEVec2Scale(&dirvec, &dirvec, g_dt);
			AEVec2Add(&player_Ship->velCurr, &player_Ship->velCurr, &dirvec);//Move player foward
			AEVec2Scale(&player_Ship->velCurr, &player_Ship->velCurr, 0.99f);//Ships "friction"
		}

		if (AEInputCheckCurr(AEVK_LEFT))
		{
			//Set rotation of ship
			player_Ship->dirCurr += SHIP_ROT_SPEED * g_dt;
			player_Ship->dirCurr = AEWrap(player_Ship->dirCurr, -PI, PI);
		}
		else if (AEInputCheckCurr(AEVK_RIGHT))
		{
			//Set rotation of ship
			player_Ship->dirCurr -= SHIP_ROT_SPEED * g_dt;
			player_Ship->dirCurr = AEWrap(player_Ship->dirCurr, -PI, PI);
		}
		//INVICIBILITY
		if (AEInputCheckCurr(AEVK_I))
		{
			if (sScore >= 500)
			{
				is_invicible = true;
				invicibility_Time = 5.f;
				sScore -= 500;
				printf("SHIELD ACTIVATED\n");
				printf("Current Score: %d\n", sScore);
			}
		}
		if (invicibility_Time > 0)
		{
			invicibility_Time -= (float)AEFrameRateControllerGetFrameTime();
		}
		if (invicibility_Time <= 0 && is_invicible)
		{
			is_invicible = false;
			printf("SHIELD DEACTIVATED\n");
		}
		//SWITCH WEAPON STATE
		if (weapon_current == 0)
		{
			//Semi auto
			if (AEInputCheckTriggered(AEVK_SPACE))
			{
				AEVec2 bullet_DirVec = { 0,0 };

				AEVec2Set(&bullet_DirVec, cosf(player_Ship->dirCurr), sinf(player_Ship->dirCurr));//Bullet direction vector.Face depending on the direction of the ship

				AEVec2Scale(&bullet_DirVec, &bullet_DirVec, player_Bullet->scale);

				gameObjInstCreate(TYPE_BULLET, 10, &player_Ship->posCurr, &bullet_DirVec, player_Ship->dirCurr);
			}
		}
		if (weapon_current == 1)
		{
			//Full auto
			if (AEInputCheckCurr(AEVK_SPACE) && next_time_to_fire >= fire_Rate)
			{
				next_time_to_fire = 0;
				AEVec2 bullet_DirVec = { 0,0 };

				AEVec2Set(&bullet_DirVec, cosf(player_Ship->dirCurr), sinf(player_Ship->dirCurr));

				AEVec2Scale(&bullet_DirVec, &bullet_DirVec, player_Bullet->scale);

				gameObjInstCreate(TYPE_BULLET, player_Bullet->scale, &player_Ship->posCurr, &bullet_DirVec, player_Ship->dirCurr);
			}
			if (next_time_to_fire < fire_Rate)
			{
				next_time_to_fire += (float)(AEFrameRateControllerGetFrameTime());
			}
		}

		//SHOULD DECRESE SPAWN RATE TIME AND INCREASE AMOUNT OF ASTEROID SPAWN AS CLOSER THE PLAYER GET TO 5000 POINTS
		if (rate_Spawn > 0)
		{
			rate_Spawn -= (float)(AEFrameRateControllerGetFrameTime());
		}
		if (asteroid_current < asteroid_total && rate_Spawn <= 0)
		{
			AEVec2 pos;
			//Get random y pos
			int side  = 10 * AERandFloat();
			if (side < 5)
			{
				pos.y = AEGfxGetWinMaxY() * AERandFloat();
				pos.x = AEGfxGetWinMinX();
			}
			else
			{
				pos.y = AEGfxGetWinMinY();
				pos.x = AEGfxGetWinMinX() * AERandFloat();
			}

			//Get random size fpr asteroid
			float asteroid_Scale = 10 + 30 * AERandFloat();
			AEVec2 bullet_DirVec = { 0,0 };
			
			gameObjInstCreate(TYPE_ASTEROID, asteroid_Scale, &pos, &hazard_Asteroid->velCurr, player_Ship->dirCurr);
			asteroid_current++;
			rate_Spawn = rate_spawn_time;
		}
		//Different spawn rate for asteroid depending on current score player has
		if (sScore > 2500 && sScore < 3500)
		{
			rate_spawn_time = 1.5f;
			asteroid_total = 20;
		}
		if (sScore > 3500)
		{
			rate_spawn_time = 1;
			asteroid_total = 30;
		}
		//If player hit 20 asteroid without getting hit, he will get an extra life
		if (Combo == 10)
		{
			Combo = 0;
			sShipLives++;

			//Console output
			printf("BONUS LIFE!!!\n");
			printf("Current Life: %d\n", sShipLives);
			printf("Current Combo: x%d\n", Combo);
		}


		for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		{
			GameObjInst* pInst = sGameObjInstList + i;
			if (pInst != nullptr)
			{
				if (pInst->flag == 1)
				{
					//Handle bullet speed
					if (pInst->pObject->type == TYPE_BULLET)
					{
						pInst->posCurr.x += (pInst->velCurr.x * g_dt * BULLET_SPEED);
						pInst->posCurr.y += (pInst->velCurr.y * g_dt * BULLET_SPEED);
					}
					//Determine speed of asteroid depending on current difficulty
					if (pInst->pObject->type == TYPE_ASTEROID)
					{
						if (sScore > 2500 && sScore < 3500)
						{
							pInst->velCurr.x = (g_dt + BULLET_SPEED * 1.25f);
							pInst->velCurr.y = (g_dt + BULLET_SPEED * 1.25f);
						}
						else if (sScore > 3500)
						{
							pInst->velCurr.x = (g_dt + BULLET_SPEED * 2.f);
							pInst->velCurr.y = (g_dt + BULLET_SPEED * 2.f);
						}
						else
						{
							pInst->velCurr.x = (g_dt + BULLET_SPEED);
							pInst->velCurr.y = (g_dt + BULLET_SPEED);
						}
					}
					//Handle ship speed
					pInst->posCurr.x += (pInst->velCurr.x * g_dt);
					pInst->posCurr.y += (pInst->velCurr.y * g_dt);
				}

			}
		}
		//SETTING BOUNINGDBOX
		for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		{
			GameObjInst* oi1 = sGameObjInstList + i;
			//Skip is object not active
			if (oi1->flag == 0)
			{
				continue;
			}
			AEVec2 min, max;
			float boundingRect_min_x = -(BOUNDING_RECT_SIZE / 2.0f) * sGameObjInstList[i].scale + sGameObjInstList[i].posCurr.x;
			float boundingRect_max_x = +(BOUNDING_RECT_SIZE / 2.0f) * sGameObjInstList[i].scale + sGameObjInstList[i].posCurr.x;
			float boundingRect_min_y = -(BOUNDING_RECT_SIZE / 2.0f) * sGameObjInstList[i].scale + sGameObjInstList[i].posCurr.y;
			float boundingRect_max_y = +(BOUNDING_RECT_SIZE / 2.0f) * sGameObjInstList[i].scale + sGameObjInstList[i].posCurr.y;
			AEVec2Set(&min, boundingRect_min_x, boundingRect_min_y);
			AEVec2Set(&max, boundingRect_max_x, boundingRect_max_y);
			sGameObjInstList[i].boundingBox.min = min;
			sGameObjInstList[i].boundingBox.max = max;
		}
		//COLLISION
		for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		{
			GameObjInst* oi1 = sGameObjInstList + i;
			if (oi1 != nullptr)
			{
				//Skip is object not active
				if (oi1->flag == 0)
				{
					continue;
				}
				if (oi1->pObject->type == TYPE_ASTEROID)
				{
					for (unsigned long j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
					{
						GameObjInst* oi2 = sGameObjInstList + j;
						if (oi2->flag == 0 || oi2->pObject->type == ASTEROID || j == i)
						{
							continue;
						}
						if (oi2->pObject->type == TYPE_SHIP)
						{
							if (CollisionIntersection_RectRect(oi1->boundingBox, oi1->velCurr,
								oi2->boundingBox, oi2->velCurr))
							{
								gameObjInstDestroy(oi1);
								asteroid_current--;
								
								if (!is_invicible)
								{
									ResetPostion(&oi2->posCurr, &oi2->velCurr);//Reset ship position
									//reset stats
									sShipLives--;
									Combo = 0;
									if (sShipLives == 0)
									{
										game_End = true;
									}

									//CONSOLE OUTPUT
									printf("Current Life: %d\n", sShipLives);
									printf("Current Combo: x%d\n", Combo);
								}

							}
						}
						//Handle bullet collision event
						else if (oi2->pObject->type == TYPE_BULLET)
						{
							if (CollisionIntersection_RectRect(oi1->boundingBox, oi1->velCurr,
								oi2->boundingBox, oi2->velCurr))
							{
								gameObjInstDestroy(oi1);
								gameObjInstDestroy(oi2);

								//Update state
								sScore += 100;
								asteroid_current--;
								Combo++;
								if (sScore == 2500)
								{
									printf("LEVEL 2\n");
								}
								if (sScore == 3500)
								{
									printf("LEVEL 3\n");
								}
								//CONSOLE OUTPUT
								printf("Current Score: %d\n", sScore);
								printf("Current Combo: x%d\n", Combo);
								if (sScore >= 5000)
								{
									game_End = true;
								}
							}
						}
					}
				}
			}
		}

		for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		{
			GameObjInst* pInst = sGameObjInstList + i;

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
			if (pInst->pObject->type == TYPE_ASTEROID)
			{
				pInst->posCurr.x = AEWrap(pInst->posCurr.x, AEGfxGetWinMinX() - pInst->scale,
					AEGfxGetWinMaxX() + pInst->scale);
				pInst->posCurr.y = AEWrap(pInst->posCurr.y, AEGfxGetWinMinY() - pInst->scale,
					AEGfxGetWinMaxY() + pInst->scale);
			}
			if (pInst->pObject->type == TYPE_BULLET)
			{
				if (pInst->posCurr.x == AEGfxGetWinMinX() || pInst->posCurr.x == AEGfxGetWinMaxX())
				{
					pInst->flag = 0;
				}
				if (pInst->posCurr.y == AEGfxGetWinMinY() || pInst->posCurr.x == AEGfxGetWinMaxY())
				{
					pInst->flag = 0;
				}
			}
		}


		// =====================================
		// calculate the matrix for all objects
		// =====================================

		for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		{
			GameObjInst* pInst = sGameObjInstList + i;
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
			AEMtx33Concat(&pInst->transform, &scale, &pInst->transform);
		}
	}
	//CHANGE WEAPON TYPE
	if (AEInputCheckCurr(AEVK_0))
	{
		weapon_current = 0;
	}
	if (AEInputCheckCurr(AEVK_1) )
	{
		weapon_current = 1;
	}
	if (game_End)
	{
		//IF PLAYER LOST GAME
		if (sShipLives == 0 && game_End)
		{
			printf("You LOST :)\n");
			printf("Your Final score was: %d", sScore);
			game_End = false;
		}
		//IF PLAYER WINS
		if (sScore >= 5000 && game_End)
		{
			printf("YOU ROCK\n");
			game_End = false;
		}
		printf("Total Time Played : %.2f\n", g_appTime);
		printf("Press 'ESC' to quit\n");

	}
	
	
}
/******************************************************************************/
/*!
	
*/
/******************************************************************************/
void GameStateAsteroidsDraw(void)
{
	char strBuffer[1024];
	
	AEGfxSetBackgroundColor(0.f, 0.0f, 0.0f);



	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;
		if (pInst != nullptr)
		{
			if (pInst->flag == 1)
			{
				if (pInst->pObject->type == TYPE_BULLET)
				{
					//render ship
					AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
					AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);//Setcolour
					AEGfxSetBlendMode(AE_GFX_BM_BLEND);
					AEGfxSetTransparency(1);//SetTransperancy
					AEGfxTextureSet(Bullet_Tex, 0.f, 0.f);

					AEMtx33 b_scale = { 0 };
					AEMtx33Scale(&b_scale, pInst->scale,pInst->scale);
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
				if (pInst->pObject->type == TYPE_ASTEROID)
				{
					//render Asteroid
					AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
					AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);//Setcolour
					AEGfxSetBlendMode(AE_GFX_BM_BLEND);
					AEGfxSetTransparency(1);//SetTransperancy
					AEGfxTextureSet(Asteroid_Tex, 0.f, 0.f);

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
				if (pInst->pObject->type == TYPE_SHIP)
				{
					//render ship
					AEGfxSetRenderMode(AE_GFX_RM_COLOR);
					AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);//Setcolour
					AEGfxSetBlendMode(AE_GFX_BM_BLEND);
					AEGfxSetTransparency(1);//SetTransperancy
					//AEGfxTextureSet(sShip_Tex, 0.f, 0.f);

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
			}
		}
	}

	static bool onValueChange = true;
	if(onValueChange)
	{
		sprintf_s(strBuffer, "Current Score:: %d", sScore);
		printf("%s \n", strBuffer);

		sprintf_s(strBuffer, "Current Life: %d", sShipLives >= 0 ? sShipLives : 0);
		printf("%s \n", strBuffer);
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
	for (int i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		gameObjInstDestroy(sGameObjInstList + 1);
	}
	gameObjInstDestroy(player_Ship);//Special
}

/******************************************************************************/
/*!
	
*/
/******************************************************************************/
void GameStateAsteroidsUnload(void)
{
	//KILL OFF TEXTURE
	AEGfxTextureUnload(Asteroid_Tex);
	AEGfxTextureUnload(Bullet_Tex);
	// free all mesh data (shapes) of each object using "AEGfxTriFree"
	int i = 0;
	while (i < 3)
	{
		AEGfxMeshFree(sGameObjList[i].pMesh);
		i++;
	}

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