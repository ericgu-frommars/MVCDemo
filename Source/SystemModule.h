////////////////////////////////////////////////////////////////////////////////
// Filename: SystemModule.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SystemModule_H_
#define _SystemModule_H_


///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define WIN32_LEAN_AND_MEAN

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;

////////////////////////////////////////////////////////////////////////////////
// Class name: SystemModule
////////////////////////////////////////////////////////////////////////////////
class SystemModule
{
public:
	SystemModule();
	~SystemModule();

	bool Initialize();	
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void Shutdown();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputModule* m_pInputModule;
	LogicModule* m_pLogicModule;
	GraphicsModule* m_pGraphicsModule;
};


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/////////////
// GLOBALS //
/////////////
static SystemModule* ApplicationHandle = 0;


#endif