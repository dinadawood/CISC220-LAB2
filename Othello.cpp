/*
 * Othello.cpp
 *
 *  Created on: Jun 18, 2022
 *      Author: dinad
 */


//class definitions - writing the functions/methods
#include <iostream>
#include <stdlib.h>
#include "Othello.hpp"
#include <string>
#include <time.h>

Othello::Othello(){
	size = 8;
	numPlayers = 0;
}

Othello::Othello(string st1, char c): p1(st1, c), p2(){
	size = 8;
	numPlayers = 1;
}

Othello::Othello(string st1, char c, string st2, char c2): p1(st1, c), p2(st2, c2){
	size = 8;
	numPlayers = 2;
}

// makemat() Method:
//done
void Othello::makemat(){
   for(int i = 0; i < 8; i++){
       for(int j = 0; j < 8; j++){
           board[i][j] = '_';
       }
   }
   board[3][3] = p1.piece;
   board[4][4] = p1.piece;
   board[3][4] = p2.piece;
   board[4][3] = p2.piece;
}

// printmat() Method:
//done
void Othello::printmat(){
	cout << "\t";
	for(int i = 0; i < 8; i++){
		cout << i << "\t";
	}
	cout << endl;

	for(int i = 0; i < 8; i++){
		cout << i << "\t";
		for(int j = 0; j < 8; j++){
			cout << board[i][j] << "\t";
		}
		cout << endl;
	}
}

// placepiece() Method:
//done..?
void Othello::placepiece(Player p){
	int x = -1, y = -1;
	bool piecesPlaced = true;
	while(x<0 || x>7 || y<0 || y>7 || board[x][y] != '_'){
		if(!piecesPlaced){
			cout << "Try again..." << endl;
		}
		cout << "Enter row(0-7): ";
		cin >> x;
		cout << "Enter column(0-7): ";
		cin >> y;
		piecesPlaced = false;
	}
	board[x][y] = p.piece;
	int flipped = countandflippieces(x, y, true, p.piece);
	if(flipped == 0){
		cout << "Player forfeits" << endl;
		board[x][y] = '_';
	}
}

// countandflippieces() Method:

int countandflippieces(int x, int y, bool flipped, char playerColor){
	 int sum = 0;
	   sum += count(x, y, true, false, 1, flipped, playerColor);
	   sum += count(x, y, false, true, 1, flipped, playerColor);
	   sum += count(x, y, true, true, 1, flipped, playerColor);
	   sum += count(x, y, true, true, -1, flipped, playerColor);
	   return sum;
}

// count() helper method:
int Othello::count(int x, int y, bool chngX, bool chngY, int chngDirection, bool flipped, char playerColor){
	int row = x;
	int column = y;
	int sum = 0;
	int tmp;
	int counter;

	for(int direction = 1; direction > -2; direction -= -2){
		row = x;
		column = y;
		tmp = 0;
		counter = 1;
		while(row>=0 && row<8 && column>=0 && column<8){
			if(chngX){
				row = x - counter*direction*chngDirection;
			}
			if(chngY){
				column = y - counter*direction;
			}
			if(board[row][column] == '_'){
				row = -1;
			}
			else if(board[row][column] == playerColor){
				sum += tmp;
			}
			if(flipped){
				flip(x, y, chngX, chngY, direction, chngDirection, tmp, playerColor);
				row = -1;
			}
			else if(board[row][column] != playerColor && board[row][column] != '_'){
				tmp++;
				counter++;
			}
		}
	}
	return sum;
}

// flip() method:
void flip(int x, int y, bool chngX, bool chngY, int direction, int chngDirection, int tmp, char playerColor){
	int row = x;
	int column = y;
	for(int counter = 1; counter<=tmp; counter++){
			if(chngX){
				row = x-counter*direction*chngDirection;
			}
			if(chngY){
				column = y-counter*direction;
			}
		board[row][column] = playerColor;
	}
}

// compplacepiece() Method:
//done
void Othello::compplacepiece(Player p){
	int sum = 0;
	int indx = 0;
	int x[60];
	int y[60];
	srand(time(NULL));

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if (board[i][j] == '_'){
				if(countandflippieces(i, j, false, p.piece)>sum){
					sum = countandflippieces(i, j, false, p.piece);
				}
			}
		}
	}

	for(int k=0; k<8; k++){
		for(int l = 0; l<8; l++){
			if(board[k][l] == '_' && countandflippieces(k, l, false, p.piece) == sum){
				x[indx] = k;
				y[indx] = l;
				indx++;
			}
		}
	}

	int randIndx = rand() % indx;
	countandflippieces(x[randIndx], y[randIndx], true, p.piece);
	board[x[randIndx]][y[randIndx]] = p.piece;
}

// ckwin() Method:
//done
bool Othello::ckwin(){
	int p1Pieces = 0;
	int p2Pieces = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j] == p1.piece){
				p1Pieces++;
			}
			else if(board[i][j] == p2.piece){
				p2Pieces++;
			}
			else if(board[i][j] == '_'){
				return false;
			}
		}
	}
	if(p1Pieces > p2Pieces){
		cout << p1.name << "won with: "<< p1Pieces << " versus " << p2Pieces << endl;
	}
	else if(p1Pieces < p2Pieces){
		cout << p2.name << "won with: "<< p2Pieces << " versus " << p1Pieces << endl;
	}
	else if(p1Pieces == p2Pieces){
		cout << "A tie" << endl;
	}
}

//playGame Method:
//done
void Othello::playGame(){
	makemat();
	printmat();
	bool play = true;
	int fullsqrs = 0;
	Player p = p1;
	bool whichp = true;
	bool turn = true;
	if (rand()%2 == 0) {  // p1 plays first
		p = p2;
		turn = false;
		whichp = false;
	}
	while ((play) && (fullsqrs < 64)){
		cout << endl << p.name <<" ("<<p.piece<<") choose your square: "<<endl;
		if ((numPlayers == 2) || ((numPlayers == 1) && turn)){
			placepiece(p);
		}
		else if ((numPlayers == 0) || ((numPlayers == 1) && (turn == false))){
			compplacepiece(p);
		}
		turn = !turn;
		printmat();
		if (whichp) {
			p = p2;
			whichp = false;
		}
		else {
		p = p1;
		whichp = true;
		}
		fullsqrs+=1;
	}
	ckwin();
}
