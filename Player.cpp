/*
 * Player.cpp
 *
 *  Created on: Jun 18, 2022
 *      Author: dinad
 */

//class definitions - writing the functions/methods


#include "Player.hpp"
#include <string>

Player::Player(){
	name = "computer";
	piece = 'B';
}

Player::Player(string st1, char c){
	name = st1;
	piece = c;
}
