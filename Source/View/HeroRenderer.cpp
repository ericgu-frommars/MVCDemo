
////////////////////////////////////////////////////////////////////////////////
// Filename: HeroRenderer.cpp
////////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

HeroRenderer::HeroRenderer()
{
	m_lpDDSHero = NULL;
}

HeroRenderer::~HeroRenderer()
{
	Shutdown();
}

bool HeroRenderer::Initialize(DXModule* pDXModule)
{
	m_lpDDSHero = pDXModule->LoadSurfaceFromFile(L"image\\hero.bmp", true);
	return true;
}

bool HeroRenderer::Render(DXModule* pDXModule, int nX, int nY)
{
	RECT rcRect = { 0, 0, 32, 32 };
	pDXModule->RenderSurface(m_lpDDSHero, nX, nY, &rcRect, true);

	return true;
}

void HeroRenderer::Shutdown()
{
	_RELEASE(m_lpDDSHero)
}
