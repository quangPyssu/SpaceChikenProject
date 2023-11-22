#include "GameState.h"

GameState::GameState(State& parentState, RenderWindow& window) : State(window)
{
	this->parentState = &parentState;
	textureBack = ResourceManager::getTexture("Blue_Blank_Background.png");

	BGHeight = textureBack.getSize().y/0.947;

	backgroundSprite.setTexture(textureBack);
	backgroundSprite.setScale(getScale::getScaleMax(sf::Vector2f(backgroundSprite.getTextureRect().width*0.9, 
		backgroundSprite.getTextureRect().height), Constants::WINDOW_SIZE));
	backgroundSprite.setPosition(SCALE*(- 10), WINDOW_SIZE.y - BGHeight * SCALE);

	{
		player = new Player();

		PlayerBullets_Standard = new BulletManager(*player);
		PlayerBullets_Detroyer = new BulletManager(*player);

		enemyManager = new EnemyManager(*player, *PlayerBullets_Standard, *PlayerBullets_Detroyer);

		PushToObject(enemyManager, this);
		PushToObject(player, this);
		PushToObject(PlayerBullets_Standard, this);
		PushToObject(PlayerBullets_Detroyer, this);

		PBplayerHealth = new ProgressBar({ 10,WINDOW_SIZE.y - 20 }, Vector2f(WINDOW_SIZE.x - 20, 20), Colors::green, Colors::grey, "HP", player->HitPoints, player->HitPointsMax);
		PushToObject(PBplayerHealth, this);

		//PBplayerSpecial = new ProgressBar({ 10,WINDOW_SIZE.y - 50 }, Vector2f(WINDOW_SIZE.x/3, 10), Colors::yellow, Colors::grey, "SP", player->specialFrameID, player->specialFrameIDMax);
		PBplayerSpecial = new ProgressBar({ 10,WINDOW_SIZE.y - 35 }, Vector2f(WINDOW_SIZE.x / 3, 15), Colors::yellow, Colors::grey, "SP", player->specialFrameID, player->specialFrameIDMax);
		PushToObject(PBplayerSpecial, this);

		levelReader.ReadLevel(CurrentLevel);

		SubTitle* LevelName = new SubTitle({ 0,WINDOW_SIZE.y / 3 }, Vector2f(WINDOW_SIZE.x, 200), tran_Grey, { 0.2,0.4 }, 20, white, levelReader.levelName, "neuro", 600);
		SubTitleList.push_back(LevelName);
		PushToObject(SubTitleList.back(), this);

		if (CurrentLevel == 0)
		{
			LevelName = new SubTitle({ 0,WINDOW_SIZE.y / 10 }, Vector2f(WINDOW_SIZE.x/8, WINDOW_SIZE.y / 8), trans, { 0.2,0.4 }, 13, yellow
				, "Use MOUSE to move, LEFT CLICK to shoot", "neuro", 400);
			SubTitleList.push_back(LevelName);
			PushToObject(SubTitleList.back(), this);
		}

		if (CurrentLevel == 1)
		{
			LevelName = new SubTitle({ 0,WINDOW_SIZE.y / 10 }, Vector2f(WINDOW_SIZE.x / 8, WINDOW_SIZE.y / 8), trans, { 0.2,0.4 }, 13, yellow
				, "RIGHT CLICK to use ultimate", "neuro", 400);
			SubTitleList.push_back(LevelName);
			PushToObject(SubTitleList.back(), this);
		}
	}

	window.setMouseCursorVisible(false);
	originalView = window.getView();

	playMusic(Constants::GameMusicTrack[CurrentLevel][0], Constants::GameMusicOffset[CurrentLevel][0]);
}

GameState::~GameState()
{
	window->setMouseCursorVisible(true);
	//set normal view
	window->setView(originalView);
}

void GameState::addEnemyPattern(EnemyType type, PatternType patternType, RotationType rotationType, Vector2f Position, Vector2f Velocity, Vector2f Acceleration,
	int total, float width, int widthCnt)
{
	EnemyPatternList.push_back(new EnemyPattern(type,patternType, rotationType, *enemyManager, Position, Velocity, Acceleration, total, width, widthCnt));
	PushToObject(EnemyPatternList.back(), this);
}

void GameState::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite); 
}	

void GameState::updateCurrent(Event& event, Vector2f& MousePos)
{
	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || event.type == sf::Event::LostFocus)
	{
		CurrentState = States::Pause, wasPaused = true;
		window->setMouseCursorVisible(true);
	}
}

