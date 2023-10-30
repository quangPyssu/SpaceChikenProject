#include "GameState.h"

GameState::GameState(State& parentState,RenderWindow& window) : State(window)
{
	this->parentState = &parentState;

	ResourceManager::unloadTexture("TerraTop.png");
	ResourceManager::unloadTexture("NeutronStar.png");
	textureBack = ResourceManager::getTexture("Blue_Blank_Background.png");

	BGHeight = textureBack.getSize().y;

	backgroundSprite.setTexture(textureBack);
	backgroundSprite.setScale(getScale::getScaleMax(sf::Vector2f(backgroundSprite.getTextureRect().width, backgroundSprite.getTextureRect().height), Constants::WINDOW_SIZE));
	backgroundSprite.setPosition(0.0f, WINDOW_SIZE.y - BGHeight * SCALE );

	player = new Player(); 

	EnimesBullets = new BulletManager(*player);
	EnimesBullets_Vulnerable = new BulletManager(*player);
	EnimesBullets_Indestructible = new BulletManager(*player);
	PlayerBullets_Standard = new BulletManager(*player);
	PlayerBullets_Detroyer = new BulletManager(*player);

	PlayerBullets_Detroyer->addTarget(*EnimesBullets);
	PlayerBullets_Detroyer->addTarget(*EnimesBullets_Vulnerable);
	PlayerBullets_Standard->addTarget(*EnimesBullets_Vulnerable);

	enemyManager = new EnemyManager(*player, *PlayerBullets_Standard, *PlayerBullets_Detroyer, *EnimesBullets,*EnimesBullets_Vulnerable,*EnimesBullets_Indestructible);

	PushToObject(enemyManager, this);
	PushToObject(EnimesBullets, this);
	PushToObject(EnimesBullets_Vulnerable, this);
	PushToObject(EnimesBullets_Indestructible, this);
	PushToObject(player,this);	
	PushToObject(PlayerBullets_Standard, this);
	PushToObject(PlayerBullets_Detroyer, this);	

	PBplayerHealth = new ProgressBar({ 10,WINDOW_SIZE.y-20 },Vector2f(WINDOW_SIZE.x-20,20), Colors::green,Colors::grey,"HP",player->HitPoints,PlayerMaxHP);
	PushToObject(PBplayerHealth, this);

	warningZone = new WarningZone();
	PushToObject(warningZone, this);

	window.setMouseCursorVisible(false);

	//cout << "CurrentLevel " << CurrentLevel << endl;
	levelReader.ReadLevel(CurrentLevel);

	{
		//addEnemyPattern(Chicken_Circle, { 400,100 }, { 10,0 }, {-1,-1}, 10, 10, 7);
		//addEnemyPattern(Chicken_Square, { 400,100 }, { -10,0 }, { -1,-1 }, 21, 400, 7);
		//addBulletPattern(Enemy_Normal_Square, { 400,100 }, { 10,0 }, { -1,-1 }, 30, 200, 10);
		//addBulletPattern(Enemy_Normal_Circle, { 400,100 }, {-10,0 }, { -1,-1 }, 30, 200, 1);
		//BulletPatternList.back()->setTimer(0,600);
		//addBulletPattern(Enemy_Normal_Firework, { 400,100 }, { 20,20 }, { -5,-5 }, 30, 0, 1);
		//addBulletPattern(Enemy_Normal_Shower, { 0,0 }, { 20,20 }, { 0,0 }, 25, 300, 1);
	}
}

GameState::~GameState()
{
	ResourceManager::unloadTexture("Blue_Blank_Background.png");
	ResourceManager::unloadTexture("Battlecruiser_Base.png");
	ResourceManager::unloadTexture("FireJet.png");
	ResourceManager::unloadTexture("Bullet.png");
	window->setMouseCursorVisible(true);
}

void GameState::addEnemyPattern(EnemyPatternType type, Vector2f Position, Vector2f Velocity, Vector2f Acceleration, 
	int total, float width, int widthCnt)
{
	EnemyPatternList.push_back(new EnemyPattern(type, *enemyManager, Position, Velocity, Acceleration, total, width, widthCnt));
	PushToObject(EnemyPatternList.back(), this);
}

void GameState::addBulletPattern(BulletPatternType type, Vector2f Position, Vector2f Velocity, Vector2f Acceleration, 
	int total, float width, int widthCnt, int timerStart, int timerEnd)
{
	BulletPatternList.push_back(new BulletPattern(type, *EnimesBullets, Position, Velocity, Acceleration, total, width, widthCnt,*warningZone,timerStart,timerEnd));
	PushToObject(BulletPatternList.back(), this);
}

void GameState::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite); 
}	

void GameState::updateCurrent(Event& event, Vector2f& MousePos)
{
	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
		CurrentState = States::Pause, wasPaused = true;
		window->setMouseCursorVisible(true);
	}
}

