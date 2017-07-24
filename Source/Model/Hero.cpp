
////////////////////////////////////////////////////////////////////////////////
// Filename: Hero.cpp
////////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

Hero::Hero()
{
	m_score = 0;
}

Hero::Hero(const Hero& other)
{

}

Hero::~Hero()
{

}

EntityType Hero::GetType()
{
	return HeroType;
}

void Hero::Update(float deltaTime)
{
	MovableEntity::Update(deltaTime);
}
