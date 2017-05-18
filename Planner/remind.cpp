#include "remind.h"

Remind::Remind(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

Remind::Remind() {}

Remind::~Remind() {}

int Remind::getDay() const {
	return this->day;
}

int Remind::getMonth() const {
	return this->month;
}

int Remind::getYear() const {
	return this->year;
}

char* Remind::getTextRemind() {
	return this->text_remind;
}

void Remind::setTextRemind(char *text) {
	for (int i = 0; text[i] != '\0' || i < MAX-1; i++) {
		text_remind[i] = text[i];
	}
}

bool Remind::operator < (const Remind &other) const {
	return (this->year < other.getYear() || 
			(this->year == other.getYear() && (this->month < other.getMonth() ||
			(this->month == other.getMonth() && this->day < other.getDay()))));
}

bool Remind::operator > (const Remind &other) const {
	return (this->year > other.getYear() || 
			(this->year == other.getYear() && (this->month > other.getMonth() ||
			(this->month == other.getMonth() && this->day > other.getDay()))));
}

bool Remind::operator == (const Remind &other) const {
	return this->year == other.getYear() && this->month == other.getMonth() && this->day == other.getDay();
}
