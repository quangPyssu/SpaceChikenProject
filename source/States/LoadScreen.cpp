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

	SubTitle* Instruction = new SubTitle({ 10,10 }, Vector2f(WINDOW_SIZE.x, 200), trans, { 0.05,0.3 }, 13, yellow,
		"Left click on available Weapon and Speacial to equip it", "neuro", -1);
	SubTitleList.push_back(Instruction);
	PushToObject(SubTitleList.back(), this);

	SubTitle* SideArm = new SubTitle({ 10,50 }, Vector2f(WINDOW_SIZE.x, 200), trans, { 0.05,0.3 }, 13, yellow,
		"Right click on available Weapon to equip side Weapon", "neuro", -1);
	SubTitleList.push_back(SideArm);
	PushToObject(SubTitleList.back(), this);

	{
		btnWeapon = new Button(Vector2f(WINDOW_SIZE.x / 6, 100*SCALE), Vector2f(100, 100)*SCALE, "W");
		btnWeapon->PushToObject(btnWeapon, this);
		btnWeapon->makeInvisible();

		btnWeapon2 = new Button(Vector2f(WINDOW_SIZE.x / 6-120*SCALE, 100*SCALE), Vector2f(100, 100)*SCALE, "E");
		btnWeapon2->PushToObject(btnWeapon2, this);
		btnWeapon2->makeInvisible();

		for (int i = 0; i < weaponMax; i++)
		{
			btnWeaponList.push_back(new Button(Vector2f(WINDOW_SIZE.x / 6, SCALE*(250 + 125 * i)), Vector2f(100, 100)*SCALE, "A"));
			btnWeaponList.back()->makeInvisible();
			PushToObject(btnWeaponList.back(), this);


			string temp = "WeaponIcon" + to_string(i) + ".jpg";
			spriteWeaponList.push_back(new SpriteOnly(temp));
			spriteWeaponList.back()->setPosition(btnWeaponList.back()->getPosition());
			spriteWeaponList.back()->setScale(getScale::getScaleMax(spriteWeaponList.back()->getSize(), btnWeaponList.back()->getSize()).x/SCALE);

			if (!WeaponUnlocked[i].first)
			{
				btnWeaponList.back()->makeUnInteractable();
				spriteWeaponList.back()->setTransparency(100);
			}

		}
	}	

	{
		btnSpecial = new Button(Vector2f(WINDOW_SIZE.x / 6 + 150*SCALE, 100*SCALE), Vector2f(100, 100)*SCALE, "S");
		btnSpecial->PushToObject(btnSpecial, this);
		btnSpecial->makeInvisible();

		for (int i = 0; i < specialMax; i++)
		{
			btnSpecialList.push_back(new Button(Vector2f(WINDOW_SIZE.x / 6 + 150*SCALE, SCALE*(250 + 125 * i)), Vector2f(100, 100)*SCALE, "A"));
			btnSpecialList.back()->makeInvisible();
			PushToObject(btnSpecialList.back(), this);

			string temp = "SpecialIcon" + to_string(i) + ".jpg";
			spriteSpecialList.push_back(new SpriteOnly(temp));
			spriteSpecialList.back()->setPosition(btnSpecialList.back()->getPosition());
			spriteSpecialList.back()->setScale(getScale::getScaleMin(spriteSpecialList.back()->getSize(), btnSpecialList.back()->getSize()).x / SCALE);

			if (!SpecialUnlocked[i].first)
			{
				btnSpecialList.back()->makeUnInteractable();
				spriteSpecialList.back()->setTransparency(100);
			}
		}
	}

	btnContinue = new Button(Vector2f(WINDOW_SIZE.x/5*4, 100), Vector2f(200,70), "Continue");
	btnContinue->PushToObject(btnContinue, this);

	btnQuit = new Button(Vector2f(WINDOW_SIZE.x /5*4, 200), Vector2f(200, 70), "Quit");
	btnQuit->PushToObject(btnQuit, this);
	
	{
		ResourceManager::getTexture("Explosion.png");
		textureList_Enemy.push_back({ "ChickenBody.png","ChickenFace.png","egg.png" });
		textureList_Enemy.push_back({ "ChickenBody.png","BossChickenBody.png","BossChickenBody2.png","BossChickenBody3.png","egg.png" });
		textureList_Enemy.push_back({ "UFO.png","UFO_Bullet.png" });
		textureList_Enemy.push_back({ "space_ship.png","exhaust.png","microgun-bullet.png"});
		textureList_Enemy.push_back({ "henterprise.png","laserCannon.png","electroBeam5.png","ChickenBody.png","ChickenFace.png","egg.png"
			,"BossChickenBody.png","BossChickenBody2.png","BossChickenBody3.png","UFO.png","UFO_Bullet.png" });
		textureList_Enemy.push_back({ });//black hole
		textureList_Enemy.push_back({ });//semi Vortex
		textureList_Enemy.push_back({ });//spiral Vortex
		textureList_Enemy.push_back({"Fire_Vortex.png","SuperHenBody2.png","Black_Hole.png","Blue_Vortex.png"});//chick boss 2 

		soundList_Enemy.push_back({ "chicken1a(die).ogg","chicken2b(die).ogg","chicken3a(die).ogg" });
		soundList_Enemy.push_back({ "(chickbossCry).ogg","(chickbossDie).ogg" });
		soundList_Enemy.push_back({ "(buglezap).ogg","(ufoEngine).ogg","engineUfoDamaged.ogg"});
		soundList_Enemy.push_back({ "(defaultweapon).ogg","(ufoEngine).ogg","engineUfoDamaged.ogg" });
		soundList_Enemy.push_back({ "MasterSpark.ogg" ,"laserSmall.ogg","(buglezap).ogg","(chickbossCry).ogg","(chickbossDie).ogg" });
		soundList_Enemy.push_back({ });
		soundList_Enemy.push_back({ });
		soundList_Enemy.push_back({ });
		soundList_Enemy.push_back({ "(chickbossCry).ogg","(chickbossDie).ogg" });


		textureList_Bullet.push_back({ "egg.png" });
		textureList_Bullet.push_back({ "Astroid.png" });
		textureList_Bullet.push_back({ "QuicklyBeam.png" });
		textureList_Bullet.push_back({ "UFO_Bullet.png" });

		soundList_Bullet.push_back({  });
		soundList_Bullet.push_back({ "rock_0.ogg","rock_1.ogg" });
		soundList_Bullet.push_back({ "laserSmall.ogg" });



		textureList_Player.push_back({ "Bullet.png","QuicklyBeam.png" });

		soundList_Player.push_back({ "(laser).ogg","laserSmall.ogg" });
	}
	isLoadComplete = 0;

	// here to load attack of Player	
}

