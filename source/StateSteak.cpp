#include "StateSteak.h"

StateSteak::StateSteak()
{
	Stack.clear();
	Dummy.CurrentState = States::Main;
	CreateState(Dummy.CurrentState);	
}

void StateSteak::CreateState(States::ID &stateID)
{
	switch (stateID)
	{
	case States::None:
		return;
		break;

	case States::Main:
		Stack.push_back(Dummy.makeUnique(new MainMenu()));
		break;

	case States::NewGame:
		Stack.push_back(Dummy.makeUnique(new GameState()));
		break;

	/*case States::HighScore:
		return new HighScore;
		break;
	case States::Load:
		return new Load;
		break;
	
	case States::Pause:
		return new Pause;
		break;
	case States::GameOver:
		return new GameOver;
		break;
	default:
		return nullptr;
		break;*/
	}
	
	stateID = States::None;
}


void StateSteak::pushState(States::ID stateID)
{
	//Stack.push_back(CreateState(stateID));
}

void StateSteak::popState()
{
	Stack.pop_back();
}

void StateSteak::clearStates()
{
	Stack.clear();
}

bool StateSteak::isEmpty() const
{
	return Stack.empty();
}

void StateSteak::update(Event& event, Vector2f& MousePos)
{
	if (!Stack.empty() && (Stack.back()->isDead)) Stack.pop_back();

	if (!Stack.empty()) CreateState(Stack.back()->CurrentState);

	if (!Stack.empty())	Stack.back()->update(event, MousePos);
}

void StateSteak::draw(RenderTarget& target, RenderStates states) const
{
	if (!Stack.empty())
	Stack.back()->draw(target, states);
}

void StateSteak::takeTime(Time& dt)
{
	if (!Stack.empty())
	Stack.back()->takeTime(dt);
}

