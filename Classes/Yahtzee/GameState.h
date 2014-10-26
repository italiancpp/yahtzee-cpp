#pragma once

#include "ScoreTable.h"

class GameState
{
public:
	GameState();

	inline bool IsFirstShot() const;
	void NewTurn();
	void NewShot();
	size_t GetShotNumber() const;

	//void AssignScoreFromPotential(Scores::ScoreName score);

	ScoreTable currentScores;

private:
	size_t currentTurn;
	size_t currentShot;
};

bool GameState::IsFirstShot() const
{
	return (currentShot == 1);
}