// For this project, I have worked on both TTT and Hangman in separate files. Then I merged both of them into a new cpp file. I still have both of the original files saved.
//I had to rename all of my TTT variables to avoid any conflicting names during the merger.

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <string>
#include <cmath>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
using namespace std;


bool TTTPlayAgain();
bool TTTAskForComputerPlayer();
void TTTPlayWithComputer(char Board[]);
void TTTPlayWithFriend(char Board[]);
bool TTTYNBoolChecker(string Message);
void TTTDisplayBoard(char Board[]);
void TTTHumanPlayerGame(char Board[]);
void TTTComputerPlayerGame(char Board[]);
string TTTAllPlayerStats(string Name, int Wins, int Loss, int Draws, int PlayCount);
void TTTDeclaration();

// I know that global variables are discouraged, but I am actually able to take advantage of them, because I am able to keep track of how these variables are manipulated.
//I make sure that I am only increasing these global variables when I actually need them to be increased or changed, because functions don't change the values of the given variables, plus they only return the value given.
int TTTP1Wins = 0;
bool TTTP1Turn = true;
int TTTP1Loss = 0;
int TTTP1Draws = 0;
int TTTCPWins = 0;
int TTTCPLoss = 0;
int TTTCPDraws = 0;
int TTTP2Wins = 0;
int TTTP2Loss = 0;
int TTTP2Draws = 0;
bool TTTP1GoesFirst = true;
bool StillPlaying = true;
char TTTPiece = 'X';
char TTTOtherPiece = 'O';
char TTTLocation = 0;
string ComputerName = "Socrates";
string TTTName1 = "";
int TTTP1PlayCount = 0;
int TTTP2PlayCount = 0;
int TTTCPPlayCount = 0;
int TTTNum = (int)TTTLocation;
string TTTName2 = "";
bool HangmanSelect = false;
bool Selection();
void BothGames();
const int Repeat = 0;
void TTTStart();


//Both of these functions and variables were made for HM. They are a bit more disorganized, but they all function properly.

void Declaration();
string WordList[1000];
string HangmanBody(int tries);
void Dictionary();
void Player();
string ChosenWord = "";
void Randomizer();
void HangmanGame();
bool PlayAgain();
int Plays = 0;
int Wins = 0;
void HangmanEngine();
string boxBuilder(vector<char> Vector);
vector<char> WordLetters;
bool Win = false;
bool Exit = false;
char Guess = 'a';
bool Loss = false;
int Losses = 0;
vector<char> Asterisk;
vector<char> LettersLeft;
bool CorrectLetter = false;
bool LetterAlreadyPlayed = true;
int AsterisksRemaining;
void AllLettersRemaining();
//if there are any words added to the list, change this value to how many words there are now.
const int AmountOfWords = 1000;

