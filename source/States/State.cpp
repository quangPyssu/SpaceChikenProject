#include "State.h"

State::State() {
	window = nullptr;
}

State::State(RenderWindow& window) : window(&window){
}


State::Ptr State::makeUnique(State* state)
{
	return std::unique_ptr<State>(state);
}