#include <iostream>
#include <random>
#include <Windows.h>

using namespace std;

int main() {
	int number{};
	int guess{};
	char randyn{};
	int numGuesses = 0;

	cout << "Generate a random number? y/n: ";
	cin >> randyn;

	if (tolower(randyn) == 'n')
	{
		cout << "Enter a number to guess: ";
		cin >> number;
		cout << endl;
	}
	else
	{
		random_device rd;
		mt19937_64 gen(rd());
		uniform_int_distribution<int> RNG(0, 1000);

		number = RNG(gen);

		cout << "Target number randomly chosen between 0 and 1000." << endl;
		Sleep(1500);
	}


	while (guess != number)
	{
		cout << "Guess a number: ";
		cin >> guess;
		cout << endl;
		system("cls");
		numGuesses++;

		if (guess < number)
		{
			cout << "Too low! Guess again." << endl;
		}
		else if (guess > number)
		{
			cout << "Too high! Guess again." << endl;
		}
		else
		{
			cout << "Correct! You guessed " << numGuesses << " times." << endl;
		}
	}


}