void GameState::takeTimeCurrent()
{
	if (wasPaused)
	{
		window->setMouseCursorVisible(false);wasPaused = false;

		sf::Vector2i pixelPosition = window->mapCoordsToPixel(player->getPosition());
		sf::Mouse::setPosition(pixelPosition);
	}
	
	if (levelReader.isLevelFinished()) // Level Complete
	{
		CurrentState = States::LevelComplete;
		if (CurrentLevel == 4) CurrentState = States::Credit;
		window->setMouseCursorVisible(true);
		return;
	}

	if (player->CurrentEnityState == EntityState::Dead) // Game Over
	{
		CurrentState = States::GameOver;
		window->setMouseCursorVisible(true);
		return;
	}

	if (isWaveEmpty())
	{
		breakTime--;

		if (breakTime <= 0)
		{
			Constants::CurrentWave++;
			levelReader.gotoNextWave();
			breakTime = breakTimeMax;

			if (levelReader.isFinalWave())
			{
				playMusic(Constants::GameMusicTrack[CurrentLevel][1], Constants::GameMusicOffset[CurrentLevel][1]);
				isBGScrolling = false;
					
				SubTitle* FinalWave = new SubTitle({ 0,WINDOW_SIZE.y / 3 + 200 }, Vector2f(WINDOW_SIZE.x, 200), tran_Grey, { 0.2,0.4 }, 20, white, "Final Wave", "neuro", 600);
				SubTitleList.push_back(FinalWave);
				PushToObject(SubTitleList.back(), this);				
			}
		}		
	}

	readWaveQueue();
	readAttackQueue();

	BGLoop();

	if (ShakeDuration > 0)
	{
		ShakeDuration--;
		window->setView(shakeView(10));
	}
	else window->setView(originalView);

	// Clean up the dead Enemy patterns	& subTitles

	for (int i = 0; i < EnemyPatternList.size(); i++)
	{
		if (EnemyPatternList[i]->CurrentEnityState == EntityState::Dead)
		{
			detachChild(*EnemyPatternList[i]);
			EnemyPatternList.erase(EnemyPatternList.begin() + i);i--;
		}
	}

	for (int i = 0; i < SubTitleList.size(); i++)
	{
		if (SubTitleList[i]->isDead())
		{
			detachChild(*SubTitleList[i]);
			SubTitleList.erase(SubTitleList.begin() + i);i--;
		}
	}
}

void GameState::readAttackQueue()
{
	if (player->isFiring)	// Player Fire
	{
		switch (EquipedWeapon[player->getCurrentWeapon()])
		{
		case 0:
		{	PlayerBullets_Standard->addBullet(BulletType_Player_Normal, player->getPosition() - Vector2f(0, 30));}
		break;

		case 1:
		{	PlayerBullets_Standard->addBullet(BulletType_Player_Laser_Normal, player->getPosition() + Vector2f(0, 10));}
		break;		

		case 2: 
		{	PlayerBullets_Standard->addBullet(BulletType_Player_Minigun, player->getPosition() - Vector2f(0, 30));	}
		break;
		}	
		player->resetGun();
	}

	if (player->isSpecialing)	// Player Special
	{
		switch (CurrentSpecial)
		{
		case 0: // shoot fan shape bullets
		{
			for (int i = 0; i < 5; i++)
			{
				PlayerBullets_Standard->addBullet(BulletType_Player_Normal, player->getPosition() - Vector2f(0, 30));
				PlayerBullets_Standard->BulletList.back()->setRotation((i - 2) * 10);
				PlayerBullets_Standard->BulletList.back()->setVelocity(player->AngleShift({0,-400}, (i - 2) * 10));
			}
			player->resetSpecial();
			player->makeSuperFlicker(50);
		}
		break;

		case 1: // shoot big laser
		{
			PlayerBullets_Detroyer->addBullet(BulletType_Player_Laser_Destroyer, player->getPosition() + Vector2f(0, 10));
			player->resetSpecial();
			player->makeSuperFlicker(100);

			//shake the screen
			ShakeDuration = 350;
		}
		break;

		case 2: // activate shield and ram
		{
			PlayerBullets_Detroyer->addBullet(BulletType_Player_Ram_Destroyer, player->getPosition() + Vector2f(0, 0));
			player->resetSpecial();
			player->makeSuperFlicker(700);
			//heal 50
			player->HitPoints = min(player->HitPointsMax, player->HitPoints + 50);
		}
		break;
		}

		
	}
}

