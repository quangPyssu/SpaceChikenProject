#pragma once
#include "../Core/Global.h"
#include <iostream>
#include <fstream>

class LevelReader 
{
public:
	void ReadLevel(int id);
	void gotoWave(int idWave);
	void gotoNextWave();

	void cleanLevel();

	bool isLevelFinished();
	bool isWaveFinished();

	void pushEmptyWave();

	void clearPattern(int id);

	int waveCount = 0;

	std::queue <std::vector <std::vector <int>>> WaveData;
	std::queue <std::vector <sf::Vector2f>> WavePosition;
	std::queue <std::vector <sf::Vector2f>> WaveVelocity;
	std::queue <std::vector <sf::Vector2f>> WaveAcceleration;
};

//	1 < -- - Number of Wave
//
//	300 < -- break time
//	1 < -number of enemy pattern + bullet pattern
//
//	//Title
//
//	1 2 10 300 5 0 - 1 <--  Pattern Bool, Pattern type, total, width, widthCnt, start timer, kill timer
//  100 100 -5 0 0 0 0 <-- Position, Velocity, Acceleration
