#include "App.h"

App::App()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 5.0;
	srand(time(NULL));

	//cout << "Screen Size: " << sf::VideoMode::getDesktopMode().width << " " << sf::VideoMode::getDesktopMode().height << endl;

	std::vector<sf::VideoMode> videoModes;
	videoModes = sf::VideoMode::getFullscreenModes();
	sf::VideoMode videoMode;

	for (unsigned i = 0; i < videoModes.size(); i++) 
		if (videoModes[i].isValid())
		{
			//std::cout << "Vanlid VideoMode: " << i << " - " << videoModes[i].width << "x" << videoModes[i].height << " b" << videoModes[i].bitsPerPixel << std::endl;
			if ((double)videoModes[i].width / videoModes[i].height == (double)4 / 3)
			{
				videoMode = videoModes[i];
				break;
			}
		}

	SCALE_X = (double)(videoMode.width) / (800);
	SCALE_Y = (double)(videoMode.height) / (600);
	SCALE = std::min(SCALE_X, SCALE_Y);

	//cout << "VideoMode: " << videoMode.width << " " << videoMode.height << endl;

	window = new sf::RenderWindow(videoMode, "Chiecken", sf::Style::Fullscreen, settings);

	window->setVerticalSyncEnabled(true);

	view = window->getDefaultView();

	float barWidth = (videoMode.width - 800 * Constants::SCALE) / 2.0f;
	float barHeight = (videoMode.height - 600 * Constants::SCALE) / 2.0f;

	view.setViewport(sf::FloatRect(barWidth / videoMode.width, barHeight / videoMode.height,
		800 * Constants::SCALE / videoMode.width, 600 * Constants::SCALE / videoMode.height));
	
	window->setFramerateLimit(60);
	window->setView(view);

	Constants::WINDOW_SIZE = sf::Vector2f(window->getSize().x,window->getSize().y);

	OutScopeX = { -300 * SCALE,1100 * SCALE };
	OutScopeY = { -300 * SCALE,900 * SCALE };


	state_stk = new StateSteak(*window);	
	event = sf::Event();
}

App::~App()
{
	delete state_stk;
	delete window;
}

void App::Run()
{
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window->isOpen()) {
		ProcessInput(); 
		if (isDead) break;

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

		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Delete) || isDead)
		{
			isDead = true;
			window->close();
		}
	

		update(event,MousePos);		
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

