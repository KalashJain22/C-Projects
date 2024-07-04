#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

const int BAR_LENGTH=50;
const int MAX_TASKS=10;

typedef struct {
    int id;
    int progress;
    int speed;
} Task;

void print_bar(Task task) {
    int bars_to_show=(task.progress*BAR_LENGTH)/100;
    printf("\nTask %d: [", task.id);
    
    for(int i=0;i<BAR_LENGTH;i++) {
        if(i<bars_to_show) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%", task.progress);
}

int main() {
    Task tasks[MAX_TASKS];
    srand(time(NULL));

    for(int i=0;i<MAX_TASKS;i++) {
        tasks[i].id=i+1;
        tasks[i].progress=0;
        tasks[i].speed=(rand()%5+1);
    }

    int task_incomplete=1;
    while(task_incomplete) {
        task_incomplete=0;

        system("cls");  //for clear screan
        for(int i=0;i<MAX_TASKS;i++) {
            tasks[i].progress+=tasks[i].speed;
            if(tasks[i].progress>100) {
                tasks[i].progress=100;
            } else if(tasks[i].progress<100) {
                task_incomplete=1;
            }
            print_bar(tasks[i]);
        }
        sleep(1);  //sleep for 1 second
    }
    printf("\nAll Task Completed");
}