#pragma once

#include <vector>
#include <string>

enum DayOfTheWeek
{
    DayOfTheWeek_Sunday = 0,
    DayOfTheWeek_Monday,
    DayOfTheWeek_Tuesday,
    DayOfTheWeek_Wednesday,
    DayOfTheWeek_Thursday,
    DayOfTheWeek_Friday,
    DayOfTheWeek_Saturday,
    DayOfTheWeek_UNKNOWN
};

enum Month
{
    Month_January = 1,
    Month_February,
    Month_March,
    Month_April,
    Month_May,
    Month_June,
    Month_July,
    Month_August,
    Month_September,
    Month_October,
    Month_November,
    Month_December
};

class Date
{
    public:
        Date(int year, int month, int day);
        Date(const Date& other);
        ~Date();
        Date& operator=(const Date& rhs);

        void SetHolidays(const std::vector<Date>& days);
        std::string Month();
        std::string DayOfWeek();
        void Add(int numDays);
        void AddTradingDays(int numDays);
        void Subtract(int numDays);
        void SubtractTradingDays(int numDays);
        int DateDifference(const Date& date);
        int TradingDateDifference(const Date& date);
        enum DayOfTheWeek DayOfTheWeek();
        bool IsHoliday();
        bool IsWeekDay();
        Date NextTradingDay();
        bool IsLeapYear();
        bool IsTradingDay();
        void Print();

        Date& operator++();
        Date& operator--();
        bool operator<(const Date &rhs) const;
        bool operator==(const Date &rhs);

    private:
        int _year;
        int _month;
        int _day;
        enum DayOfTheWeek _weekDay;
        std::vector<Date> _holidays;

};