int main()
{
	//This is the start of both games. In fact, all int main() does is ask for the player's name and then goes to the menu.
	Declaration();


	//This checks if the user inputs a name. If the user types enter, the console will reject it.
	cout << "Please enter your name:\n";
	do {
		//getline gets the entire line, including spaces.
		getline(cin, TTTName1);

		//this will ensure that something is inputted. Not just enter.
	} while (TTTName1.size() < 1);
	// the BothGames function is actually kind of like another int main function. Int main starts the program, then the BothGames is the game launcher.
	BothGames();

}
bool TTTPlayAgain() {

	string TTTPlayAgain = "\nWould you like to play again? (Y/N):\n";
	//Asks the user if they want to play again, and then validates their input.
	return TTTYNBoolChecker(TTTPlayAgain);
}
bool TTTAskForComputerPlayer() {

	string Message = "\nDo you want to play against the computer? (\'C\' for Computer, \'P\' for another Player):\n";
	//Again, this function is designed to validate the input of the user. Anything other 
	//return TTTYNBoolChecker(Message);
	//while the constant Repeat is 0 (and it is a constant) the question will keep asking until a valid return type is given.
	while (Repeat == 0) {
		string Response = "";
		cout << Message;
		cin >> Response;
		//The z response is if the user decides to escape the game. If they do, it prints all of the match results.
		if (Response == "z" || Response == "Z") {
			cout << "\nYou have escaped the program.\n\n" << TTTName1 << "\'s total scores for Hangman are: " << Wins << " wins, " << Losses << " losses, and " << Plays << " plays.\n" << TTTAllPlayerStats(TTTName1, TTTP1Wins, TTTP1Draws, TTTP1Loss, TTTP1PlayCount);
			if (TTTP2PlayCount > 0)
				cout << TTTAllPlayerStats(TTTName2, TTTP2Wins, TTTP2Draws, TTTP2Loss, TTTP2PlayCount);
			if (TTTCPPlayCount > 0)
				cout << TTTAllPlayerStats(ComputerName, TTTCPWins, TTTCPDraws, TTTCPLoss, TTTCPPlayCount);
			exit(EXIT_SUCCESS);
			return false;
		}
		else if (Response == "C" || Response == "c")
			return true;

		else if (Response == "P" || Response == "p")
			return false;

		else
			cout << "\nYour answer, \'" << Response << "\', is invalid. Please try again.\n";
	}

}
void TTTPlayWithComputer(char Board[]) {

	cout << "\nYou have chosen to play against the computer named " << ComputerName << ".\n";
	//Because of how that char value works, I have to clear the input, or else it will give multiple values all in one go. By telling the user that only the leading value will be counted, if they put in a value like '13' or '2m' the console will only take the '1' or '2', respectively.
	cout << "\nIf any numbers inputted are greater than 9, then only the leading number will be considered.\n";
	//increases the play count global variables only when called here.
	TTTP1PlayCount++;
	TTTCPPlayCount++;
	do {

		TTTDisplayBoard(Board);
		// This block activates once per turn.
		{
			TTTComputerPlayerGame(Board);
		}
		//all of the winning conditions, all of the TTTNumbers on the board are increased by 1.

	} while (StillPlaying == true);
}
void TTTPlayWithFriend(char Board[]) {
	//If the second human player's name has already been inputted, then the program will already know their name. Otherwise, the player's new name is the input value.
	if (TTTName2 == "") {
		cin.ignore();
		cout << "\nPlease enter P2's name:\n";
		do {
			//Same with P1, this checks to see if something has been entered.
			getline(cin, TTTName2);
			//this will ensure that something is inputted. Not just enter.
		} while (TTTName2.size() < 1);
	}
	//Because the char value is difficult to work with (and the only values that I can both check and apply), I tell the user that any number greater than 9 will only count the first value.
	cout << "\nIf any numbers inputted are greater than 9, then only the leading numumber will be considered.\n";
	//I am careful with the placements of increasing global variables. These two are placed so that the amount of attempts are increased immediately, so if the user quits a match using 'z' or 'Z', the attempts value will go up without any actual wins, draws or ties.
	TTTP1PlayCount++;
	TTTP2PlayCount++;
	//While the match is ongoing, do this function.
	do {
		TTTDisplayBoard(Board);
		// This block activates once per turn.
		{
			TTTHumanPlayerGame(Board);
		}
	} while (StillPlaying == true);
}
bool TTTYNBoolChecker(string Message) {
	//again, repeats the question while Repeat == 0, which since it is a constant...
	while (Repeat == 0) {
		string Response = "";
		cout << Message;
		cin >> Response;
		//The z response is if the user decides to escape the game. If they do, it prints all of the match results.
		if (Response == "z" || Response == "Z") {
			cout << "\nYou have escaped the program.\n\n" << TTTName1 << "\'s total scores for Hangman are: " << Wins << " wins, " << Losses << " losses, and " << Plays << " plays.\n" << TTTAllPlayerStats(TTTName1, TTTP1Wins, TTTP1Draws, TTTP1Loss, TTTP1PlayCount);
			if (TTTP2PlayCount > 0)
				cout << TTTAllPlayerStats(TTTName2, TTTP2Wins, TTTP2Draws, TTTP2Loss, TTTP2PlayCount);
			if (TTTCPPlayCount > 0)
				cout << TTTAllPlayerStats(ComputerName, TTTCPWins, TTTCPDraws, TTTCPLoss, TTTCPPlayCount);
			exit(EXIT_SUCCESS);
			return false;
		}
		else if (Response == "Y" || Response == "y")
			return true;

		else if (Response == "N" || Response == "n")
			return false;

		else
			cout << "\nYour answer, \'" << Response << "\', is invalid. Please try again.\n";
	}
}
void TTTDisplayBoard(char Board[]) {
	//This function prints the board, with any numbers or pieces still on it. I am just using a 1D array, so I just formatted it to look appealing. I could write it as one long line with line breaks, but visually this looks a lot better.
	cout << "\n+---+---+---+" << endl;
	cout << "| " << Board[0] << " | " << Board[1] << " | " << Board[2] << " |" << endl;
	cout << "+---+---+---+\n";
	cout << "| " << Board[3] << " | " << Board[4] << " | " << Board[5] << " |" << endl;
	cout << "+---+---+---+\n";
	cout << "| " << Board[6] << " | " << Board[7] << " | " << Board[8] << " |" << endl;
	cout << "+---+---+---+\n";
}
void TTTHumanPlayerGame(char Board[]) {
	if (TTTP1Turn == true) {
		cout << TTTName1 << ": please enter the space you want to mark with an " << TTTPiece << ":\n";
		cin >> TTTLocation;
		//If multiple values are inputted, the program will only grab the first letter/TTTNumber.
		cin.clear();
		//these cin.ignores are an extrodinary value becuase it will ignore all of the TTTNumbers excluding the first TTTNumber.
		cin.ignore(9999999999999999, '\n');

		while (!((TTTLocation == '1') || (TTTLocation == '2') || (TTTLocation == '3') || (TTTLocation == '4') || (TTTLocation == '5') || (TTTLocation == '6') || (TTTLocation == '7') || (TTTLocation == '8') || (TTTLocation == '9')))
		{
			if (TTTLocation == 'z' || TTTLocation == 'Z') {
				// input of Z or z will end the program inside the function.
				cout << "\nYou have escaped the program.\n\n" << TTTName1 << "\'s total scores for Hangman are: " << Wins << " wins, " << Losses << " losses, and " << Plays << " plays.\n" << TTTAllPlayerStats(TTTName1, TTTP1Wins, TTTP1Draws, TTTP1Loss, TTTP1PlayCount);
				if (TTTP2PlayCount > 0)
					cout << TTTAllPlayerStats(TTTName2, TTTP2Wins, TTTP2Draws, TTTP2Loss, TTTP2PlayCount);
				if (TTTCPPlayCount > 0)
					cout << TTTAllPlayerStats(ComputerName, TTTCPWins, TTTCPDraws, TTTCPLoss, TTTCPPlayCount);
				exit(EXIT_SUCCESS);

			}
			cout << "\nYour input is unreconized. Please try again.\n\n";
			cout << TTTName1 << ": please enter the space you want to mark with an " << TTTPiece << ":\n";
			cin >> TTTLocation;
			cin.clear();
			cin.ignore(9999999999999999, '\n');
			//it will repeat this loop until a valid answer is given, regardless if it is a duplicate or not, which will be checked below.
		}
		TTTNum = (int)TTTLocation;
		if (Board[TTTNum - 49] == TTTOtherPiece || Board[TTTNum - 49] == TTTPiece) {
			cout << "\nA piece is already there. Please try again.\n\n";
			TTTP1Turn = true;
			//if a piece is already on the spot, it is still P1's turn. They haven't played a piece yet.
		}
		else {
			Board[TTTNum - 49] = TTTPiece;
			TTTP1Turn = false;
			//Now that checking is done, sets the Board array value to P1's piece.
		}
	}
	//Skip all of what happened above if it is P2's turn. Also do everything P1 did, just with the other piece.
	else {
		cout << TTTName2 << ": please enter the space you want to mark with an " << TTTOtherPiece << ":\n";
		cin >> TTTLocation;
		//If multiple values are inputted, the program will only grab the first letter/TTTNumber.
		cin.clear();
		cin.ignore(9999999999999999, '\n');
		while (!((TTTLocation == '1') || (TTTLocation == '2') || (TTTLocation == '3') || (TTTLocation == '4') || (TTTLocation == '5') || (TTTLocation == '6') || (TTTLocation == '7') || (TTTLocation == '8') || (TTTLocation == '9')))
		{
			if (TTTLocation == 'z' || TTTLocation == 'Z') {
				// input of Z or z will end the program inside the function.
				cout << "\nYou have escaped the program.\n\n" << TTTName1 << "\'s total scores for Hangman are: " << Wins << " wins, " << Losses << " losses, and " << Plays << " plays.\n" << TTTAllPlayerStats(TTTName1, TTTP1Wins, TTTP1Draws, TTTP1Loss, TTTP1PlayCount);
				if (TTTP2PlayCount > 0)
					cout << TTTAllPlayerStats(TTTName2, TTTP2Wins, TTTP2Draws, TTTP2Loss, TTTP2PlayCount);
				if (TTTCPPlayCount > 0)
					cout << TTTAllPlayerStats(ComputerName, TTTCPWins, TTTCPDraws, TTTCPLoss, TTTCPPlayCount);
				exit(EXIT_SUCCESS);

			}
			cout << "\nYour input is unreconized. Please try again.\n\n";
			cout << TTTName2 << ": please enter the space you want to mark with an " << TTTOtherPiece << ":\n";
			cin >> TTTLocation;
			cin.clear();
			cin.ignore(9999999999999999, '\n');
		}
		//Turns the validated TTTLocation into an integer variable.
		TTTNum = (int)TTTLocation;
		//This is using the ASCII values of intgers and subtracting 49 to turn the values of the integers 0-9 into their coresponding ASCII values.
		if (Board[TTTNum - 49] == TTTOtherPiece || Board[TTTNum - 49] == TTTPiece) {
			cout << "\nA piece is already there. Please try again.\n\n";


			TTTP1Turn = false;
		}
		else {
			Board[TTTNum - 49] = TTTOtherPiece;

			TTTP1Turn = true;
		}
	}
	//These if statements are the winning conditions. They are extremely long, but there are not too many win conditions, so if the board reads one of these types of array values combined, it knows what the board looks like to issue a win or a loss, which is the other if statement with OtherPiece.
	//I check for winning conditions after every turn, because there is not going to be a win until one of the win conditions are met. These are not going to be true until after the 5th turn. Going to check anyway.
	//Because P1 and P2's pieces are dynamic (they can change from X to O and vice versa, I just check if the player's piece is correct.
	if ((Board[0] == TTTPiece && Board[1] == TTTPiece && Board[2] == TTTPiece) || (Board[3] == TTTPiece && Board[4] == TTTPiece && Board[5] == TTTPiece) || (Board[6] == TTTPiece && Board[7] == TTTPiece && Board[8] == TTTPiece) || (Board[3] == TTTPiece && Board[4] == TTTPiece && Board[5] == TTTPiece) || (Board[0] == TTTPiece && Board[3] == TTTPiece && Board[6] == TTTPiece) || (Board[1] == TTTPiece && Board[4] == TTTPiece && Board[7] == TTTPiece) || (Board[2] == TTTPiece && Board[5] == TTTPiece && Board[8] == TTTPiece) || (Board[0] == TTTPiece && Board[4] == TTTPiece && Board[8] == TTTPiece) || (Board[2] == TTTPiece && Board[4] == TTTPiece && Board[6] == TTTPiece)) {
		TTTDisplayBoard(Board);
		cout << TTTName1 << " wins!\n";
		//Sets all of the values issued during an end.
		TTTP1Wins++;
		StillPlaying = false;
		TTTP2Loss++;
		TTTP1GoesFirst = true;
		TTTP1Turn = true;
	}
	//Now checking to see if player 2 has the win condition.
	else if ((Board[0] == TTTOtherPiece && Board[1] == TTTOtherPiece && Board[2] == TTTOtherPiece) || (Board[3] == TTTOtherPiece && Board[4] == TTTOtherPiece && Board[5] == TTTOtherPiece) || (Board[6] == TTTOtherPiece && Board[7] == TTTOtherPiece && Board[8] == TTTOtherPiece) || (Board[3] == TTTOtherPiece && Board[4] == TTTOtherPiece && Board[5] == TTTOtherPiece) || (Board[0] == TTTOtherPiece && Board[3] == TTTOtherPiece && Board[6] == TTTOtherPiece) || (Board[1] == TTTOtherPiece && Board[4] == TTTOtherPiece && Board[7] == TTTOtherPiece) || (Board[2] == TTTOtherPiece && Board[5] == TTTOtherPiece && Board[8] == TTTOtherPiece) || (Board[0] == TTTOtherPiece && Board[4] == TTTOtherPiece && Board[8] == TTTOtherPiece) || (Board[2] == TTTOtherPiece && Board[4] == TTTOtherPiece && Board[6] == TTTOtherPiece)) {
		TTTDisplayBoard(Board);
		cout << TTTName2 << " wins!\n";
		TTTP2Wins++;
		StillPlaying = false;
		TTTP1Loss++;
		TTTP1GoesFirst = false;
		TTTP1Turn = false;
	}
	{
		//This part here is checking to see if all possible spots are taken by pieces. If so, then the game is over and must issue a tie.
		int CheckForEmptySpaces = 0;
		for (int index = 0; index < 9; index++) {
			if (!(Board[index] == 'X' || Board[index] == 'O'))
				CheckForEmptySpaces++;
			//This variable counts if there is any non-X or any non-O values. If so, increase. If it increases one time or more, then there is still a number value on the board.
		}
		if (CheckForEmptySpaces == 0 && StillPlaying == true)
		{
			//If there are no more empty spaces, that means every single spot has an X or O. Therefore there are no spaces left to play.
			cout << "\nThis game resulted in a tie!\nIf you would like to play again, " << TTTName1 << " will go first.\n\n";
			TTTP1Draws++;
			TTTP2Draws++;
			StillPlaying = false;
			TTTP1Turn = true;
			TTTP1GoesFirst = true;
		}
	}
}
string TTTAllPlayerStats(string Name, int Wins, int Draws, int Loss, int PlayCount) {
	//Simply formatting the data into one print line.
	return ("\n" + Name + " played TTT " + to_string(PlayCount) + " time(s), winning " + to_string(Wins) + " time(s), drawing " + to_string(Draws) + " time(s), and losing " + to_string(Loss) + " time(s). Thank you for playing!\n");
}
void TTTComputerPlayerGame(char Board[]) {
	// This if statement is identical to the multiplayer statement.
	if (TTTP1Turn == true) {
		cout << TTTName1 << ": please enter the space you want to mark with an " << TTTPiece << ":\n";
		cin >> TTTLocation;
		//If multiple values are inputted, the program will only grab the first letter/Number.
		cin.clear();
		cin.ignore(9999999999999999, '\n');

		while (!((TTTLocation == '1') || (TTTLocation == '2') || (TTTLocation == '3') || (TTTLocation == '4') || (TTTLocation == '5') || (TTTLocation == '6') || (TTTLocation == '7') || (TTTLocation == '8') || (TTTLocation == '9')))
		{
			if (TTTLocation == 'z' || TTTLocation == 'Z') {
				// input of Z or z will end the program inside the function.
				cout << "\nYou have escaped the program.\n\n" << TTTName1 << "\'s total scores for Hangman are: " << Wins << " wins, " << Losses << " losses, and " << Plays << " plays.\n" << TTTAllPlayerStats(TTTName1, TTTP1Wins, TTTP1Draws, TTTP1Loss, TTTP1PlayCount);
				if (TTTP2PlayCount > 0)
					cout << TTTAllPlayerStats(TTTName2, TTTP2Wins, TTTP2Draws, TTTP2Loss, TTTP2PlayCount);
				if (TTTCPPlayCount > 0)
					cout << TTTAllPlayerStats(ComputerName, TTTCPWins, TTTCPDraws, TTTCPLoss, TTTCPPlayCount);
				exit(EXIT_SUCCESS);

			}
			cout << "\nYour input is unreconized. Please try again.\n\n";
			cout << TTTName1 << ": please enter the space you want to mark with an " << TTTPiece << ":\n";
			cin >> TTTLocation;
			cin.clear();
			cin.ignore(9999999999999999, '\n');
		}
		TTTNum = (int)TTTLocation;
		if (Board[TTTNum - 49] == TTTOtherPiece || Board[TTTNum - 49] == TTTPiece) {
			cout << "\nA piece is already there. Please try again.\n\n";

			TTTP1Turn = true;
		}
		else {
			Board[TTTNum - 49] = TTTPiece;

			TTTP1Turn = false;
		}
	}
	//Here is where the computer is automatically picking pieces.
	else {
		//Initializing the randomization
		srand(time(0));
		int range = 9;
		int randomVal = (rand() % range);
		bool Randomization = false;
		//This is to make the computer appear simalar to an actual player.
		cout << ComputerName << ": please enter the space you want to mark with an " << TTTOtherPiece << ":\n";
		Randomization = false;
		//Repeating the randomization until the computer knows that it picked an open spot.
		while (Randomization == false) {
			randomVal = (rand() % range);
			if ((Board[randomVal] != 'X') && (Board[randomVal] != 'O')) {
				Board[randomVal] = TTTOtherPiece;
				Randomization = true;
			}
		}
		//The computer selects a value to place its piece, then it is the player's turn.
		cout << (randomVal + 1) << endl;
		TTTP1Turn = true;
	}
	//The two win conditions again.
	if ((Board[0] == TTTPiece && Board[1] == TTTPiece && Board[2] == TTTPiece) || (Board[3] == TTTPiece && Board[4] == TTTPiece && Board[5] == TTTPiece) || (Board[6] == TTTPiece && Board[7] == TTTPiece && Board[8] == TTTPiece) || (Board[3] == TTTPiece && Board[4] == TTTPiece && Board[5] == TTTPiece) || (Board[0] == TTTPiece && Board[3] == TTTPiece && Board[6] == TTTPiece) || (Board[1] == TTTPiece && Board[4] == TTTPiece && Board[7] == TTTPiece) || (Board[2] == TTTPiece && Board[5] == TTTPiece && Board[8] == TTTPiece) || (Board[0] == TTTPiece && Board[4] == TTTPiece && Board[8] == TTTPiece) || (Board[2] == TTTPiece && Board[4] == TTTPiece && Board[6] == TTTPiece)) {
		TTTDisplayBoard(Board);
		cout << TTTName1 << " wins!\n";
		TTTP1Wins++;
		StillPlaying = false;
		TTTCPLoss++;
		TTTP1GoesFirst = true;
		TTTP1Turn = true;
	}
	else if ((Board[0] == TTTOtherPiece && Board[1] == TTTOtherPiece && Board[2] == TTTOtherPiece) || (Board[3] == TTTOtherPiece && Board[4] == TTTOtherPiece && Board[5] == TTTOtherPiece) || (Board[6] == TTTOtherPiece && Board[7] == TTTOtherPiece && Board[8] == TTTOtherPiece) || (Board[3] == TTTOtherPiece && Board[4] == TTTOtherPiece && Board[5] == TTTOtherPiece) || (Board[0] == TTTOtherPiece && Board[3] == TTTOtherPiece && Board[6] == TTTOtherPiece) || (Board[1] == TTTOtherPiece && Board[4] == TTTOtherPiece && Board[7] == TTTOtherPiece) || (Board[2] == TTTOtherPiece && Board[5] == TTTOtherPiece && Board[8] == TTTOtherPiece) || (Board[0] == TTTOtherPiece && Board[4] == TTTOtherPiece && Board[8] == TTTOtherPiece) || (Board[2] == TTTOtherPiece && Board[4] == TTTOtherPiece && Board[6] == TTTOtherPiece)) {
		TTTDisplayBoard(Board);
		cout << ComputerName << " wins!\n";
		TTTCPWins++;
		StillPlaying = false;
		TTTP1Loss++;
		TTTP1GoesFirst = false;
		TTTP1Turn = false;
	}
	{
		int CheckForEmptySpaces = 0;
		for (int index = 0; index < 9; index++) {
			if (!(Board[index] == 'X' || Board[index] == 'O'))
				CheckForEmptySpaces++;
		}
		if (CheckForEmptySpaces == 0 && StillPlaying == true)
		{
			cout << "\nThis game resulted in a tie!\nIf you would like to play again, " << TTTName1 << " will go first.\n\n";
			TTTP1Draws++;
			TTTCPDraws++;
			StillPlaying = false;
			TTTP1Turn = true;
			TTTP1GoesFirst = true;
		}
	}
}
void TTTDeclaration() {
	//Printing the declatation box.
	//This was used for my TTT program. I kept it during the merge, but this function is not called.
	cout << "+-----------------------------------------------------------------+\n";
	cout << "|-Application Name: Tic-Tac-Toe                                   |\n";
	cout << "|-Source File: Tic-Tac-Toe.cpp                                    |\n";
	cout << "|-Author/Creator: Darean Wilde                                    |\n";
	cout << "|-Description: Lets the user play TicTacToe with the choice of    |\n";
	cout << "| playing the computer or another player. The first to three      |\n";
	cout << "| symbols matching vertically, horizontally, or diagonally wins.  |\n";
	cout << "|-To quit during a match, please type in \"z\" or \"Z\".              |\n";
	cout << "+-----------------------------------------------------------------+\n";
}
bool Selection() {
	//This is the main menu where the user selects HM or TTT. If 'z' is selected, the game ends, displaying the results.
	while (StillPlaying == true) {
		string Message = "\nWould you like to play Hangman or Tic-Tac-Toe? (\'H\' for Hangman, \'T\' for TTT)\n";

		for (int Search = 0; Search < INFINITY; Search++) {
			string Response = "";
			cout << Message;
			cin >> Response;
			//The z response is if the user decides to escape the game. If they do, it prints all of the match results.
			if (Response == "z" || Response == "Z") {
				cout << "\nYou have escaped the program.\n\n" << TTTName1 << "\'s total scores for Hangman are: " << Wins << " wins, " << Losses << " losses, and " << Plays << " plays.\n" << TTTAllPlayerStats(TTTName1, TTTP1Wins, TTTP1Draws, TTTP1Loss, TTTP1PlayCount);
				if (TTTP2PlayCount > 0)
					cout << TTTAllPlayerStats(TTTName2, TTTP2Wins, TTTP2Draws, TTTP2Loss, TTTP2PlayCount);
				if (TTTCPPlayCount > 0)
					cout << TTTAllPlayerStats(ComputerName, TTTCPWins, TTTCPDraws, TTTCPLoss, TTTCPPlayCount);
				exit(EXIT_SUCCESS);
				return false;
			}
			else if (Response == "H" || Response == "h")
				return true;

			else if (Response == "T" || Response == "t")
				return false;

			else
				cout << "\nYour answer, \'" << Response << "\', is invalid. Please try again.\n";
		}
	}
}
void BothGames() {
	while (StillPlaying == true) {
		if (Selection() == true)
			HangmanGame();
		else
			TTTStart();
		StillPlaying = TTTYNBoolChecker("\nWould you like to return to the main menu? (Y/N)\n");
	}
	cout << "\nThank you for playing!\n\n" << TTTName1 << "\'s total scores for Hangman are: " << Wins << " wins, " << Losses << " losses, and " << Plays << " plays.";
	cout << " \n" << TTTAllPlayerStats(TTTName1, TTTP1Wins, TTTP1Draws, TTTP1Loss, TTTP1PlayCount);
	if (TTTP2PlayCount > 0)
		cout << TTTAllPlayerStats(TTTName2, TTTP2Wins, TTTP2Draws, TTTP2Loss, TTTP2PlayCount);
	if (TTTCPPlayCount > 0)
		cout << TTTAllPlayerStats(ComputerName, TTTCPWins, TTTCPDraws, TTTCPLoss, TTTCPPlayCount);
}
void TTTStart() {
	do {
		//This is the original game board. When displayed, Board[0] = 1, Board[1] = 2, and so forth.
		char Board[9] = { '1','2','3','4','5','6','7','8','9' };
		//this variable defines the start of the round, and while StillPlaying is true, the round is ongoing.
		StillPlaying = true;

		if (TTTP1GoesFirst == true) {
			TTTPiece = 'X';
			TTTOtherPiece = 'O';
		}
		else {
			TTTPiece = 'O';
			TTTOtherPiece = 'X';
		}
		//The TTTAskForComputerPlayer function is activated in the if statement, and if the result is true, then play with the computer. Otherwise, play with another human.
		if (TTTAskForComputerPlayer() == true) {
			TTTPlayWithComputer(Board);
		}
		else
			TTTPlayWithFriend(Board);


		//This loop starting from the do statement determines if the user keeps wanting to play. As soon as 'N' is inputted, the result becomes false, and the program is exited.
	} while (TTTPlayAgain() == true);
	//These prints below are all designed to format the exit statement. It is a given that the user will have an exit statement, and the other two are only printed if those statements are true.

}
void HangmanGame() {
	int Tries = 0;
	//Declaration();
	Dictionary();
	srand(time(0));
	HangmanEngine();

}
/*
+---+\n
| " << ChosenWord.at(index) <<" |\n
+---+\n

+---+\n| " << ChosenWord.at(index) <<" |\n+---+\n

---+\n
 " << ChosenWord.at(index) <<" |\n
---+\n

---+\n " << ChosenWord.at(index) <<" |\n---+\n

*/

