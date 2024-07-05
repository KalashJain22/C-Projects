#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<windows.h>

void fix_fgets_input(char* );
void input_credentials(char* , char* );

#define MAX_USERS 10
#define CREDENTIAL_LENGTH 30 

typedef struct {
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USERS];
int user_count=0;

void register_user() {
    if(user_count==MAX_USERS){
        printf("Sorry! Maximum %d users are allowed.", MAX_USERS);
        return;
    }
    
    printf("Register a new User\n");
    input_credentials(users[user_count].username, users[user_count].password);
    user_count++;
    printf("\nRegistration Successful!");
}

int login_user() {
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];

    input_credentials(username, password);
    for(int i=0;i<user_count;i++){
        if(strcmp(username, users[i].username)==0 && strcmp(password, users[i].password)==0) {
            return i;
        }
    }
    return -1;
}

boolean setStdinEcho(int true) {
    HANDLE hStdin=GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode;
    
    GetConsoleMode(hStdin, &mode);
    if (true){
        mode |= ENABLE_ECHO_INPUT;
    }
    else{
        mode &= ~ENABLE_ECHO_INPUT;
    }
    SetConsoleMode(hStdin, mode);
}

void input_credentials(char* username, char* password) {
    printf("Username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);
    printf("Password (Masking Enabled): ");
    setStdinEcho(0);  // Disable echo
    
    int i=0;
    while(i<CREDENTIAL_LENGTH) {
        char ch=getchar();
        if (ch=='\n' || ch==EOF) {
            break;
        }
        printf("*");
        password[i]=ch;
        i++;
    }
    password[i]='\0';
    
    setStdinEcho(1);  // Enable echo
}

//fixes the extra line of fgets function
void fix_fgets_input(char* string) {
    int index=strcspn(string, "\n");
    string[index]='\0';
}

int main() {
    int choice;
    int user_index;

    while(1) {
        printf("\n\n----------------------------------------------------");
        printf("\nWelcome to User Management...\n");
        printf("\n1. User Registration");
        printf("\n2. User Login");
        printf("\n3. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        printf("\n");
        getchar(); //consume extra enter

        switch (choice)
        {
        case 1: register_user();
            break;
        case 2: user_index=login_user();
            if(user_index>=0) {
                printf("\nLogin successfull! Welcome, %s", users[user_index].username);
            } else {
                printf("\nLogin failed! Incorrect username and password");
            }
            break;
        case 3: printf("\nExiting Program");
            return 0;
            break;
        default: printf("\nInvalid Option! Please try again");
            break;
        }
    }
}