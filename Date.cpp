#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "Date.h"


Date::Date(int year, int month, int day)
    : _year(year), _month(month), _day(day), _weekDay(DayOfTheWeek_UNKNOWN)
{
}

Date::~Date()
{
}

Date::Date(const Date &other)
    :_year(other._year), _month(other._month), _day(other._day),
     _weekDay(other._weekDay), _holidays(other._holidays)
{
}

Date& Date::operator=(const Date& rhs)
{
    if (this != &rhs)
    {
        _day = rhs._day;
        _month = rhs._month;
        _year = rhs._year;
        _weekDay = rhs._weekDay;
        _holidays = rhs._holidays;
    }
    return *this;
}

bool Date::operator<(const Date &rhs) const
{
    if(_year < rhs._year)
        return true;
    if(_year == rhs._year && _month < rhs._month)
        return true;
    if(_year == rhs._year && _month == rhs._month && _day < rhs._day)
        return true;
    return false;
}

bool Date::operator==(const Date &rhs)
{
    return _day == rhs._day && _month == rhs._month && _year == rhs._year;
}

void Date::SetHolidays(const std::vector<Date> &days)
{
    _holidays = days;
}

bool Date::IsHoliday()
{
    return std::find(_holidays.begin(), _holidays.end(), *this) != _holidays.end();
}


// Convert enumeration values to month strings.
std::string Date::Month()
{
    switch(_month)
    {
        case Month_January:
            return "January";
        case Month_February:
            return "February";
        case Month_March:
            return "March";
        case Month_April:
            return "April";
        case Month_May:
            return "May";
        case Month_June:
            return "June";
        case Month_July:
            return "July";
        case Month_August:
            return "August";
        case Month_September:
            return "September";
        case Month_October:
            return "October";
        case Month_November:
            return "November";
        case Month_December:
            return "December";
        default: throw std::runtime_error("unknown month");
    }
}

std::string Date::DayOfWeek()
{
    switch(this->DayOfTheWeek())
    {
        case DayOfTheWeek_Sunday:
            return "Sunday";
        case DayOfTheWeek_Monday:
            return "Monday";
        case DayOfTheWeek_Tuesday:
            return "Tuesday";
        case DayOfTheWeek_Wednesday:
            return "Wednesday";
        case DayOfTheWeek_Thursday:
            return "Thursday";
        case DayOfTheWeek_Friday:
            return "Friday";
        case DayOfTheWeek_Saturday:
            return "Saturday";
        default: throw std::runtime_error("unknown day of week");
    }
}

void Date::Add(int numDays)
{
    for(int i = 0; i < numDays; ++i)
    {
        ++*this;
    }
}

void Date::AddTradingDays(int numDays)
{
    while (!IsTradingDay())
    {
        ++*this;
    }

    for (int i = 0; i < numDays; ++i)
    {
        ++*this;
        while (!IsTradingDay())
        {
            ++*this;
        }
    }
}

void Date::Subtract(int numDays)
{
    for(int i = 0; i < numDays; ++i)
    {
        --*this;
    }
}

void Date::SubtractTradingDays(int numDays)
{
    while (!IsTradingDay())
    {
        --*this;
    }

    for (int i = 0; i < numDays; ++i)
    {
        --*this;
        while (!IsTradingDay())
        {
            --*this;
        }
    }
}

int Date::DateDifference(const Date& date)
{
    Date d = *this;

    if (d < date)
    {
        int diff = 0;
        while (d < date)
        {
            ++d;
            ++diff;
        }
        return diff;
    }

    int diff = 0;

    while (!d.IsTradingDay())
        --d;

    while(date < d)
    {
        --d;
        --diff;
        while (!d.IsTradingDay())
            --d;
    }
    return diff;
}