void HangmanEngine() {
	do {

		Win = false;
		Loss = false;
		Plays++;
		Randomizer();
		//Enable this line to see the randomly selected word.
		//cout << ChosenWord;
		LettersLeft.clear();
		Asterisk.clear();
		//uses ASCII code to ensure that all characters will return a value, regardless if it is acceptable or not.
		for (int ASCII = 97; ASCII < 123; ASCII++) {
			LettersLeft.push_back(ASCII);
		}
		while (ChosenWord.size() > Asterisk.size()) {
			Asterisk.push_back('*');
		}
		int Attempts = 0;
		while ((Attempts < 6) && (Win == false)) {
			CorrectLetter = false;
			LetterAlreadyPlayed = false;
			//This do statement asks the user to input a value, and it keeps doing this until a proper answer is given.
			do {
				cout << HangmanBody(Attempts) << endl;
				boxBuilder(Asterisk);
				AllLettersRemaining();
				cout << "\nYou have " << 6 - Attempts << " wrong letters left.\nAny letters inputted past the first character will be ignored.";
				cout << "\nPlease enter your guess:\n";
				cin >> Guess;
				cin.ignore(9999999999999999, '\n');
				//This statement is able to turn capital letters into lowercase.
				if (64 < Guess && Guess < 91) {
					Guess = Guess + 32;
				}
				//The last statement turns only uppercase letters lowercase, and then it checks if either the original or newly lowercase letters are valid.
				if (!(96 < Guess && Guess < 123)) {
					cout << "\nThis input is invalid. Please try again.\n";
				}

				else
				{
					//now checking to see if the value has been played or not.
					if ((LettersLeft[Guess - 97] != '-')) {
						LettersLeft[Guess - 97] = '-';
						LetterAlreadyPlayed = true;
					}
					else {
						cout << "\nThat letter has already been played. Please try again.\n";
						LetterAlreadyPlayed = false;
					}
				}
				cout << endl;
				//Now it checks if all of the validation measures are met.
			} while ((!(96 < Guess && Guess < 123)) || (LetterAlreadyPlayed == false));
			AsterisksRemaining = 0;

			CorrectLetter = false;
			for (int index = 0; index < ChosenWord.size(); index++) {

				if (Guess == WordLetters[index]) {
					Asterisk[index] = Guess;
					CorrectLetter = true;
				}
				//This statement is checking to see if any spots are still hidden.
				if (Asterisk[index] == '*') {
					AsterisksRemaining++;
				}
			}


			//If all of the asterisks are gone, that means all of the letters have been revealed, and so the game is won.
			if (AsterisksRemaining == 0)
				Win = true;
			//if the guess is not correct, but has been validated, this is counted as an attempt.
			if (CorrectLetter == false)
				Attempts++;
			//This is the win condition.
			if (Attempts <= 6 && Win == true) {
				cout << HangmanBody(Attempts) << endl;
				boxBuilder(Asterisk);
				Win = true;
				Loss = false;
				Player();
				cout << "\nYou win! The word was \"" << ChosenWord << "\"" << endl;
				Loss = false;
				Win = true;


			}
			//if the win condition has not been met, then it checks for a loss condition. It only checks if the win has not been met, avoiding any conflicts.
			else if (Attempts == 6 && Win == false) {
				cout << HangmanBody(Attempts) << endl;
				boxBuilder(Asterisk);
				AllLettersRemaining();
				Loss = true;
				Win = false;
				Player();
				cout << "\nYou lost! The word was \"" << ChosenWord << "\"" << endl;
				Loss = false;
				Win = true;



			}



		}
		//all of this while the user wants to play again.
	} while (TTTPlayAgain() == true);


}


