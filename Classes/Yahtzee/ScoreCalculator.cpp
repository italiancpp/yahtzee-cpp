#include "ScoreCalculator.h"
#include <iostream>

using namespace std;

ScoreCalculator::ScoreCalculator( YahtzeeWriter &writer, unsigned short _maxDiceValue ) : _writer(_writer), maxDiceValue(_maxDiceValue)
{}

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

inline unsigned short Score(unsigned short score, bool isFirstShot, unsigned short extraIfFirstRoll = 5)
{
	return isFirstShot ? score + extraIfFirstRoll : score;
}

void ScoreCalculator::CheckScore(const std::vector<Die>& dice, bool isFirstShort, ScoreTable& currentTable) const
{
	unsigned short* ranks = new unsigned short[maxDiceValue]();
	CalculateRanks(dice, ranks);

	Histogram histogram;
	CalculateHistogram(ranks, maxDiceValue, histogram);

	if (histogram_has(histogram, 1))
	{
		for (auto single : histogram.find(1)->second)
		{
			currentTable.AssignScoreIfNotAssigned(DieValueToScore(single), single);
		}
	}

	if (histogram_has(histogram, 2))
	{
		_writer.writeLine("PAIR");
		for (auto pair : histogram.find(2)->second)
		{
			currentTable.AssignScoreIfNotAssigned(DieValueToScore(pair), 2 * pair);
		}
	}

	if ((histogram_has(histogram, 2)) && histogram.find(2)->second.size() == 2)
		_writer.writeLine("DOULE PAIR");

	if (histogram_has(histogram, 3))
	{
		_writer.writeLine("TRIS");
		auto trisValue = histogram.find(3)->second.front();
		currentTable.AssignScoreIfNotAssigned(DieValueToScore(trisValue), 3 * trisValue);
	}

	if (histogram_has(histogram, 2) && histogram_has(histogram, 3))
	{
		_writer.writeLine("FULL");
		currentTable.AssignScoreIfNotAssigned(Scores::full, Score(30, isFirstShort));
	}

	if (histogram_has(histogram, 4))
	{
		_writer.writeLine("POKER");
		currentTable.AssignScoreIfNotAssigned(Scores::poker, Score(40, isFirstShort));
		auto pokerValue = histogram.find(4)->second.front();
		currentTable.AssignScoreIfNotAssigned(DieValueToScore(pokerValue), 4 * pokerValue);
	}

	if ((histogram.size() == 1) && histogram_has(histogram, 1))
	{
		_writer.writeLine("STRAIGHT");
		currentTable.AssignScoreIfNotAssigned(Scores::straight, Score(20, isFirstShort));
	}

	if (histogram_has(histogram, 5))
	{
		_writer.writeLine("GENERALA");
		currentTable.AssignScoreIfNotAssigned(Scores::generala, Score(50, isFirstShort));
		auto generalaValue = histogram.find(5)->second.front();
		currentTable.AssignScoreIfNotAssigned(DieValueToScore(generalaValue), 5 * generalaValue);
	}

	/*if (histogram_has(histogram, 5) && state.currentScores.HasScore(Scores::generala))
	{
		_writer.writeLine("DOUBLE GENERALA");
		currentTable.AssignScoreIfNotAssigned(Scores::double_generala, Score(100, isFirstShort));
		auto generalaValue = histogram.find(5)->second.front();
		currentTable.AssignScoreIfNotAssigned(DieValueToScore(generalaValue), 5 * generalaValue);
	}*/

	delete [] ranks;
}

void ScoreCalculator::CheckScore(const vector<Die>& dice, GameState& state) const
{
	//CheckScore(dice, state.IsFirstShot(), state.potentialScores);
}