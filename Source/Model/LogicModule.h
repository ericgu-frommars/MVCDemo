
////////////////////////////////////////////////////////////////////////////////
// Filename: LogicModule.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LogicModule_H_
#define _LogicModule_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////

const int CELL_SIZE = 32;
const int GRID_WIDTH = 480 / CELL_SIZE;
const int GRID_HEIGHT = 320 / CELL_SIZE;

class BaseEntity;
typedef map<int, BaseEntity*> mapBaseEntity;
typedef map<int, BaseEntity*>::iterator iterBaseEntity;

////////////////////////////////////////////////////////////////////////////////
// Class name: LogicModule
////////////////////////////////////////////////////////////////////////////////
class LogicModule
{
public:
	LogicModule();
	~LogicModule();
	
	bool Initialize();	
	bool Update(float deltaTime);
	BaseEntity* GetEntity(int x, int y);

	mapBaseEntity& GetMapEntity()
	{
		return m_mapEntity;
	}

	Hero* GetHero()
	{
		return m_pHero;
	}

private:
	void AddEntityRecord(BaseEntity* pEntity);
	void Shutdown();

	Hero*		  m_pHero;
	mapBaseEntity m_mapEntity;
};

#endif
