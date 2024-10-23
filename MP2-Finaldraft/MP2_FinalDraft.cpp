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

//global vairables - known to all functions
int score1 = 0;
int score2 = 0;
int turn_score1 = 0;
int turn_score2 = 0;
char continue_or_quit;

//time implementation
chrono::nanoseconds seconds(500000000);

//main function 
int main() {

	bool GameWon = false;

	//ensuring all random numbers are not repeats (implement srand())
	srand(static_cast<unsigned int>(time(0)));

	while (!GameWon) {

		cout << "\n --- Players Turn --- \n";

		bool playerturnover = false;

		while (!playerturnover) {

			//utilize input function(getInput) and implement a wait before next output
			char playerchoice = getInput();
			this_thread::sleep_for(seconds);

			if (playerchoice == 'r' || playerchoice == 'R') {

				//rolling die
				int die1 = rollDie();
				int die2 = rollDie();

				//printing out die values, followed by a wait function 
				cout << "You rolled a " << die1 << " and " << die2 << endl;
				this_thread::sleep_for(seconds);

				//Function takes 2 integer arguments, if true, total score and round score points are lost, player turn over 
				if (isGameScoreLost(die1, die2)) {
					score1 = 0;
					turn_score1 = 0;
					cout << "You rolled two 1's! You lose all your points! \n";
					playerturnover = true;
				}

				//Function takes 2 integer arguments, if ture, round score is lost, player turn over 
				else if (isTurnPointsLost(die1, die2)) {
					turn_score1 = 0;
					cout << "You rolled a 1! You lose your points for this round\n";
					playerturnover = true;
				}

				//If previous functions fail, then die values added to round score, print out updated score for round
				else {
					turn_score1 += die1 + die2;
					cout << "Your points for this round: " << turn_score1 << endl;
				}
			}

			//If player terminates turn, then round score is added to total score, and round score reset to 0, player tun over 
			else if (!cin.fail() && (playerchoice == 'e' || playerchoice == 'E')) {
				score1 += turn_score1;
				turn_score1 = 0;
				playerturnover = true;
			}
		}

		//wait function, then total score printed 
		this_thread::sleep_for(seconds);
		cout << "Your total score: " << score1 << endl;

		//checking to see if player won, if true, gameover(while loop terminated)
		if (isWinningScore(score1)) {
			cout << "Congradulations! You WON!\n" << endl;
			GameWon = true;
			break;
		}

		//computers turn
		bool computerturnover = false;

		this_thread::sleep_for(seconds);

		cout << "\n ---- Computers Turn ---- \n" << endl;

		while (!computerturnover) {
			
			//rolling die
			int die1 = rollDie();
			int die2 = rollDie();

			//prints out die values, then wait function 
			cout << "Computer rolled: " << die1 << " and " << die2 << endl;
			this_thread::sleep_for(seconds);

			//Function takes 2 integer values as arguments, if true(both die = 1), round score and total score lost, computer turn over 
			if (isGameScoreLost(die1, die2)) {
				turn_score2 = 0;
				score2 = 0;
				cout << "Computer rolled two 1's. Computer loses all points\n";
				computerturnover = true;
			}

			//Function takes 2 integer arguments, if true(either die = 1), round score is lost, computer turn over 
			else if (isTurnPointsLost(die1, die2)) {
				turn_score2 = 0;
				cout << "Computer rolled a 1. Computer lost all points for this round\n";
				computerturnover = true;
			}

			//If above functions false, then die vlaues added to round score, then printed out 
			else {
				turn_score2 += die1 + die2;
				cout << "Computer's points for that round are " << turn_score2 << endl;

				//checking computer score, if greater then 20 or 100, round score added to total score, round score reset, computer turn over 
				if (turn_score2 >= 20 || (score2 + turn_score2 >= 100)) {
					score2 += turn_score2;
					turn_score2 = 0;
					computerturnover = true;
				}
			}
		}

		//wait function, then computer total score printed 
		this_thread::sleep_for(seconds);
		cout << "Computers total score: " << score2 << endl;

		//checking if computer won, if true, game while loop terminated 
		if (isWinningScore(score2)) {
			cout << "Computer won the game! Better luck next time\n";
			GameWon = true;
			break;
		}
	}
}

//Introduction function--prompting user for input
char getInput(void) {
	
	while (!cin.fail() && ((continue_or_quit != 'e') || (continue_or_quit != 'E') || !(continue_or_quit != 'r') || !(continue_or_quit != 'R'))) {
		cout << "\n Enter 'R' if you would like to roll, or enter 'E' if you would like to terminate your turn" << endl;
		cin >> continue_or_quit;
		cout << endl;
		break;
	}

	return continue_or_quit;
}

//checking if score is greater than 100
bool isWinningScore(int score) {

	if (score >= 100) {
		return true;
	}
	else {
		return false;
	}
}

//if one die = 1 score points are lost 
bool isTurnPointsLost(int die1value, int die2value) {

	if (die1value == 1 || die2value == 1) {
		return true;
	}

	else {
		return false;
	}
}

//checking if both die = 1, then round score and total score lost 
bool isGameScoreLost(int die1value, int die2value) {

	if (die1value == 1 && die2value == 1) {
		return true;
	}

	else {
		return false;
	}
}

//rolling die function 
int rollDie(void) {

	return rand() % 6 + 1; 

}
