#pragma once

#include "../Entiy/Entity.h"

enum PatternType
{
	None,Circle,Square,Shower,Firework
};

enum RotationType
{
	defaultRotation,Spin,WithVelocity,tiltUp,WithOwnVelocity,SpinOwn
};

class Pattern : public Entity
{
	public:
	~Pattern();

	void takeTimeCurrent() override;

	void setTimer(int timerStart, int timerEnd);

	protected:

	void setUpPattern(PatternType type);	

	PatternType type;
	RotationType rotationType=Spin;

	vector <Entity*> entityList;
	vector <unsigned short> entityListIndex;
	
	Vector2f CurrentPos;

	float angleVelocity = 0;
	float angleAcceleration = 0;

	float width = 0;
	int widthCnt = 0;

	int total = 0;
};
