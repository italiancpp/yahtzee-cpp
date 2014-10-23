#pragma once

#include "GameState.h"

class DicePlayer
{
public:
	DicePlayer(const std::string& pName);

	const std::string name;
	GameState state;
};

