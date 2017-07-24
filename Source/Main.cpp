////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemModule* pSystem;
	bool result;
	
	// Create the system object.
	pSystem = new SystemModule;
	if(!pSystem)
	{
		return 0;
	}

	// Initialize and run the system object.
	result = pSystem->Initialize();
	if(result)
	{
		pSystem->Run();
	}

	// Shutdown and release the system object.
	_DELETE(pSystem)

	return 0;
}