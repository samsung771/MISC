#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include "Noise.h"
#include "ConGame.h"

int size = 50;

//node data type
struct node
{
    bool obstacle = false;
    bool tested = false;
    int x;
    int y;
    double gWeight = 1000000;
    double lWeight = 1000000;
    std::vector<node*> neighbours;
    node* parent = nullptr;
};

//operator overloads
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<double>>& a)
{
    /*
    char square = 219;
    for (std::vector<double> i : a)
    {
        for (double j : i)
        {
            if (j == 1)
            {
                os << square;
                os << square;
                //os << square;
                //os << square;
            }
            else if (j == 0)
            {
                os << "SS";
            }
            else if (j == 0.1)
            {
                os << "EE";
            }
            else if (j == 100)
            {
                os << "--";
            }
            else
            {
                os << "  ";
            }
        }
        os << "\n";
        
        for (double j : i)
        {
            if (j == 1)
            {
                os << square;
                os << square;
                os << square;
                os << square;
            }
            else if (j == 0)
            {
                os << "SSSS";
            }
            else if (j == 0.1)
            {
                os << "EEEE";
            }
            else
            {
                os << "    ";
            }
        }
        os << "\n";
        
    }
*/
    createSquare(COORD{ 0,0 }, COORD{ (short)(size), (short)size }, WHITE);
    for (short i = 0; i < a.size(); i++)
    {
        for (short j = 0; j < a[0].size(); j++)
        {
            if (a[i][j] == 100000)
            {
                createPix(COORD{ (short)(j * 2), i }, BLACK);
            }
            else if (a[i][j] == 0)
            {
                createPix(COORD{ (short)(j * 2), i }, GREEN);
            }
            else if (a[i][j] == 0.1)
            {
                createPix(COORD{ (short)(j * 2), i }, RED);
            }
            else if (a[i][j] == 100)
            {
                createPix(COORD{ (short)(j * 2), i }, BLUE);
            }
        }
    }

    SetConsoleTextAttribute(hConsole, WHITE);
    SetConsoleCursorPosition(hConsole, COORD{ 0, (short)(size+ 2)});

    return os;
}

void printNoise(const std::vector<std::vector<double>>& a)
{
    createSquare(COORD{ 0,0 }, COORD{ (short)(size), (short)size }, WHITE);
    for (short i = 0; i < a.size(); i++)
    {
        for (short j = 0; j < a[0].size(); j++)
        {
            if (a[i][j] >= 180)
            {
                createPix(COORD{ (short)(j * 2), i }, BLACK);
            }
            else if (a[i][j] >= 125)
            {
                createPix(COORD{ (short)(j * 2), i }, GREY);
            }
        }
    }

    SetConsoleTextAttribute(hConsole, WHITE);
    SetConsoleCursorPosition(hConsole, COORD{ 0, (short)(size + 2) });
}

