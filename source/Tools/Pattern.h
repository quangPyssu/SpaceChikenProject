#pragma once

#include "../Entiy/Entity.h"

enum PatternType
{
	Circle
};

class Pattern : public Entity
{
	public:
	~Pattern();

	void takeTimeCurrent() override;
	protected:

	void setUpPattern(PatternType type);

	PatternType type;
	vector <Entity*> entityList;
	
	Vector2f CurrentPos;

	float angleVelocity = 0;
	float angleAcceleration = 0;
};
