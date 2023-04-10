#pragma once

#include <vector>


// Simple random walk generating class. This can be used for price simulation puporses
class RandomWalkGenerator
{
    public:
        // Class constructors
        RandomWalkGenerator(int size, double start, double step);
        RandomWalkGenerator(const RandomWalkGenerator& other);

        // Destructor
        ~RandomWalkGenerator();

        // Assignment Operator
        RandomWalkGenerator& operator=(const RandomWalkGenerator& other);

        // Main method that returns a vector with values of the random walk
        std::vector<double> GenerateWalk();

        // Returns a single step of the random walk
        double ComputeRandomStep(double currentPrice);
    private:
        int _numSteps;        // the number of steps
        double _stepSize;     // size of each step (in percentage points)
        double _initialPrice; // starting price
};
