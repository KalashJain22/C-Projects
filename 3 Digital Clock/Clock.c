#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

void fill_time(char* buffer, int format) {
    time_t raw_time;
    struct tm *current_time;
    
    time(&raw_time);
    current_time = localtime(&raw_time);
    
    if(format == 1) {
        strftime(buffer, 50, "%H:%M:%S", current_time);
    } else {
        strftime(buffer, 100, "%I:%M:%S %p", current_time);
    }
}

void fill_date(char* buffer) {
    time_t raw_time;
    struct tm *current_time;
    
    time(&raw_time);
    current_time = localtime(&raw_time);
     strftime(buffer, 50, "%A %d, %B %Y", current_time);
}

int input_format() {
    int format;
    printf("\nChoose the Time Format: ");
    printf("\n1. 24 Hour Format\n2. 12 Hour Format (Default)");
    printf("\n\nMake a choice (1/2): ");
    scanf("%d", &format);
    return format;
}

int main() {
    char time[50], date[100];
    int format = input_format();

    while(1) {
        fill_time(time, format);
        fill_date(date);
        system("cls");
        printf("Current Time: %s", time);
        printf("\nDate: %s", date);
        sleep(1); //sleep for 1 second
    }
}