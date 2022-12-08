#pragma once

#include <list>

enum Move {
	HELP,
	BETRAY
};

using std::list;

class BaseStrategy
{
public:
	BaseStrategy(uint32_t playerNumber) {
		PlayerNumber = playerNumber;
		PreferredMove = new Move[PlayerNumber];
	}
	~BaseStrategy() {
		delete[] PreferredMove;
	}

	Move* makeMove(const list<Move**> &moveList, uint32_t me) {
		if (!moveList.empty())
			analysMove(moveList, me);
		return PreferredMove;
	}
protected:
	virtual void analysMove(const list<Move**> &moveList, uint32_t me) = 0;
	uint32_t playerNumber() const {
		return PlayerNumber;
	}

	void setPreferredMove(Move* mv) {
		PreferredMove = mv;
	}
private:
	Move* PreferredMove;
	uint32_t PlayerNumber;
};

