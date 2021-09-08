// Weekly 3 Anders P. Åsbø.
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>

int randNumb();
void gameplayLoop();
void saveFile(std::string, int);
void loadFile(std::vector<std::string>&, std::vector<int>&);
void menu();
void leaderBoard();
void delSave();
void clearCin();

int main() {
	// Program for playing guess a number.
	menu();

	return 0;
}

int randNumb() {
	// Function generating random integer from uniform distibutrion
	// in given interval using 64bit Mersenne-Twister (the superior
	// random number generator).
	// Returns random number of type integer.

	int difficulty{};
	int end{};
	std::vector<std::string> difficulties = { "Easy (1-5)", "Medium (1-10)", "Hard (1-30)" };

	// asking for difficulty to determine interval for distribution:
	for (int i = 0; i < 3; i++)
	{
		std::cout << " " << i+1 << ". " << difficulties[i] << std::endl;
	}

	do
	{ // loop persists until valid selection is made.
		clearCin();
		std::cout << "Select difficulty: ";
		std::cin >> difficulty;
		system("cls");

		switch (difficulty)
		{
		case 1:
			end = 5;
			break;
		case 2:
			end = 10;
			break;
		case 3:
			end = 30;
			break;
		default:
			break;
		}

	} while (difficulty != 1 && difficulty != 2 && difficulty != 3);

	// sets up random number generator:
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> RNG(1, end);

	// gives interval for random number to user:
	std::cout << " Target number randomly chosen between 1 and " << end << "." << std::endl;
	system("pause");
	system("cls");

	return RNG(gen);
}

void gameplayLoop()
{
	//Function executing main gameplay loop.
	char want_to_play{ 'y' };
	std::string name{};

	clearCin();
	std::cout << " Type your name: ";
	std::getline(std::cin, name);
	std::cout << std::endl;

	while (want_to_play == 'y')  // looping while player wants to play.
	{
		// game variables
		int number{};
		int guess{};
		char randyn{};
		int numGuesses = 0;

		while (randyn != 'n' && randyn != 'y') {
			// asks whether to generate random number:
			std::cout << " Generate a random number? y/n: ";
			std::cin >> randyn;
			randyn = tolower(randyn);

			switch (randyn)
			{
				case 'n':  // asks for number to guess:
					std::cout << " Enter a number to guess: ";
					std::cin >> number;
					std::cout << std::endl;
					break;
				case 'y':  // generates random number:
					number = randNumb();
					break;
				default:  // asks for correct input:
					std::cout << " Please answer 'y' or 'n'." << std::endl;
					break;
			}
		}


		while (guess != number)
		{
			// asks for guess:
			std::cout << " Guess a number: ";
			std::cin >> guess;
			std::cout << std::endl;
			system("cls");
			numGuesses++;

			// checks guess:
			if (guess < number)
			{
				std::cout << " " << guess << " is too low! Guess again." << std::endl;
			}
			else if (guess > number)
			{
				std::cout << " " << guess << " is too high! Guess again." << std::endl;
			}
			else
			{
				std::cout << " " << guess << " is correct! You guessed " << numGuesses << " times." << std::endl;
			}
		}

		saveFile(name, numGuesses);

		// checks if player wants to play again:
		std::cout << " Play again? y/n: ";
		std::cin >> want_to_play;
		want_to_play = tolower(want_to_play);
	}
	system("cls");
}

void saveFile(std::string name, int score)
{
	// Function for saving name and score to file. Each line
	// contains name of player and their score.
	// 
	// Args:
	//	name - string containing player name.
	//	score - integer containing number of turns to guess.

	//opens savefile:
	std::ofstream ofile("scores.txt", std::ios::app);
	if (ofile.is_open())
	{
		ofile << name << ':' << score << std::endl;  // saves data
		ofile.close();
	}
	else
	{
		std::cout << "Save failed." << std::endl;  // exits on failure to open savefile
		exit(1);
	}
}

void loadFile(std::vector<std::string> &names, std::vector<int> &scores)
{
	// Function for loading save data. Names is stored in names
	// and scores are stored in scores at matching index.
	// 
	// Arg:
	//	names - vector of strings passed by reference.
	//	scores - vector of integers passed by reference.

	std::ifstream ifile("scores.txt");
	std::string line;

	if (ifile.is_open())
	{
		while (std::getline(ifile, line))
		{
			if (line.size() > 0)
			{
				names.push_back(line.substr(0, line.find(':')));
				scores.push_back(stoi(line.substr(line.find(':')+1, -1)));
			}
		}
		ifile.close();
	}
	else
	{
		std::cout << "Load savefile failed." << std::endl;  // exits on failure to open savefile
		exit(1);
	}
}

void menu()
{
	// Function for displaying menu and choosing options.

	std::vector<std::string> menu_options = {
	"~~ Main Menu ~~",
	"Play game (p)",
	"Leaderboard (l)",
	"Delete save (d)",
	"Quit (q)"
	};
	char choice{};

	while (true) { // menu persists until valid selection is made.

		// prints menu options:
		for (int i = 0; i < menu_options.size(); i++)
		{
			if (i != 0)
			{
				std::cout << " " << i << ". " << menu_options[i] << std::endl;
			}
			else
			{
				std::cout << " " << menu_options[i] << std::endl;
			}
		}

		// takes input:
		std::cout << " Input menu number to select: ";
		std::cin >> choice;
		choice = tolower(choice);
		system("cls");

		switch (choice)  // switches to menu option and executes selection.
		{
		case '1': case 'p':  // plays game
			gameplayLoop();
			break;
		case '2': case 'l':  // displays leaderboard (not yet implemented)
			leaderBoard();
			break;
		case '3': case 'd':
			delSave();
			break;
		case '4': case 'q':  // quits game
			return;
		default:
			break;
		}
	}
}

void leaderBoard()
{
	// Function generating leaderboard.

	// reading and storing save data:
	std::vector<std::string> names{};
	std::vector<int> scores{};
	loadFile(names, scores);

	// printing names and scores:
	std::cout << " Number of turns to solve (lower is better): " << std::endl;
	for (int i = 0; i < scores.size(); i++)
	{
		std::cout << " " << i + 1 << ". " << names[i] << ": " << scores[i] << std::endl;
	}
	system("pause");
	system("cls");
}

void delSave() {
	// function that empties save file.

	std::string confirm{};
	std::cout << " Type 'DELETE' to confirm: ";
	std::cin >> confirm;
	if (confirm == "DELETE")
	{
		std::ofstream ofile("scores.txt");  // overwrites savefile with empty file.
		ofile.close();
		std::cout << " Saves deleted." << std::endl;
	}
	else
	{
		std::cout << " Aborted deletion." << std::endl;
	}
	system("pause");
	system("cls");
}

void clearCin()
{
	// Function that clears cin buffer.
	// Courtesy of Johannes Skjeltorp-Borgaas.

	std::cin.clear();
	std::cin.ignore(32767, '\n');
}
