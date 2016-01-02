//lecture 7 homework

/* 
to compile: gcc -g whatDay.c -o whatDay

to run: ./whatDay
*/

#include <stdio.h>
#include <stdlib.h>

int thisYearsDoomsday(int year);
int thisCenturysAnchorDay(int year);
char * dayOfWeekString(int day);
char * monthNameString(int month);
int distanceFromNearestDoomsday(int day, int month);

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
    int inputDateAsDayNum = doomsday + distanceFromNearestDoomsday(day, month);
    char *dayName = dayOfWeekString(inputDateAsDayNum);
    
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

//determine the "doomsday" (as a day number) for that specific year (we have to know what it is for a particular year first, then calculate from that)
//it's Saturday (6) in the 12/32/2015 test case

int thisYearsDoomsday(int year) {
    //get the anchor for this century 
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

char * dayOfWeekString(int day) {
    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    
    return days[abs(day)];
}

char * monthNameString(int month) {
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
    return months[month - 1];
}

int distanceFromNearestDoomsday (int day, int month) {
    /* 
     1/3 or 1/4 depending on if it's a leap year
     3/0 (or 2/29)
     3/7
     4/4
     5/9
     6/6
     7/11
     8/8
     9/5
     10/10
     11/17
     12/12
     */
    
    int distance;
    
    if (month == 1) {
        //absolute value of day - 3 or 4 leap year variation
        distance = day - 3;
    } else if (month == 2) {
        distance = day - 29;
    } else if (month == 3) {
        distance = day - 7;
    } else if (month == 4) {
        distance = day - 4;
    } else if (month == 5) {
        distance = day - 9;
    } else if (month == 6) {
        distance = day - 6;
    } else if (month == 7) {
        distance = day - 11;
    } else if (month == 8) {
        distance = day - 8;
    } else if (month == 9) {
        distance = day - 5;
    } else if (month == 10) {
        distance = day - 10;
    } else if (month == 11) {
        distance = day - 17;
    } else if (month == 12) {
        distance = day - 12;
    }
    
    //take out all the multiples of 7 to get pos or neg offset to get distance from day of week doomsday
    distance = distance % 7;
    
    //give back this distance (-6 ... 6)
    return distance;
}