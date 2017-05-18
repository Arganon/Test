#include "calendar.h"

Calendar::Calendar() {}

Calendar::~Calendar() {}

bool Calendar::isLeapYear(int year) {
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

bool Calendar::isCorrectMonth(int month) {
	return month > 12 || month < 1 ? false : true;
}

bool Calendar::isCorrectDate(int day, int month, int year) {
	if (!isCorrectMonth(month)) {
		return false;
	}
	int monthLengths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	return day > 0 && day <= (monthLengths[month - 1] + (month == FEBRUARY && isLeapYear(year))) ? true : false;
}

tm *Calendar::getCurrentDate() {
	time_t raw_time;

	time(&raw_time);
	struct tm *date;
	date = gmtime(&raw_time);
	return date;
}
