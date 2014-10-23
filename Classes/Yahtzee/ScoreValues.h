#pragma once

#include <array>

namespace Scores 
{
	enum ScoreName
	{
		one = 0,
		two,
		three,
		four,
		five,
		six,
		straight,
		full,
		poker,
		generala,
		double_generala,

		placeholder_last
	};

	static const size_t scores_count = placeholder_last - one;
}

static const std::array<std::string, Scores::scores_count> score_names = 
	{
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"straight",
		"full",
		"poker",
		"generala",
		"double generala"
	};

Scores::ScoreName DieValueToScore(unsigned short dieValue);