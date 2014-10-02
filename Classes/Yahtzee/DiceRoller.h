#pragma once

#include <random>
#include <vector>
#include "Die.h"

class DiceRoller
{
public:
	DiceRoller(unsigned short pMaxDiceValue);
	void Roll(std::vector<Die>& dice);

private:
	const unsigned short maxDiceValue;
	std::default_random_engine rengine;
};

