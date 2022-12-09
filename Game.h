#pragma once

#include "StrategyHolder.h"
#include "Player.h"

#include <string>

const uint32_t MoveBufferSize = 5;

namespace moveScore {
	int32_t help_help = 1;
	int32_t help_betray = -2;
	int32_t betray_help = 2;
	int32_t betray_betray = -1;
}

class Game
{
public:
	Game(uint32_t playerNumber, StrategyIdx* preferredStrategies);
	~Game();
	void rounds(uint32_t roundNumber = 1);
	void calculateMove();
	std::string getInfo() const;
	std::string getLastRound() const;
private:
	Player** Players;
	uint32_t PlayerNumber;
	StrategyHolder* StratHolder;
	list<Move**> MoveList;
};

Game::Game(uint32_t playerNumber, StrategyIdx* preferredStrategies) {
	PlayerNumber = playerNumber;

	Players = new Player*[PlayerNumber];
	for (uint32_t i = 0; i < PlayerNumber; i++) {
		Players[i] = new Player(i, preferredStrategies[i]);
	}
	StratHolder = new StrategyHolder(playerNumber);
	rounds();
}

Game::~Game() {
	// delete[] Players;
	delete StratHolder;
}

void Game::rounds(uint32_t roundNumber) {
	for (uint32_t i = 0; i < roundNumber; i++) {
		Move** currentMove = new Move*[PlayerNumber];
		for (uint32_t j = 0; j < PlayerNumber; j++) {
			currentMove[j] = StratHolder->callStrategy(Players[j]->strategy(), MoveList, j);
		}

		MoveList.push_back(currentMove);
		if (MoveList.size() > MoveBufferSize) {
			MoveList.pop_front();
		}

		calculateMove();
	}
}

void Game::calculateMove() {
	Move** last = MoveList.back();
	for (uint32_t i = 0; i < PlayerNumber - 1; i++) {
		for (uint32_t j = i + 1; j < PlayerNumber; j++) {
			if (last[i][j] == HELP && last[j][i] == HELP) {
				Players[i]->addScore(moveScore::help_help);
				Players[j]->addScore(moveScore::help_help);
			}
			else if (last[i][j] == HELP && last[j][i] == BETRAY) {
				Players[i]->addScore(moveScore::help_betray);
				Players[j]->addScore(moveScore::betray_help);
			}
			else if (last[i][j] == BETRAY && last[j][i] == HELP) {
				Players[i]->addScore(moveScore::betray_help);
				Players[j]->addScore(moveScore::help_betray);
			}
			else {
				Players[i]->addScore(moveScore::betray_betray);
				Players[j]->addScore(moveScore::betray_betray);
			}
		}
	}
}

std::string Game::getInfo() const {
	std::string info = "";
	info += "PLAYER\tSCORE\tSTRATEGY\n";
	for (uint32_t i = 0; i < PlayerNumber; i++) {
		info += "Player " + std::to_string(i + 1) + ":\t";
		info += std::to_string(Players[i]->score()) + "\t";
		info += StratHolder->getStrategyString(Players[i]->strategy()) + "\n";
	}

	return info;
}

std::string Game::getLastRound() const {
	std::string round;
	round = "   ";
	for (uint32_t i = 0; i < PlayerNumber; i++) {
		round += std::to_string(i + 1) + "  ";
	}
	round += "\n";

	Move** last = MoveList.back();

	for (uint32_t i = 0; i < PlayerNumber; i++) {
		round += std::to_string(i + 1) + "  ";
		for (uint32_t j = 0; j < PlayerNumber; j++) {
			if (i == j)
				round += "N  ";
			else
				round += std::string(last[i][j] == HELP ? "1" : "0") + "  ";
		}
		round += "\n";
	}

	return round;
}

