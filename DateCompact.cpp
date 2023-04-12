#include <iostream>
#include <cstring>

#include "DateCompact.h"

DateCompact::DateCompact(int year, int month, int day)
{
    SetYear(year);
    SetMonth(month);
    SetDay(day);
}

DateCompact::DateCompact(const DateCompact &other)
{
    strcpy(_date, other._date);
}

DateCompact::~DateCompact()
{
}

DateCompact& DateCompact::operator=(const DateCompact& rhs)
{
    if (rhs != *this)
    {
        strcpy(_date, rhs._date);
    }
    return *this;
}

// Use string comparison to determine if the dates are equal
bool DateCompact::operator==(const DateCompact &rhs) const
{
    return strncmp(_date, rhs._date, 8) == 0;
}

// Use the strncmp function to determine if a date is less than the other.
bool DateCompact::operator<(const DateCompact &rhs) const
{
    // strcmp returns negative values if the first
    // argument is less than the second
    return strncmp(_date, rhs._date, 8) < 0;
}


// Function to calculate the year, month, and days as integeres,
// based on the characters contained in the string '_date'.

int DateCompact::Year()
{
    // (x - 'O') computes the numeric value
    // corresponding to each character.
    return 1000 * (_date[0] - 'O') + 100 * (_date[1] - '0')
           + 10 * (_date[2] - '0') +       (_date[3] - '0');
}

int DateCompact::Month()
{
    return 10 * (_date[4] - '0') + (_date[5] - '0');
}

int DateCompact::Day()
{
    return 10 * (_date[6] - '0') + (_date[7] - '0');
}

void DateCompact::Print()
{
    // Copy the _date string int o a NULL terminated string (with 9 characters)
    char s[9];
    strncpy(s, _date, 8);
    s[8] = '\0'; // properly terminate the string
    std::cout << s << std::endl;
}

// Calculate the string corresponding to the given numeric parameter
void DateCompact::SetYear(int year)
{
    _date[3] = '0' + (year % 10);
    year /= 10;
    _date[2] = '0' + (year % 10);
    year /= 10;
    _date[1] = '0' + (year % 10);
    year /= 10;
    _date[0] = '0' + (year % 10);
}

void DateCompact::SetMonth(int month)
{
    _date[5] = '0' + (month % 10);
    month  /= 10;
    _date[4] = '0' + (month % 10);
    month  /= 10;
}

void DateCompact::SetDay(int day)
{
    _date[7] = '0' + (day % 10);
    day  /= 10;
    _date[6] = '0' + (day % 10);
    day  /= 10;
}

//#include "Date.h"

int main()
{
    DateCompact d(2008, 3, 17);
    DateCompact e(2008, 5, 11);
    std::cout << "Size of DateCompact: " << sizeof(DateCompact) << std::endl;

    d.Print();
    e.Print();

    if (d < e)
        std::cout << "d is less than e" << std::endl;
    else
        std::cout << "d is not less than e" << std::endl;

    //Date date(2008, 3, 17);
    //std::cout << "Size of Date: " << sizeof(Date) << std::endl;

    return 0;
}
