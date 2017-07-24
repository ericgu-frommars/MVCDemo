
////////////////////////////////////////////////////////////////////////////////
// Filename: MovableEntity.cpp
////////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

MovableEntity::MovableEntity()
{
	m_isMoving = false;
	m_speed = 1;
}

MovableEntity::MovableEntity(const MovableEntity& other)
{

}

MovableEntity::~MovableEntity()
{

}

inline int MovableEntity::GetSpeed()
{
	return m_speed;
}

inline void MovableEntity::SetSpeed(int speed)
{
	m_speed = speed;
}

void MovableEntity::SetTarget(int targetX, int targetY)
{
	m_targetX = targetX;
	m_targetY = targetY;
	m_isMoving = true;
}

void MovableEntity::Update(float deltaTime)
{
	if (m_isMoving)
	{


		SetX(m_targetX);
		SetY(m_targetY);
		m_isMoving = false;
	}
}
