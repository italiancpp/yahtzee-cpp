#include "GameState.h"
#include "ScoreTable.h"

using namespace std;

GameState::GameState() : currentTurn(0), currentShot(0)
{}

void GameState::NewTurn()
{
	currentShot = 0;
	currentTurn++;
}

void GameState::NewShot()
{
	potentialScores = currentScores;
	currentShot++;
}

void GameState::AssignScoreFromPotential(Scores::ScoreName score)
{
	currentScores.AssignScoreIfNotAssigned(score, score, true);
}
