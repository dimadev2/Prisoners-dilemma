#pragma once
#include "BaseStrategy.h"
class Voter :
    public BaseStrategy
{
public:
    Voter(uint32_t playerNumber) : BaseStrategy(playerNumber) { ; }
protected:
    void analysMove(const list<Move**>& moveList, uint32_t me) {
        int32_t *sum = new int32_t[playerNumber()];
        for (uint32_t i = 0; i < playerNumber(); i++) {
            sum[i] = 0;
        }

        for (auto move : moveList) {
            for (uint32_t i = 0; i < playerNumber(); i++) {
                sum[i] += move[i][me];
            }
        }

        Move* mv = new Move[playerNumber()];
        for (uint32_t i = 0; i < playerNumber(); i++) {
            mv[i] = sum[i] >= 0 ? HELP : BETRAY;
        }
        setPreferredMove(mv);
    }
};