DayOfTheWeek Date::DayOfTheWeek()
{
    if (_weekDay != DayOfTheWeek_UNKNOWN)
        return _weekDay;

    int day = 1;
    Date d(1900, 1, 1);
    for (; d < *this; ++d)
    {
        if (day == 6)
            day = 0;
        else
            day++;
    }
    _weekDay = static_cast<enum DayOfTheWeek>(day);

    return _weekDay;
}

bool Date::IsWeekDay()
{
    enum DayOfTheWeek dayOfWeek = DayOfTheWeek();
    if (dayOfWeek == DayOfTheWeek_Sunday || dayOfWeek == DayOfTheWeek_Saturday)
    {
        return false;
    }
    return true;
}

bool Date::IsTradingDay()
{
    if (!IsWeekDay())
        return false;
    if (_holidays.size() == 0)
        return true;
    if (IsHoliday())
        return false;
    return true;
}

Date Date::NextTradingDay()
{
    Date d = *this;
    if (d.IsTradingDay())
        return ++d;

    while(!d.IsTradingDay())
        ++d;
    return d;
}

bool Date::IsLeapYear()
{
    if (_year % 4 != 0)
        return false;
    if (_year % 100 != 0)
        return true;
    if (_year % 400 != 0)
        return false;
    return true;
}

Date& Date::operator--()
{
    if (_weekDay != DayOfTheWeek_UNKNOWN) //update Weekday
    {
        if (_weekDay == DayOfTheWeek_Sunday)
            _weekDay = DayOfTheWeek_Saturday;
        else
            _weekDay = static_cast<enum DayOfTheWeek>(_weekDay - 1);
    }
    if (_day > 1)
    {
        _day--;
        return *this;
    }

    if (_month == Month_January)
    {
        _month = Month_December;
        _day = 31;
        _year--;
        return *this;
    }

    _month--;
    if (_month == Month_February)
    {
        _day = IsLeapYear()? 29: 28;
        return *this;
    }

    // List of months with 31 days
    std::vector<int> monthWithThirtyOneDays = {1, 3, 5, 7, 8, 10, 12};

    if (std::find(monthWithThirtyOneDays.begin(), monthWithThirtyOneDays.end(), _month)
            != monthWithThirtyOneDays.end())
    {
        _day = 31;
    }
    else
    {
        _day = 30;
    }

    return *this;
}

Date& Date::operator++()
{
    // List of months with 31 days
    std::vector<int> monthWithThirtyOneDays = {1, 3, 5, 7, 8, 10, 12};

    if (_day == 31)
    {
        _day = 1;
        _month++;
    }
    else if (_day == 30 && std::find(monthWithThirtyOneDays.begin(),
                                     monthWithThirtyOneDays.end(),
                                     _month) == monthWithThirtyOneDays.end())
    {
        _day = 1;
        _month++;
    }
    else if (_day == 29 && _month == 2)
    {
        _day = 1;
        _month++;
    }
    else if (_day == 28 && _month == 2 && !IsLeapYear())
    {
        _day = 1;
        _month++;
    }
    else
    {
        _day++;
    }

    if (_month > 12)
    {
        _month = 1;
        _year++;
    }

    if (_weekDay != DayOfTheWeek_UNKNOWN) // update weekday
    {
        if (_weekDay == DayOfTheWeek_Saturday)
            _weekDay = DayOfTheWeek_Sunday;
        else
                _weekDay = static_cast<enum DayOfTheWeek>(_weekDay + 1);
    }
    return *this;
}

void Date::Print()
{
    std::cout << _year << "/" << _month << "/" << _day << std::endl;
}


int main()
{
    Date d(2023, 4, 11);
    DayOfTheWeek wd = d.DayOfTheWeek();
    std::cout << "day of the week: " << wd  << " "
              << d.DayOfWeek() << std::endl;
    d.Print();

    d.Add(25);
    d.Print();

    d.AddTradingDays(120);
    d.Print();
    std::cout << "day of the week: " << d.DayOfTheWeek() << " "
              << d.DayOfWeek() << std::endl;

    return 0;
}

