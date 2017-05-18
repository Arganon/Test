#include "planner.h"

int main(int argc, char* argv[]) {
	// Calendar c;
	// struct tm *date = c.getCurrentDate();
	// std::cout << date->tm_mday << "\n";

	// Before adding remind to database we need to set date and text of our remind.

	Planner planner;
	// planner.deleteRemindByIndex(2);
	planner.setDate(28, 12, 2010);
	planner.setRemind("It will be a wonderful day\n");
	planner.addRemind();



	planner.showAllReminds();

	return 0;
}
