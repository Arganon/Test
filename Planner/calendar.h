#ifndef CALENDAR_H
#define CALENDAR_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <time.h>

enum Month { JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, 
	JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};

class Calendar {

	public:
		Calendar();
		~Calendar();
		bool isLeapYear(int year);

		bool isCorrectMonth(int month);
		bool isCorrectDate(int day, int month, int year);
		tm *getCurrentDate();
};

#endif // CALENDAR_H
