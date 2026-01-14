#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define DEFAULT_TERMINAL_WIDTH 120
#define MAX_LENGTH 128
#define DATA_FILE "account-information.txt"

// Function prototype
void gotoxy(int x,int y);
void newLineClear(char *str);
void cleanScreen();
int loadingScreen();
void adminTerminal();
void createAccount();
void loginAccount();
void firstIntroduction();

typedef struct
{
	char account_name[MAX_LENGTH];
	char account_surname[MAX_LENGTH];
	char account_password[MAX_LENGTH];
	char account_code[MAX_LENGTH];
	float account_balance;
} accountInformation;

int main() 
{
	firstIntroduction();
	return 0;
}

void gotoxy(int x,int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void cleanScreen()
{
	system("cls");
    fflush(stdout);
}

int loadingScreen()
{
	int r, q;
	gotoxy(55,12);
	printf("Loading...\n");
	gotoxy(49,14);
	for(r=1;r<=20;r++)
	{
		for(q=0; q<=100000000;q++);
		printf("%c",177);
	}
	
	printf("\n");
	cleanScreen();
}

void adminTerminal()
{
	cleanScreen();
	loadingScreen();
	cleanScreen();
	
	FILE *fp = fopen(DATA_FILE, "rb");
	if (fp == NULL) {
        printf("Error opening data file!\n");
        return;
    }
	accountInformation temp_account;
	printf("\x1b[1m\x1b[36mAccount List\x1b[0m\n");
	
	while (fread(&temp_account, sizeof(accountInformation), 1, fp) == 1) {
        printf("Name: %s, Surname: %s, Password: %s, AccountCode: %s\n", 
               temp_account.account_name, temp_account.account_surname, temp_account.account_password, temp_account.account_code);
    }
	fclose(fp);
	printf("\nPress any key to return to the main menu: ");
	getch();
	firstIntroduction();
	
}

void newLineClear(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

void createAccount()
{
    cleanScreen();
    loadingScreen();
    cleanScreen();
    
    accountInformation new_account;
    
    printf("\x1b[1m\x1b[35mAccount Creation Screen\x1b[0m\n");
    printf("\x1b[33mWARNING: \x1b[0mPlease use only English characters!\n");
    
    printf("Please enter your name: ");
    fgets(new_account.account_name, MAX_LENGTH, stdin);
    newLineClear(new_account.account_name);
    
    printf("Please enter your surname: ");   
    fgets(new_account.account_surname, MAX_LENGTH, stdin);
    newLineClear(new_account.account_surname);
    
    printf("Please create a password: ");
    fgets(new_account.account_password, MAX_LENGTH, stdin);
    newLineClear(new_account.account_password);
    
    
    int i;
	const char alphabet_numbers[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"};
	char randomStr[7];
	
	srand(time(NULL));
	
	for(i=0;i<6;i++)
	{
		int index = rand() % (sizeof(alphabet_numbers)-1);
		randomStr[i] = alphabet_numbers[index];
	}
	
	randomStr[6] = '\0';
    
    strcpy(new_account.account_code, randomStr);
    
    
    new_account.account_balance = 0.0; 

    FILE *fp = fopen(DATA_FILE, "ab");
    if (fp == NULL) {
        printf("Error opening data file!\n");
        return;
    }

    fwrite(&new_account, sizeof(accountInformation), 1, fp);
    
    fclose(fp);
    
    printf("Account created successfully!\n");
    Sleep(1500);
    cleanScreen();
    firstIntroduction();
}

void loginAccount()
{
	cleanScreen();
	loadingScreen();
	cleanScreen();
	printf("\x1b[1m\x1b[35mAccount Log In Screen\x1b[0m\n");
	
	char input_name[MAX_LENGTH];
    char input_surname[MAX_LENGTH];
    char input_password[MAX_LENGTH];
	
	printf("Please enter your name: ");
    fgets(input_name, MAX_LENGTH, stdin);newLineClear(input_name);

    printf("Please enter your surname: ");
    fgets(input_surname, MAX_LENGTH, stdin);newLineClear(input_surname);

    printf("Please enter your password: ");
    fgets(input_password, MAX_LENGTH, stdin);newLineClear(input_password);
	
	
	FILE *fp = fopen(DATA_FILE,"rb");
	if (fp == NULL)
    {
        printf("\x1b[1m\x1b[31mERROR: \x1b[0mAccount data file not found.\n");
        sleep(2);
        firstIntroduction();
        return;
    }
    
    accountInformation check_account;
    int login_success = 0;
    
    while(fread(&check_account,sizeof(accountInformation),1,fp) == 1)
    {
    	if(strcmp(input_name, check_account.account_name) == 0 
		&& strcmp(input_surname, check_account.account_surname) == 0 
		&& strcmp(input_password, check_account.account_password) == 0)
		{
			login_success = 1;
			break;
		}
	}
	fclose(fp);
	cleanScreen();
	
	if(login_success)
	{
		printf("\x1b[1m\x1b[32mLogin Successful!\x1b[0m\n");
        printf("Welcome, %s %s.\n", input_name, input_surname);
        sleep(3);
        //DEVAM EDECEK
	}
	else
	{
		printf("\x1b[1m\x1b[31mLogin Failed: \x1b[0mIncorrect name, surname, or password.\n");
		sleep(2);
		firstIntroduction();
	}
	
}

void firstIntroduction()
{
	cleanScreen();
	loadingScreen();
	cleanScreen();
	
	char selected_menu;
	printf("\x1b[1m\x1b[32mBanking Terminal\x1b[0m\n");
	printf("1-Create a New Account\n");
	printf("2-Log In to Your Account\n");
	printf("3-Login to The Administrator Terminal\n");
	printf("q-Quit\n");
	printf("\nPlease select a menu: ");
	selected_menu = getch();
		
	if (selected_menu != '1' && selected_menu !='2' && selected_menu !='3' && selected_menu !='q')
	{
		cleanScreen();
		printf("\x1b[1m\x1b[31mERROR: \x1b[0mPlease enter a valid value!\n");
		sleep(2);
		firstIntroduction();
	}
	
	else if (selected_menu == '1')
	{
		createAccount();
	}
	
	else if (selected_menu == '2')
	{
		loginAccount();
	}
	
	else if (selected_menu == '3')
	{
		adminTerminal();
	}
	else if (selected_menu == 'q')
	{
		return;
	}
}

