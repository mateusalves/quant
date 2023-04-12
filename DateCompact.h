#pragma once

// A compact representation for dates, using a character string
class DateCompact
{
    public:
        DateCompact(int year, int month, int day);
        DateCompact(const DateCompact &other);
        ~DateCompact();
        DateCompact &operator=(const DateCompact &rhs);

        void SetYear(int y);
        void SetMonth(int m);
        void SetDay(int d);

        int Year();
        int Month();
        int Day();
        void Print();

        bool operator==(const DateCompact &rhs) const;
        bool operator<(const DateCompact &rhs) const;

    private:
        char _date[8];

};
