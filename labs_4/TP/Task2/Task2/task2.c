#include <stdio.h>
#include <string.h>
#define bool char
#define true 1
#define false 0

typedef struct {
	char *name;
	char *abbr;
	int days;
	int number;
} month;

month months[12];

void init() {
	months[0].name = "January";
	months[0].abbr = "jan";
	months[0].days = 31;
	months[0].number = 1;

	months[1].name = "February";
	months[1].abbr = "feb";
	months[1].days = 28;
	months[1].number = 2;

	months[2].name = "March";
	months[2].abbr = "mar";
	months[2].days = 31;
	months[2].number = 3;

	months[3].name = "April";
	months[3].abbr = "apr";
	months[3].days = 30;
	months[3].number = 4;

	months[4].name = "May";
	months[4].abbr = "may";
	months[4].days = 31;
	months[4].number = 5;

	months[5].name = "June";
	months[5].abbr = "jun";
	months[5].days = 30;
	months[5].number = 6;

	months[6].name = "July";
	months[6].abbr = "jul";
	months[6].days = 31;
	months[6].number = 7;

	months[7].name = "August";
	months[7].abbr = "aug";
	months[7].days = 31;
	months[7].number = 8;

	months[8].name = "September";
	months[8].abbr = "sep";
	months[8].days = 30;
	months[8].number = 9;

	months[9].name = "October";
	months[9].abbr = "oct";
	months[9].days = 31;
	months[9].number = 10;

	months[10].name = "November";
	months[10].abbr = "nov";
	months[10].days = 30;
	months[10].number = 11;

	months[11].name = "December";
	months[11].abbr = "dec";
	months[11].days = 31;
	months[11].number = 12;
}

bool check_year(int year) {
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int main() {
	init();
	int year;

	printf_s("Enter number of the year :\n");
	scanf_s("%d", &year);
	if (year <= 0) {
		printf_s("Incorrect input");
		return 0;
	}

	if (check_year(year))
		months[1].days = 29;

	printf_s("Enter number of the month, name or abbreviation:\n");
	char tmp[40];
	scanf_s("%s", tmp, 40);

	int mon = -1;
	if (strlen(tmp) <= 2) {
		mon = atoi(tmp);
		mon--;
		if (mon > 11)
			return 0;
	}
	else {
		bool flag = true;
		for (int i = 0; i < 12; i++) {
			if (!strcmp(tmp, months[i].name) || !strcmp(tmp, months[i].abbr)) {
				mon = i;
				flag = false;
				break;
			}
		}
		if (flag)
			return 0;
	}

	printf_s("Enter number of the day:\n");
	int day = -1;
	scanf_s("%d", &day);

	if (day <= 0 || day > months[mon].days)
		return 0;

	int result = 0;
	for (int i = 0; i < mon; i++) {
		result += months[i].days;
	}

	result += day;
	printf_s("Amount of days: %d\n", result);
	system("pause");
	return 0;
}