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
	// INVECCHIAMENTO
	//ScoreCalculator(std::vector<Rule>&& pRules);
	ScoreCalculator(YahtzeeWriter &writer) : _writer(_writer)
	{}

	// INVECCHIAMENTO
	~ScoreCalculator();
	// INVECCHIAMENTO
	ScoreCalculator(const ScoreCalculator& other);

	void CheckScore(const std::vector<Die>& dice, unsigned short maxDiceValue, GameState& currentTable) const;

	// INVECCHIAMENTO
//private:
//	std::vector<Rule> rules;

private:
	YahtzeeWriter &_writer;
};

