#include <vector>

#pragma once

#ifndef NOISE_UTILS
#define NOISE_UTILS

namespace noise
{
    //perlin noise generator
    std::vector<std::vector<double>> Perlin2D(int&, int size = time(0));
}
#endif