bool operator== (node a, node* b)
{
    if (a.x == b->x && a.y == b->y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//func makes the grid a map
void normalise(std::vector<std::vector<double>>& a)
{
    for (int x = 0; x < a.size(); x++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            if (a[x][j]/255 < 0.6)
            {
                a[x][j] = 1;
            }
            else
            {
                a[x][j] = 100000;
            }
        }
    }
}

//A* func
std::vector<std::vector<int>> Astar(std::vector<std::vector<double>> map, int& Sx, int& Sy, int& Ex, int& Ey)
{
    //lambda function, distance = [] == distance = lambda, (a,b) == lambda x,y also needs a semi colon at the end
    //returns the euclidian distance using pythagoras
    auto distance = [](node* a, node* b) 
    {
        return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
    };

    auto heuristic = [&](node* a, node* b) 
    {
        return distance(a, b);
    };

    std::vector<std::vector<node>> grid;
    for (int y = 0; y < map.size(); y++)
    {
        std::vector<node> temp;
        for (int x = 0; x < map[0].size(); x++)
        {
            node xy;

            if (map[y][x] == 100000)
            {
                xy.obstacle = true;
            }
            xy.x = x;
            xy.y = y;
            temp.push_back(xy);
        }
        grid.push_back(temp);
    }

    //giving neighbour pointers to each node
    for (int y = 0; y < grid.size(); y++)
    {
        for (int x = 0; x < grid[0].size(); x++)
        {
            if (y > 0)
            {
                grid[y][x].neighbours.push_back(&grid[y - 1][x]);
                if (x < grid.size()-1)
                {
                    grid[y][x].neighbours.push_back(&grid[y - 1][x + 1]);
                }
                if (x > 0)
                {
                    grid[y][x].neighbours.push_back(&grid[y - 1][x - 1]);
                }
            }
            if (x > 0)
            {
                grid[y][x].neighbours.push_back(&grid[y][x - 1]);
            }
            if (x < grid.size()-1)
            {
                grid[y][x].neighbours.push_back(&grid[y][x + 1]);
            }
            if (y < grid.size()-1)
            {
                grid[y][x].neighbours.push_back(&grid[y + 1][x]);
                if (x < grid.size() - 1)
                {
                    grid[y][x].neighbours.push_back(&grid[y + 1][x + 1]);
                }
                if (x > 0)
                {
                    grid[y][x].neighbours.push_back(&grid[y + 1][x - 1]);
                }
            }
        }
    }

    //creates pointers start and end nodes
    node* nodeEnd = &grid[Ey][Ex];

    node* nodeStart = &grid[Sy][Sx];
    nodeStart->lWeight = 0.0f;
    nodeStart->gWeight = heuristic(nodeStart, nodeEnd);

    node* nodeCurrent = nodeStart;

    //creates queue array of pointers
    std::vector<node*> Queue;
    Queue.push_back(nodeCurrent);

    int nodesChecked = 1;

    //searching until it finds the end or the queue is empty
    while (!Queue.empty() && !(*nodeCurrent == nodeEnd))
    {
        //sorts the queue using a compare lambda function that returns what gWeight is higher
        std::sort(Queue.begin(), Queue.end(), [](node* a, node* b) {return a->gWeight < b->gWeight; });

        //removes tested nodes from queue
        while (!Queue.empty() && Queue.front()->tested)
        {
            Queue.erase(Queue.begin());
        }

        //breaks loop if queue is finished
        if (Queue.empty())
        {
            break;
        }

        //changes current node
        nodeCurrent = Queue.front();
        nodeCurrent->tested = true;
        nodesChecked++;

        //goes through each neighbour of the current node
        for (node* nodeNeighbour : nodeCurrent->neighbours)
        {
            //add node to queue if not already tested or an obstacle
            if (!nodeNeighbour->tested && !nodeNeighbour->obstacle)
            {
                Queue.push_back(nodeNeighbour);
            }

            //changes the local weight of the node if its smaller
            double goalTest = nodeCurrent->lWeight + distance(nodeCurrent, nodeNeighbour);

            if (goalTest < nodeNeighbour->lWeight)
            {
                //updates parent node if its changed
                nodeNeighbour->parent = nodeCurrent;
                nodeNeighbour->lWeight = goalTest;

                //updatees global weight
                nodeNeighbour->gWeight = nodeNeighbour->lWeight + heuristic(nodeNeighbour, nodeEnd);
            }
        }
    }

    std::cout << "nodes checked " << nodesChecked << "/" << size*size << '\n';

    node* backtracker = &grid[Ey][Ex];

    //creates vector of coords for the trail
    std::vector<std::vector<int>> trail;

    //while the backtracker is not at the start
    while (!(*backtracker == nodeStart))
    {
        //add the backtracker to the list
        trail.push_back({backtracker->x, backtracker->y});

        //changes backtracker pointer to the parent of the current node
        backtracker = backtracker->parent;
    }
    std::cout << nodeCurrent->lWeight << '\n';

    return trail;
}

//makes a ppm img with a template so any vector will work
template <class matrix>
void makeImg(std::string name, matrix& a)
{
    std::ofstream img(name);
    img << "P3\n";
    img << a.size() << " " << a[0].size() << "\n";
    img << "255\n";

    for (int y = 0; y < a.size(); y++)
    {
        for (int x = 0; x < a[0].size(); x++)
        {
            if (a[y][x] == 0)
            {
                img << 0 << " " << 255 << " " << 0 << "\n";
            }
            else if (a[y][x] == 0.1)
            {
                img << 255 << " " << 0 << " " << 0 << "\n";
            }
            else if (a[y][x] == 100000)
            {
                img << 0 << " " << 0 << " " << 0 << "\n";
            }
            else if (a[y][x] == 100)
            {
                img << 0 << " " << 0 << " " << 255 << "\n";
            }
            else
            {
                img << 255 << " " << 255 << " " << 255 << "\n";
            }
        }
    }
    img.close();
}

int main()
{
    system("cls");
    
    std::vector<std::vector<double>> grid = noise::Perlin2D(size);

    std::cout << "press space to start\n";

    while (true)
    {
        if (GetKeyState(' ') & 0x8000)
        {
            break;
        }
        else if (GetKeyState('A') & 0x8000)
        {
            printNoise(grid);
        }
    }

    system("cls");

    srand(time(0));
    int Sx = rand() % size;
    int Sy = rand() % size;

    int Ex = rand() % size;
    int Ey = rand() % size;

    normalise(grid);

    grid[Sy][Sx] = 0;
    grid[Ey][Ex] = 0.1;

    makeImg("normal.ppm", grid);

    std::cout << grid;
    std::vector<std::vector<int>> trail = Astar(grid, Sx,Sy,Ex,Ey);
    for (int i = 0; i < trail.size(); i++)
    {
        grid[trail[i][1]][trail[i][0]] = 100;
    }

    grid[Ey][Ex] = 0.1;

    makeImg("solved.ppm", grid);

    std::cout << grid;

    while (true)
    {
        if (GetKeyState(27) & 0x8000)
        {
            break;
        }
    }

    SetConsoleTextAttribute(hConsole, WHITE);
    SetConsoleCursorPosition(hConsole, COORD{ 0, (short)(size + 4) });
}