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
		std::cout << "Generate a random number? y/n: ";
		std::cin >> randyn;
		randyn = tolower(randyn);

		switch (randyn)
		{
			case 'n':
				std::cout << "Enter a number to guess: ";
				std::cin >> number;
				std::cout << std::endl;
				break;
			case 'y':
				number = randNumb();
			default:
				std::cout << "Please answer 'y' or 'n'." << std::endl;
				break;
		}
	}


	while (guess != number)
	{
		std::cout << "Guess a number: ";
		std::cin >> guess;
		std::cout << std::endl;
		system("cls");
		numGuesses++;

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
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> RNG(0, 5);
	std::cout << "Target number randomly chosen between 0 and 5." << std::endl;
	Sleep(1500);

	return RNG(gen);
}