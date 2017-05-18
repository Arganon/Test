#include "planner.h"


Planner::Planner() {
	this->db->openDbFile();
}

Planner::~Planner() {
	this->db->closeDbFile();
}

void Planner::setDate(int day, int month, int year) {
	if (!this->calendar.isCorrectDate(day, month, year)) {
		std::cout << "Incorrect date!\n";
		exit(1);
	}
	this->day = day;
	this->month = month;
	this->year = year;
}

void Planner::setRemind(char *text_remind) {
	if (strlen(text_remind) > MAX) {
		exit(1);
	}
	this->text_remind = text_remind;
}

void Planner::addRemind() {
	Remind remind(this->day, this->month, this->year);
	remind.setTextRemind(this->text_remind);
	this->db->add(remind);
}

void Planner::getRemind(int index) {
	Remind temp; 
	this->db->get(temp, index);
	std::cout << temp.getYear() << "." << temp.getMonth() << "." 
	<< temp.getDay() << ": " << temp.getTextRemind() << std::endl;
}

void Planner::getRemindByDate(int day, int month, int year) {
	Remind temp;
	for (int i = 1; i <= this->db->size(temp); i++) {
		this->db->get(temp, i);
		if (year == temp.getYear() && month == temp.getMonth() && day == temp.getDay()) {
			getRemind(i);
			break;
		}
	}
}

void Planner::showAllReminds() {
	Remind temp;
	for (int i = 1; i <= this->db->size(temp); i++) {
		this->db->get(temp, i);
		std::cout << temp.getYear() << "." << temp.getMonth() << "." 
		<< temp.getDay() << ": " << temp.getTextRemind() << std::endl;
	}
}

void Planner::deleteRemindByIndex(int index) {
	Remind temp;
	this->db->del(temp, index);
}

void Planner::deleteRemindByDate(int day, int month, int year) {
	Remind temp;
	for (int i = 1; i <= this->db->size(temp); i++) {
		this->db->get(temp, i);
		if (year == temp.getYear() && month == temp.getMonth() && day == temp.getDay()) {
			deleteRemindByIndex(i);
			break;
		}
	}
}

void Planner::clear() {
	this->db->clearDb();
}
