#pragma once
#include "BaseStrategy.h"
class Agressor :
    public BaseStrategy
{
public:
    Agressor(uint32_t playerNumber) : BaseStrategy(playerNumber) { 
        Move* mv = new Move[playerNumber];
        for (uint32_t i = 0; i < playerNumber; i++) {
            mv[i] = BETRAY;
        }
        setPreferredMove(mv);
    }
protected:
    void analysMove(const list<Move**> &moveList, uint32_t me) {
        Move* mv = new Move[playerNumber()];
        for (uint32_t i = 0; i < playerNumber(); i++) {
            mv[i] = BETRAY;
        }
        setPreferredMove(mv);
    }
};

