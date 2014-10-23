#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "Rule.h"
#include "Die.h"
#include "YahtzeeWriter.h"

class GameState;

class ScoreCalculator
{
public:
	
	ScoreCalculator(YahtzeeWriter &writer) : _writer(_writer)
	{}

	~ScoreCalculator();

	void CheckScore(const std::vector<Die>& dice, unsigned short maxDiceValue, GameState& currentTable) const;

private:
	YahtzeeWriter &_writer;
};

