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

	bool isFinalWave();

	void pushEmptyWave();

	bool clearEnemyPattern(int id);
	bool clearBulletPattern(int id);

	int waveCount = 0;

	std::queue <std::vector <std::vector <int>>> EnemyWaveData;	// enemyType, patternType, rotationType, total, width, widthCnt, start timer, kill timer(int)
	std::queue <std::vector <std::vector <sf::Vector2f>>> EnemyWaveAttribute; // Position, Velocity, Acceleration
	std::queue <std::vector <ii> > EnemyWaveLoop; // LoopCnt, LoopTimer(int)
	std::queue <std::vector <int>> EnemyWaveTimerMax;	// timerMax (first timerStart)

	std::queue <std::vector <std::vector <int>>> BulletWaveData;	// bulletType, patternType, rotationType, total, width, widthCnt, start timer, kill timer(int)
	std::queue <std::vector <std::vector <sf::Vector2f>>> BulletWaveAttribute; // Position, Velocity, Acceleration
	std::queue <std::vector <ii> > BulletWaveLoop;	// LoopCnt, LoopTimer(int)
	std::queue <std::vector <bool>> BulletWavePhysic;	// have physic
	std::queue <std::vector <int>> BulletWaveTimerMax;	// timerMax (first timerStart)

};

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