void Declaration() {
	//the declaration for both games. This is the used function.
	cout << "+------------------------------------------------------------------------+\n";
	cout << "| Application Name: Hangman And Tic-Tac-Toe                              |\n";
	cout << "| Source Files: \"tttgame_DW.cpp\", uses \"Dictionary.txt\"                  |\n";
	cout << "| Author/Creator: Darean Wilde                                           |\n";
	cout << "| Description: The user gets to decide if they want to play hangman      |\n";
	cout << "| or tic-tac-toe. Both games are played traditionally with instructions. |\n";
	cout << "| If playing TTT, please type \'Z\' or \'z\' in the prompt to exit.          |\n";
	cout << "+------------------------------------------------------------------------+\n\n";
}

void Dictionary() {
	//Opens the word file, and then assigns each word on the list with a spot on an array.
	ifstream File;

	File.open("Dictionary.txt");
	string word;

	for (int index = 0; index < AmountOfWords; index++) {
		File >> word;
		WordList[index] = word;
		// Shows which word coresponds to the number
		//cout << WordList[index] << endl << index + 1 << endl << endl;
	}
	File.close();

}
void Randomizer() {
	//This randomizer is used to randomly select a word from the array that was defined in the above function.
	WordLetters.clear();

	int Range = AmountOfWords;
	int Random = (rand() % Range);
	ChosenWord = WordList[Random];
	int Number = 0;
	while (WordLetters.size() < ChosenWord.size()) {
		WordLetters.push_back(ChosenWord.at(Number));

		Number++;
	}
}
void Player() {
	//checks for the player's win conditions.
	if (Win == true) {
		Wins++;
		Win = false;
	}
	else if (Loss == true) {
		Losses++;
		Loss = false;
	}

	//if (Exit == true) {
	//	cout << "\nThank you for playing! Your final score is " << Wins << " win(s), " << Losses << " loss(es), and " << Plays << " play(s).\n";
	//	exit(EXIT_SUCCESS);
	//}
}


