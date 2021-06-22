#include <iostream>
#include <string>
#include <cmath>

//denary to binary converter
std::string denBin(int number)
{
	std::string out = "";

	while (number != 0)
	{
		//appending the modulo of the number
		out.append(std::to_string(number % 2));

		//bitshifts the number 1 to the right (flat division by 2)
		number >>= 1;
	}

	//flips 'out' string
	std::string backOut;
	for (int i = out.size() - 1; i >= 0; i--)
	{
		backOut += out[i];
	}
	return backOut;
}
 
//binary to denary converter
int binDen(std::string number)
{
	int out = 0;
	//decrementing for loop through the number
	for (int i = number.size() - 1; i >= 0; i--)
	{
		//adding the power of 2 for each 1 in the number
		out += pow(number[i] == '1' ? 2 : 0, i);
	}
	return out;
}

int main()
{
	//output
	std::cout << denBin(2523) << "\n" << binDen("10100101") << "\n" << binDen("1001");
}