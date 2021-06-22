#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

//initializes fuctions
void playGame();
void printVector(const std::vector<int> &);
int updateHighScores(int);
int getHighScore();

//main function
int main()
{
	//creates a random seed based on current time
	srand(time(NULL));

	int input;

	//do once
	do
	{
		//prints out menu
		std::cout << "Menu\nPlay Game(1) or Quit(0)\n";

		//gets user input, makes it 500 if not valid
		input = std::cin >> input ? input : 500;

		//decides what to do from input
		switch (input)
		{
			case 0:
				//quits
				return 0;
			case 1:
				//plays game
				playGame();
				break;
			default:
				//prints out error
				std::cout << "1 or 0 only\n";
				break;
		}

		//resets input
		input = 10;

		//clears input stream
		std::cin.clear();
		std::cin.ignore();
	} 
	//repeat
	while (input != 0);
}

//play game function
void playGame()
{
	//prints current high score
	std::cout << "Current High Score is " << getHighScore() << std::endl;

	//creates random number
	int range = 100;
	int random = rand() % range+1;

	//creates guess vector (works like a list)
	std::vector<int> guesses;

	std::cout << "Guess the number i've chosen between 0 and " << range << std::endl;

	std::cout << "Guess " << guesses.size() + 1 << std::endl;

	while (true)
	{
		int guess;

		//gets user input, 500 if not valid
		guess = std::cin >> guess ? guess : 500;

		//gives user clues
		if (guess == random)
		{
			std::cout << "You Win\n";

			//adds guess to vector
			guesses.push_back(guess);

			//prints out how many guesses
			std::cout << "You Got it in " << guesses.size() + 1  << " guesses, they were: "<< std::endl;

			printVector(guesses);

			//updates high score and prints whether or not its a new high score
			updateHighScores(guesses.size() + 1) == 1 ? std::cout << "\n NEW HIGH SCORE! \n\n" : std::cout << "";

			break;
		}
		else if (guess > random)
		{
			std::cout << "Lower\n";

			//adds guess to vector
			guesses.push_back(guess);

			//prints out how many guesses
			std::cout << "Guess " << guesses.size() + 1 << std::endl;
		}
		else
		{
			std::cout << "Higher\n";

			//adds guess to vector
			guesses.push_back(guess);

			//prints out how many guesses
			std::cout << "Guess " << guesses.size() + 1 << std::endl;
		}

		//clears input stream
		std::cin.clear();
		std::cin.ignore();
	}
}

//funcion that prints vectors, uses & to make it a reference so the entire vector isnt copied each time and made a const so that it cant be changed
void printVector(const std::vector<int> &vector)
{
	//prints using range for loop, works like "for i in vector" rather than "for i in range(len(vector))"
	for (int i : vector)
	{
		std::cout << i << "  ";
	}

	std::cout << "\n";
}

//function that updates high score file
int updateHighScores(int score)
{
	//gets current high score
	int highScore = getHighScore();

	//updates if current score is better
	if (score < highScore)
	{
		//opens file
		std::ofstream file;
		file.open("HighScores.txt");

		//updates score
		file << score;

		//closes file
		file.close();

		//returns 1 if new high score
		return 1;
	}

	//else returns 0
	return 0;
}

//function that gets highest score
int getHighScore()
{
	//creates input file object
	std::ifstream file;
	file.open("HighScores.txt");

	//returns 99999999 if file cant open
	if (!(file.is_open())) 
	{ 
		return 99999999; 
	}

	//creates highScore variable
	int highScore;
	file >> highScore;

	//closes file
	file.close();

	return highScore;
}