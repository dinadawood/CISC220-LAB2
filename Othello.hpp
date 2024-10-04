/*
 * Othello.hpp
 *
 *  Created on: Jun 18, 2022
 *      Author: dinad
 */


//class declarations - calling it

#include "Player.cpp"
#include <string>

#ifndef OTHELLO_HPP
#define OTHELLO_HPP

class Othello{
	char board[8][8];
	int size;
	int numPlayers;

	Player p1, p2;

public:
	Othello();
	Othello(string st1, char c);
	Othello(string st1, char c, string st2, char c2);
	void makemat();
	void printmat();
	void placepiece(Player p);
	int countandflippieces(int x, int y, bool flipped, char playerColor);
	bool ckwin();
	int count(int x, int y, bool chngX, bool chngY, int chngDirection, bool flipped, char playerColor );
	void flip(int x, int y, bool chngX, bool chngY, int direction, int chngDirection, int tmp, char playerColor);
	void compplacepiece(Player p);
	void playGame();
};

#endif
