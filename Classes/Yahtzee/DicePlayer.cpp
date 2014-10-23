#include "DicePlayer.h"


DicePlayer::DicePlayer( const std::string& pName, IDiceRoller& r )
	: name(pName), roller(&r)
{

}
