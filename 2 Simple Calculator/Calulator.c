#include<stdio.h>
#include<math.h>

void print_menu() {
    printf("\nChoose one of the Following Option:\n");
    printf("1.Add\n");
    printf("2.Subtract\n");
    printf("3.Multiply\n");
    printf("4.Divide\n");
    printf("5.Modulus\n");
    printf("6.Power\n");
    printf("7.Exit\n");
}

double divide(double a, double b) {
    if(b == 0) {
        fprintf(stderr, "Invalid Arguments for Divide\n");
        return NAN;
    } else {
        return a / b;
    }
}

double modulus(int a, int b) {
    if(b == 0) {
        fprintf(stderr, "Invalid Arguments for Modulus\n");
        return NAN;
    } else {
        return a % b;
    }
}

int main() {
    int choice;
    double first,second,result;

    printf("\n\nWelcome To Simple Calculator\n");

    while(1) {
        printf("\n-----------------------------------");
        print_menu();
        printf("\nNow, Enter Your Choice: ");
        scanf("%d", &choice);

        if(choice == 7) {
            break;
        }

        if(choice < 1 || choice > 7) {
            fprintf(stderr, "Invalid Menu Choice\n");
            continue;
        }

        printf("Please Enter First Number: ");
        scanf("%lf", &first);
        printf("Please Enter Second Number: ");
        scanf("%lf", &second);

        switch(choice) {
            case 1: //Add
                result = first + second;
                break;
            case 2: //Subtract
                result = first - second;
                break;
            case 3: //Multiply
                result = first * second;
                break;
            case 4: //Divide
                result = divide(first, second);
                break;
            case 5: //Modulus
                result = modulus((int)first, (int)second);
                break;
            case 6: //Power
                result = pow(first, second);
                break;
        }

        if(!isnan(result)) {
            printf("\nResult of Operation is %.2f\n", result);
        }
    };
}