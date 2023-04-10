#include <iostream>
#include "GenericOption.h"

GenericOption::GenericOption(double strike, OptionType type, double cost)
    : _strike(strike), _type(type), _cost(cost)
{
}

GenericOption::GenericOption(const GenericOption& other)
    :_strike(other._strike), _type(other._type), _cost(other._cost)
{
}

GenericOption::~GenericOption()
{
}

GenericOption &GenericOption::operator=(const GenericOption &rhs)
{
    if(this != &rhs)
    {
        _type  = rhs._type;
        _strike = rhs._strike;
        _cost = rhs._cost;
    }
    return *this;
}

// Computes the value of the option at expiration date.
// Value depends of the type of option (CALL or PUT) and strike
double GenericOption::ValueAtExpiration(double underlyingAtExpiration)
{
    double value = 0.0;

    if(_type == OptionType_Call)
    {
        if(_strike < underlyingAtExpiration)
            value = underlyingAtExpiration - _strike;
    }
    else // it is an OptionType_Put
    {
        if(_strike > underlyingAtExpiration)
            value = _strike - underlyingAtExpiration;
    }
    return value;
}


// Return the profit (value at expiration minus options cost)
double GenericOption::ProfitAtExpiration(double underlyingAtExpiration)
{
    double finalValue = ValueAtExpiration(underlyingAtExpiration);
    double value = (finalValue > _cost)? finalValue - _cost: 0;
    return value;
}


int main()
{
    GenericOption option(100.0, OptionType_Put, 1.1);
    double price1 = 120.0;
    double value = option.ValueAtExpiration(price1);

    std::cout << "For 100PUT, value at expiration for price "
        << price1 << " is " << value << std::endl;

    double price2 = 85.0;
    value = option.ValueAtExpiration(price2);

    std::cout << "For 100PUT, value at expiration for price "
        << price2 << " is " << value << std::endl;

    // Test ProfitAtExpiration
    auto limit = 120.0;
    double profit;
    for (auto price = 80.0; price <= limit; price += 0.1)
    {
        profit = option.ProfitAtExpiration(price);
        std::cout << price  << ", " << profit << std::endl;
    }

    return 0;
}
