#include "State.h"


State::Ptr State::makeUnique(State* state)
{
	return std::unique_ptr<State>(state);
}