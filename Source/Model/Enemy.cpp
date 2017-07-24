
////////////////////////////////////////////////////////////////////////////////
// Filename: Enemy.cpp
////////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

Enemy::Enemy()
{

}

Enemy::Enemy(const Enemy& other)
{

}

Enemy::~Enemy()
{

}

EntityType Enemy::GetType()
{
	return EnemyType;
}

void Enemy::Update(float deltaTime)
{
	MovableEntity::Update(deltaTime);

	//maybe we could add some special AI code here...

}
