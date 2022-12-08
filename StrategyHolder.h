#pragma once

#include "StrategyInclude.h"

const uint32_t StrategiesNumber = 6;
enum StrategyIdx {
	PACIFIC = 0,
	AGRESSOR,
	REPEATER,
	CHANGER,
	VOTER,
	RANDOM
};

class StrategyHolder
{
public:
	StrategyHolder(uint32_t playerNumber) {
		Strategies = new BaseStrategy*[StrategiesNumber];

		Strategies[0] = new Pacific(playerNumber);
		Strategies[1] = new Agressor(playerNumber);
		Strategies[2] = new Repeater(playerNumber);
		Strategies[3] = new Changer(playerNumber);
		Strategies[4] = new Voter(playerNumber);
		Strategies[5] = new Random(playerNumber);
	}

	~StrategyHolder() {
		delete Strategies[0];
		delete Strategies[1];
		delete Strategies[2];
		delete Strategies[3];
		delete Strategies[4];
		delete Strategies[5];

		delete[] Strategies;
	}

	std::string getStrategyString(StrategyIdx idx) {
		std::string str;
		
		switch (idx) {
		case PACIFIC: str = "Pacific"; break;
		case AGRESSOR: str = "Agressor"; break;
		case REPEATER: str = "Repeater"; break;
		case CHANGER: str = "Changer"; break;
		case VOTER: str = "Voter"; break;
		case RANDOM: str = "Random"; break;
		}

		return str;
	}

	Move* callStrategy(StrategyIdx idx, const list<Move**> &moveList, uint32_t currentPlayer=0) const {
		return Strategies[idx]->makeMove(moveList, currentPlayer);
	}
private:
	 BaseStrategy** Strategies;
};

