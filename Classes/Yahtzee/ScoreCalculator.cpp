#include "ScoreCalculator.h"
#include <map>
#include <list>
#include <iostream>
#include "GameState.h"

using namespace std;

//ScoreCalculator::ScoreCalculator(std::vector<Rule>&& pRules) : rules(move(pRules))
//{
//}

// INVECCHIAMENTO
ScoreCalculator::~ScoreCalculator()
{}

// INVECCHIAMENTO
ScoreCalculator::ScoreCalculator(const ScoreCalculator& other)
	//: rules(other.rules)
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
	// INVECCHIAMENTO (=> vector + return by-value)
	unsigned short* ranks = new unsigned short[maxDiceValue];
	CalculateRanks(dice, ranks);
	//auto ranks = CalculateRanks(dice, maxDiceValue);
	Histogram histogram;
	CalculateHistogram(ranks, maxDiceValue, histogram);
	//auto histogram = CalculateHistogram(ranks);
	
	// INVECCHIAMENTO (regole cambiate in mega-if)
	
	if (histogram_has(histogram, 1))
	{
		for (auto single : histogram.find(1)->second)
		{
			state.potentialScores.TryAssignScore(single, single);
		}
	}
	
	if (histogram_has(histogram, 2))
	{
		cout << "PAIR" << endl;
		for (auto pair : histogram.find(2)->second)
		{
			state.potentialScores.TryAssignScore(pair, 2 * pair);
		}
	}
	
	if ((histogram_has(histogram, 2)) && histogram.find(2)->second.size() == 2)
		cout << "DOULE PAIR" << endl;

	if (histogram_has(histogram, 3))
	{
		cout << "TRIS" << endl;
		auto trisValue = histogram.find(3)->second.front();
		state.potentialScores.TryAssignScore(trisValue, 3 * trisValue);
	}

	if (histogram_has(histogram, 2) && histogram_has(histogram, 3))
	{
		cout << "FULL" << endl;
		state.potentialScores.TryAssignScore(Scores::full, Score(30, state));
	}

	if (histogram_has(histogram, 4))
	{
		cout << "POKER" << endl;
		state.potentialScores.TryAssignScore(Scores::poker, Score(40, state));
		auto pokerValue = histogram.find(4)->second.front();
		state.potentialScores.TryAssignScore(pokerValue, 4 * pokerValue);
	}

	if ((histogram.size() == 1) && histogram_has(histogram, 1))
	{
		cout << "STRAIGHT" << endl;
		state.potentialScores.TryAssignScore(Scores::straight, Score(20, state));
	}

	if (histogram_has(histogram, 5))
	{
		cout << "GENERALA" << endl;
		state.potentialScores.TryAssignScore(Scores::generala, Score(50, state));
		auto generalaValue = histogram.find(5)->second.front();
		state.potentialScores.TryAssignScore(generalaValue, 5 * generalaValue);
	}

	if (histogram_has(histogram, 5) && state.currentScores.HasScore(Scores::generala))
	{
		cout << "DOUBLE GENERALA" << endl;
		state.potentialScores.TryAssignScore(Scores::double_generala, Score(100, state));
		auto generalaValue = histogram.find(5)->second.front();
		state.potentialScores.TryAssignScore(generalaValue, 5 * generalaValue);
	}

	/*for (auto& rule : rules)
	{
		rule(histogram, gameState);
	}*/

	delete [] ranks;
}