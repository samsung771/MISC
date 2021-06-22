#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <chrono>
#include "ConGame.h"

#define x 10
#define y 20

std::vector<std::vector<Colour>> J = { {EMPTY,BLUE},{EMPTY,BLUE},{BLUE,BLUE} };
std::vector<std::vector<Colour>> S = { {GREEN,EMPTY},{GREEN,GREEN},{EMPTY,GREEN} };
std::vector<std::vector<Colour>> Z = { {EMPTY,RED},{RED,RED},{RED,EMPTY} };
std::vector<std::vector<Colour>> L = { {EMPTY,LRED},{EMPTY,LRED},{LRED,LRED} };
std::vector<std::vector<Colour>> O = { {YELLOW,YELLOW},{YELLOW,YELLOW} };
std::vector<std::vector<Colour>> T = { {PINK,EMPTY},{PINK,PINK},{PINK,EMPTY} };
std::vector<std::vector<Colour>> I = { {LBLUE},{LBLUE},{LBLUE},{LBLUE} };

enum Move {NONE = 0, LEFT, RIGHT};

Move rot = NONE;
COORD currPos = { 12,0 };

int moveTime = 500;
int rotTime = 200;

std::chrono::steady_clock::time_point lastMove;
std::chrono::steady_clock::time_point lastRot;
std::chrono::steady_clock::time_point curTime;

std::vector<std::vector<Colour>> temp = J;

std::vector<std::vector<Colour>> rotateRight(const std::vector<std::vector<Colour>>& matrix)
{
	std::vector<std::vector<Colour>> newVect;
	for (int i = matrix[0].size()-1; i >= 0; i--)
	{
		std::vector<Colour> temp;
		for (int j = 0; j < matrix.size(); j++)
		{
			temp.push_back(matrix[j][i]);
		}
		newVect.push_back(temp);
	}
	return newVect;
}

std::vector<std::vector<Colour>> rotateLeft(const std::vector<std::vector<Colour>>& matrix)
{
	std::vector<std::vector<Colour>> newVect;
	for (int i = 0; i < matrix[0].size(); i++)
	{
		std::vector<Colour> temp;
		for (int j = matrix.size()-1; j >= 0; j--)
		{
			temp.push_back(matrix[j][i]);
		}
		newVect.push_back(temp);
	}
	return newVect;
}

void Setup()
{
	system("cls");
	createSquare(COORD{ 0,0 }, COORD{ (short)(x + 2), (short)(y + 1) }, WHITE);
	createSquare(COORD{ 2,0 }, COORD{ x + 2, y }, BLACK);
}

void Input()
{
	if (GetKeyState('A') & 0x8000)
	{
		rot = rot == RIGHT ? NONE : LEFT;
	}
	if (GetKeyState('S') & 0x8000)
	{
		//speed up
	}
	if (GetKeyState('D') & 0x8000)
	{
		rot = rot == LEFT ? NONE : RIGHT;
	}
}

void Update()
{
	curTime = std::chrono::steady_clock::now();

	if (std::chrono::duration_cast<std::chrono::milliseconds>(curTime - lastMove).count() >= moveTime)
	{
		eraseShape(temp, currPos);
		currPos.Y++;
		createShape(temp, currPos);
		lastMove = std::chrono::steady_clock::now();
		rotTime = 200;
		rot = NONE;
	}
	if (std::chrono::duration_cast<std::chrono::milliseconds>(curTime - lastRot).count() >= rotTime)
	{
		if (rot == LEFT)
		{
			eraseShape(temp, currPos);
			temp = rotateLeft(temp);
			createShape(temp, currPos);
			rotTime = 500;
		}
		if (rot == RIGHT)
		{
			eraseShape(temp, currPos);
			temp = rotateRight(temp);
			createShape(temp, currPos);
			rotTime = 500;
		}
		rot = NONE;
		lastRot = std::chrono::steady_clock::now();
	}
}

int main()
{
	Setup();
	while (true)
	{
		Update();
		Input();
	}

	SetConsoleCursorPosition(hConsole, COORD{0, y+2});
}