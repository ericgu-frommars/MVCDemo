////////////////////////////////////////////////////////////////////////////////
// Filename: GraphicsModule.cpp
////////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

GraphicsModule::GraphicsModule(LogicModule* pLogicModule)
{
	m_pLogicModule = pLogicModule;
	m_pDXModule = NULL;

	m_pGridMapRenderer = NULL;
	m_pHeroRenderer = NULL;
	m_pEnemyRenderer = NULL;
	m_pObstacleRenderer = NULL;
}

GraphicsModule::~GraphicsModule()
{
	Shutdown();
}

bool GraphicsModule::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Initialize the DX module
	m_pDXModule = new DXModule;
	if (!m_pDXModule)
		return false;

	result = m_pDXModule->Initialize(screenWidth, screenHeight, hwnd, FULL_SCREEN);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize DirectX.", L"Error", MB_OK);
		return false;
	}

	//
	m_pGridMapRenderer = new GridMapRenderer;
	if (!m_pGridMapRenderer)
		return false;

	m_pGridMapRenderer->Initialize(m_pDXModule);

	//
	m_pHeroRenderer = new HeroRenderer;
	if (!m_pHeroRenderer)
		return false;
	
	m_pHeroRenderer->Initialize(m_pDXModule);

	//
	m_pEnemyRenderer = new EnemyRenderer;
	if (!m_pEnemyRenderer)
		return false;

	m_pEnemyRenderer->Initialize(m_pDXModule);

	//
	m_pObstacleRenderer = new ObstacleRenderer;
	if (!m_pObstacleRenderer)
		return false;

	m_pObstacleRenderer->Initialize(m_pDXModule);
	
	return true;
}

void GraphicsModule::Shutdown()
{	
	_DELETE(m_pGridMapRenderer)
	_DELETE(m_pHeroRenderer)
	_DELETE(m_pEnemyRenderer)
	_DELETE(m_pObstacleRenderer)

	_DELETE(m_pDXModule)
}

void GraphicsModule::Render()
{
	m_pGridMapRenderer->Render(m_pDXModule, 0, 0);
	
	mapBaseEntity& mapEntity = m_pLogicModule->GetMapEntity();
	for (iterBaseEntity it = mapEntity.begin(); it != mapEntity.end(); it++)
	{
		BaseEntity* pEntity = (it->second);

		if (pEntity->GetType() == HeroType)
		{
			m_pHeroRenderer->Render(m_pDXModule, pEntity->GetX() * CELL_SIZE, pEntity->GetY() * CELL_SIZE);
		}
		else if (pEntity->GetType() == EnemyType)
		{
			m_pEnemyRenderer->Render(m_pDXModule, pEntity->GetX() * CELL_SIZE, pEntity->GetY() * CELL_SIZE);
		}
		else if (pEntity->GetType() == ObstacleType)
		{
			m_pObstacleRenderer->Render(m_pDXModule, pEntity->GetX() * CELL_SIZE, pEntity->GetY() * CELL_SIZE);
		}
	}

	m_pDXModule->RenderToScreen();
}
