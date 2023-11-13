#include "LevelReader.h"

void LevelReader::ReadLevel(int id)
{
	std::string path = "Data/Level/Level_" + std::to_string(id) + ".inp";

	std::cout << path << std::endl;

	std::ifstream fin(path);

	if (!fin.is_open())
	{
		std::cout << "Can't open file " << path << std::endl;
		return;
	}
	
	pushEmptyWave(); pushEmptyWave(); pushEmptyWave();
	
	fin >> waveCount;

	for (int i = 0; i < waveCount; i++)
	{
		int enemyPatternCnt; fin >> enemyPatternCnt;
		int bulletPatternCnt; fin >> bulletPatternCnt;
		
		std::vector <std::vector <int>> patternData;
		std::vector <std::vector <sf::Vector2f>> patternAttribute;
		std::vector <std::pair <int, int>> patternLoop;
		std::vector <int> patternTimerMax;
		std::vector <bool> patternPhysic;

		for (int j = 0; j < enemyPatternCnt; j++)
		{
			int enemyType, patternType, rotationType, total, width, widthCnt, startTimer, killTimer;
			fin >> enemyType >> patternType >> rotationType >> total >> width >> widthCnt >> startTimer >> killTimer;

			patternData.push_back({ enemyType, patternType, rotationType, total, width, widthCnt, startTimer, killTimer });

			float x, y, vx, vy, ax, ay;
			fin >> x >> y >> vx >> vy >> ax >> ay;

			patternAttribute.push_back({ {x, y}, {vx, vy}, {ax, ay} });

			int loopCnt, loopTimer;
			fin >> loopCnt >> loopTimer;

			patternLoop.push_back({ loopCnt, loopTimer });

			patternTimerMax.push_back(startTimer);
		}

		EnemyWaveData.push(patternData); patternData.clear();
		EnemyWaveAttribute.push(patternAttribute);	patternAttribute.clear();
		EnemyWaveLoop.push(patternLoop); patternLoop.clear();
		EnemyWaveTimerMax.push(patternTimerMax); patternTimerMax.clear();

		for (int j=0; j<bulletPatternCnt; j++)
		{
			int bulletType, patternType, rotationType, total, width, widthCnt, startTimer, killTimer;
			fin >> bulletType >> patternType >> rotationType >> total >> width >> widthCnt >> startTimer >> killTimer;

			patternData.push_back({ bulletType, patternType, rotationType, total, width, widthCnt, startTimer, killTimer });

			float x, y, vx, vy, ax, ay;
			fin >> x >> y >> vx >> vy >> ax >> ay;

			patternAttribute.push_back({ {x, y}, {vx, vy}, {ax, ay} });

			int loopCnt, loopTimer;
			fin >> loopCnt >> loopTimer;

			patternLoop.push_back({ loopCnt, loopTimer });

			bool physic; fin >> physic;
			
			patternPhysic.push_back(physic);

			patternTimerMax.push_back(startTimer);
		}

		BulletWaveData.push(patternData); patternData.clear();
		BulletWaveAttribute.push(patternAttribute); patternAttribute.clear();
		BulletWaveLoop.push(patternLoop); patternLoop.clear();
		BulletWavePhysic.push(patternPhysic); patternPhysic.clear();
		BulletWaveTimerMax.push(patternTimerMax); patternTimerMax.clear();
	}	

	std::getline(fin, levelName);
	std::getline(fin, levelName);

	std::string c = std::to_string(id+1);
	levelName = "Level " + c + ": " + levelName;
	
	fin.close();
}

//  1 < -- Number of Wave
//
//	1 1 < -- number of enemy pattern + bullet pattern

//	0 2 0 10 300 5 0 -1 < --   enemyType, patternType, rotationType, total, width, widthCnt, start timer, kill timer(int)
//	100 100 -5 0 0 0 0 < --  Position, Velocity, Acceleration(Vector2f)
// 	1 0 < -- LoopCnt, LoopTimer(int)

//	0 1 0 20 300 5 100 -1 < --   bulletType, patternType, rotationType, total, width, widthCnt, start timer, kill timer(int)
//	200 200 -5 0 0 0 0 < --  Position, Velocity, Acceleration(Vector2f)
// 	100 500 < -- LoopCnt, LoopTimer(int)
//  0   < -- have physic
// 
// the name af <<-- Level name

void LevelReader::gotoWave(int idWave)
{
	for (int i = 0; i <= idWave; i++) gotoNextWave();
}

void LevelReader::gotoNextWave()
{
	EnemyWaveData.pop();
	EnemyWaveAttribute.pop();
	EnemyWaveLoop.pop();
	EnemyWaveTimerMax.pop();

	BulletWaveData.pop();
	BulletWaveAttribute.pop();
	BulletWaveLoop.pop();
	BulletWavePhysic.pop();
	BulletWaveTimerMax.pop();
}

void LevelReader::pushEmptyWave()
{
	std::vector <std::vector <int>> patternData;
	std::vector <std::vector <sf::Vector2f>> patternAttribute;
	std::vector <std::pair <int, int>> patternLoop;
	std::vector <int> patternTimerMax;
	std::vector <bool> patternPhysic;


	EnemyWaveData.push(patternData);
	EnemyWaveAttribute.push(patternAttribute);
	EnemyWaveLoop.push(patternLoop);
	EnemyWaveTimerMax.push(patternTimerMax);

	BulletWaveData.push(patternData);
	BulletWaveAttribute.push(patternAttribute);
	BulletWaveLoop.push(patternLoop);	
	BulletWavePhysic.push(patternPhysic);
	BulletWaveTimerMax.push(patternTimerMax);
}

void LevelReader::cleanLevel()
{
	while (!EnemyWaveData.empty())
	{
		gotoNextWave();
	}
}

bool LevelReader::isLevelFinished()
{
	return EnemyWaveData.empty();
}

bool LevelReader::isWaveFinished()
{
	if (EnemyWaveData.empty()) return true;
	return (EnemyWaveData.front().empty());
}

bool LevelReader::isFinalWave()
{
	return (EnemyWaveData.size() == 1);
}

bool LevelReader::clearEnemyPattern(int id)
{
	if (EnemyWaveData.empty() || id >= EnemyWaveData.front().size()) return false;

	EnemyWaveData.front().erase(EnemyWaveData.front().begin() + id);
	EnemyWaveAttribute.front().erase(EnemyWaveAttribute.front().begin() + id);
	EnemyWaveLoop.front().erase(EnemyWaveLoop.front().begin() + id);
	EnemyWaveTimerMax.front().erase(EnemyWaveTimerMax.front().begin() + id);

	return true;
}
bool LevelReader::clearBulletPattern(int id)
{
	if (EnemyWaveData.empty() || id >= BulletWaveData.front().size()) return false;

	BulletWaveAttribute.front().erase(BulletWaveAttribute.front().begin() + id);
	BulletWaveData.front().erase(BulletWaveData.front().begin() + id);
	BulletWaveLoop.front().erase(BulletWaveLoop.front().begin() + id);
	BulletWavePhysic.front().erase(BulletWavePhysic.front().begin() + id);
	BulletWaveTimerMax.front().erase(BulletWaveTimerMax.front().begin() + id);

	return true;
}