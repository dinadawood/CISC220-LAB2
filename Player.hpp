/*
 * Player.hpp
 *
 *  Created on: Jun 18, 2022
 *      Author: dinad
 */

///class declarations - calling it

#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

#ifndef PLAYER_HPP
#define PLAYER_HPP


class Player{
	friend class Othello;
	string name;
	char piece;

public:
   Player();
   Player(string st1,char c);
};

#endif
