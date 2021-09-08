// Weekly 3 Anders P. Åsbø.
#include <iostream>
#include <random>
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>

int randNumb();
void gameplayLoop();
void saveFile(std::string, int);
void menu();

int main() {
	// Program for playing guess a number.
	menu();

	return 0;
}

int randNumb() {
	// Function generating random integer from uniform distibutrion
	// in given interval using 64bit Mersenne-Twister (the superior
	// random number generator).

	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> RNG(0, 5);

	// gives interval for random number to user:
	std::cout << " Target number randomly chosen between 0 and 5." << std::endl;
	Sleep(1500);
	system("cls");

	return RNG(gen);
}

void gameplayLoop()
{
	char want_to_play{ 'y' };

	while (want_to_play == 'y')
	{
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
		std::cout << " Play again? y/n: ";
		std::cin >> want_to_play;
		want_to_play = tolower(want_to_play);
	}

}

void saveFile(std::string name, int score)
{
	std::ofstream ofile("\saves\scores.txt", std::ios::app);
	if (ofile.is_open())
	{
		ofile << name << " " << score << std::endl;
		ofile.close();
	}
	else
	{
		std::cout << "Save failed." << std::endl;
		exit(1);
	}
}

void menu()
{
	std::vector<std::string> menu_options = {
	"~~ Main Menu ~~",
	"Play game (p)",
	"Leaderboard (l)",
	"Quit (q)"
	};
	char choice{};

	while (choice != 'n') {
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

		std::cout << " Input menu number to select: ";
		std::cin >> choice;
		choice = tolower(choice);

		switch (choice)
		{
		case '1': case 'p':
			gameplayLoop();
			break;
		case '2': case 'l':
			break;
		case '3': case 'q':
			return;
		default:
			break;
		}
		system("cls");
	}
}
