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

	void updateCurrent(Event& event, Vector2f& MousePos) override;

	void takeTimeCurrent() override;

	LevelReader levelReader;

	private:
		Button* btnWeapon;
		Button* btnSpecial;

		vector <Button*> btnWeaponList;
		vector <Button*> btnSpecialList;

		Button* btnContinue;
		Button* btnQuit;


		ProgressBar* progressBar;
		int loadProgress = 0;
		int loadProgressMax = 100;

		bool isLoadComplete = false;

		void loadPlayer();

		sf::Sprite backgroundSprite;

		vector <vector <string>> textureList_Enemy;
		vector <vector <string>> textureList_Bullet;
		vector <vector <string>> textureList_Player;

		vector <vector <string>> soundList_Enemy;
		vector <vector <string>> soundList_Bullet;
		vector <vector <string>> soundList_Player;
		//Thread* loadThread;
};

