#pragma once
#include "BaseStrategy.h"

#include <random>
#include <ctime>

class Random :
    public BaseStrategy
{
public:
    Random(uint32_t playerNumber) : BaseStrategy(playerNumber) { 
        std::srand((std::time(nullptr)));
    }
protected:
    void analysMove(const list<Move**>& moveList, uint32_t me) {
        Move* mv = new Move[playerNumber()];
        for (uint32_t i = 0; i < playerNumber(); i++) {
            uint32_t r = std::rand();
            if (r % 2 == 0)
                mv[i] = HELP;
            else
                mv[i] = BETRAY;
        }
        setPreferredMove(mv);
    }
};