string HangmanBody(int tries) {
	// I have hardcoded the hangman's body, by taking the gallows and manipulating it to a two-dimentional image.
	string gallows[7] = { "\n  +-----+\n  |     |\n  |\n  |\n  |\n  |","  +-----+\n  |     |\n  |     o\n  |\n  |\n  |","  +-----+\n  |     |\n  |     o\n  |     |\n  |\n  |","  +-----+\n  |     |\n  |     o\n  |    /|\n  |\n  |","  +-----+\n  |     |\n  |     o\n  |    /|\\\n  |\n  |","  +-----+\n  |     |\n  |     o\n  |    /|\\\n  |    /\n  |","  +-----+\n  |     |\n  |     o\n  |    /|\\\n  |    / \\\n  |" };
	//this comment was for ensuring all of the gallows looked correct.
	// cout << gallows[0] << endl << gallows[1] << endl << gallows[2] << endl << gallows[3] << endl << gallows[4] << endl << gallows[5] << endl << gallows[6];
	if (tries > 6)
		return gallows[6];
	else
		return gallows[tries];
}
/*
		 +-----+\n
		 |     |\n
		 |\n
		 |\n
		 |\n
		 |\n
  -------+---------\n

		 +-----+\n         |     |\n         |\n         |\n         |\n         |\n  -------+---------\n


		 +-----+\n
		 |     |\n
		 |     o\n
		 |\n
		 |\n
		 |\n
  -------+---------\n

		 +-----+\n         |     |\n         |     o\n         |\n         |\n         |\n  -------+---------\n


		 +-----+\n
		 |     |\n
		 |     o\n
		 |     |\n
		 |\n
		 |\n
  -------+---------\n

		 +-----+\n         |     |\n         |     o\n         |     |\n         |\n         |\n  -------+---------\n

		 +-----+\n
		 |     |\n
		 |     o\n
		 |    /|\n
		 |\n
		 |\n
  -------+---------\n

		 +-----+\n         |     |\n         |     o\n         |    /|\n         |\n         |\n  -------+---------\n


		 +-----+\n
		 |     |\n
		 |     o\n
		 |    /|\\\n
		 |\n
		 |\n
  -------+---------\n

		 +-----+\n         |     |\n         |     o\n         |    /|\\\n         | \n         |\n  -------+---------\n


		 +-----+\n
		 |     |\n
		 |     o\n
		 |    /|\\\n
		 |    /\n
		 |\n
  -------+---------\n

		 +-----+\n         |     |\n         |     o\n         |    /|\\\n         |    /\n         |\n  -------+---------\n


		 +-----+\n
		 |     |\n
		 |     o\n
		 |    /|\\\n
		 |    / \\\n
		 |\n
  -------+---------\n

		 +-----+\n         |     |\n         |     o\n         |    /|\\\n         |    / \\\n         |\n  -------+---------\n










		 +-----+\n
		 |     |\n
		 |     o\n
		 |    /|\\n
		 |    / \\n
		 |\n
  -------+---------\n


		 +-----+\n         |     |\n         |     o\n         |    /|\\n         |    / \\n         |\n  -------+---------\n
 */

