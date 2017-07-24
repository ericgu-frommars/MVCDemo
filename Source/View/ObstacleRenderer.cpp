
////////////////////////////////////////////////////////////////////////////////
// Filename: ObstacleRenderer.cpp
////////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

ObstacleRenderer::ObstacleRenderer()
{
	m_lpDDSObstacle = NULL;
}

ObstacleRenderer::~ObstacleRenderer()
{
	Shutdown();
}

bool ObstacleRenderer::Initialize(DXModule* pDXModule)
{
	m_lpDDSObstacle = pDXModule->LoadSurfaceFromFile(L"image\\obstacle.bmp", true);
	return true;
}

bool ObstacleRenderer::Render(DXModule* pDXModule, int nX, int nY)
{
	RECT rcRect = { 0, 0, 32, 32 };
	pDXModule->RenderSurface(m_lpDDSObstacle, nX, nY, &rcRect, true);

	return true;
}

void ObstacleRenderer::Shutdown()
{
	_RELEASE(m_lpDDSObstacle)
}
