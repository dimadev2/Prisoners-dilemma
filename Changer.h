#pragma once
#include "BaseStrategy.h"
class Changer :
    public BaseStrategy
{
public:
    Changer(uint32_t playerNumber) : BaseStrategy(playerNumber) { ; }
protected:
    void analysMove(const list<Move**> &moveList, uint32_t me) {
        Move** last = moveList.back();
        Move* nw = new Move[playerNumber()];
        for (uint32_t i = 0; i < playerNumber(); i++) {
            nw[i] = last[me][i] == HELP ? BETRAY : HELP;
        }
        setPreferredMove(nw);
    }
};

