#pragma once

class GameConfiguration
{
public:
	GameConfiguration(size_t numOfDice, unsigned short maxDiceValue, size_t turnsNumber);

	const size_t NumberOfDice;
	const unsigned short MaxDiceValue;
	const size_t TurnsNumber;
};

GameConfiguration CreateDefaultGameConfiguration();