#include "stdio.h"
#include "conio.h"
#include "windows.h"
#define ENTER 13
#define TAB 9
#define BCKSPC 8

struct user {
    char fullName[50];
    char username[50];
    char email[50];
    char phone[50];
    char password[50];
};

void takeInput(char ch[50]) {
    fgets(ch, 50, stdin);
    ch[strlen(ch) - 1] = 0; // Removes the \n character from the string
}

char generateUsername(char email[50], char username[50]) {
    // 12345@gmail
    for (int i = 0; i < strlen(email); i++) {
        if (email[i] == '@') break;
        else username[i] = email[i];
    }
}

void takePassword(char pwd[50]) {
    int i;
    char ch;

    while (1) {
        ch = getch();
        if (ch == ENTER || ch == TAB) {
            pwd[i] = '\0';
            break;
        } else if (ch == BCKSPC) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            pwd[i++] = ch;
            printf("* \b");
        }
    }
}

int main() {
    system("color 0b");
    FILE *fp;

    int opt, userFound = 0;
    struct user user;
    char comfirm_password[50];

    printf("\n\t\t\t\t----------Welcome To Authentication System----------");
    printf("\nPlease choose your operation");
    printf("\n1 - Signup");
    printf("\n2 - Login");
    printf("\n3 - Exit");

    printf("\n\nYour choice:\t");
    scanf("%d", &opt);
    fgetc(stdin); // Removes the last \n character from the input

    switch (opt) {
        case 1:
            system("cls");

            printf("Enter your full name:\t");
            takeInput(user.fullName);
            printf("Enter your email:\t");
            takeInput(user.email);
            printf("Enter phone number:\t");
            takeInput(user.phone);
            printf("Enter your password:\t");
            takePassword(user.password);
            printf("\nComfirm your password:\t");
            takePassword(comfirm_password);

            if (!strcmp(user.password, comfirm_password)) {
                generateUsername(user.email, user.username);

                fp = fopen("Users.dat", "a+");
                fwrite(&user, sizeof(struct user), 1, fp);

                if (fwrite != 0) {
                    printf("\n\nUser registered successfully, username is %s", user.username);
                    printf("\n-----------------------------------------\n\n");
                } else {
                    printf("\n\nOpps! Something went wrong :(");
                    printf("\n\n\n\n");
                }
            } else {
                printf("\nPasswords don't match");
                Beep(750, 300);
                printf("\n\n");
            }
            fclose(fp);
        break;

        case 2:
            char username[50], pword[50];
            struct user usr;

            printf("\nEnter your username:\t");
            takeInput(username);
            printf("\nEnter your password:\t");
            takePassword(pword);

            fp = fopen("Users.dat", "r");
            while (fread(&usr, sizeof(struct user), 1, fp)) {
                if (!strcmp(usr.username, username)) {
                    if (!strcmp(usr.password, pword)) {
                        system("cls");
                        printf("\n\t\t\t\t\tWelcome %s", usr.fullName);

                        printf("\n\n|Full Name:\t%s", usr.fullName);
                        printf("\n|User Name:\t%s", usr.username);
                        printf("\n|Email:\t\t%s", usr.email);
                        printf("\n|Phone Number:\t%s", usr.phone);
                        printf("\n-------------------------------\n");
                    } else {
                        printf("\nEither username or password is incorrect.\n");
                        Beep(800, 300);
                    }
                    userFound = 1;
                }
            }

            if (!userFound) {
                printf("\nNo user Found with the provided credentials\n");
                Beep(800, 300);
            }
            fclose(fp);
        break;

        case 3:
            printf("\t\t\tBye Bye :)");
            printf("\n-------------------------------\n");
            return 0;
        break;

        default:
			printf("\nSorry, invalid option");
            printf("\n-------------------------------\n");
            Beep(850, 300);
		break;
    }

    return 0;
}
