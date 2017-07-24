////////////////////////////////////////////////////////////////////////////////
// Filename: InputModule.cpp
////////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

InputModule::InputModule(LogicModule* pLogicModule)
{
	m_pLogicModule = pLogicModule;
}

InputModule::~InputModule()
{
}

void InputModule::Initialize()
{
	int i;
	
	// Initialize all the keys to being released and not pressed.
	for(i=0; i<256; i++)
	{
		m_keys[i] = false;
	}
}

void InputModule::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;
}

void InputModule::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	m_keys[input] = false;
}

bool InputModule::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return m_keys[key];
}

void InputModule::OnClicked(int x, int y)
{
	int gridX = x / CELL_SIZE;
	int gridY = y / CELL_SIZE;

	if (m_pLogicModule->GetEntity(gridX, gridY) == NULL)
	{
		Hero* pHero = m_pLogicModule->GetHero();
		if (pHero)
		{
			pHero->SetTarget(gridX, gridY);
		}
	}
}
