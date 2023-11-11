#pragma once
#include "State.h"
#include "../Tools/LevelReader.h"
#include "../Tools/ProgressBar.h"
#include "../Entiy/Enemy.h"
#include "../Entiy/Bullet.h"
#include "../Entiy/Player.h"


class LoadScreen : public State
{
	public:
	LoadScreen(State& parentState);
	~LoadScreen();

	vector <string> textureList;

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void takeTimeCurrent() override;

	LevelReader levelReader;

	private:
		ProgressBar* progressBar;
		int loadProgress = 0;
		int loadProgressMax = 100;

		void loadPlayer();

		sf::Sprite backgroundSprite;

		//Thread* loadThread;
};

