#pragma once

#include "SceneNode.h"

namespace States {
    enum ID {
    };
};

class StateSteak;

class State : public SceneNode { 
public:
    typedef std::unique_ptr<State> Ptr;

	State(StateSteak& stateSteak, sf::RenderWindow& window);
	virtual ~State();

	virtual void handleEvent(sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};

class StateSteak : private sf::NonCopyable {
public: 


};