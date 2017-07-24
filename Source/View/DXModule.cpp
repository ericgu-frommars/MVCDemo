////////////////////////////////////////////////////////////////////////////////
// Filename: DXModule.cpp
////////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

DXModule::DXModule()
{
	m_lpDD = NULL;
	m_lpDDSPrimary = NULL;
	m_lpDDSBack = NULL;
	m_lpDDSBuffer = NULL;
}

DXModule::~DXModule()
{
	Shutdown();
}

bool DXModule::Initialize(int screenWidth, int screenHeight, HWND hWnd, bool isFullScreen)
{
	m_screenWidth  = screenWidth;
	m_screenHeight = screenHeight;
	m_isFullScreen = isFullScreen;
	m_hWnd = hWnd;

	DDSURFACEDESC ddsd;
	DDSCAPS ddscaps;

	if (DirectDrawCreate(NULL, &m_lpDD, NULL) != DD_OK)
		return FALSE;

	if (isFullScreen)
	{
		if (m_lpDD->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN) != DD_OK)
			return FALSE;

		if (m_lpDD->SetDisplayMode(screenWidth, screenHeight, 32) != DD_OK)
			return FALSE;
	}
	else
	{
		if (m_lpDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL) != DD_OK)
			return FALSE;
	}

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	if (isFullScreen)
	{
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 1;
	}
	else
	{
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	}

	if (m_lpDD->CreateSurface(&ddsd, &m_lpDDSPrimary, NULL) != DD_OK)
		return FALSE;

	if (isFullScreen)
	{
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		if (m_lpDDSPrimary->GetAttachedSurface(&ddscaps, &m_lpDDSBack) != DD_OK)
			return FALSE;
	}
	else
	{
		if (m_lpDD->CreateClipper(0, &m_lpDDClipper, NULL) != DD_OK)
			return FALSE;

		m_lpDDClipper->SetHWnd(0, hWnd);
		m_lpDDSPrimary->SetClipper(m_lpDDClipper);
	}

	m_lpDDSBuffer = CreateSurface(m_lpDD, screenWidth, screenHeight);

    return true;
}

void DXModule::Shutdown()
{
	_RELEASE(m_lpDDSBuffer)

	_RELEASE(m_lpDDClipper)

	_RELEASE(m_lpDDSPrimary)

	_RELEASE(m_lpDDSBack)

	_RELEASE(m_lpDD)
}

IDirectDrawSurface* DXModule::LoadSurfaceFromFile(LPCWSTR lpFileName, bool isSetColorKey)
{
	LPDIRECTDRAWSURFACE lpDDSObj = DDLoadBitmap(m_lpDD, lpFileName);

	if (isSetColorKey)
	{
		DDSetColorKey(lpDDSObj, RGB(0, 0, 0));
	}

	return lpDDSObj;
}

void DXModule::RenderSurface(LPDIRECTDRAWSURFACE lpDDSObj, int nX, int nY, RECT *pRect, bool isTrans)
{
	ClipBlt(m_lpDDSBuffer, nX, nY, lpDDSObj, pRect, isTrans);
}

void DXModule::RenderToScreen()
{
	if (m_isFullScreen)
	{
		RECT rcSource = { 0, 0, m_screenWidth, m_screenHeight };
		m_lpDDSBack->BltFast(0, 0, m_lpDDSBuffer, &rcSource, FALSE);

		HRESULT ddrval;
		while (1)
		{
			ddrval = m_lpDDSPrimary->Flip(NULL, 0);
			if (ddrval == DD_OK)
			{
				break;
			}
			if (ddrval == DDERR_SURFACELOST)
			{
				ddrval = RestoreDDraw();
				if (ddrval != DD_OK)
				{
					break;
				}
			}
			if (ddrval != DDERR_WASSTILLDRAWING)
			{
				break;
			}
		}
	}
	else
	{
		RECT rcClient = { 0 };
		ChangeClientToSreen(rcClient);
		m_lpDDSPrimary->Blt(&rcClient, m_lpDDSBuffer, NULL, DDBLT_WAIT, NULL);
	}
}

