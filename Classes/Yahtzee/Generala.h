#pragma once

#include "GameState.h"
#include <vector>
#include <iostream>

class Generala
{
	size_t _playerNum;
	std::vector<GameState> _states;
public:

	Generala()
	:_playerNum(0)
	{

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
};

