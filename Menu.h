#pragma once

#include <iostream>
#include "Game.h"

enum MenuState {
	MENU,
	PREGAME,
	GAME,
	QUIT
};

namespace strategies {
	std::string pacific = "Pacific";
	std::string agressor = "Agressor";
	std::string changer = "Changer";
	std::string random = "Random";
	std::string repeater = "Repeater";
	std::string voter = "Voter";
}

namespace commands {
	namespace menu {
		std::string newGameCommand = "newGame";
	}
	namespace pregame {
		std::string setPlayers = "setPlayerNumber";
		std::string setStrategy = "setStrategy";
		std::string playerNumber = "playerNumber";
		std::string startGameCommand = "start";
	}
	namespace game {
		std::string roundCommand = "round";
		std::string roundsCommand = "rounds";
		std::string infoCommand = "info";
	}

	std::string helpCommand = "!h";
	std::string quitCommand = "!q";
	std::string defaultGame = "!def";
}

class Menu
{
public:
	static void start() {
		Menu menu = Menu();
		menu.stateMachine();
	}
private:
	Menu();

	void stateMachine();

	std::string getCommand();

	void interpretCommand(std::string& command);
	
	void printAvaiableStrategies();
	void readPlayerNumber();
	void readStrategy();

	uint32_t askRoundNumber();
	void printInfo();

	void quitCommand();
	void printHelp();

	void printCommandError();
	
	void defaultGame();

	Game* CurrentGame;
	MenuState CurrentState;

	uint32_t PlayerNumber;
	StrategyIdx* PreferredStrategies;
};

Menu::Menu() {
	CurrentGame = nullptr;
	PreferredStrategies = nullptr;
	PlayerNumber = 0;
	CurrentState = MENU;
}

void Menu::stateMachine() {
	while (CurrentState != QUIT) {
		std::string command = getCommand();
		interpretCommand(command);
	}
}

std::string Menu::getCommand() {
	std::cout << "\n!#: ";
	std::string command;
	std::cin >> command;
	return command;
}

void Menu::interpretCommand(std::string& command) {
	if (command == commands::quitCommand) {
		quitCommand();
	}
	else if (command == commands::helpCommand) {
		printHelp();
	}
	else if (command == commands::defaultGame) {
		defaultGame();
	}
	else if (CurrentState == MENU) {
		if (command == commands::menu::newGameCommand) {
			CurrentState = PREGAME;
			printHelp();
		}
		else {
			printCommandError();
		}
	}
	else if (CurrentState == PREGAME) {
		if (command == commands::pregame::setPlayers) {
			readPlayerNumber();
			PreferredStrategies = new StrategyIdx[PlayerNumber];
		}
		else if (command == commands::pregame::setStrategy) {
			readStrategy();
		}
		else if (command == commands::pregame::playerNumber) {
			std::cout << "\tNumber of players: " << PlayerNumber << std::endl;
		}
		else if (command == commands::pregame::startGameCommand) {
			if (PlayerNumber > 0 && PreferredStrategies != nullptr) {
				CurrentGame = new Game(PlayerNumber, PreferredStrategies);
				CurrentState = GAME;
				printHelp();
			}
			else {
				std::cout << "Need to have a number of players and choose strategy first";
			}
		}
		else {
			printCommandError();
		}
	}
	else if (CurrentState == GAME) {
		if (command == commands::game::roundCommand) {
			CurrentGame->rounds();
		}
		else if (command == commands::game::roundsCommand) {
			CurrentGame->rounds(askRoundNumber());
		}
		else if (command == commands::game::infoCommand) {
			printInfo();
		}
		else {
			printCommandError();
		}
	}
}

void Menu::printAvaiableStrategies() {
	std::cout << "\t\tPacific - all moves turned to help" << std::endl;
	std::cout << "\t\tAgressor - all moves turned to betray" << std::endl;
	std::cout << "\t\tChanger - change turn every move" << std::endl;
	std::cout << "\t\tRepeater - repeat previous turn of enemy" << std::endl;
	std::cout << "\t\tVoter - check how much you betray him and decide what turn choose" << std::endl;
	std::cout << "\t\tRandom - random turn every move" << std::endl;
}

void Menu::readPlayerNumber() {
	std::cout << "\tNumber of players: ";
	int32_t plNum;
	std::cin >> plNum;
	if (plNum <= 0) {
		while (plNum <= 0) {
			std::cout << "\tNumber of players must be positive\n";
			std::cout << "\tNumber of players: ";
			std::cin >> plNum;
		}
	}

	PlayerNumber = plNum;
}

