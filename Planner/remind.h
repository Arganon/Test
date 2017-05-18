#ifndef REMIND_H
#define REMIND_H

#define MAX 512

class Remind {
	private:
		char text_remind[MAX];
		int day;
		int month;
		int year;
		long next;
		
	public:
		Remind(int day, int month, int year);
		Remind();
		~Remind();
		int getDay() const;
		int getMonth() const;
		int getYear() const;
		char* getTextRemind();
		void setTextRemind(char *text);
		bool operator < (const Remind &other) const;
		bool operator > (const Remind &other) const;
		bool operator ==(const Remind &other) const;
};

#endif // REMIND_H