LoadScreen::~LoadScreen()
{
	for (int i = 0; i < spriteWeaponList.size(); i++)
		delete spriteWeaponList[i];

	for (int i = 0; i < spriteSpecialList.size(); i++)
		delete spriteSpecialList[i];
	
}

void LoadScreen::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite);
	target.draw(*progressBar);

	for (int i = 0; i < spriteWeaponList.size(); i++) target.draw(*spriteWeaponList[i]);

	spriteWeaponList[EquipedWeapon[0]]->setPosition(btnWeapon->getPosition());
	target.draw(*spriteWeaponList[EquipedWeapon[0]]);
	spriteWeaponList[EquipedWeapon[0]]->setPosition(btnWeaponList[EquipedWeapon[0]]->getPosition());

	spriteWeaponList[EquipedWeapon[1]]->setPosition(btnWeapon2->getPosition());
	target.draw(*spriteWeaponList[EquipedWeapon[1]]);
	spriteWeaponList[EquipedWeapon[1]]->setPosition(btnWeaponList[EquipedWeapon[1]]->getPosition());

	for (int i = 0; i < spriteSpecialList.size(); i++) target.draw(*spriteSpecialList[i]);

	spriteSpecialList[CurrentSpecial]->setPosition(btnSpecial->getPosition());
	target.draw(*spriteSpecialList[CurrentSpecial]);
	spriteSpecialList[CurrentSpecial]->setPosition(btnSpecialList[CurrentSpecial]->getPosition());
}

void LoadScreen::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (btnContinue->isLeftClicked(event, MousePos) && isLoadComplete)
	{
		loadPlayer();
		CurrentState = States::NewGame;
	}

	if (btnQuit->isLeftClicked(event, MousePos) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
		CurrentState = States::KillMe;
		parentState->CurrentState = States::None;
	}

	for (int i = 0; i < btnWeaponList.size(); i++)
	{
		if (btnWeaponList[i]->isLeftClicked(event, MousePos)) EquipedWeapon[0] = i;

		if (btnWeaponList[i]->isRightClicked(event, MousePos))	EquipedWeapon[1] = i;
	}	

	for (int i = 0; i < btnSpecialList.size(); i++)
	{
		if (btnSpecialList[i]->isLeftClicked(event, MousePos))
		{
			CurrentSpecial = i;
		}
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

	for (int i=0;i<weaponMax;i++) switch (EquipedWeapon[i])
	{
		case 0:
		{
			Texture texture = ResourceManager::getTexture("Bullet.png");
			SoundBuffer sound = ResourceManager::getSoundBuffer("(laser).ogg");
		}
			break;
		
		case 1:
		{
			Texture texture = ResourceManager::getTexture("QuicklyBeam.png");
			SoundBuffer sound = ResourceManager::getSoundBuffer("laserSmall.ogg");
		}		
			break;

		case 2:
		{
			Texture texture = ResourceManager::getTexture("microgun-bullet.png");
			SoundBuffer sound = ResourceManager::getSoundBuffer("(defaultweapon).ogg");
		}	
		break;
	}

	switch (CurrentSpecial)
	{
		case 0:
		{
			Texture texture = ResourceManager::getTexture("Bullet.png");
			SoundBuffer sound = ResourceManager::getSoundBuffer("(laser).ogg");
		}
			break;

		case 1:
		{
			Texture texture = ResourceManager::getTexture("BigBeam.png");
			Texture texture2 = ResourceManager::getTexture("BigBeamBody.png");

			SoundBuffer sound = ResourceManager::getSoundBuffer("MasterSpark.ogg");
		}
			break;

		case 2:
		{
			Texture texture = ResourceManager::getTexture("Dreadnought_Shield.png");
			SoundBuffer sound = ResourceManager::getSoundBuffer("MarioStar.ogg");
		}
			break;
	}
}