void GameState::readWaveQueue()
{
	if (levelReader.isLevelFinished()) return;
	
	for (int i = 0; i < levelReader.EnemyWaveData.front().size(); i++)
	{
		levelReader.EnemyWaveData.front()[i][6] = max(0, levelReader.EnemyWaveData.front()[i][6] - 1);

		if (!levelReader.EnemyWaveData.front()[i][6]) // add new enemy wave
		{
			EnemyType type = static_cast<EnemyType>(levelReader.EnemyWaveData.front()[i][0]);
			PatternType patternType = static_cast<PatternType>(levelReader.EnemyWaveData.front()[i][1]);
			RotationType rotationType = static_cast<RotationType>(levelReader.EnemyWaveData.front()[i][2]);
			Vector2f Position = Vector2f(levelReader.EnemyWaveAttribute.front()[i][0].x, levelReader.EnemyWaveAttribute.front()[i][0].y);
			Vector2f Velocity = Vector2f(levelReader.EnemyWaveAttribute.front()[i][1].x, levelReader.EnemyWaveAttribute.front()[i][1].y);
			Vector2f Acceleration = Vector2f(levelReader.EnemyWaveAttribute.front()[i][2].x, levelReader.EnemyWaveAttribute.front()[i][2].y);
			int total = levelReader.EnemyWaveData.front()[i][3];
			float width = levelReader.EnemyWaveData.front()[i][4];
			int widthCnt = levelReader.EnemyWaveData.front()[i][5];

			addEnemyPattern(type, patternType, rotationType, Position, Velocity, Acceleration, total, width, widthCnt);
			EnemyPatternList.back()->setTimer(levelReader.EnemyWaveTimerMax.front()[i], levelReader.EnemyWaveData.front()[i][7]);

			if (levelReader.EnemyWaveLoop.front()[i].ff)
			{
				levelReader.EnemyWaveLoop.front()[i].ff--;
				levelReader.EnemyWaveData.front()[i][6] = levelReader.EnemyWaveLoop.front()[i].ss;
			}
			else if (levelReader.clearEnemyPattern(i)) i--;
		}		
	}

	for (int i = 0; i < levelReader.BulletWaveData.front().size(); i++)
	{
		levelReader.BulletWaveData.front()[i][6] = max(0, levelReader.BulletWaveData.front()[i][6] - 1);

		if (!levelReader.BulletWaveData.front()[i][6]) // add new bullet wave
		{
			BulletType type = static_cast<BulletType>(levelReader.BulletWaveData.front()[i][0]);
			PatternType patternType = static_cast<PatternType>(levelReader.BulletWaveData.front()[i][1]);
			RotationType rotationType = static_cast<RotationType>(levelReader.BulletWaveData.front()[i][2]);
			Vector2f Position = Vector2f(levelReader.BulletWaveAttribute.front()[i][0].x, levelReader.BulletWaveAttribute.front()[i][0].y);
			Vector2f Velocity = Vector2f(levelReader.BulletWaveAttribute.front()[i][1].x, levelReader.BulletWaveAttribute.front()[i][1].y);
			Vector2f Acceleration = Vector2f(levelReader.BulletWaveAttribute.front()[i][2].x, levelReader.BulletWaveAttribute.front()[i][2].y);
			bool Physics = levelReader.BulletWavePhysic.front()[i];
			int total = levelReader.BulletWaveData.front()[i][3];
			float width = levelReader.BulletWaveData.front()[i][4];
			int widthCnt = levelReader.BulletWaveData.front()[i][5];
			int timerStart = levelReader.BulletWaveTimerMax.front()[i];
			int timerEnd = levelReader.BulletWaveData.front()[i][7];

			enemyManager->addBulletPattern(type, patternType, rotationType, Position, Velocity, Acceleration, Physics, total, width, widthCnt, timerStart, timerEnd,SCALE);

			if (levelReader.BulletWaveLoop.front()[i].ff)
			{
				levelReader.BulletWaveLoop.front()[i].ff--;
				levelReader.BulletWaveData.front()[i][6] = levelReader.BulletWaveLoop.front()[i].ss;
			}
			else if (levelReader.clearBulletPattern(i)) i--;
		}		
	}
}

bool GameState::isWaveEmpty()
{
	return (levelReader.isWaveFinished() && EnemyPatternList.empty());
}

void GameState::BGLoop()
{
	if (!isBGScrolling) return;
	backgroundSprite.move(0.0f, scrollSpeed * TIME_PER_FRAME.asSeconds());
	if (backgroundSprite.getPosition().y >= 0) backgroundSprite.setPosition(SCALE * (-10) , WINDOW_SIZE.y - BGHeight * SCALE);
}