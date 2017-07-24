
////////////////////////////////////////////////////////////////////////////////
// Filename: MovableEntity.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MovableEntity_H_
#define _MovableEntity_H_

////////////////////////////////////////////////////////////////////////////////
// Class name: MovableEntity
////////////////////////////////////////////////////////////////////////////////
class BaseEntity;
class MovableEntity : public BaseEntity
{
public:
	MovableEntity();
	MovableEntity(const MovableEntity&);
	~MovableEntity();

	int  GetSpeed();
	void SetSpeed(int speed);

	void Update(float deltaTime);
	void SetTarget(int targetX, int targetY);

private:
	int m_targetX;
	int m_targetY;
	int m_speed;

	bool m_isMoving;
};

#endif