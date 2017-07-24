
////////////////////////////////////////////////////////////////////////////////
// Filename: EnemyRenderer.cpp
////////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

EnemyRenderer::EnemyRenderer()
{
	m_lpDDSEnemy = NULL;
}

EnemyRenderer::~EnemyRenderer()
{
	Shutdown();
}

bool EnemyRenderer::Initialize(DXModule* pDXModule)
{
	m_lpDDSEnemy = pDXModule->LoadSurfaceFromFile(L"image\\enemy.bmp", true);
	return true;
}

bool EnemyRenderer::Render(DXModule* pDXModule, int nX, int nY)
{
	RECT rcRect = { 0, 0, 32, 32 };
	pDXModule->RenderSurface(m_lpDDSEnemy, nX, nY, &rcRect, true);

	return true;
}

void EnemyRenderer::Shutdown()
{
	_RELEASE(m_lpDDSEnemy)
}
