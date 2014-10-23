#pragma once
#include <string>
#include <functional>
#include "DiceRoller.h"

class DicePlayer
{
public:
	DicePlayer(const std::string& pName, IDiceRoller& r);

	std::string name;
	IDiceRoller* roller;
};

