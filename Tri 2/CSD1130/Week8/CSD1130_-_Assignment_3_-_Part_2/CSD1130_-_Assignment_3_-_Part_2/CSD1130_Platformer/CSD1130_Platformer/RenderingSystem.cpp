#include "AEEngine.h"
#include "RenderingSystem.h"
#include "Particle.h"

void RenderEntity(Particle& en, AEGfxVertexList* mesh)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);

	AEMtx33 b_scale = { 1 };
	AEMtx33Scale(&b_scale, en.scale.x, en.scale.y);
	AEMtx33 b_rotate = { 0 };
	AEMtx33Rot(&b_rotate, en.rotation);
	AEMtx33 b_translate = { 0 };
	AEMtx33Trans(&b_translate, en.ParticleVec.x, en.ParticleVec.y);
	AEMtx33 b_transform = { 0 };
	AEMtx33Concat(&b_transform, &b_rotate, &b_scale);
	AEMtx33Concat(&b_transform, &b_translate, &b_transform);
	AEGfxSetTransform(b_transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}
void RenderEntity(AEVec2 scale, AEVec2 pos, f32 rot, AEGfxVertexList* mesh)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetTintColor(1.f, 1.f, 1.f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);

	AEMtx33 b_scale = { 1 };
	AEMtx33Scale(&b_scale, scale.x, scale.y);
	AEMtx33 b_rotate = { 0 };
	AEMtx33Rot(&b_rotate, rot);
	AEMtx33 b_translate = { 0 };
	AEMtx33Trans(&b_translate, pos.x, pos.y);
	AEMtx33 b_transform = { 0 };
	AEMtx33Concat(&b_transform, &b_rotate, &b_scale);
	AEMtx33Concat(&b_transform, &b_translate, &b_transform);
	AEGfxSetTransform(b_transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}