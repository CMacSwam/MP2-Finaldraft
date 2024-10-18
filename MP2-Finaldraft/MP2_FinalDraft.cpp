/*
* Author:Chase McCluskey
* Date: 10/17/2024
* File: MP2-Roll'em Pigs
* 
* Description: Create a dice based game using functions, random number generator, and user input against a computer 
*/

#include <iomanip>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

//function prototypes 
char getInput(void);
bool isWinningScore(int score);
bool isTurnPointsLost(int die1value, int die2value);
bool isGameScoreLost(int die1value, int die2value);
int rollDie();

int score1 = 0;
int score2 = 0;
int turn_score1 = 0;
int turn_score2 = 0;
char continue_or_quit;
chrono::nanoseconds seconds(500000000);

//main function 

int main() {
	bool GameWon = false;
	srand(static_cast<unsigned int>(time(0)));

	while (!GameWon) {

		cout << "\n --- Players Turn --- \n";

		bool playerturnover = false;

		while (!playerturnover) {

			char playerchoice = getInput();

			this_thread::sleep_for(seconds);

			if (playerchoice == 'r' || playerchoice == 'R') {

				int die1 = rollDie();
				int die2 = rollDie();

				cout << "You rolled a " << die1 << " and " << die2 << endl;
				this_thread::sleep_for(seconds);

				if (isGameScoreLost(die1, die2)) {
					score1 = 0;
					turn_score1 = 0;
					cout << "You rolled two 1's! You lose all your points! \n";
					playerturnover = true;
				}
				else if (isTurnPointsLost(die1, die2)) {
					turn_score1 = 0;
					cout << "You rolled a 1! You lose your points for this round\n";
					playerturnover = true;
				}
				else {
					turn_score1 += die1 + die2;
					cout << "Your points for this round: " << turn_score1 << endl;
				}
			}

			else if (!cin.fail() && (playerchoice == 'e' || playerchoice == 'E')) {
				score1 += turn_score1;
				turn_score1 = 0;
				playerturnover = true;
			}
		}

		this_thread::sleep_for(seconds);
		cout << "Your total score: " << score1 << endl;

		if (isWinningScore(score1)) {
			cout << "Congradulations! You WON!\n" << endl;
			GameWon = true;
			break;
		}

		bool computerturnover = false;

		this_thread::sleep_for(seconds);

		cout << "\n ---- Computers Turn ---- \n" << endl;

		while (!computerturnover) {
			
			int die1 = rollDie();
			int die2 = rollDie();
			cout << "Computer rolled: " << die1 << " and " << die2 << endl;
			this_thread::sleep_for(seconds);

			if (isGameScoreLost(die1, die2)) {
				score2 = 0;
				cout << "Computer rolled two 1's. Computer loses all points\n";
				computerturnover = true;
			}
			else if (isTurnPointsLost(die1, die2)) {
				turn_score2 = 0;
				cout << "Computer rolled a 1. Computer lost all points for this round\n";
				computerturnover = true;
			}
			else {
				turn_score2 += die1 + die2;
				cout << "Computer's points for that round are " << turn_score2 << endl;

				if (turn_score2 >= 20 || (score2 + turn_score2 >= 100)) {
					score2 += turn_score2;
					turn_score2 = 0;
					computerturnover = true;
				}
			}
		}

		this_thread::sleep_for(seconds);
		cout << "Computers total score: " << score2 << endl;

		if (isWinningScore(score2)) {
			cout << "Computer won the game! Better luck next time\n";
			GameWon = true;
			break;
		}
	}
}

char getInput(void) {
	
	while (!cin.fail() && ((continue_or_quit != 'e') || (continue_or_quit != 'E') || !(continue_or_quit != 'r') || !(continue_or_quit != 'R'))) {
		cout << "\n Enter 'R' if you would like to roll, or enter 'E' if you would like to terminate your turn" << endl;
		cin >> continue_or_quit;
		cout << endl;
		break;
	}

	return continue_or_quit;
}

bool isWinningScore(int score) {
	if (score >= 100) {
		return true;
	}
	else {
		return false;
	}
}

bool isTurnPointsLost(int die1value, int die2value) {
	if (die1value == 1 || die2value == 1) {
		return true;
	}
	else {
		return false;
	}
}

bool isGameScoreLost(int die1value, int die2value) {
	if (die1value == 1 && die2value == 1) {
		return true;
	}
	else {
		return false;
	}
}

int rollDie(void) {
	return rand() % 6 + 1; 
}
