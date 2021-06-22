#include <iostream>
#include <string>

int main()
{
	std::string text = "this is a test hello";
	std::string toRemove = "hell";
	text.replace(text.find(toRemove), toRemove.length(), (toRemove[0] + std::string(toRemove.length() - 1, '*')));

	std::cout << text << std::endl;

	std::cout << text.substr(0, 4);
}