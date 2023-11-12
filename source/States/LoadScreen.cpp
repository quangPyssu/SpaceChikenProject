#include "LoadScreen.h"

LoadScreen::LoadScreen(State& parentState) 
{
	ResourceManager::unloadTexture("TerraTop.png");
	ResourceManager::unloadTexture("NeutronStar.png");

	backgroundSprite.setTexture(ResourceManager::getTexture("Blue_Background.png"));
	backgroundSprite.setScale(getScale::getScaleMax(sf::Vector2f(backgroundSprite.getTextureRect().width, backgroundSprite.getTextureRect().height), Constants::WINDOW_SIZE));

	parentState.music->stop();

	this->parentState = &parentState;
	//CurrentState = States::Load;	

	levelReader.ReadLevel(CurrentLevel);

	loadProgressMax = levelReader.EnemyWaveData.size();
	loadProgress = 0;

	progressBar = new ProgressBar(Vector2f( 10,WINDOW_SIZE.y - 20 ), Vector2f(WINDOW_SIZE.x - 20, 20), Colors::green, Colors::grey, "Loading", loadProgress,loadProgressMax);
	PushToObject(progressBar, this);

	loadPlayer();

	// here to load attack of Player

}

LoadScreen::~LoadScreen()
{
}

void LoadScreen::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite);
	target.draw(*progressBar);
}

void LoadScreen::takeTimeCurrent()
{
	if (levelReader.EnemyWaveData.size())
	{
		for (int i = 0; i < levelReader.EnemyWaveData.front().size(); i++)
		{
			EnemyType type = static_cast<EnemyType>(levelReader.EnemyWaveData.front()[i][0]);
			Enemy* a = EnemyFactory::createEnemy(type,{0,0});
			delete a;
		}

		for (int i = 0; i < levelReader.BulletWaveData.front().size(); i++)
		{
			BulletType type = static_cast<BulletType>(levelReader.BulletWaveData.front()[i][0]);
			Bullet* a = BulletFactory::createBullet(type, { 0,0 });
			delete a;
		}

		levelReader.EnemyWaveData.pop();
		levelReader.BulletWaveData.pop();
		loadProgress++;
	}
	else
	{
		CurrentState = States::NewGame;
	}
}

void LoadScreen::loadPlayer()
{
	//Player* player = new Player();
	//delete player;

	Texture texture;
	texture = ResourceManager::getTexture("Battlecruiser_Base.png");
	texture = ResourceManager::getTexture("FireJet.png");
	texture = ResourceManager::getTexture("Battlecruiser_Destruction.png");
	texture = ResourceManager::getTexture("Explosion.png");
}