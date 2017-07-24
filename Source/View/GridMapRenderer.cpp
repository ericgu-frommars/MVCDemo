
////////////////////////////////////////////////////////////////////////////////
// Filename: GridMapRenderer.cpp
////////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

GridMapRenderer::GridMapRenderer()
{
	m_lpDDSGridMap = NULL;
}

GridMapRenderer::~GridMapRenderer()
{
	Shutdown();
}

bool GridMapRenderer::Initialize(DXModule* pDXModule)
{
	m_lpDDSGridMap = pDXModule->LoadSurfaceFromFile(L"image\\gridmap.bmp", false);
	return true;
}

bool GridMapRenderer::Render(DXModule* pDXModule, int nX, int nY)
{
	RECT rcRect = { 0, 0, 480, 320 };
	pDXModule->RenderSurface(m_lpDDSGridMap, nX, nY, &rcRect, false);

	return true;
}

void GridMapRenderer::Shutdown()
{
	_RELEASE(m_lpDDSGridMap)
}




