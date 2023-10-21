#include "GameState.h"

GameState::GameState() 
{
	ResourceManager::unloadTexture("TerraTop.png");
	ResourceManager::unloadTexture("NeutronStar.png");
	textureBack = ResourceManager::getTexture("Blue_Blank_Background.png");
	backgroundSprite.setTexture(textureBack);
	backgroundSprite.setScale(getScale::getScaleMax(sf::Vector2f(backgroundSprite.getTextureRect().width, backgroundSprite.getTextureRect().height), Constants::WINDOW_SIZE));

	EnimesBullets = new BulletManager();
	PushToObject(EnimesBullets, this);

	player = new Player(); 
	PushToObject(player,this);

	PlayerBullets_Standard = new BulletManager();
	PushToObject(PlayerBullets_Standard, this);

	PlayerBullets_Detroyer = new BulletManager();
	PushToObject(PlayerBullets_Detroyer, this);	
}

GameState::~GameState()
{
	ResourceManager::unloadTexture("Blue_Blank_Background.png");
}

void GameState::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite); 
}	

void GameState::updateCurrent(Event& event, Vector2f& MousePos)
{
	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) isDead = true;

	
}

void GameState::takeTimeCurrent()
{
	if (player->isFiring)
	{
		PlayerBullets_Standard->addBullet(Normal, player->getPosition()-Vector2f(0,30));
		player->resetGun();
	} 

	//cout << "PlayerBullets_Standard->getBulletCount() " << PlayerBullets_Standard->getBulletCount() << endl;
}