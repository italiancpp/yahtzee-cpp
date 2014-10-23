#pragma once

#include "ScoreTable.h"

class GameState
{
public:
	GameState();

	inline bool IsFirstShot() const;
	void NewTurn();
	void NewShot();
	
	void AssignScoreFromPotential(Scores::ScoreName score);

	ScoreTable currentScores;
	ScoreTable potentialScores;

private:
	size_t currentTurn;
	size_t currentShot;
};

bool GameState::IsFirstShot() const
{
	return (currentShot == 1);
}