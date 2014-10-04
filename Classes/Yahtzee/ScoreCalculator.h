#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "Rule.h"
#include "Die.h"

class GameState;

class ScoreCalculator
{
public:
	// INVECCHIAMENTO
	//ScoreCalculator(std::vector<Rule>&& pRules);
	ScoreCalculator(){}

	// INVECCHIAMENTO
	~ScoreCalculator();
	// INVECCHIAMENTO
	ScoreCalculator(const ScoreCalculator& other);

	void CheckScore(const std::vector<Die>& dice, unsigned short maxDiceValue, GameState& currentTable) const;

	// INVECCHIAMENTO
//private:
//	std::vector<Rule> rules;
};