void Menu::readStrategy() {
	if (PlayerNumber == 0) {
		std::cout << "\tEnter number of players first\n";
		return;
	}
	std::cout << "\tPlayer Id: ";
	uint32_t plId;
	std::cin >> plId;
	if (plId <= 0) {
		while (plId <= 0) {
			std::cout << "\tPlayer Id must be positive\n";
			std::cout << "\tPlayer Id: ";
			std::cin >> plId;
		}
	}
	plId--;

	std::string strat;
	bool correctStrategy = false;
	std::cout << "\tStrategy: ";
	std::cin >> strat;
	while (!correctStrategy) {
		if (strat == strategies::pacific) {
			PreferredStrategies[plId] = PACIFIC;
			correctStrategy = true;
		}
		else if (strat == strategies::agressor) {
			PreferredStrategies[plId] = AGRESSOR;
			correctStrategy = true;
		}
		else if (strat == strategies::random) {
			PreferredStrategies[plId] = RANDOM;
			correctStrategy = true;
		}
		else if (strat == strategies::voter) {
			PreferredStrategies[plId] = VOTER;
			correctStrategy = true;
		}
		else if (strat == strategies::repeater) {
			PreferredStrategies[plId] = REPEATER;
			correctStrategy = true;
		}
		else if (strat == strategies::changer) {
			PreferredStrategies[plId] = CHANGER;
			correctStrategy = true;
		}
		else {
			std::cout << "\tWrong strategy. Avaiable strategies: " << std::endl;
			printAvaiableStrategies();
			std::cout << "\tStrategy: ";
			std::cin >> strat;
		}
	}
}

uint32_t Menu::askRoundNumber() {
	int32_t rounds = -1;
	std::cout << "\tNumber of rounds: ";
	std::cin >> rounds;
	if (rounds <= 0) {
		while (rounds <= 0) {
			std::cout << "\tNumber of rounds must be positive" << std::endl;
			std::cout << "\tNumber of rounds: ";
			std::cin >> rounds;
		}
	}

	return rounds;
}

void Menu::printInfo() {
	std::cout << CurrentGame->getLastRound() << std::endl;
	std::cout << CurrentGame->getInfo() << std::endl;
}

void Menu::quitCommand() {
	if (CurrentState == MENU) {
		CurrentState = QUIT;
	}
	else if (CurrentState == PREGAME) {
		if (PreferredStrategies != nullptr)
			delete[] PreferredStrategies;
		PlayerNumber = 0;
		CurrentState = MENU;
	}
	else if (CurrentState == GAME) {
		delete CurrentGame;
		delete[] PreferredStrategies;
		CurrentGame = nullptr;
		PreferredStrategies = nullptr;
		CurrentState = MENU;
	}
	printHelp();
}

void Menu::printHelp() {
	std::cout << "Avaiable commands:" << std::endl;
	if (CurrentState == MENU) {
		std::cout << commands::menu::newGameCommand << "; " <<
			commands::quitCommand << "; " <<
			commands::helpCommand << std::endl;
	}
	else if (CurrentState == PREGAME) {
		std::cout << commands::pregame::playerNumber << "; " <<
			commands::pregame::setPlayers << "; " <<
			commands::pregame::setStrategy << "; " <<
			commands::pregame::startGameCommand << "; " <<
			commands::quitCommand << "; " <<
			commands::helpCommand << std::endl;
	}
	else if (CurrentState == GAME) {
		std::cout << commands::game::infoCommand << "; " <<
			commands::game::roundCommand << "; " <<
			commands::game::roundsCommand << "; " <<
			commands::quitCommand << "; " <<
			commands::helpCommand << std::endl;
	}
	else {
		std::cout << "None" << std::endl;
	}
}

void Menu::printCommandError() {
	std::cout << "Invalid command" << std::endl;
	printHelp();
}

void Menu::defaultGame() {
	PlayerNumber = 3;
	delete[] PreferredStrategies;
	PreferredStrategies = new StrategyIdx[PlayerNumber];
	PreferredStrategies[0] = VOTER;
	PreferredStrategies[1] = RANDOM;
	PreferredStrategies[2] = CHANGER;
	delete CurrentGame;
	CurrentGame = new Game(PlayerNumber, PreferredStrategies);
	CurrentState = GAME;
	printHelp();
}

