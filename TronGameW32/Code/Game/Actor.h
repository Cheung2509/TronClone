#pragma once
#include "GameObject.h"

class Actor : public GameObject
{
public:
	Actor() = default;
	~Actor() = default;

	//Getters
	bool getIsAlive()const;
	//Setters
	void setIsAlive(bool alive);

protected:
	bool isAlive;
};
