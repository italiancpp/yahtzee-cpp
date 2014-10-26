#pragma once
#include <string>
#include <functional>
#include "DiceRoller.h"
#include <vector>

class DicePlayer
{
public:
	DicePlayer(const std::string& pName, IDiceRoller& r);

	void RollDice(std::vector<Die>& dice);

	std::string name;
	IDiceRoller* roller;
};

