
////////////////////////////////////////////////////////////////////////////////
// Filename: EnemyRenderer.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _EnemyRenderer_H_
#define _EnemyRenderer_H_

////////////////////////////////////////////////////////////////////////////////
// Class name: EnemyRenderer
////////////////////////////////////////////////////////////////////////////////
class EnemyRenderer
{
public:
	EnemyRenderer();
	~EnemyRenderer();

	bool Initialize(DXModule* pDXModule);
	bool Render(DXModule* pDXModule, int nX, int nY);

private:
	void Shutdown();

	LPDIRECTDRAWSURFACE m_lpDDSEnemy;
};

#endif




