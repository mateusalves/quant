#include <iostream>
#include <vector>

#include "RandomWalkGenerator.h"


// Constructor. The supplied parameters represent the number of elements in the
// walk, the initial price, and the step for the random walk.
RandomWalkGenerator::RandomWalkGenerator(int size, double start, double step)
    : _numSteps(size), _stepSize(step), _initialPrice(start)
{
}

RandomWalkGenerator::RandomWalkGenerator(const RandomWalkGenerator& other)
    : _numSteps(other._numSteps), _stepSize(other._stepSize), _initialPrice(other._initialPrice)
{
}

RandomWalkGenerator::~RandomWalkGenerator()
{
}

RandomWalkGenerator& RandomWalkGenerator::operator=(const RandomWalkGenerator &other)
{
    if (this != &other)
    {
        _numSteps = other._numSteps;
        _stepSize = other._stepSize;
        _initialPrice = other._initialPrice;
    }
    return *this;
}

// Returns a single step of the random walk
double RandomWalkGenerator::ComputeRandomStep(double currentPrice)
{
    const int num_directions = 3;
    int r = rand() % num_directions;
    double val = currentPrice;
    if (r == 0)
    {
        val += (_stepSize * val);
    }
    else if (r == 1)
    {
        val -= (_stepSize * val);
    }
    return val;
}

// This is the main method. It will generate random numbers with the constraints
// set by the constructor.
std::vector<double> RandomWalkGenerator::GenerateWalk()
{
    std::vector<double> walk;
    double prev = _initialPrice;

    for(int i = 0; i < _numSteps; ++i)
    {
        double val = ComputeRandomStep(prev);
        walk.push_back(val);
        prev = val;
    }

    return walk;
}


int main()
{
    // 100 steps starting at $30
    RandomWalkGenerator rw(100, 30, 0.01);
    std::vector<double> walk = rw.GenerateWalk();

    for(size_t i = 0; i < walk.size(); ++i)
    {
        std::cout << i << ", " << walk[i] << std::endl;
    }
    std::cout << std::endl;
    return 0;
}
