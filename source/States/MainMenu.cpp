#include "MainMenu.h"

MainMenu::MainMenu()
{
	textureBack = ResourceManager::getTexture("Blue_Background.png");
	backgroundSprite.setTexture(textureBack);
	backgroundSprite.setScale(getScale::getScaleMax(sf::Vector2f(backgroundSprite.getTextureRect().width, backgroundSprite.getTextureRect().height), Constants::WINDOW_SIZE));

	Vector2f PlanetTopSize = Vector2f(ResourceManager::getTexture("TerraTop.png").getSize());

	animePlanetTop = new Animation(22, PlanetTopSize.x/40, 1, 1, WINDOW_SIZE + sf::Vector2f(-WINDOW_SIZE.x, -PlanetTopSize.y),{0,0}, "TerraTop.png");
	animePlanetTop->PushToObject(animePlanetTop, this);

	Vector2f NeutronStarSize = Vector2f(ResourceManager::getTexture("NeutronStar.png").getSize());

	animeNeutronStar = new Animation(20, NeutronStarSize.x / 80, 1, 1, WINDOW_SIZE + Vector2f(-NeutronStarSize.x / 60,-WINDOW_SIZE.y+NeutronStarSize.y * 0.5),{0,0}, "NeutronStar.png");
	animeNeutronStar->PushToObject(animeNeutronStar, this);	

	btn_Quit = new Button(sf::Vector2f(200, 600), sf::Vector2f(200, 100), "Quit"); 
	btn_Quit->PushToObject(btn_Quit,this);

	btn_NewGame = new Button(sf::Vector2f(200, 100), sf::Vector2f(400, 100), "New Game");
	btn_NewGame->PushToObject(btn_NewGame, this);
}

MainMenu::~MainMenu()
{
}

void MainMenu::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite);
}	

void MainMenu::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (btn_Quit->isLeftClicked(event,MousePos)) isDead = true; else
		if (btn_NewGame->isLeftClicked(event, MousePos))
		{
			CurrentState = States::NewGame;
		}
}

void MainMenu::takeTimeCurrent()
{
}