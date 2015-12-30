//week 2 homework

//to compile:
//gcc -g daysToGo.c -o daysToGo
//to run:
//./daysToGo

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MIN_INPUT 1
#define MAX_INPUT 7
#define FRIDAY 6

int daysTilFriday (int givenDay);

int main (void) {
    
    int input;

    printf("How many days 'til Friday? Enter today's number: \n(1 = Sunday, 2 = Monday, 3 = Tuesday, 4 = Wednesday, 5 = Thursday, 6 = Friday, 7 = Saturday)\n");
    
    scanf("%d", &input);
    
    if (input == FRIDAY) {
        printf("Today is Friday!!\n");
    } else if (input <= MAX_INPUT && input >= MIN_INPUT) {
        int daysToGo;
        daysToGo = daysTilFriday(input);
        printf("Just *** %d day(s) *** to go until Friday, including today.\n", daysToGo);
    } else {
        printf("%d is an INVALID DAY!\n", input);
    }
    
	return EXIT_SUCCESS;
}

int daysTilFriday(int givenDay) {
    if (givenDay <= FRIDAY) {
        return FRIDAY - givenDay;
    } else { //user entered a 7 (saturday)
        return FRIDAY;
    }
}
