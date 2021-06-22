#include <iostream>
#include <cmath>
#include <iomanip>
#include <float.h>

double longAdd(double a, double b) 
{

}


int main()
{
	long double pi = 0;

	for (int i = 0; i < 92; i++)
	{
		pi = pi + (std::pow(std::tgamma(i + 1), 2) * std::pow(2, i + 1)) / std::tgamma(2 * i + 2);
	}
	std::cout << std::setprecision(31) << pi << std::endl;
	std::cout << "3.141592653589793238462643383279" << std::endl;
	std::cout << LDBL_DIG << std::endl;
}