IDirectDrawSurface* DXModule::DDLoadBitmap(IDirectDraw *lpDD, LPCWSTR sFileName)
{
	HBITMAP hbm;   BITMAP bm;
	DDSURFACEDESC  ddsd;  IDirectDrawSurface *lpDDS;
	HDC hdcImage, hdc;

	hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), sFileName,
		IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	if (hbm == NULL)
		hbm = (HBITMAP)LoadImage(NULL, sFileName, IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (hbm == NULL)
		return FALSE;

	if (GetObject(hbm, sizeof(bm), &bm) == 0)
		return FALSE;

	//Initial Surface
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth = bm.bmWidth;
	ddsd.dwHeight = bm.bmHeight;
	if (lpDD->CreateSurface(&ddsd, &lpDDS, NULL) != DD_OK)
		return FALSE;

	if (!(hdcImage = CreateCompatibleDC(NULL)))
		return FALSE;
	SelectObject(hdcImage, hbm);

	if ((lpDDS->GetDC(&hdc)) != DD_OK)
		return FALSE;

	StretchBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcImage,
		0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	lpDDS->ReleaseDC(hdc);
	DeleteObject(hbm);
	DeleteDC(hdcImage);
	//	DeleteDC(hdc);
	return lpDDS;
}

IDirectDrawSurface* DXModule::CreateSurface(IDirectDraw *lpDD, int nWidth, int nHeight)
{
	DDSURFACEDESC ddsd;
	IDirectDrawSurface *lpDDS;

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth = nWidth;
	ddsd.dwHeight = nHeight;
	if (lpDD->CreateSurface(&ddsd, &lpDDS, NULL) != DD_OK)
		return FALSE;

	return lpDDS;
}

HRESULT DXModule::DDSetColorKey(IDirectDrawSurface * pdds, COLORREF rgb)
{
	DDCOLORKEY	ddck;
	COLORREF	rgbT;
	HDC		hdc;
	DWORD	dw = CLR_INVALID;
	DDSURFACEDESC	ddsd;
	HRESULT         hres;

	if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
	{
		rgbT = GetPixel(hdc, 0, 0);     // Save current pixel value
		SetPixel(hdc, 0, 0, rgb);       // Set our value
		pdds->ReleaseDC(hdc);
	}

	ddsd.dwSize = sizeof(ddsd);
	while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING);

	if (hres == DD_OK)
	{
		dw = *(DWORD *)ddsd.lpSurface;                 // Get DWORD
		if (ddsd.ddpfPixelFormat.dwRGBBitCount < 32)
			dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount) - 1;  // Mask it to bpp
		pdds->Unlock(NULL);
	}
	//
	if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
	{
		SetPixel(hdc, 0, 0, rgbT);
		pdds->ReleaseDC(hdc);
	}

	ddck.dwColorSpaceLowValue = dw;
	ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
	return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}

void DXModule::ClipBlt(IDirectDrawSurface *pdds1, int iX, int iY, IDirectDrawSurface *pdds2, RECT *prcArea, BOOL bTrans)
{
	POINT src;
	src.x = iX; src.y = iY;

	RECT  rcRect;
	rcRect.left = prcArea->left;	rcRect.top = prcArea->top;
	rcRect.right = prcArea->right;   rcRect.bottom = prcArea->bottom;

	if (iX<0)
	{
		rcRect.left = prcArea->left - iX;
		src.x = 0;
	}
	if (iY<0)
	{
		rcRect.top = prcArea->top - iY;
		src.y = 0;
	}
	if (iX + prcArea->right - prcArea->left>m_screenWidth)
	{
		rcRect.right = prcArea->left + (m_screenWidth - iX);
	}
	if (iY + prcArea->bottom - prcArea->top>m_screenHeight)
	{
		rcRect.bottom = prcArea->top + (m_screenHeight - iY);
	}

	pdds1->BltFast(src.x, src.y, pdds2, &rcRect, bTrans ? DDBLTFAST_SRCCOLORKEY : FALSE);
}

HRESULT DXModule::RestoreDDraw()
{
	HRESULT	ddrval;

	if (m_lpDDSBuffer)
		ddrval = m_lpDDSBuffer->Restore();

	if (m_lpDDSPrimary)
		ddrval = m_lpDDSPrimary->Restore();

	if (m_lpDDSBack)
		ddrval =m_lpDDSBack->Restore();

	return ddrval;
}

void DXModule::ChangeClientToSreen(RECT &rc)
{
	GetClientRect(m_hWnd, &rc);
	ClientToScreen(m_hWnd, (LPPOINT)&rc);
	ClientToScreen(m_hWnd, (LPPOINT)&rc + 1);
}
