#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<conio.h>

#define QUES_LEN 300
#define OPT_LEN 100

volatile int timeout_happened = 0;

const char* COLOR_END = "\033[0m";
const char* RED = "\033[1;31m";
const char* GREEN = "\033[1;32m";
const char* YELLOW = "\033[1;33m";
const char* BLUE = "\033[1;34m";
const char* PINK = "\033[1;35m";
const char* AQUA = "\033[1;36m";

typedef struct {
    char text[QUES_LEN];
    char options[4][OPT_LEN];
    char correct_option;
    int time_out;
    int prize_money;
} Questions;

int use_lifeline(Questions* questions, int* lifeline);

int read_questions(char* file_name, Questions** question) {
    FILE *file = fopen(file_name, "r");
    if(file == NULL) {
        printf("\nUnable to open the question bank");
        exit(0);
    }

    char str[QUES_LEN];
    int no_of_lines = 0;
    while(fgets(str, QUES_LEN, file)) {
        no_of_lines++;
    }
    int no_of_questions = no_of_lines / 8;
    (*question) = (Questions *) malloc(no_of_questions * sizeof(Questions));

    rewind(file);
    for(int i =0; i < no_of_questions; i++) {
        fgets((*question)[i].text, QUES_LEN, file);

        for(int j = 0; j < 4; j++) {
            fgets((*question)[i].options[j], OPT_LEN, file);
        }

        char options[10];
        fgets(options, 10, file);
        (*question)[i].correct_option = options[0];

        char timeout[10];
        fgets(timeout, 10, file);
        (*question)[i].time_out = atoi(timeout);

        char prize_money[10];
        fgets(prize_money, 10, file);
        (*question)[i].prize_money = atoi(prize_money);
    }
    fclose(file);
    return no_of_questions;
}

void print_formatted_question(Questions questions) {
    printf("\n\n%s%s%s", YELLOW, questions.text, COLOR_END);
    for (int i = 0; i < 4; i++) {
        if (questions.options[i][0] != '\0') {
            printf("%s%c. %s%s", AQUA, ('A' + i), questions.options[i], COLOR_END);
        }
    }
    printf("\n%sHurry!! You have only %d Seconds to answer..%s", YELLOW, questions.time_out, COLOR_END);
    printf("\n%sEnter your answer (A, B, C, or D) or L for lifeline: %s", GREEN, COLOR_END);
}

DWORD WINAPI timeout_thread(LPVOID lpParam) {
    int timeout = *(int*)lpParam;
    Sleep(timeout * 1000);
    timeout_happened = 1;
    printf("%s\n\nTime out!!!!!  Press Any Key...%s\n", RED, COLOR_END);
    return 0;
}

void play_game(Questions* questions, int no_of_questions) {
    int money_won = 0;
    int lifeline[] = {1, 1};

    for(int i = 0; i < no_of_questions; i++) {
        print_formatted_question(questions[i]);
        timeout_happened = 0;

        DWORD threadId;
        HANDLE hThread = CreateThread(NULL, 0, timeout_thread, &questions[i].time_out, 0, &threadId);

        char ch = _getch();
        printf("%c", ch);
        TerminateThread(hThread, 0);
        CloseHandle(hThread);

        ch = toupper(ch);

        if (timeout_happened == 1) {
            break;
        }

        if(ch == 'L') {
            int value = use_lifeline(&questions[i], lifeline);
            if(value != 2) {
                i--;
            }
            continue;
        }
        if(ch == questions[i].correct_option) {
            printf("%s\nCorrect!%s", GREEN, COLOR_END);
            money_won += questions[i].prize_money;
            printf("\n%sYou have won: Rs %d%s", BLUE, questions[i].prize_money, COLOR_END);
        } else {
            printf("%s\nWrong! Correct answer is %c.%s", RED, questions[i].correct_option, COLOR_END);
            break;
        }
    }
    printf("\n\n%sGame Over! Your total winnings are: Rs %d%s\n", BLUE,  money_won, COLOR_END);
}

int use_lifeline(Questions* questions, int* lifeline) {
    printf("\n\n%sAvailable Lifelines:%s", PINK, COLOR_END);
    //Lifeline is available or not 
    if (lifeline[0]) printf("\n%s1. Fifty-Fifty (50/50)%s", PINK, COLOR_END);
    if (lifeline[1]) printf("\n%s2. Skip the Question%s", PINK, COLOR_END);
    printf("\n%sChoose a lifeline or 0 to return: %s", PINK, COLOR_END);

    char ch = _getch();
    printf("%c", ch);

    switch (ch)
    {
    case '1':
        if (lifeline[0]) {
            lifeline[0] = 0;
            int removed = 0;
            while (removed < 2) {
                int num = rand() % 4;
                if ((num + 'A') != questions->correct_option && questions->options[num][0] != '\0') {
                    questions->options[num][0] = '\0';
                    removed++;
                }
            }     
            return 1;
        }
        break;
    case '2':
        if (lifeline[1]) {
            lifeline[1] = 0;
            return 2;
        }
        break;
    default: 
        printf("\n%sReturning to the Question.%s", PINK, COLOR_END);
        break;
    }
    return 0;
}

int main() {
    srand(time(NULL));
    printf("\n\t\t%sChalo Khelte Hai Kon Banega Crorepati!!!%s", PINK, COLOR_END);
    Questions* questions;
    int no_of_questions = read_questions("Questions.txt", &questions);
    play_game(questions, no_of_questions);  
} 