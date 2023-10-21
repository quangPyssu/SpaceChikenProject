#include "source/Core/Global.h"
#include "source/StateSteak.h"


#pragma once
class App
{
	public:
	App();
	~App();

	sf::RenderWindow* window;

	

	void Run();

private:
	void ProcessInput();
	void update(Event& event, Vector2f& MousePos);
	void render();
	void TakeTime(sf::Time dt);
	void updateMousePos();

	sf::Event event;
	sf::View view;

	sf::Vector2f MousePos;
	sf::Time dt;

	bool isDead = false;
	Clock clock;

	StateSteak* state_stk;


	// subject for delete later	
};

