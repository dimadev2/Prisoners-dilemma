#pragma once
#include "BaseStrategy.h"

#include <random>
#include <ctime>

class Random :
    public BaseStrategy
{
public:
    Random(uint32_t playerNumber) : BaseStrategy(playerNumber) { 
        srand((time(0)));
    }
protected:
    void analysMove(const list<Move**>& moveList, uint32_t me) {
        Move* mv = new Move[playerNumber()];
        for (uint32_t i = 0; i < playerNumber(); i++) {
            if (rand() % 2 == 0)
                mv[i] = HELP;
            else
                mv[i] = BETRAY;
        }
    }
};

