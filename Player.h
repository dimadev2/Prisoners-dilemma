#pragma once

#include "StrategyHolder.h"

class Player
{
	friend class Game;
private:
	Player(uint32_t playerId, StrategyIdx preferredStrategy = PACIFIC) {
		PreferredStrategy = preferredStrategy;
		Score = 0;
		Id = playerId;
	}

	void addScore(int32_t score) {
		Score += score;
	}

	int32_t score() const {
		return Score;
	}

	StrategyIdx strategy() const {
		return PreferredStrategy;
	}

	StrategyIdx PreferredStrategy;
	int32_t Score;
	uint32_t Id;
};

