//week 2 homework

//to compile:
//gcc -g whatDay.c -o whatDay
//to run:
//./whatDay

#include <stdio.h>

//ask user for the day, month, and year they want to check
//example: 12/31/2015

//process year to determine if it's a 365 day year or a 366 day year
//365 day year

//determine the "doomsday" for that specific year (we have to know what it is for a particular year first, then calculate from that)
//it's Saturday in this case

//determine nearest doomsday day/month combo
//we have 12/31 as our date and we compare month and day (with tbd algoritm) to find 12/12

//count days since that doomsday (we may be counting across months of varying lengths)
//12/31 is 19 days from a doomsday (12/12)

//divide 'days from doomsday' + 1 by 7 (20 % 7 = 5) gives us Friday (day 5)

//return date and day of week ("December 31st 2015 is a Thursday")