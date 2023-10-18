#include "App.h"

App::App()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 5.0;

	window = new sf::RenderWindow(sf::VideoMode(800 * Constants::SCALE, 600 * Constants::SCALE), "Chieken", sf::Style::Fullscreen,settings);

	window->setFramerateLimit(60);

	// Use the minimum scaling factor to maintain the aspect ratio

	view = window->getDefaultView();

	float barWidth = (window->getSize().x - 800 * Constants::SCALE) / 2.0f;
	float barHeight = (window->getSize().y - 600 * Constants::SCALE) / 2.0f;

	// Create a view that preserves the aspect ratio and positions the content

	view.setViewport(sf::FloatRect(barWidth / window->getSize().x, barHeight / window->getSize().y,
		800 * Constants::SCALE / window->getSize().x, 600 * Constants::SCALE / window->getSize().y));
	
	window->setFramerateLimit(60);
	window->setView(view);

	//window->setMouseCursorVisible(false);

	Constants::WINDOW_SIZE = sf::Vector2f(window->getSize().x,window->getSize().y);

	state_stk = new StateSteak();


	//delete later	
}

App::~App()
{
	delete state_stk;
	delete window;
}

void App::Run()
{
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
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Delete) || isDead) window->close();

		update(event,MousePos);		
		//std::cout << MousePos.x << " " << MousePos.y << std::endl;
		//std::cout << window->getSize().x << " " << window->getSize().y << std::endl;
	}
}

void App::update(Event& event, Vector2f& MousePos)
{
	state_stk->update(event,MousePos);
	if (state_stk->isEmpty()) isDead=true;
}

void App::TakeTime(sf::Time dt)
{
}

void App::render()
{
	window->clear(Colors::white);

	state_stk->draw(*window, sf::RenderStates::Default);

	window->display();
}

