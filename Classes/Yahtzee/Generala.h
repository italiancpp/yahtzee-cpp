#pragma once

#include "GameState.h"
#include "Die.h"
#include "DiceRoller.h"
#include "ScoreCalculator.h"
#include <vector>
#include <iostream>

class YahtzeeWriter
{
public:
	virtual void startTurnFor(size_t player_count, size_t current_turn, size_t const turns_number) = 0;
	virtual void showPotentialScores(ScoreTable scores) = 0;
};

class Generala
{
	size_t _playerNum;
	std::vector<GameState> _states;
	size_t current_turn;
	static const size_t dice_number;
	static const unsigned short max_dice_value;
	static const size_t turns_number;
	static const size_t shots_number;
	size_t player_count = 1u;
	size_t current_state_index = 0;
	size_t current_shot;

	std::vector<Die> dice;
	DiceRoller roller;
	//ScoreCalculator calculator(RuleGenerator::GenerateRules());
	ScoreCalculator calculator;



public:

	Generala()
	:_playerNum(0), dice(dice_number, Die(1)), roller(max_dice_value)
	{
		player_count = 1u;
		current_turn = Scores::scores_count;
		current_shot = Generala::shots_number;
	}

	GameState& state()
	{
		return _states[current_state_index];
	}


	size_t playerNumber()
	{
		return _playerNum;
	}

	void playerNumber(size_t n)
	{
		_states.resize(n);
		_playerNum = n;
		std::cout << "Created game for " << _playerNum << " players!" << std::endl;
	}

	int Start();

    void rollDice();

	YahtzeeWriter *yahtzeeWriter;

	void selectScore(Scores::ScoreName score);

	void holdDice(std::vector<int> diceIndex);
};

