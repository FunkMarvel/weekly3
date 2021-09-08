// Weekly 3 Anders P. Åsbø.
#include <iostream>
#include <random>
#include <Windows.h>

int randNumb();

int main() {
	// Program for playing guess a number.
	int number{};
	int guess{};
	char randyn{};
	int numGuesses = 0;
	
	while (randyn != 'n' && randyn != 'y') {
		// asks whether to generate random number:
		std::cout << "Generate a random number? y/n: ";
		std::cin >> randyn;
		randyn = tolower(randyn);

		switch (randyn)
		{
			case 'n':  // asks for number to guess:
				std::cout << "Enter a number to guess: ";
				std::cin >> number;
				std::cout << std::endl;
				break;
			case 'y':  // generates random number:
				number = randNumb();
			default:  // asks for correct input:
				std::cout << "Please answer 'y' or 'n'." << std::endl;
				break;
		}
	}


	while (guess != number)
	{
		// asks for guess:
		std::cout << "Guess a number: ";
		std::cin >> guess;
		std::cout << std::endl;
		system("cls");
		numGuesses++;

		// checks guess:
		if (guess < number)
		{
			std::cout << guess << " is too low! Guess again." << std::endl;
		}
		else if (guess > number)
		{
			std::cout << guess << " is too high! Guess again." << std::endl;
		}
		else
		{
			std::cout << guess << " is correct! You guessed " << numGuesses << " times." << std::endl;
		}
	}


}

int randNumb() {
	// Function generating random integer from uniform distibutrion
	// in given interval using 64bit Mersenne-Twister (the superior
	// random number generator).

	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> RNG(0, 5);

	// gives interval for random number to user:
	std::cout << "Target number randomly chosen between 0 and 5." << std::endl;
	Sleep(1500);
	system("cls");

	return RNG(gen);
}