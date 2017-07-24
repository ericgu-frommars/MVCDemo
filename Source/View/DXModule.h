////////////////////////////////////////////////////////////////////////////////
// Filename: DXModule.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _DXModule_H_
#define _DXModule_H_


/////////////
// LINKING //
/////////////
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d8.lib")
#pragma comment(lib, "d3dx8.lib")
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "winmm.lib")


////////////////////////////////////////////////////////////////////////////////
// Class name: DXModule
////////////////////////////////////////////////////////////////////////////////
class DXModule
{
public:
	DXModule();
	~DXModule();

	bool Initialize(int screenWidth, int screenHeight, HWND hWnd, bool isFullScreen);	

	IDirectDrawSurface* LoadSurfaceFromFile(LPCWSTR fileName, bool isSetColorKey = true);
	void RenderSurface(LPDIRECTDRAWSURFACE lpDDSObj, int nX, int nY, RECT *pRect, bool isTrans = true);
	void RenderToScreen();

private:
	IDirectDrawSurface* DDLoadBitmap(IDirectDraw *lpDD, LPCWSTR sFileName);
	IDirectDrawSurface* CreateSurface(IDirectDraw *lpDD, int nWidth, int nHeight);
	HRESULT DDSetColorKey(IDirectDrawSurface * pdds, COLORREF rgb);
	void ClipBlt(IDirectDrawSurface *pdds1, int iX, int iY, IDirectDrawSurface *pdds2, RECT *prcArea, BOOL bTrans = TRUE);
	HRESULT RestoreDDraw();

	void ChangeClientToSreen(RECT &rc);
	void Shutdown();

private:
	LPDIRECTDRAW        m_lpDD;
	LPDIRECTDRAWSURFACE m_lpDDSPrimary;
	LPDIRECTDRAWSURFACE m_lpDDSBack;
	LPDIRECTDRAWSURFACE m_lpDDSBuffer;
	LPDIRECTDRAWCLIPPER m_lpDDClipper;

	int m_screenWidth, m_screenHeight;
	bool m_isFullScreen;
	HWND m_hWnd;
};

#endif