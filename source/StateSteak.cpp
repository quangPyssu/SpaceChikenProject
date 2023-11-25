#include "StateSteak.h"

StateSteak::StateSteak(RenderWindow& window) : window(&window)
{
	Stack.clear();
	Dummy.parentState = nullptr;
	Dummy.CurrentState = States::Main;
	CreateState(Dummy.CurrentState);	
}

void StateSteak::CreateState(States::ID &stateID)
{
	switch (stateID)
	{
	case States::None:	{	return;	}	break;

	case States::Main:
	{		Stack.push_back(Dummy.makeUnique(new MainMenu()));	}	break;

	case States::NewGame:
	{		Stack.push_back(Dummy.makeUnique(new GameState(*Stack.back(), *window)));	}	break;

	case States::GameOver:
	{		Stack.push_back(Dummy.makeUnique(new GameOverScreen(*Stack.back())));	}	break;

	case States::KillMe:
	{
		while (Stack.size() > 0 && Stack.back()->CurrentState == States::KillMe)
		{
			Stack.pop_back();
			//cout << "Stack pop : " << Stack.size() << endl;
		}
		//cout << "Stack size: " << Stack.size() << endl << endl;

		if (!Stack.empty()) CreateState(Stack.back()->CurrentState);
		
		break;
	}
	break;

	case States::Credit:
	{		Stack.push_back(Dummy.makeUnique(new Credit(*Stack.back())));	}	break;

	case States::Pause:
	{		Stack.push_back(Dummy.makeUnique(new PauseMenu(*Stack.back())));	}	break;

	case States::Load:	
	{		Stack.push_back(Dummy.makeUnique(new LoadScreen(*Stack.back())));	}	break;

	case States::Setting:
	{		Stack.push_back(Dummy.makeUnique(new SettingMenu(*Stack.back())));	}	break;

	case States::LevelComplete:
	{		Stack.push_back(Dummy.makeUnique(new PostGameMenu(*Stack.back())));	}	break;

	/*case States::HighScore:
		return new HighScore;
		break;
	
	
	default:
		return nullptr;
		break;*/
	}
	
	if (!Stack.empty()) Stack.back()->CurrentState = States::None;
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
	if (!Stack.empty())	Stack.back()->update(event, MousePos);
}

void StateSteak::draw(RenderTarget& target, RenderStates states) const
{
	if (!Stack.empty())
	Stack.back()->draw(target, states);
}

void StateSteak::takeTime()
{
	if (!Stack.empty())	CreateState(Stack.back()->CurrentState);
	if (!Stack.empty()) Stack.back()->takeTime();
}

StateSteak::~StateSteak()
{
	clearStates();
}