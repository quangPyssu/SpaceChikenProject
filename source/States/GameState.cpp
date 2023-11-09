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

	BulletFilter[Enemy_Bullet_Normal] = 0;
	BulletFilter[Astroid] = 1;
	BulletFilter[Player_Bullet_Normal] = 2;
	BulletFilter[Player_Laser_Destroyer] = 3;
	BulletFilter[Player_Bullet_Destroyer] = 3;

	player = new Player(); 

	EnimesBullets = new BulletManager(*player);
	EnimesBullets_Vulnerable = new BulletManager(*player);
	PlayerBullets_Standard = new BulletManager(*player);
	PlayerBullets_Detroyer = new BulletManager(*player);

	PlayerBullets_Detroyer->addTarget(*EnimesBullets);
	PlayerBullets_Detroyer->addTarget(*EnimesBullets_Vulnerable);
	PlayerBullets_Standard->addTarget(*EnimesBullets_Vulnerable);	

	warningZone = new WarningZone();

	enemyManager = new EnemyManager(*player, *PlayerBullets_Standard, *PlayerBullets_Detroyer, *EnimesBullets,*EnimesBullets_Vulnerable,*warningZone);

	PushToObject(enemyManager, this);
	PushToObject(EnimesBullets, this);
	PushToObject(EnimesBullets_Vulnerable, this);
	PushToObject(player,this);	
	PushToObject(PlayerBullets_Standard, this);
	PushToObject(PlayerBullets_Detroyer, this);	

	//BulletManagerList.push_back(EnimesBullets); BulletManagerList.push_back(EnimesBullets_Vulnerable);
	//BulletManagerList.push_back(PlayerBullets_Standard); BulletManagerList.push_back(PlayerBullets_Detroyer);

	PBplayerHealth = new ProgressBar({ 10,WINDOW_SIZE.y-20 },Vector2f(WINDOW_SIZE.x-20,20), Colors::green,Colors::grey,"HP",player->HitPoints,PlayerMaxHP);
	PushToObject(PBplayerHealth, this);	
	PushToObject(warningZone, this);

	window.setMouseCursorVisible(false);

	//cout << "CurrentLevel " << CurrentLevel << endl;
	levelReader.ReadLevel(CurrentLevel);

	{
		//enemyManager->addEnemy(EnemyType::Boss_Chicken_1);
		//addEnemyPattern(EnemyType::Boss_Chicken_1, PatternType::None, RotationType::defaultRotation, { 400,100 }, { 10,0 }, { -1,-1 }, 1, 0, 1);
		//addEnemyPattern(Chicken_Circle, { 400,100 }, { 10,0 }, {-1,-1}, 10, 10, 7);
		//addEnemyPattern(Chicken_Square, { 400,100 }, { -10,0 }, { -1,-1 }, 21, 400, 7);
		//enemyManager->addBulletPattern(Enemy_Normal_Square, { 400,100 }, { 10,0 }, { -1,-1 }, 30, 200, 10);
		//enemyManager->addBulletPattern(Enemy_Normal_Circle, { 400,100 }, {-10,0 }, { -1,-1 }, 30, 200, 1);
		//enemyManager->addBulletPattern(Astroid_Shower, { 0,0 }, { 5,5 }, { 0,0 }, 5, 300, 1, 0, -1);
		//enemyManager->addBulletPattern(Enemy_Normal_Firework, { 400,100 }, { 20,20 }, { -5,-5 }, 30, 0, 1);
		//enemyManager->addBulletPattern(Enemy_Normal_Shower, { 0,0 }, { 20,20 }, { 0,0 }, 25, 300, 1);
	}

	parentState.music->stop();

	//music = new Music();
	//music->openFromFile(Constants::GameMusicTrack[CurrentLevel][0]);
	//music->setLoop(true);
	//music->play();
	//music->setLoopPoints(sf::Music::TimeSpan(sf::seconds(20), music->getDuration()));

	playMusic(Constants::GameMusicTrack[CurrentLevel][0], Constants::GameMusicOffset[CurrentLevel][0]);

	//make music play from start the first time then loop back to specified offset
}

GameState::~GameState()
{
	ResourceManager::unloadTexture("Blue_Blank_Background.png");
	ResourceManager::unloadTexture("Battlecruiser_Base.png");
	ResourceManager::unloadTexture("FireJet.png");
	ResourceManager::unloadTexture("Bullet.png");
	ResourceManager::unloadTexture("Enemy_Bullet.png");
	ResourceManager::unloadTexture("ChickenBody.png");

	window->setMouseCursorVisible(true);

	BulletManagerList.clear();

	music->stop();
	delete music;

	parentState->music->play();
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

			if (levelReader.isFinalWave()) // Level Complete
			{
				cout << "Level Complete" << endl;

				playMusic(Constants::GameMusicTrack[CurrentLevel][1], Constants::GameMusicOffset[CurrentLevel][1]);
			}
		}
	}

	readWaveQueue();
	readAttackQueue();

	BGLoop();

	// Clean up the dead Enemy patterns	

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
	backgroundSprite.move(0.0f, scrollSpeed * TIME_PER_FRAME.asSeconds());
	if (backgroundSprite.getPosition().y >= 0) backgroundSprite.setPosition(0.0f, WINDOW_SIZE.y - BGHeight * SCALE);
}