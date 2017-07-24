
////////////////////////////////////////////////////////////////////////////////
// Filename: LogicModule.cpp
////////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

LogicModule::LogicModule()
{

}

LogicModule::~LogicModule()
{
	Shutdown();
}

bool LogicModule::Initialize()
{
	Hero* pHero = new Hero;
	pHero->SetX(GRID_WIDTH / 2);
	pHero->SetY(GRID_HEIGHT / 2);
	AddEntityRecord(pHero);
	m_pHero = pHero;

	Enemy* pEnemy = new Enemy;
	pEnemy->SetX(pHero->GetX() + 3);
	pEnemy->SetY(pHero->GetY() + 2);
	AddEntityRecord(pEnemy);

	Obstacle* pObstacle = new Obstacle;
	pObstacle->SetX(pEnemy->GetX() - 1);
	pObstacle->SetY(pEnemy->GetY() + 1);
	AddEntityRecord(pObstacle);

	return true;
}

bool LogicModule::Update(float deltaTime)
{
	for (iterBaseEntity it = m_mapEntity.begin(); it != m_mapEntity.end(); it++)
	{
		BaseEntity* pEntity = (it->second);
		pEntity->Update(deltaTime);
	}

	return true;
}

void LogicModule::Shutdown()
{
	for (iterBaseEntity it = m_mapEntity.begin(); it != m_mapEntity.end(); it++)
	{
		_DELETE(it->second)
	}
	m_mapEntity.clear();
}

void LogicModule::AddEntityRecord(BaseEntity* pEntity)
{
	int pitch = pEntity->GetY() * GRID_WIDTH + pEntity->GetX();
	m_mapEntity.insert(mapBaseEntity::value_type(pitch, pEntity));
}

BaseEntity* LogicModule::GetEntity(int x, int y)
{
	int pitch = y * GRID_WIDTH + x;
	iterBaseEntity it = m_mapEntity.find(pitch);
	if (it != m_mapEntity.end())
	{
		return it->second;
	}

	return NULL;
}


/*
	private Droid droid;
	private List<Enemy>		enemies = new ArrayList<Enemy>();
	private List<Obstacle>	obstacles = new ArrayList<Obstacle>();

	public Arena(Droid droid)
	{
		this.droid = droid;


		// add 5 obstacles and 5 enemies at random positions
		for (int i = 0; i < 5; i++)
		{
			int x = random.nextInt(WIDTH);
			int y = random.nextInt(HEIGHT);

			while (grid[y][x] != null)
			{
				x = random.nextInt(WIDTH);
				y = random.nextInt(HEIGHT);
			}

			grid[y][x] = new Obstacle(x, y);
			obstacles.add((Obstacle)grid[y][x]);

			while (grid[y][x] != null)
			{
				x = random.nextInt(WIDTH);
				y = random.nextInt(HEIGHT);
			}

			grid[y][x] = new Enemy(x, y);
			enemies.add((Enemy)grid[y][x]);
		}
	}
	*/


