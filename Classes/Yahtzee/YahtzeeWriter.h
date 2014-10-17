#pragma once

class YahtzeeWriter
{
public:
	virtual void startTurnFor(size_t player_count, size_t current_turn, size_t const turns_number) = 0;
	virtual void showPotentialScores(ScoreTable scores) = 0;

	void numberOfPlayersChanged(size_t oldValue, size_t newValue);
	void writeLine(std::string s)
	{

	}
};