bool PlayAgain() {

	//This repeat will continue forever, until a return of true or false is given.
	while (Repeat == 0) {
		//asking the user if they want to play again. It is a bool, because I have a few while loops depending on whether this function trturns a true (yes, play again) or no (I'm done).
		string Response = "";
		cout << "\nWould you like to play again? (Y/N):\n";
		cin >> Response;
		if (Response == "Y" || Response == "y") {
			return true;
		}
		else if (Response == "N" || Response == "n") {
			Exit = true;
			Win = false;
			Loss = false;
			Player();
			return false;
		}
		else {
			cout << "\nThis answer is not a Y or N, please try again.\n";
		}

	}
}
string boxBuilder(vector<char> Vector) {
	//This is the box builder for hangman. It counts the amount of letters, then returns the box as a string of a built box. This also prints that box.
	string Box = "+---+";
	for (int index = 0; index < ChosenWord.size() - 1; index++) {
		Box += "---" "+";
	}
	cout << Box << endl;
	for (int index = 0; index < ChosenWord.size(); index++) {
		cout << "| " << Vector.at(index) << " ";
	}
	cout << "|";
	cout << endl << Box << endl;
	return Box;
}
void AllLettersRemaining() {
	//This function is the display counting all of the letters left for HM.
	cout << "Letters remaining:\n";
	int spaces = 0;
	for (int index = 1; index < LettersLeft.size() + 1; index++) {
		//If a letter is used, the letter becomes the char value '-'. If it is, it is ignored. Else, the letter will be printed.
		if (LettersLeft[index - 1] != '-') {
			cout << LettersLeft[index - 1] << " ";
			spaces++;
			//This makes all of the letters display in nice rows of five.
			if (spaces % 5 == 0)
				cout << endl;

		}
	}
	cout << endl;
}
