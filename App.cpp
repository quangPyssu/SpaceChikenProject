#include "App.h"

App::App()
{
	window = new sf::RenderWindow(sf::VideoMode(800 * Constants::SCALE, 600 * Constants::SCALE), "Chieken", sf::Style::Fullscreen);

	window->setFramerateLimit(60);

	// Use the minimum scaling factor to maintain the aspect ratio

	view = window->getDefaultView();

	float barWidth = (window->getSize().x - 800 * Constants::SCALE) / 2.0f;
	float barHeight = (window->getSize().y - 600 * Constants::SCALE) / 2.0f;

	// Create a view that preserves the aspect ratio and positions the content

	view.setViewport(sf::FloatRect(barWidth / window->getSize().x, barHeight / window->getSize().y,
		800 * Constants::SCALE / window->getSize().x, 600 * Constants::SCALE / window->getSize().y));

	window->setView(view);
	window->setMouseCursorVisible(false);


	shape.setSize(sf::Vector2f(20, 20));
	shape.setFillColor(Colors::grey);
	texture = ResourceManager::getTexture("Cursors.png");

	shape.setTexture(&texture);
	button = new Button(sf::Vector2f(200, 100), sf::Vector2f(200, 100), "Button"); std::cout << "1asdasd" << std::endl;

	
}

App::~App()
{
	delete window;
}

void App::Run()
{
	std::cout << "1asdasd" << std::endl;
	while (window->isOpen()) {
		ProcessInput(); 

		dt += clock.restart();

		while (dt > TIME_PER_FRAME)
		{
			dt -= TIME_PER_FRAME;
			//update with frame

			TakeTime(TIME_PER_FRAME);
		}

		render();
	}
}

void App::ProcessInput()
{
	dt = sf::Time::Zero;
	MousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) window->close();

		update();		
	}
}

void App::update()
{
	button->update(event, MousePos);
	shape.setPosition(MousePos);

}

void App::TakeTime(sf::Time dt)
{
	button->takeTime(dt);
}

void App::render()
{
	window->clear(Colors::white);
	button->draw(*window, sf::RenderStates::Default);
	window->draw(shape);
	window->display();
}

