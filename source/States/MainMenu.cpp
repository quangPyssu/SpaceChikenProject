#include "MainMenu.h"

MainMenu::MainMenu()
{
	textureBack = ResourceManager::getTexture("Blue_Background.png");
	backgroundSprite.setTexture(textureBack);
	backgroundSprite.setScale(getScale::getScaleMax(sf::Vector2f(backgroundSprite.getTextureRect().width, backgroundSprite.getTextureRect().height), Constants::WINDOW_SIZE));

	Vector2f PlanetTopSize = Vector2f(ResourceManager::getTexture("TerraTop.png").getSize());

	animePlanetTop = new Animation(15, 60, 1, 1, WINDOW_SIZE + sf::Vector2f(-WINDOW_SIZE.x-20*SCALE, -PlanetTopSize.y*SCALE),{0,0}, "TerraTop.png");
	animePlanetTop->PushToObject(animePlanetTop, this);

	Vector2f NeutronStarSize = Vector2f(ResourceManager::getTexture("NeutronStar.png").getSize());

	animeNeutronStar = new Animation(20, 80, 1, 1, WINDOW_SIZE + Vector2f(-NeutronStarSize.x / 60 * SCALE,-WINDOW_SIZE.y+NeutronStarSize.y * 0.5 * SCALE),{0,0}, "NeutronStar.png");
	animeNeutronStar->PushToObject(animeNeutronStar, this);	

	btn_NewGame = new Button(sf::Vector2f(200, 225), sf::Vector2f(400, 100), "New Game");
	btn_NewGame->PushToObject(btn_NewGame, this);

	btn_Continue = new Button(sf::Vector2f(200, 350), sf::Vector2f(300, 100), "Continue");
	btn_Continue->PushToObject(btn_Continue, this);

	btn_Setting = new Button(sf::Vector2f(200, 475), sf::Vector2f(300, 100), "Settings");
	btn_Setting->PushToObject(btn_Setting, this);

	btn_Quit = new Button(sf::Vector2f(200, 600), sf::Vector2f(200, 100), "Quit");
	btn_Quit->PushToObject(btn_Quit, this);

	playMusic(Constants::MenuMusicTrack, 0);

	CurrentData::getData();
}

MainMenu::~MainMenu()
{
	CurrentData::writeData();
}

void MainMenu::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite);
}	

void MainMenu::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (btn_Quit->isLeftClicked(event,MousePos)) CurrentState = States::KillMe; else
		if (btn_NewGame->isLeftClicked(event, MousePos))
		{
			CurrentLevel = 0;
			CurrentData::writeData();
			CurrentData::getData();
			CurrentState = States::Load;
		}
		else
			if (btn_Setting->isLeftClicked(event, MousePos)) CurrentState = States::Setting; else
				if (btn_Continue->isLeftClicked(event, MousePos))
				{
					CurrentState = States::Load;
				}
}

void MainMenu::takeTimeCurrent()
{
	if (CurrentLevel==0) btn_Continue->makeUnInteractable(); 
	else btn_Continue->makeInteractable();
}