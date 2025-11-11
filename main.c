#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <conio.h>
#include <windows.h>

#define DEFAULT_TERMINAL_WIDTH 120
#define MAX_LENGTH 128
#define DATA_FILE "account-information.txt"

typedef struct
{
	int account_num;
	char account_name[MAX_LENGTH];
	char account_surname[MAX_LENGTH];
	int account_password;
	float account_balance;
} accountInformation;

void gotoxy(int x,int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void newLineClear(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

void cleanScreen()
{
	printf("\033[3J\033[H\033[2J");
    fflush(stdout);
}

int loadingScreen()
{
	int r, q;
	gotoxy(55,12);
	printf("Loading...\n");
	gotoxy(50,14);
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
}

void createAccount()
{
	cleanScreen();
	loadingScreen();
	cleanScreen();
	
	accountInformation accounts[MAX_LENGTH];
	
	char unverified_name[MAX_LENGTH];
	char unverified_surname[MAX_LENGTH];
	char unverified_password[MAX_LENGTH];
	
	printf("\x1b[1m\x1b[35mAccount Creation Screen\x1b[0m\n");
	
	printf("\x1b[33mWARNING: \x1b[0mPlease use only English characters!\n");
	printf("Please enter your name: ");
	fgets(unverified_name,MAX_LENGTH,stdin);newLineClear(unverified_name);
	printf("Please enter your surname: ");	
	fgets(unverified_surname,MAX_LENGTH,stdin);newLineClear(unverified_surname);
	printf("Please create a password: ");
	fgets(unverified_password, MAX_LENGTH, stdin);newLineClear(unverified_password);
	
	FILE *fp = fopen(DATA_FILE,"a");
	fprintf(fp,"Name: %s Surname: %s Password: %d\n",unverified_name,unverified_surname,atoi(unverified_password));
	fclose(fp);
	cleanScreen();
	firstIntroduction();
}

void loginAccount()
{
	cleanScreen();
	loadingScreen();
	cleanScreen();
	
	printf("\x1b[1m\x1b[35mAccount Log In Screen\x1b[0m\n");
}

void firstIntroduction()
{
	cleanScreen();
	loadingScreen();
	cleanScreen();
	
	char selected_menu[MAX_LENGTH];
	printf("\x1b[1m\x1b[32mBank Transactions Terminal\x1b[0m\n");
	printf("1-Create a New Account\n");
	printf("2-Log In to Your Account\n");
	printf("3-Login to The Administrator Terminal\n");
	printf("q-Quit\n");
	printf("Please select a menu: ");
	fgets(selected_menu, MAX_LENGTH, stdin);
	selected_menu[strcspn(selected_menu, "\n")] = '\0';
	
	if (strcmp(selected_menu,"1") != 0 && strcasecmp(selected_menu,"2") != 0 && strcasecmp(selected_menu,"3") != 0 && strcasecmp(selected_menu,"q") != 0)
	{
		cleanScreen();
		printf("\x1b[1m\x1b[31mERROR: \x1b[0mPlease enter a valid value!\n");
		firstIntroduction();
	}
	
	else if (strcmp(selected_menu,"1")==0)
	{
		createAccount();
	}
	
	else if (strcmp(selected_menu,"2")==0)
	{
		loginAccount();
	}
	
	else if (strcmp(selected_menu,"3")==0)
	{
		adminTerminal();
	}
	else if (strcmp(selected_menu,"q")==0)
	{
		return;
	}
}

int main() 
{
	firstIntroduction();
	
	
	return 0;
}
