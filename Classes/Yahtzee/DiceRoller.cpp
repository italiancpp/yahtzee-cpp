#include "DiceRoller.h"
#include <chrono>
#include <iostream>

using namespace std;

DiceRoller::DiceRoller(unsigned short pMaxDiceValue) : maxDiceValue(pMaxDiceValue), rengine((unsigned int) time(0))
{
}

void DiceRoller::Roll(vector<Die>& dice)
{
	uniform_int_distribution<unsigned short> rdist(1, maxDiceValue); 
	
	// INVECCHIAMENTO
	for (int i = 0; i < dice.size(); ++i)
	{
		dice[i].value = rdist(rengine);
	}

	/*for (auto& die : dice)
	{
		if (false == die.hold)
			die.value = rdist(rengine);
	}*/
}


