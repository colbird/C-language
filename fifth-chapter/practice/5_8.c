#include <stdio.h>

static char daytab [2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
int day_of_year(int, int, int);
void month_day(int, int, int*, int *);

int main(){
	int year, month, day, yearday;
	scanf ("%d%d%d", &year, &month, &day);
	yearday = day_of_year(year, month, day);
	printf ("month = %d\n", month);
	printf ("day = %d\n", day);
	printf ("year = %d\n", year);
	printf ("yearday = %d\n", yearday);

	int tmonth, tday;
	month_day (year, yearday, &tmonth, &tday);
	printf ("month = %d\n", tmonth);
	printf ("day = %d\n", tday);
	printf ("year = %d\n", year);
	return 0;
}

/*  day_fo_year函数: 将某月某日的日期表示形式转换为某年中第几天的表示形式  */
int day_of_year(int year, int month, int day){
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (year <= 0 || month < 0 || month > 12 || day < 0 || daytab[leap][month] < day ){
		printf ("error: day_of_year error so return -1\n");
		return -1;
	}
	for (i = 1; i < month; ++i)
		day += daytab[leap][i];
	return day;
}

/*   month_day函数: 将某年中第几天的日期表示形式转换为某日某月的表示形式  */
void month_day(int year, int yearday, int *pmonth, int *pday){
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (yearday < 0 || leap && yearday > 365 || !leap && yearday > 364){
		printf ("error: month_day so return\n");
		return;
	}
	for (i = 1; yearday > daytab[leap][i]; ++i)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}
