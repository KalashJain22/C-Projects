#include<stdio.h>
#include<string.h>

void fix_fgets_input(char* );

const char* ACCOUNT_FILE = "account.dat";

typedef struct {
    char name[50];
    int acc_no;
    float balance;
} Account;

void create_account() {
    Account acc;

    FILE *file=fopen(ACCOUNT_FILE, "ab+");  //ab+ = append binary
    if(file == NULL) {
        printf("\nCould not open file");
        return;
    }

    printf("Enter Your Name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    fix_fgets_input(acc.name);
    printf("Enter Your Account Number: ");
    scanf("%d", &acc.acc_no);

    Account temp;
    while (fread(&temp, sizeof(temp), 1, file)) {
        if (temp.acc_no == acc.acc_no) {
            printf("\nAccount Number already exists\nPlease use a different Account Number");
            fseek(file, -sizeof(acc), SEEK_CUR);
            fclose(file);
            return;
        }
    }
    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\nAccount Created Successfuly");
}

void deposit_money() {
    int acc_no;
    float money;
    Account acc_d;

    FILE *file=fopen(ACCOUNT_FILE, "rb+");  //rb+ = read and write binary
    if(file == NULL) {
        printf("\nCould not open file");
        return;
    }
    printf("Enter your Account Number: ");
    scanf("%d", &acc_no);
    printf("Enter Amount to Deposit: Rs");
    scanf("%f", &money);

    while(fread(&acc_d, sizeof(acc_d), 1, file)) {
        if(acc_d.acc_no == acc_no) {
            acc_d.balance +=money;
            fseek(file, -sizeof(acc_d), SEEK_CUR);
            fwrite(&acc_d, sizeof(acc_d), 1, file);
            fclose(file);
            printf("Succefully Deposited Rs%.2f \nNew Balance: Rs%.2f", money, acc_d.balance);
            return;
        }
    }
    fclose(file);
    printf("\nAccount Number %d was not found", acc_no);
}

void withdraw_money() {
    int acc_no;
    float money;
    Account acc_w;

    FILE *file=fopen(ACCOUNT_FILE, "rb+");  //rb+ = read and write binary
    if(file == NULL) {
        printf("\nCould not open file");
        return;
    }
    printf("Enter your Account Number: ");
    scanf("%d", &acc_no);
    printf("Enter Amount to Withdraw: Rs");
    scanf("%f", &money);

    while(fread(&acc_w, sizeof(acc_w), 1, file)) {
        if(acc_w.acc_no == acc_no) {
            if(money <= acc_w.balance) {
                acc_w.balance -= money;
                fseek(file, -sizeof(acc_w), SEEK_CUR);
                fwrite(&acc_w, sizeof(acc_w), 1, file);
                printf("Succefully withdrawl Rs%.2f \nRemaining Balance: Rs%.2f", money, acc_w.balance);
            } else {
                printf("\nInsufficient Balance for Withdrawl");
            }
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("\nAccount Number %d was not found", acc_no);
}

void check_balance() {
    int acc_no;
    Account acc_read;

    FILE *file=fopen(ACCOUNT_FILE, "rb");  //rb = read binary
    if(file == NULL) {
        printf("\nCould not open file");
        return;
    }
    printf("Enter Your Account Number: ");
    scanf("%d", &acc_no);

    while(fread(&acc_read, sizeof(acc_read), 1, file)) {
        if(acc_read.acc_no == acc_no) {
            printf("\nYour Account Balance is Rs.%.2f", acc_read.balance);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("\nAccount Number %d was not found", acc_no);
}

//fixes the extra line of fgets function
void fix_fgets_input(char* string) {
    int index=strcspn(string, "\n");
    string[index]='\0';
}

int main() {
    int choice;
    while(1) {
        printf("\n\n----------------------------------------------------");
        printf("\nWelcome to Bank Management System...\n");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Check Balance");
        printf("\n5. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        printf("\n");
        getchar();  //consumes extra enter

        switch (choice)
        {
        case 1: create_account();
            break;
        case 2: deposit_money();
            break;
        case 3: withdraw_money();
            break;
        case 4: check_balance();
            break;
        case 5: printf("Exiting Program");
            return 0;
            break;
        default: printf("Invalid Option! Please try again");
            break;
        }
    }
}