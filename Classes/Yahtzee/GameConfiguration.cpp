#include "GameConfiguration.h"
#include "..\Classes\Yahtzee\ScoreValues.h"

GameConfiguration::GameConfiguration( size_t numOfDice, unsigned short maxDiceValue, size_t turnsNumber )
	: NumberOfDice(numOfDice), MaxDiceValue(maxDiceValue), TurnsNumber(turnsNumber)
{

}

GameConfiguration CreateDefaultGameConfiguration()
{
	return GameConfiguration(5u, 6, Scores::scores_count);
}
