#pragma once
#include "AEEngine.h"
#include "Particle.h"

void RenderEntity(Particle& en, AEGfxVertexList* mesh);
void RenderEntity(AEVec2 scale,AEVec2 pos,f32 rot, AEGfxVertexList* mesh);