void GameState::takeTimeCurrent()
{
	if (wasPaused)
	{
		window->setMouseCursorVisible(false);
		wasPaused = false;

		sf::Vector2i pixelPosition = window->mapCoordsToPixel(player->getPosition());
		sf::Mouse::setPosition(pixelPosition);
	}
	
	if (levelReader.isLevelFinished()) // Level Complete
	{
		CurrentState = States::GameOver;
		//CurrentState = States::LevelComplete;
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
			breakTime = 300;
		}
	}

	readWaveQueue();
	readAttackQueue();

	BGLoop();

	// Clean up the dead patterns

	for (int i = 0; i < BulletPatternList.size(); i++)
	{
		if (BulletPatternList[i]->CurrentEnityState == EntityState::Dead)
		{
			detachChild(*BulletPatternList[i]);
			BulletPatternList.erase(BulletPatternList.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < EnemyPatternList.size(); i++)
	{
		if (EnemyPatternList[i]->CurrentEnityState == EntityState::Dead)
		{
			detachChild(*EnemyPatternList[i]);
			EnemyPatternList.erase(EnemyPatternList.begin() + i);
			i--;
		}
	}

	{
		//cout << enemyManager->enemy.size() << endl;
		//cout << "PlayerBullets_Standard->getBulletCount() " << PlayerBullets_Standard->getBulletCount() << endl;
		//cout << "PlayerBullets_Detroyer->getBulletCount() " << PlayerBullets_Detroyer->getBulletCount() << endl;
		//cout << "EnimesBullets->getBulletCount() " << EnimesBullets->getBulletCount() << endl;cout << endl;
		//cout << "BulletPatternList.size() " << BulletPatternList.size() << endl;
		//cout << "EnemyPatternList.size() " << EnemyPatternList.size() << endl;
	}
}

void GameState::readAttackQueue()
{
	if (player->isFiring)	// Player Fire
	{
		PlayerBullets_Standard->addBullet(Player_Bullet_Normal, player->getPosition() - Vector2f(0, 30));
		player->resetGun();
	}

	if (player->isSpecialing)	// Player Special
	{
		PlayerBullets_Detroyer->addBullet(Player_Laser_Destroyer, player->getPosition() + Vector2f(0, 10));
		player->resetSpecial();
	}

	while (!enemyManager->AttackQueueType.empty())
	{
		EnemyAttackType tmp = enemyManager->AttackQueueType.front();
		Vector2f pos = enemyManager->AttackQueuePosition.front();

		switch (tmp)
		{
			case EnemyAttackType::Attack_Chicken_1:
			{
				EnimesBullets->addBullet(BulletType::Enemy_Bullet_Normal, pos);
				//addBulletPattern(Enemy_Normal_Circle, Vector2f(pos.x/SCALE,pos.y/SCALE), { 0,20 }, { 0,0 }, 3, 20, 1);
			}
			break;


		}
		enemyManager->AttackQueueType.pop();
		enemyManager->AttackQueuePosition.pop();
	}
}

void GameState::readWaveQueue()
{
	if (levelReader.isLevelFinished()) // Level is empty
		return;
	
	for (int i = 0; i < levelReader.WaveData.front().size(); i++)
	{
		//cout << levelReader.WaveData.front().size() << endl;
		levelReader.WaveData.front()[i][5] = max(0, levelReader.WaveData.front()[i][5] - 1);
		
		if (levelReader.WaveData.front()[i][5] <= 0) // Time to add a new pattern with WaveData, WavePosition, WaveVelocity, WaveAcceleration;
		{
			if (levelReader.WaveData.front()[i][0])	// Enemy Pattern
			{
				addEnemyPattern((EnemyPatternType)levelReader.WaveData.front()[i][1], levelReader.WavePosition.front()[i], levelReader.WaveVelocity.front()[i],
					levelReader.WaveAcceleration.front()[i], levelReader.WaveData.front()[i][2], levelReader.WaveData.front()[i][3],
					levelReader.WaveData.front()[i][4]);
				EnemyPatternList.back()->setTimer(0, levelReader.WaveData.front()[i][6]);
			}
			else  // Bullet Pattern
			{
				addBulletPattern((BulletPatternType)levelReader.WaveData.front()[i][1], levelReader.WavePosition.front()[i], levelReader.WaveVelocity.front()[i],
					levelReader.WaveAcceleration.front()[i], levelReader.WaveData.front()[i][2], levelReader.WaveData.front()[i][3],
					levelReader.WaveData.front()[i][4], levelReader.WaveLoop.front()[i].ss/5, levelReader.WaveData.front()[i][6]);
				//BulletPatternList.back()->setTimer();
			}

			if (levelReader.WaveLoop.front()[i].ff)
			{
				levelReader.WaveLoop.front()[i].ff--;
				levelReader.WaveData.front()[i][5] = levelReader.WaveLoop.front()[i].ss;
			}
			else
			{
				if (levelReader.clearPattern(i)) i--;
			}
		}
	}
}

bool GameState::isWaveEmpty()
{
	return (levelReader.isWaveFinished() && EnemyPatternList.empty());
}

void GameState::BGLoop()
{
	backgroundSprite.move(0.0f, scrollSpeed * TIME_PER_FRAME.asSeconds());
	if (backgroundSprite.getPosition().y >= 0) backgroundSprite.setPosition(0.0f, WINDOW_SIZE.y - BGHeight * SCALE);
}