////////////////////////////////////////////////////////////////////////////////
// Filename: GraphicsModule.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GraphicsModule_H_
#define _GraphicsModule_H_

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsModule
////////////////////////////////////////////////////////////////////////////////
class GraphicsModule
{
public:
	GraphicsModule(LogicModule* pLogicModule);
	~GraphicsModule();

	bool Initialize(int, int, HWND);
	void Render();

private:
	void Shutdown();

private:
	LogicModule* m_pLogicModule;
	DXModule* m_pDXModule;

	GridMapRenderer*  m_pGridMapRenderer;
	HeroRenderer*	  m_pHeroRenderer;
	EnemyRenderer*	  m_pEnemyRenderer;
	ObstacleRenderer* m_pObstacleRenderer;
};

#endif