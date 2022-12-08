#pragma once
#include "BaseStrategy.h"
class Pacific :
    public BaseStrategy
{
public:
    Pacific(uint32_t playerNumber) : BaseStrategy(playerNumber) { 
        Move* mv = new Move[playerNumber];
        for (uint32_t i = 0; i < playerNumber; i++) {
            mv[i] = HELP;
        }
        setPreferredMove(mv);
    }
protected:
    virtual void analysMove(const list<Move**>& moveList, uint32_t me) { 
        Move* mv = new Move[playerNumber()];
        for (uint32_t i = 0; i < playerNumber(); i++) {
            mv[i] = HELP;
        }
        setPreferredMove(mv);
    }
};

