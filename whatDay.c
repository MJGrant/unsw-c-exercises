//lecture 7 homework

/* 
to compile: gcc -g whatDay.c -o whatDay

to run: ./whatDay
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int thisYearsDoomsday(int year);
int thisCenturysAnchorDay(int year);
char * dayOfWeekString(int day);
char * monthNameString(int month);
int dayOfWeek(int doomsday, int day, int month, int year);
bool isLeapYear(int year);

//ask user for the day, month, and year they want to check
//example: 12/31/2015

int main (void) {
    
    int day;
    int month;
    int year;
    
    int doomsday; //0 ... 6 (Sunday, Monday, etc)
    
    printf("This program will tell you what day of the week a certain date lands on.\n");
    
    //DAY
    printf("Enter DAY (1-31):\n");
    scanf("%d", &day);
    
    if (day < 1 || day > 31) {
        printf("%d is not a valid day (1...31)\n", day);
        return EXIT_FAILURE;
    }
    
    //MONTH
    printf("Enter MONTH (1-12):\n");
    scanf("%d", &month);

    if (month < 1 || month > 12) {
        printf("%d is not a valid month (1...12)\n", month);
        return EXIT_FAILURE;
    }

    
    //YEAR
    printf("Enter YEAR (1800-2199):\n");
    scanf("%d", &year);
    
    if (year >= 1800 && year <=2199) {
        doomsday = thisYearsDoomsday(year);
        printf("%d's doomsday: %s\n", year, dayOfWeekString(doomsday));
    } else {
        printf("%d is not a valid year (1800...2199)\n", year);
        return EXIT_FAILURE;
    }
    

    //put it all together
    char *dayName = dayOfWeekString(dayOfWeek(doomsday, day, month, year));
    
    printf("%s %d, %d is a %s\n", monthNameString(month), day, year, dayName);
    return EXIT_SUCCESS;
}

//Anchor days

//1800-1899 Friday (5)
//1900-1999 Wednesday (3)
//2000-2999 Tuesday (2)
//2100-2199 Sunday (0)

int thisCenturysAnchorDay(int year) {
    int anchorDay;
    
    if (year >= 1800 && year <= 1899) {
        anchorDay = 5;
    } else if (year >= 1900 && year <= 1999) {
        anchorDay = 3;
    } else if (year >= 2000 && year <= 2999) {
        anchorDay = 2;
    } else if (year >= 2100 && year <= 2199) {
        anchorDay = 0;
    } else {
        printf("Anchor day could not be calculated");
        anchorDay = 1;
    }

    return anchorDay;
}

//Determine if the given year is a leapyear
bool isLeapYear(int year) {
    bool isLY;
    
    //http://stackoverflow.com/questions/3220163/how-to-find-leap-year-programatically-in-c
    
    if (year % 4 != 0) {
        isLY = false;
    } else if (year % 100 != 0) {
        isLY = true;
    } else if (year % 400 == 0) {
        isLY = true;
    } else {
        isLY = false;
    }
    
    return isLY;
}

//Determine the "doomsday" (as a day number between 0 and 6) for that specific year

int thisYearsDoomsday(int year) {
    int anchor;
    anchor = thisCenturysAnchorDay(year);
    
    //using the "odd+11" method, find this year's doomsday
    
    //get the last two digits of the year
    int t;
    t = year % 100;
    
    //if t is odd, add 11
    if (t % 2 != 0) {
        t += 11;
    }
    
    //now set t to whatever results when you divide it by 2
    t = (t / 2);
    
    //if t is odd, add 11 (do this again)
    if (t % 2 != 0) {
        t += 11;
    }
    
    //finally, let t = 7 - (t mod 7)
    t = 7 - (t % 7);
    
    //count t days from the century's anchor day and mod it by 7 and use the remainder
    int doomsday;
    doomsday = (anchor + t) % 7;

    //returns this year's doomsday as a number (0 = Sunday, 1 = Monday, etc)
    return doomsday;
}


//Return day of week name
char * dayOfWeekString(int day) {
    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    
    return days[day];
}

//Return month name
char * monthNameString(int month) {
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
    return months[month - 1];
}

//Return day of week for a specific date (0 = Sunday, 1 = Monday, etc)
int dayOfWeek (int doomsdayDayOfWeek, int day, int month, int year) {
    
    int doomsdayJulian = 3;
    int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dayOfWeekNum;
    int thisDateJulian = 0; //a date's sequential number in a year (ie: 12/25/2016 is 360)
    
    //A year's first doomsday is the 3rd Julian day in ordinary years and the 4th fourth Julian day in a leap year
    if (isLeapYear(year)) {
        months[1] = 29;
        doomsdayJulian = 4;
    }
    
    
    //Add all the days in all the leading up to (but not including) the passed in month's number
    for (int i = 0; i < month - 1; i ++) {
        thisDateJulian = thisDateJulian + months[i];
    }
    
    //Now add all the days leading up to (but not including) the passed in date's date
    for (int i = 0; i < day; i++) {
        thisDateJulian ++;
    }
    
    //Now we need the number of days between the year's first Julian day (3 or 4) and the given date's Julian day (which could be anywhere from 1 to 366)
    int distance = 0;
    distance = thisDateJulian - doomsdayJulian;
    if (distance < 0) {
        //in the case of days before the year's first 'doomsday', add a week to fix negative problem
        distance = distance + 7;
    }
    
    dayOfWeekNum = (doomsdayDayOfWeek + distance) % 7;

    return dayOfWeekNum;
}