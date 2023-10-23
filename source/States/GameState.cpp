#include "GameState.h"

GameState::GameState(State& parentState)
{
	this->parentState = &parentState;

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

	for (int i = 0; i < 2; i++)
	{
		enemy.push_back(new Enemy(Enemy_Chicken_1, Vector2f(rand()%1000, 100)));
		PushToObject(enemy.back(), this);
	}

	{	//Target setting
		for (int i = 0; i < enemy.size(); i++) PlayerBullets_Standard->addTarget(*enemy[i]);

		EnimesBullets->addTarget(*player);
	}
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
	if (wasPaused)
	{
		wasPaused = false;
		cout << "wasPaused" << endl;
	}

	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) CurrentState=States::Pause,wasPaused=true;	
	
}

void GameState::takeTimeCurrent()
{
	//cout << player->CurrentEnityState << endl;
	if (player->CurrentEnityState == EntityState::Dead) // Game Over
	{
		CurrentState = States::GameOver;
		return;
	}
	
	if (player->isFiring)	// Player Fire
	{
		cout << "Player Fire" << endl;
		PlayerBullets_Standard->addBullet(Player_Bullet_Normal, player->getPosition()-Vector2f(0,30));
		player->resetGun();
	} 

	for (auto it = enemy.begin(); it != enemy.end(); ) // Enemy Fire	
	{
		if ((*it)->CurrentEnityState == EntityState::Dead)
		{
			this->detachChild(**it);
			it=enemy.erase(it); 
		}
		else
		{
			if ((*it)->CurrentEnityState == EntityState::Alive && (*it)->isFiring)
			{
				EnimesBullets->addBullet(Enemy_Bullet_Normal, (*it)->getPosition());
				(*it)->resetGun();
			}
			it++;
		}
	}

	//cout << enemy.size() << endl;
	//cout << "PlayerBullets_Standard->getBulletCount() " << PlayerBullets_Standard->getBulletCount() << endl;
	//cout << "EnimesBullets->getBulletCount() " << EnimesBullets->getBulletCount() << endl;cout << endl;
}