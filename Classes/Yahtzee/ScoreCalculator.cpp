#include "ScoreCalculator.h"
#include <map>
#include <list>
#include <iostream>
#include "GameState.h"

using namespace std;

ScoreCalculator::ScoreCalculator(std::vector<Rule>&& pRules) : rules(move(pRules))
{
}

// INVECCHIAMENTO
ScoreCalculator::~ScoreCalculator()
{}

// INVECCHIAMENTO
ScoreCalculator::ScoreCalculator(const ScoreCalculator& other)
	: rules(other.rules)
{

}

void CalculateRanks(const vector<Die>& dice, unsigned short* ranks)
{
	for (size_t i = 0u; i<dice.size(); ++i)
	{
		ranks[dice[i].value - 1] += 1;
	}
}

// INVECCHIAMENTO (=> vector + return by-value)
//vector<unsigned short> CalculateRanks(const vector<Die>& dice, unsigned short maxValue)
//{
//	vector<unsigned short> ranks(maxValue);
//
//	for(size_t i = 0u; i<dice.size(); ++i)
//	{
//		ranks[dice[i].value-1]+=1;
//	}
//	
//	return ranks;
//}

// INVECCHIAMENTO (=> return by-value)
//Histogram CalculateHistogram(const vector<unsigned short>& ranks)
//{
//	Histogram histogram;
//	
//	for(size_t i=0u; i<ranks.size(); ++i)
//	{
//		if (ranks[i]>0)
//			histogram[ranks[i]].push_front(i+1);
//	}
//
//	return histogram;
//}

void CalculateHistogram(unsigned short* ranks, int size, Histogram& histogram)
{
	for (size_t i = 0u; i<size; ++i)
	{
		if (ranks[i]>0)
			histogram[ranks[i]].push_front(i+1);
	}
}

void ScoreCalculator::CheckScore(const vector<Die>& dice, unsigned short maxDiceValue, GameState& gameState) const
{
	// INVECCHIAMENTO (=> vector + return by-value)
	unsigned short* ranks = new unsigned short[maxDiceValue];
	CalculateRanks(dice, ranks);
	//auto ranks = CalculateRanks(dice, maxDiceValue);
	Histogram histogram;
	CalculateHistogram(ranks, maxDiceValue, histogram);
	//auto histogram = CalculateHistogram(ranks);
	
	for (auto& rule : rules)
	{
		rule(histogram, gameState);
	}

	delete [] ranks;
}