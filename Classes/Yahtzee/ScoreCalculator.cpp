#include "ScoreCalculator.h"

using namespace std;

ScoreCalculator::~ScoreCalculator()
{}

void CalculateRanks(const vector<Die>& dice, unsigned short* ranks)
{
	for (size_t i = 0u; i<dice.size(); ++i)
	{
		ranks[dice[i].value - 1] += 1;
	}
}

void CalculateHistogram(unsigned short* ranks, int size, Histogram& histogram)
{
	for (int i = 0; i<size; ++i)
	{
		if (ranks[i]>0)
			histogram[ranks[i]].push_front(i+1);
	}
}

inline bool histogram_has(const Histogram& histogram, unsigned short val)
{
	return histogram.find(val) != end(histogram);
}

inline unsigned short Score(unsigned short score, const GameState& state, unsigned short extraIfFirstRoll = 5)
{
	return state.IsFirstShot() ? score + extraIfFirstRoll : score;
}


void ScoreCalculator::CheckScore(const vector<Die>& dice, unsigned short maxDiceValue, GameState& state) const
{
	unsigned short* ranks = new unsigned short[maxDiceValue];
	CalculateRanks(dice, ranks);

	Histogram histogram;
	CalculateHistogram(ranks, maxDiceValue, histogram);
	
	if (histogram_has(histogram, 1))
	{
		for (auto single : histogram.find(1)->second)
		{
			state.potentialScores.AssignScoreIfNotAssigned(DieValueToScore(single), single);
		}
	}
	
	if (histogram_has(histogram, 2))
	{
		_writer.writeLine("PAIR");
		for (auto pair : histogram.find(2)->second)
		{
			state.potentialScores.AssignScoreIfNotAssigned(DieValueToScore(pair), 2 * pair);
		}
	}
	
	if ((histogram_has(histogram, 2)) && histogram.find(2)->second.size() == 2)
		_writer.writeLine("DOULE PAIR");

	if (histogram_has(histogram, 3))
	{
		_writer.writeLine("TRIS");
		auto trisValue = histogram.find(3)->second.front();
		state.potentialScores.AssignScoreIfNotAssigned(DieValueToScore(trisValue), 3 * trisValue);
	}

	if (histogram_has(histogram, 2) && histogram_has(histogram, 3))
	{
		_writer.writeLine("FULL");
		state.potentialScores.AssignScoreIfNotAssigned(Scores::full, Score(30, state));
	}

	if (histogram_has(histogram, 4))
	{
		_writer.writeLine("POKER");
		state.potentialScores.AssignScoreIfNotAssigned(Scores::poker, Score(40, state));
		auto pokerValue = histogram.find(4)->second.front();
		state.potentialScores.AssignScoreIfNotAssigned(DieValueToScore(pokerValue), 4 * pokerValue);
	}

	if ((histogram.size() == 1) && histogram_has(histogram, 1))
	{
		_writer.writeLine("STRAIGHT");
		state.potentialScores.AssignScoreIfNotAssigned(Scores::straight, Score(20, state));
	}

	if (histogram_has(histogram, 5))
	{
		_writer.writeLine("GENERALA");
		state.potentialScores.AssignScoreIfNotAssigned(Scores::generala, Score(50, state));
		auto generalaValue = histogram.find(5)->second.front();
		state.potentialScores.AssignScoreIfNotAssigned(DieValueToScore(generalaValue), 5 * generalaValue);
	}

	if (histogram_has(histogram, 5) && state.currentScores.HasScore(Scores::generala))
	{
		_writer.writeLine("DOUBLE GENERALA");
		state.potentialScores.AssignScoreIfNotAssigned(Scores::double_generala, Score(100, state));
		auto generalaValue = histogram.find(5)->second.front();
		state.potentialScores.AssignScoreIfNotAssigned(DieValueToScore(generalaValue), 5 * generalaValue);
	}

	delete [] ranks;
}