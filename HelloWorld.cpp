#include <iostream> //imports input/output library
#include <string> //imports library for creating string variables

int multi(int, int);
int pow(int, int);
void print(std::string);

int main() //initializises function as integer so it can only return an integer, main is run at start (like __init__)
{
	std::string text = " Hello World "; //creates string variable called text

	int num = 10; //creates integer variable called num

	int input; //initializes input variable as int

	signed int x = -5; //signed gives a sign bit for 2s complement this is default

	unsigned int y = 5; //unsigned means no sign bit for 2s complement

	//integers can be 'short' 16bits, 'int' 32bits, 'long', 'long long'

	char a = 'a'; //character or small number, max 8 bits, '' for char "" for string

	//the arrows go towards the data flow
	std::cin >> input; //makes input = to console input 
	std::cout << input << text << num << std::endl; //outputs to console and concetates the variables num and text, endl is like new line
	std::cout << multi(10, 3) << std::endl;
	std::cout << pow(10, 2) << std::endl;
	print(text);

	switch (input) //like a series of if else statements
	{
		case 5: //if its 5
			std::cout << "it is 5";
			break;
		case 6: //else if its 6
			std::cout << "it is 6";
			break;
		case 7: //else if its 7 or 8
		case 8:
			std::cout << "it is 7 or 8";
			break;
		default: //else
			std::cout << "it isnt 5 or 6";
			break;
	}

	//conditional variables (condition) ? (if true) : (if false)
	std::string guess = input == 5 ? "Correct" : "Incorrect";


	//also works on its ownv
	guess == "Correct" ? std::cout << std::endl << guess : std::cout << std::endl << guess << " oof";

	return 0; //returns 0
}

int multi(int x, int y) //initializises function as integer so it can only return an integer
{
	return x * y;
}

int pow(int base, int power)
{
	int num = 1;

	for (int i = 0; i < power; i++) 
	{
		num = num * base;
	}
	
	return num;
}

void print(std::string x) //void functions dont return anything
{
	std::cout << x;
}