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

//ask user for the day, month, and year they want to check
//example: 12/31/2015

int main (void) {
    
    int day;
    int month;
    int year;
    
    int doomsday;
    
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
        printf("This year's doomsday: %s\n", dayOfWeekString(doomsday));
    } else {
        printf("%d is not a valid year (1800...2199)\n", year);
        return EXIT_FAILURE;
    }
    
    
    printf("You entered: %d/%d/%d\n", day, month, year);
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
    //get the anchor
    int anchor;
    anchor = thisCenturysAnchorDay(year);
    printf("Anchor day for this century: %d\n", anchor);
    
    //using the "odd+11" method, find this year's doomsday
    
    //get the last two digits of the year
    int t;
    t = year % 100;
    printf("Last two digits: %d\n", t);
    
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
    char *dayStr = "Noneday";
    
    if (day == 0) {
        dayStr = "Sunday";
    } else if (day == 1) {
        dayStr = "Monday";
    } else if (day == 2) {
        dayStr = "Tuesday";
    } else if (day == 3) {
        dayStr = "Wednesday";
    } else if (day == 4) {
        dayStr = "Thursday";
    } else if (day == 5) {
        dayStr = "Friday";
    } else if (day == 6) {
        dayStr = "Saturday";
    }
    
    return dayStr;
}

//determine nearest doomsday day/month combo
//we have 12/31 as our date and we compare month and day (with tbd algoritm) to find 12/12

//count days since that doomsday (we may be counting across months of varying lengths)
//12/31 is 19 days from a doomsday (12/12)

//divide 'days from doomsday' + 1 by 7 (20 % 7 = 5) gives us Friday (day 5)

//return date and day of week ("December 31st 2015 is a Thursday")