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
	
	ScoreCalculator(YahtzeeWriter &writer, unsigned short _maxDiceValue);
	~ScoreCalculator();

	void CheckScore(const std::vector<Die>& dice, GameState& currentTable) const;
	void CheckScore(const std::vector<Die>& dice, bool isFirstShot, ScoreTable& currentTable) const;

private:
	YahtzeeWriter &_writer;
	unsigned short maxDiceValue;
};

