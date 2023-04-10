#pragma once

// Option types based on direction: call or put

enum OptionType
{
    OptionType_Call = 0, OptionType_Put
};


// Class that represents a generic option
class GenericOption
{
    public:
        GenericOption(double strike, OptionType type, double cost);
        GenericOption(const GenericOption& other);
        ~GenericOption();
        GenericOption &operator=(const GenericOption& rhs);

        double ValueAtExpiration(double underlyingAtExpiration);
        double ProfitAtExpiration(double underlyingAtExpiration);

    private:
        double _strike;
        OptionType _type;
        double _cost;
};
