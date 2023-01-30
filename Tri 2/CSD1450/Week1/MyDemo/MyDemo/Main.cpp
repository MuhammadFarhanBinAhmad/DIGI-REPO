// ---------------------------------------------------------------------------
#include "pch.h"
#include <iostream>
#define M_PI 3.14159265358979323846
// ---------------------------------------------------------------------------
// main



float R = 255;
float G = 0;
float B = 0;

float speed = .001f;
float percentage = 0;
bool shot;

float start = 0;
float end = 360;

int AR_x = 1920;
int AR_y = 1080;

f32 cam_x;
f32 cam_y;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	int gGameRunning = 1;

	//Initialize GameObject
	Projectile bullet(0,0,0,10,0);
	bullet.speed = 15;
	
	
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, AR_x, AR_y, 1, 60, true, NULL);
	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/Cannon.png");

	// reset the system modules
	AESysReset();

	// Pointer to Mesh
	AEGfxVertexList* pMesh = 0;
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	AEGfxTriAdd(
		-1.f, -1.f, 0x00FF00FF, 0.f, 0.f,
		1.f, -1.f, 0x00FFFF00, 1.f, 0.f,
		-1.f, 1.f, 0x0000FFFF, 0.f, 1.f);
	AEGfxTriAdd(
		1.f, -1.f, 0x00FFFFFF, 1.f, 0.f,
		1.f, 1.f, 0x00FFFFFF, 1.f, 1.f,
		-1.f, 1.f, 0x00FFFFFF,0.f, 1.0f);
	//AEGfxTriAdd
	// Saving the mesh (list of triangles) in pMesh
	pMesh = AEGfxMeshEnd();

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		// Your own update logic goes here
		if (percentage > 1)
		{
			speed *= -1;
		}
		if (percentage < 0)
		{
			speed *= -1;
		}
		percentage += 0.1f * speed;

		AEGfxSetBackgroundColor(255.0f, 0.0f, 0.0f);

		//TEXTURE
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);//Setcolour
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1);//SetTransperancy
		AEGfxTextureSet(pTex, 0.f, 0.f);

		//ROTATION
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, ((bullet.angle *3) /PI));

		//TRANSLATION
		AEMtx33 origin = { 0 };
		AEMtx33Trans(&origin, bullet.pos_x, bullet.pos_y);
		std::cout << bullet.direction_y << std::endl;
		//OBJECT ROTATION DIRECTION
		M_MATH::Clamp(0, 3, bullet.angle);

		if (AEInputCheckCurr(AEVK_Q))
		{
			if (bullet.angle <= 3)
			{
				bullet.angle += .1;
				TO::ObjectRotate(&bullet.pos_x,&bullet.pos_y, &bullet.direction_x, &bullet.direction_y, &bullet.angle);
			}
		}
		if (AEInputCheckCurr(AEVK_E))
		{
			if (bullet.angle >= 0)
			{
				bullet.angle -= .1;
				TO::ObjectRotate(&bullet.pos_x, &bullet.pos_y, &bullet.direction_x, &bullet.direction_y, &bullet.angle);
			}
		}
		if (AEInputCheckTriggered(AEVK_A))
		{
			shot = true;
		}

		AEGfxGetCamPosition(&cam_x, &cam_y);
		if (AEInputCheckCurr(AEVK_W))
			AEGfxSetCamPosition(cam_x, cam_y + 2);
		else if (AEInputCheckCurr(AEVK_S))
			AEGfxSetCamPosition(cam_x, cam_y - 2);


		if (shot)
		{
			TO::TransformFoward(&bullet.pos_x, &bullet.pos_y, &bullet.direction_x, &bullet.direction_y,&bullet.speed);
		}
		//SCALE
		AEMtx33 scale = { 1 };
		AEMtx33Scale(&scale, 25.f, 25.f);

		// Concat the matrices (TRS)
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &origin, &transform);

		// Choose the transform to use
		AEGfxSetTransform(transform.m);

		//DRAWMESH
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}
	//Free mesh

	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pTex);

	// free the system
	AESysExit();
	
}