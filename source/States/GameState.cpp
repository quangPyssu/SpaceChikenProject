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
	PlayerBullets_Standard = new BulletManager(*player);
	PlayerBullets_Detroyer = new BulletManager(*player);
	PlayerBullets_Detroyer->addTarget(*EnimesBullets);

	enemyManager = new EnemyManager(*player, *PlayerBullets_Standard, *PlayerBullets_Detroyer, *EnimesBullets);

	PushToObject(enemyManager, this);
	PushToObject(EnimesBullets, this);
	PushToObject(player,this);	
	PushToObject(PlayerBullets_Standard, this);
	PushToObject(PlayerBullets_Detroyer, this);	

	PBplayerHealth = new ProgressBar({ 10,WINDOW_SIZE.y-20 },Vector2f(WINDOW_SIZE.x-20,20), Colors::green,Colors::grey,"HP",player->HitPoints,PlayerMaxHP);
	PushToObject(PBplayerHealth, this);

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



	//cout << enemyManager->enemy.size() << endl;
	//cout << "PlayerBullets_Standard->getBulletCount() " << PlayerBullets_Standard->getBulletCount() << endl;
	//cout << "PlayerBullets_Detroyer->getBulletCount() " << PlayerBullets_Detroyer->getBulletCount() << endl;
	//cout << "EnimesBullets->getBulletCount() " << EnimesBullets->getBulletCount() << endl;cout << endl;
}