#include "App.h"

App::App()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 5.0;
	srand(time(NULL));

	window = new sf::RenderWindow(sf::VideoMode(800 * Constants::SCALE, 600 * Constants::SCALE), "Chieken", sf::Style::Fullscreen,settings);

	window->setVerticalSyncEnabled(true);

	view = window->getDefaultView();

	float barWidth = (window->getSize().x - 800 * Constants::SCALE) / 2.0f;
	float barHeight = (window->getSize().y - 600 * Constants::SCALE) / 2.0f;

	view.setViewport(sf::FloatRect(barWidth / window->getSize().x, barHeight / window->getSize().y,
		800 * Constants::SCALE / window->getSize().x, 600 * Constants::SCALE / window->getSize().y));
	
	window->setFramerateLimit(60);
	window->setView(view);

	Constants::WINDOW_SIZE = sf::Vector2f(window->getSize().x,window->getSize().y);

	OutScopeX = { -300 * SCALE,WINDOW_SIZE.x * SCALE };
	OutScopeY = { -300 * SCALE,WINDOW_SIZE.y * SCALE };

	state_stk = new StateSteak(*window);	
}

App::~App()
{
	delete state_stk;
	delete window;
}

void App::Run()
{
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	std::thread logicThread(&App::GameLogicThread, this);

	while (window->isOpen()) {
		ProcessInput(); 

		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME) 
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			TakeTime(TIME_PER_FRAME);
		}
		TakeTime(TIME_PER_FRAME);

		render();
	}

	logicThread.join();
}

void App::GameLogicThread() {
	/*sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window->isOpen()) 
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			TakeTime(TIME_PER_FRAME);
		}
		TakeTime(TIME_PER_FRAME);
	}*/
}

void App::ProcessInput()
{
	dt = sf::Time::Zero;
	MousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	while (window->pollEvent(event)) {
		if (event.type == sf::Event::GainedFocus)
			IsPaused = false;
		else if (event.type == sf::Event::LostFocus)
			IsPaused = true;

		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Delete) || isDead) window->close();

		update(event,MousePos);		
		//std::cout << MousePos.x << " " << MousePos.y << std::endl;
	}
}

void App::update(Event& event, Vector2f& MousePos)
{
	updateMousePos();
	state_stk->update(event,MousePos);
	if (state_stk->isEmpty()) isDead=true;
}

void App::updateMousePos()
{
	Vector2f dtMP = MousePos - lastMousePos;
	dtMousePos = dtMP;
	lastMousePos = MousePos;
}

void App::TakeTime(sf::Time dt)
{
	state_stk->takeTime();
}

void App::render()
{
	window->clear(Colors::white);

	state_stk->draw(*window, sf::RenderStates::Default);

	window->display();
}

