#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    int random, guess;
    int no_of_guess = 0;
    srand(time(NULL));

    printf("\n\nWelcome to the World of Guessing Numbers\n");
    random = (rand() % 100) + 1; //Generates a Random no. between 1 to 100
    
    do {
        printf("\nPlease Enter your Guess between (1 to 100):  ");
        scanf("%d", &guess);
        no_of_guess++;

        if(guess < random) {
            printf("Guess a Larger Number ---\n");
        } else if(guess > random) {
            printf("Guess a Smaller Number ---\n");
        } else {
            printf("\nCongratulations!! You have Successfully Guess the Number ---\n");
            printf("You take %d Attempts", no_of_guess);
        }
    } while(guess != random);

    printf("\n\nBye Bye, THank you for Playing.");
    printf("\nDeveloped by KalashJain\n\n");
}