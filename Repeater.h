#pragma once
#include "BaseStrategy.h"
class Repeater :
    public BaseStrategy
{
public:
    Repeater(uint32_t playerNumber) : BaseStrategy(playerNumber) { ; }
protected:
    void analysMove(const list<Move**> &moveList, uint32_t me) {
        Move** last = moveList.back();
        Move* nw = new Move[playerNumber()];
        for (uint32_t i = 0; i < playerNumber(); i++) {
            nw[i] = last[i][me];
        }
        setPreferredMove(nw);
    }
};

