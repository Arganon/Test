#ifndef PLANNER_H
#define PLANNER_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "remind.h"
#include "calendar.h"
#include "db.cpp"

class Planner {
	private:
		int day;
		int month;
		int year;
		Calendar calendar;
		Db<Remind> *db;
		char *text_remind;

	public:
		Planner();
		~Planner();
		void setDate(int day, int month, int year);
		void setRemind(char *text_remind);
		void addRemind();
		void getRemind(int index);
		void getRemindByDate(int day, int month, int year);
		void changeRemind();
		void deleteRemindByIndex(int index);
		void deleteRemindByDate(int day, int month, int year);
		void clear();
		void showAllReminds();
};

#endif // PLANNER_H
