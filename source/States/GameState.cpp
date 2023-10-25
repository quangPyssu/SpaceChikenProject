#include "GameState.h"

GameState::GameState(State& parentState,RenderWindow& window) : State(window)
{
	this->parentState = &parentState;

	ResourceManager::unloadTexture("TerraTop.png");
	ResourceManager::unloadTexture("NeutronStar.png");
	textureBack = ResourceManager::getTexture("Blue_Blank_Background.png");
	backgroundSprite.setTexture(textureBack);
	backgroundSprite.setScale(getScale::getScaleMax(sf::Vector2f(backgroundSprite.getTextureRect().width, backgroundSprite.getTextureRect().height), Constants::WINDOW_SIZE));


	player = new Player(); 

	EnimesBullets = new BulletManager(*player);

	PushToObject(EnimesBullets, this);
	PushToObject(player,this);

	PlayerBullets_Standard = new BulletManager(*player);
	PushToObject(PlayerBullets_Standard, this);

	PlayerBullets_Detroyer = new BulletManager(*player);
	PlayerBullets_Detroyer->addTarget(*EnimesBullets);

	PushToObject(PlayerBullets_Detroyer, this);	

	PBplayerHealth = new ProgressBar({ 10,WINDOW_SIZE.y-20 },Vector2f(WINDOW_SIZE.x-20,20), Colors::green,Colors::grey,"HP",player->HitPoints,PlayerMaxHP);
	PushToObject(PBplayerHealth, this);

	for (int i = 0; i < 10; i++)
	{
		enemy.push_back(new Enemy(Enemy_Chicken_1, Vector2f(rand()%1000, 100)));
		PushToObject(enemy.back(), this);
	}

	{	//Target setting
		for (int i = 0; i < enemy.size(); i++)
		{
			PlayerBullets_Standard->addTarget(*enemy[i]);
			PlayerBullets_Detroyer->addTarget(*enemy[i]);
		}

		EnimesBullets->addTarget(*player);
	}

	window.setMouseCursorVisible(false);
}

GameState::~GameState()
{
	ResourceManager::unloadTexture("Blue_Blank_Background.png");
	ResourceManager::unloadTexture("Battlecruiser_Base.png");
	ResourceManager::unloadTexture("FireJet.png");
	ResourceManager::unloadTexture("Bullet.png");
	window->setMouseCursorVisible(true);
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

	//cout << player->CurrentEnityState << endl;
	if (player->CurrentEnityState == EntityState::Dead) // Game Over
	{
		CurrentState = States::GameOver;
		window->setMouseCursorVisible(true);
		return;
	}
	
	if (player->isFiring)	// Player Fire
	{
		PlayerBullets_Standard->addBullet(Player_Bullet_Normal, player->getPosition() - Vector2f(0,30));
		player->resetGun();
	} 

	if (player->isSpecialing)	// Player Special
	{
		PlayerBullets_Detroyer->addBullet(Player_Laser_Destroyer, player->getPosition() + Vector2f(0,10));
		player->resetSpecial();
	}

	for (int i = 0; i < enemy.size(); i++)	// Enemy Fire
	{
		if (enemy[i]->CurrentEnityState == EntityState::Dead)
		{
			// Detach the child
			this->detachChild(*enemy[i]);

			PlayerBullets_Standard->removeTarget(*enemy[i]);
			PlayerBullets_Detroyer->removeTarget(*enemy[i]);

			// Erase it from the enemy vector
			enemy.erase(enemy.begin() + i);
			i--; 
		}
		else if (enemy[i]->CurrentEnityState == EntityState::Alive && enemy[i]->isFiring)
		{
			EnimesBullets->addBullet(Enemy_Bullet_Normal, enemy[i]->getPosition());
			enemy[i]->resetGun();
		}
	}

	//cout << enemy.size() << endl;
	//cout << "PlayerBullets_Standard->getBulletCount() " << PlayerBullets_Standard->getBulletCount() << endl;
	//cout << "PlayerBullets_Detroyer->getBulletCount() " << PlayerBullets_Detroyer->getBulletCount() << endl;
	//cout << "EnimesBullets->getBulletCount() " << EnimesBullets->getBulletCount() << endl;cout << endl;
}