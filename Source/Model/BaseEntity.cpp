
////////////////////////////////////////////////////////////////////////////////
// Filename: BaseEntity.cpp
////////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

BaseEntity::BaseEntity()
{

}

BaseEntity::BaseEntity(const BaseEntity& other)
{

}

BaseEntity::~BaseEntity()
{

}

int BaseEntity::GetX()
{
	return m_x;
}

int BaseEntity::GetY()
{
	return m_y;
}

void BaseEntity::SetX(int x)
{
	m_x = x;
}

void BaseEntity::SetY(int y)
{
	m_y = y;
}

EntityType BaseEntity::GetType()
{
	return BaseType;
}

void BaseEntity::Update(float deltaTime)
{

}
