#include <vector>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <cmath>
#include "Noise.h"

namespace noise
{
    //perlin noise generator
    std::vector<std::vector<double>> Perlin2D(int& size, int seeds)
    {
        int size2 = size * size;

        //creates 1d array and populates it with random nums between 0 and 1
        std::vector<double> seed;
        srand(seeds);
        for (int i = 0; i < size2; i++)
        {
            seed.push_back((double)(rand() % 10000) / 10000);
        }

        //finds out how many times the array can be divided by 2
        int octaves = 0;
        while (size >> octaves != 1)
        {
            octaves++;
        }

        //creates output matrix and populates with 0s
        std::vector<std::vector<double>> output;
        for (int i = 0; i < size; i++)
        {
            std::vector<double> place;
            for (int j = 0; j < size; j++)
            {
                place.push_back(0);
            }
            output.push_back(place);
            place.clear();
        }

        double total = 0;
        double multiplyer = 1;
        for (int i = 0; i < octaves; i++)
        {
            for (int x = 0; x < output.size(); x++)
            {
                for (int j = 0; j < output[0].size(); j++)
                {
                    output[x][j] = output[x][j] + multiplyer * seed[((size >> i) + (x + 1) * output.size() + j) % size2];
                }
            }
            total = total + multiplyer;
            multiplyer = multiplyer / 2;
        }

        for (int x = 0; x < output.size(); x++)
        {
            for (int j = 0; j < output[0].size(); j++)
            {
                output[x][j] = (output[x][j] / total) * 255;
            }
        }

        seed.clear();

        return output;
    }
}