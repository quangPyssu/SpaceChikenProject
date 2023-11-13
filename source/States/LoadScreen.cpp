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

	progressBar = new ProgressBar(Vector2f( 10,WINDOW_SIZE.y - 20 ), Vector2f(WINDOW_SIZE.x - 20, 20), Colors::green, Colors::grey, "Load Progress", loadProgress,loadProgressMax);
	PushToObject(progressBar, this);

	btnWeapon = new Button(Vector2f(WINDOW_SIZE.x / 4, 100), Vector2f(100, 100), "Weapon");
	btnWeapon->PushToObject(btnWeapon, this);

	btnSpecial = new Button(Vector2f(WINDOW_SIZE.x / 4, 250), Vector2f(100, 100), "Special");
	btnSpecial->PushToObject(btnSpecial, this);

	btnContinue = new Button(Vector2f(WINDOW_SIZE.x/5*4, 100), Vector2f(200,70), "Continue");
	btnContinue->PushToObject(btnContinue, this);

	btnQuit = new Button(Vector2f(WINDOW_SIZE.x / 5*4, 200), Vector2f(200, 70), "Quit");
	btnQuit->PushToObject(btnQuit, this);
	
	{
		ResourceManager::getTexture("Explosion.png");
		textureList_Enemy.push_back({ "ChickenBody.png","ChickenFace.png","egg.png" });
		textureList_Enemy.push_back({ "ChickenBody.png","BossChickenBody.png","BossChickenBody2.png","BossChickenBody3.png","egg.png" });

		soundList_Enemy.push_back({ "chicken1a(die).ogg","chicken2b(die).ogg","chicken3a(die).ogg" });
		soundList_Enemy.push_back({ "(chickbossCry).ogg","(chickbossDie).ogg" });


		textureList_Bullet.push_back({ "egg.png" });
		textureList_Bullet.push_back({ "Astroid_0.png", "Astroid_1.png" ,"Astroid_2.png","BlueBurn.png" });

		soundList_Bullet.push_back({  });
		soundList_Bullet.push_back({ "rock_0.ogg","rock_1.ogg" });


		textureList_Player.push_back({ "Bullet.png","QuicklyBeam.png" });

		soundList_Player.push_back({ "(laser).ogg","laserSmall.ogg" });
	}
	isLoadComplete = 0;

	// here to load attack of Player
	loadPlayer();
}

LoadScreen::~LoadScreen()
{
}

void LoadScreen::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite);
	target.draw(*progressBar);
}

void LoadScreen::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (btnContinue->isLeftClicked(event, MousePos) && isLoadComplete)
	{
		CurrentState = States::NewGame;
	}

	if (btnQuit->isLeftClicked(event, MousePos) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
		CurrentState = States::KillMe;
		parentState->CurrentState = States::None;
	}
}

void LoadScreen::takeTimeCurrent()
{
	if (levelReader.EnemyWaveData.size())
	{
		for (int i = 0; i < levelReader.EnemyWaveData.front().size(); i++)
		{
			EnemyType type = static_cast<EnemyType>(levelReader.EnemyWaveData.front()[i][0]);
			for (int j = 0; j < textureList_Enemy[type].size(); j++)
				Texture texture = ResourceManager::getTexture(textureList_Enemy[type][j]);
			
			for (int j = 0; j < soundList_Enemy[type].size(); j++)
				SoundBuffer sound = ResourceManager::getSoundBuffer(soundList_Enemy[type][j]);
		
		}

		for (int i = 0; i < levelReader.BulletWaveData.front().size(); i++)
		{
			BulletType type = static_cast<BulletType>(levelReader.BulletWaveData.front()[i][0]);
			for (int j = 0; j < textureList_Bullet[type].size(); j++)
				Texture texture = ResourceManager::getTexture(textureList_Bullet[type][j]);

			for (int j = 0; j < soundList_Bullet[type].size(); j++)
				SoundBuffer sound = ResourceManager::getSoundBuffer(soundList_Bullet[type][j]);
			
		}

		levelReader.EnemyWaveData.pop();
		levelReader.BulletWaveData.pop();
		loadProgress++;
	}
	else
	{
		isLoadComplete = 1;
	}
}

void LoadScreen::loadPlayer()
{
	for (int i = 0; i < textureList_Player.size(); i++)
	{
		for (int j = 0; j < textureList_Player[i].size(); j++)
			Texture texture = ResourceManager::getTexture(textureList_Player[i][j]);

		for (int j = 0; j < soundList_Player[i].size(); j++)
			SoundBuffer sound = ResourceManager::getSoundBuffer(soundList_Player[i][j]);
	}

	Texture texture = ResourceManager::getTexture("Battlecruiser_Base.png");
	Texture texture2 = ResourceManager::getTexture("Battlecruiser_Destruction.png");
	Texture texture3 = ResourceManager::getTexture("Battlecruiser_Engine.png");

	SoundBuffer sound = ResourceManager::getSoundBuffer("PlayerExplode.ogg");

}