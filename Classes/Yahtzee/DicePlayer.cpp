#include "DicePlayer.h"


DicePlayer::DicePlayer( const std::string& pName, IDiceRoller& r )
	: name(pName), roller(&r)
{

}

void DicePlayer::RollDice( std::vector<Die>& dice )
{
	roller->Roll(dice);
}
