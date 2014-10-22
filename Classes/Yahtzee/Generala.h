#pragma once

#include "GameState.h"
#include "Die.h"
#include "DiceRoller.h"
#include "ScoreCalculator.h"
#include <vector>
#include "YahtzeeWriter.h"

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
	IDiceRoller& roller;
	//ScoreCalculator calculator(RuleGenerator::GenerateRules());

	YahtzeeWriter *yahtzeeWriter;
	ScoreCalculator calculator;



public:

	Generala(IDiceRoller& _roller, YahtzeeWriter *writer)
	:_playerNum(0), dice(dice_number, Die(1)), roller(_roller), yahtzeeWriter(writer), calculator(*yahtzeeWriter)
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
		auto old = _playerNum;
		_states.resize(n);
		_playerNum = n;
		yahtzeeWriter->numberOfPlayersChanged(old, _playerNum);
	}

	int Start();

    void rollDice();


	void selectScore(Scores::ScoreName score);

	void holdDice(std::vector<int> diceIndex);
};

