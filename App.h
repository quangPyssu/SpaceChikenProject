#include "source/Core/Global.h"
#include "source/Button.h"

#pragma once
class App
{
	public:
	App();
	~App();

	sf::RenderWindow* window;
	sf::Event event;
	sf::View view;

	void Run();

private:
	void ProcessInput();
	void update();
	void render();
	void TakeTime(sf::Time dt);

	sf::Vector2f MousePos;
	sf::Time dt;

	Clock clock;


	sf::RectangleShape shape;
	sf::Texture texture;
	Button* button;
};

