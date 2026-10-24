#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "func.h"

int main() {
	setlocale(LC_CTYPE, ".utf-8");

	struct tm *mytime;
	char buffer[80];
	time_t t;
	int months;
	int max_days;
	int days;

	t = time(NULL);
	mytime = localtime(&t);
	time_now(mytime);

	/*Задание 2.2, Вариант 7*/
	switch (mytime->tm_mon) {
	case 3: case 5: case 8: case 10:
		max_days = 30; break;
	case 1:
		if (((mytime->tm_year + 1900) % 4 == 0 && (mytime->tm_year + 1900) % 100 != 0) || ((mytime->tm_year + 1900) % 400 == 0))
			max_days = 29;
		else
			max_days = 28;
		break;
	default: max_days = 31;
	}

	months = 11 - mytime->tm_mon;
	days = max_days - mytime->tm_mday;

	/*Задание 2.3, красивая рамка*/
	int len = sprintf(buffer, "до Нового года осталось %d месяцев и %d дней", months, days);
	int w = 80; int h = 10;
	int p = (w - (len - 30))/2;

	full_char_str(w);
	empty_str(h, w);
	printf("*");
	padding(p);
	printf("%s", buffer);
	padding(p);
	printf("*\n");
	empty_str(h, w);
	full_char_str(w);

	return 0;
}

void padding(int p) {
	for (int i = 0; i < p; i++) putchar(' ');
}

void full_char_str(int width) {
	for (int i = 0; i < width; i++) putchar('*');
	putchar('\n');
}

void empty_str(int height, int width) {
	for (int i = 1; i <= (height - 3) / 2; i++) {
		putchar('*');
		for (int j = 0; j < width - 2; j++) putchar(' ');
		printf("*\n");
	}
}

void time_now(struct tm *mytime) {
	printf("Московское время %02d:%02d:%02d\n", mytime->tm_hour, mytime->tm_min, mytime->tm_sec);
}