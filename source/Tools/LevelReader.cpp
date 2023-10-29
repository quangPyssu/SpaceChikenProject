#include "LevelReader.h"

void LevelReader::ReadLevel(int id)
{
	std::string path = "Level/Level_" + std::to_string(id) + ".inp";

	std::cout << path << std::endl;

	std::ifstream fin(path);

	if (!fin.is_open())
	{
		std::cout << "Can't open file " << path << std::endl;
		return;
	}
	
	//pushEmptyWave();
	
	fin >> waveCount;

	for (int i = 0; i < waveCount; i++)
	{
		int patternCount;
		fin >> patternCount;

		std::vector <std::vector <int>> patternData;
		std::vector <sf::Vector2f> patternPosition;
		std::vector <sf::Vector2f> patternVelocity;
		std::vector <sf::Vector2f> patternAcceleration;

		for (int j = 0; j < patternCount; j++)
		{
			int patternBool; fin >> patternBool;

			int patternType; fin >> patternType;

			int total; fin >> total;

			int width; fin >> width;

			int widthCnt; fin >> widthCnt;

			int startTimer; fin >> startTimer;

			int killTimer; fin >> killTimer;

			std::vector <int> pType;
			patternData.push_back(pType);
			
			{
				patternData.back().push_back(patternBool);
				patternData.back().push_back(patternType);
				patternData.back().push_back(total);
				patternData.back().push_back(width);
				patternData.back().push_back(widthCnt);
				patternData.back().push_back(startTimer);
				patternData.back().push_back(killTimer);
			}

			sf::Vector2f position;	fin >> position.x >> position.y;

			sf::Vector2f velocity;  fin >> velocity.x >> velocity.y;

			sf::Vector2f acceleration;	fin >> acceleration.x >> acceleration.y;

			patternPosition.push_back(position);
			patternVelocity.push_back(velocity);
			patternAcceleration.push_back(acceleration);			
		}

		WaveData.push(patternData);
		WavePosition.push(patternPosition);
		WaveVelocity.push(patternVelocity);
		WaveAcceleration.push(patternAcceleration);
	}
	
	fin.close();
}

//  1 < -- Number of Wave
//
//	1 < -- number of enemy pattern + bullet pattern
//	Pattern Bool = 1 -> Enemy Pattern, 0 -> Bullet Pattern
//	1 2 20 300 5 0 -1 < --   Pattern Bool, Pattern type, total, width, widthCnt, start timer, kill timer(int)
//	100 100 -5 0 0 0 0 < --  Position, Velocity, Acceleration(Vector2f)

void LevelReader::gotoWave(int idWave)
{
	for (int i = 0; i <= idWave; i++)
	{
		WaveData.pop();
		WavePosition.pop();
		WaveVelocity.pop();
		WaveAcceleration.pop();
	}
}

void LevelReader::gotoNextWave()
{
	WaveData.pop();
	WavePosition.pop();
	WaveVelocity.pop();
	WaveAcceleration.pop();
}

void LevelReader::pushEmptyWave()
{
	std::vector <std::vector <int>> patternData;
	std::vector <sf::Vector2f> patternPosition;
	std::vector <sf::Vector2f> patternVelocity;
	std::vector <sf::Vector2f> patternAcceleration;

	WaveData.push(patternData);
	WavePosition.push(patternPosition);
	WaveVelocity.push(patternVelocity);
	WaveAcceleration.push(patternAcceleration);
}

void LevelReader::cleanLevel()
{
	while (!WaveData.empty())
	{
		WaveData.pop();
		WavePosition.pop();
		WaveVelocity.pop();
		WaveAcceleration.pop();
	}
}

bool LevelReader::isLevelFinished()
{
	return WaveData.empty();
}

bool LevelReader::isWaveFinished()
{
	if (WaveData.empty()) return true;
	return WaveData.front().empty();
}

void LevelReader::clearPattern(int id)
{
	if (WaveData.empty()) return;

	WaveData.front().erase(WaveData.front().begin() + id);
	WavePosition.front().erase(WavePosition.front().begin() + id);
	WaveVelocity.front().erase(WaveVelocity.front().begin() + id);
	WaveAcceleration.front().erase(WaveAcceleration.front().begin() + id);
}
