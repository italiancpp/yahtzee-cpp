#pragma once

struct Die
{
	Die(unsigned short pValue, bool pHold = false) 
		: value(pValue), hold(pHold)
	{}

	unsigned short value;
	bool hold;
};

