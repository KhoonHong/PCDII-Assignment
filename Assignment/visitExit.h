#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h> 
#include "header.h"
#include "sanitizeValidation.h"
#include "universal.h"
#include "sanitize.h"
#include "admin.h"
#include "visitor.h"
#include "venue.h"
//Structure

//Global Variable
VisitExitInfo visitExit[50];
int visitExitCount = 0;

//Function Declaration


void visitExitMain(int userId, char currentName[], char currentIcNo[], char currentPhoneNumber[]) {

	int status;
	do {
		status = displayMenu(userId, currentName, currentIcNo, currentPhoneNumber);
	} while (status != 5);

}

//Visit Exit Menu for admin
void visitExitMenu() {

	int choice;
	do {

		printf("\t  --------------------------------------------------------------------------------- \n");
		printf("\t |                                                                                 |\n");
		printf("\t |                          TARUC SEJAHTERA (ADMIN PANEL)                          |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |      1. Modify Visit/Exit Record             2. Show Visit/Exit Report          |\n");
		printf("\t |      3. Search Visit/Exit Record             4. Exit Program                    |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  --------------------------------------------------------------------------------- \n");

		printf("\n\t Action? > ");
		scanf("%d", &choice);
		rewind(stdin);
		if (choice < 1 || choice > 4) {
			system("cls");
			printf("\t Invalid action. Please type again!\n");
		}
		else {
			switch (choice) {
			case 1: // Modify announcement
				system("cls");
				modifyVisitExit();
				system("pause");
				system("cls");
				break;
			case 2:// Show announcement
				system("cls");
				report();
				system("pause");
				system("cls");
				break;
			case 3:
				system("cls");
				adminSearch();
				system("pause");
				system("cls");
				break;
			case 4:
				return;
			}
		}
	} while (choice != 3);
}

//Display Menu Function
int displayMenu(int userId, char currentName[], char currentIcNo[], char currentPhoneNumber[]) {
	int choice;

	//Display menu for the user to choose
	printf("\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                      HERE IS THE MENU FOR YOU TO CHOOSE !                       |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |               1. Visit Venue                      2. Exit Venue                 |\n");
	printf("\t |               3. Search Record                    4. History                    |\n");
	printf("\t |               5. Exit                                                           |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");

	do {
		//Get user's choice
		printf("\n\t Please enter your choice (1, 2, 3, 4 or 5) > ");
		scanf("%d", &choice);
		rewind(stdin);

		if (choice < 1 || choice > 5) {
			printf("\tInvalid choice !! Please try again !! Only allow integers (1, 2, 3, 4 or 5) !!\n");
		}
		else {
			switch (choice) {
			case 1:
				system("cls");
				visitVenue(userId, currentName, currentIcNo, currentPhoneNumber);//Visitor Visit 
				system("pause");
				system("cls");
				return 1;
				break;
			case 2:
				system("cls");
				exitVenue(userId); //Visitor Exit 
				system("pause");
				system("cls");
				return 2;
				break;
			case 3:
				system("cls");
				searchVisitExit(userId); //Visitor Search 
				system("pause");
				system("cls");
				return 3;
				break;
			case 4:
				system("cls");
				history(userId); //Visitor History
				system("pause");
				system("cls");
				return 4;
				break;
			default:
				return 5;
			}
		}

	} while (choice != 5);


}

//Read array from text file
void readVisitExit() {
	FILE* fptr;
	fptr = fopen("VisitExit.txt", "r");

	//Check for file availability 
	if (fptr == NULL) {
		printf("\t Unable to open VisitExit.txt !\n");
		exit(-1);
	}

	//Read the visitExit array from VisitExit text file
	while (fscanf(fptr, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%f|%c|%d|%[^|]|%d|%d|%d|%d|%d|%[^|]|%d|%d|%d|%d\n",
		&visitExit[visitExitCount].visitId,
		&visitExit[visitExitCount].visitorInfo.userId,
		visitExit[visitExitCount].visitorInfo.userName,
		visitExit[visitExitCount].visitorInfo.icNum,
		visitExit[visitExitCount].visitorInfo.phoneNum,
		visitExit[visitExitCount].venueName,
		&visitExit[visitExitCount].temperature,
		&visitExit[visitExitCount].symptoms,
		&visitExit[visitExitCount].visit.day,
		visitExit[visitExitCount].visit.month,
		&visitExit[visitExitCount].visit.year,
		&visitExit[visitExitCount].visit.hour,
		&visitExit[visitExitCount].visit.min,
		&visitExit[visitExitCount].visit.sec,
		&visitExit[visitExitCount].exit.day,
		visitExit[visitExitCount].exit.month,
		&visitExit[visitExitCount].exit.year,
		&visitExit[visitExitCount].exit.hour,
		&visitExit[visitExitCount].exit.min,
		&visitExit[visitExitCount].exit.sec) != EOF) {
		visitExitCount++;
	}

	fclose(fptr);
}

//Write the visitExit array into VisitExit text file
void writeVisitExit() {
	FILE* fptr;
	fptr = fopen("VisitExit.txt", "w");

	//Check for file availability
	if (fptr == NULL) {
		printf("\t Unable to open visitExit.txt !\n");
		exit(-1);
	}

	//Write visitExit array into VisitExit text file
	for (int i = 0; i < visitExitCount; i++) {
		fprintf(fptr, "%d|%d|%s|%s|%s|%s|%f|%c|%d|%s|%d|%d|%d|%d|%d|%s|%d|%d|%d|%d\n",
			visitExit[i].visitId,
			visitExit[i].visitorInfo.userId,
			visitExit[i].visitorInfo.userName,
			visitExit[i].visitorInfo.icNum,
			visitExit[i].visitorInfo.phoneNum,
			visitExit[i].venueName,
			visitExit[i].temperature,
			visitExit[i].symptoms,
			visitExit[i].visit.day,
			visitExit[i].visit.month,
			visitExit[i].visit.year,
			visitExit[i].visit.hour,
			visitExit[i].visit.min,
			visitExit[i].visit.sec,
			visitExit[i].exit.day,
			visitExit[i].exit.month,
			visitExit[i].exit.year,
			visitExit[i].exit.hour,
			visitExit[i].exit.min,
			visitExit[i].exit.sec);
	}

	fclose(fptr);
}


//Visit venue function
void visitVenue(int userId, char currentName[], char currentIcNo[], char currentPhoneNumber[]) {
	char venueName[31];
	float temperature;
	char symptoms;
	DateTime visit;
	DateTime time = getCurrentDateTime();

	//Display menu
	printf("\n\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                     WELCOME TO TARUC PENANG BRANCH CAMPUS                       |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");

	printf("\t Please enter the following details before you enter the venue !! \n");

	//Check for the venue capacity
	switch (getVenName(venueName)) {
	case -1:
		printf("\t %s is currently not available to visit.\n\n", venueName);
		return;
	case -2:
		printf("\t %s currently reached its maximum capacity, please visit later!\n\n", venueName);
		return;
	case -3:
		printf("\t %s had closed!\n\n", venueName);
		return;
	default:
		strcpy(visitExit[visitExitCount].venueName, venueName);
	}

	//Get users' information 
	do {
		printf("\t Temperature > ");
		scanf("%f", &temperature);
		rewind(stdin);

		if (temperature < 35) {
			printf("\t Please try again !! Temperature must be bigger than 30 degress !!\n");
		}

		//Break and return the program if temperature exceed 38
		if (temperature >= 38) {
			printf("\t Please stand aside and wait for your temperature to drop and re-enter all the details\n");
			return;
		}

		visitExit[visitExitCount].temperature = temperature;
	} while (temperature < 35);


	do {
		printf("\t Symptoms (Y/N) > ");
		scanf("%c", &symptoms);
		rewind(stdin);

		if (symptoms != 'n' && symptoms != 'N' && symptoms == 'Y' && symptoms == 'y') {
			printf("\t Please try again !! Must only contain alphabet Y or N \n");
		}

		//Break the program if users are having any symptoms
		if (symptoms == 'Y' || symptoms == 'y') {
			printf("\t You are prohibited from entering this venue !! Please go to the nearest clinic or hospital for checkup\n");
		}

		visitExit[visitExitCount].symptoms = symptoms;

	} while (symptoms != 'n' && symptoms != 'N' && symptoms == 'Y' && symptoms == 'y');


	//Print the visit date and time from the computer
	printf("\t Visit Date > %02d %s %04d \n", time.day, time.month, time.year);
	visitExit[visitExitCount].visit.day = time.day;
	strcpy(visitExit[visitExitCount].visit.month, time.month);
	visitExit[visitExitCount].visit.year = time.year;

	printf("\t Visit Time > %02d:%02d:%02d \n", time.hour, time.min, time.sec);
	visitExit[visitExitCount].visit.hour = time.hour;
	visitExit[visitExitCount].visit.min = time.min;
	visitExit[visitExitCount].visit.sec = time.sec;

	visitExit[visitExitCount].visitorInfo.userId = userId;
	visitExit[visitExitCount].visitId = visitExitCount + 1;
	strcpy(visitExit[visitExitCount].visitorInfo.icNum, currentIcNo);
	strcpy(visitExit[visitExitCount].visitorInfo.phoneNum, currentPhoneNumber);
	strcpy(visitExit[visitExitCount].visitorInfo.userName, currentName);
	visitExitCount++;

	//Display message
	printf("\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                  THANK YOU FOR ENTERING ALL THE DETAILS                         |\n");
	printf("\t |               REMEMBER TO CHECK OUT WHEN YOU EXIT THE VENUE                     |\n");
	printf("\t |           ALWAYS HAVE YOUR MASK ON AND PRACTICE SOCIAL DISTANCING               |\n");
	printf("\t |                          HAVE A NICE DAY AHEAD !!!                              |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
}

//Exit Venue Function
void exitVenue(int userId) {
	DateTime exit;
	DateTime time = getCurrentDateTime();

	if (visitExit[visitExitCount - 1].visitorInfo.userId != userId || visitExit[visitExitCount - 1].exit.day != 0) {
		printf("\t You haven't visit any venue!\n");
		return;
	}

	//Display the exit menu
	printf("\n\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                       READY TO LEAVE THE VENUE ???                              |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");

	//Print the exit date and time from computer
	printf("\t Exit Date > %02d %s %04d \n", time.day, time.month, time.year);
	visitExit[visitExitCount - 1].exit.day = time.day;
	strcpy(visitExit[visitExitCount - 1].exit.month, time.month);
	visitExit[visitExitCount - 1].exit.year = time.year;

	printf("\t Exit Time > %02d:%02d:%02d \n", time.hour, time.min, time.sec);
	visitExit[visitExitCount - 1].exit.hour = time.hour;
	visitExit[visitExitCount - 1].exit.min = time.min;
	visitExit[visitExitCount - 1].exit.sec = time.sec;

	//Display message
	printf("\n\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                      THANK YOU FOR YOUR COOPERATION !!!                         |\n");
	printf("\t |                         HAVE A GOOD DAY !! BYE !!                               |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");

}

//User Search Record Function
void searchVisitExit(int userId) {
	//Variable Declaration
	int userChoice;
	char venueName[30];
	int day, year, upRange, downRange;
	char month[4];



	//Get users' choice
	do {
		userChoice = -1;
		//Display menu
		printf("\n\n");
		printf("\t  --------------------------------------------------------------------------------- \n");
		printf("\t |                                                                                 |\n");
		printf("\t |                           SEARCH YOUR RECORDS HERE !                            |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |                 1. Venue Name             2. Visit Date and Time                |\n");
		printf("\t |                 3. Exit Date and Time     4. Exit Program                       |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  --------------------------------------------------------------------------------- \n");

		printf("\n\t Please enter the number > ");
		scanf("%d", &userChoice);
		rewind(stdin);

		if (userChoice != 1 && (userChoice > 4 && userChoice < 1)) {
			printf("\tPlease try again !! Please enter 1, 2, 3 or 4 only !!\n");
		}

		else {

			//Get the search information
			switch (userChoice)
			{
			case 1:
				//Get the venue id keyword from the users to search for the target
				do {
					printf("\t Please enter the venue name > ");
					scanf("%[^\n]", venueName);
					rewind(stdin);


					int records = 0;
					VisitExitInfo searchList[50];

					if (isAlphaNumber(venueName) == 0) {
						printf("\tPlease try again !! It cannot contain any special characters !!\n");
					}
					else {
						//Copy the visitExit array to searchList array
						for (int i = 0; i < visitExitCount; i++) {
							if (userId == visitExit[i].visitorInfo.userId) {
								searchList[i].visitId = visitExit[i].visitId;
								searchList[i].visitorInfo.userId = visitExit[i].visitorInfo.userId;
								strcpy(searchList[i].visitorInfo.userName, visitExit[i].visitorInfo.userName);
								strcpy(searchList[i].visitorInfo.icNum, visitExit[i].visitorInfo.icNum);
								strcpy(searchList[i].visitorInfo.phoneNum, visitExit[i].visitorInfo.phoneNum);
								strcpy(searchList[i].venueName, visitExit[i].venueName);
								searchList[i].temperature = visitExit[i].temperature;
								searchList[i].symptoms = visitExit[i].symptoms;
								searchList[i].visit.day = visitExit[i].visit.day;
								strcpy(searchList[i].visit.month, visitExit[i].visit.month);
								searchList[i].visit.year = visitExit[i].visit.year;
								searchList[i].visit.hour = visitExit[i].visit.hour;
								searchList[i].visit.min = visitExit[i].visit.min;
								searchList[i].visit.sec = visitExit[i].visit.sec;
								searchList[i].exit.day = visitExit[i].exit.day;
								strcpy(searchList[i].exit.month, visitExit[i].exit.month);
								searchList[i].exit.year = visitExit[i].exit.year;
								searchList[i].exit.hour = visitExit[i].exit.hour;
								searchList[i].exit.min = visitExit[i].exit.min;
								searchList[i].exit.sec = visitExit[i].exit.sec;
								records++;
							}
						}
					}

					for (int i = 0; i < records; i++) {

						//Compare both string by changing both strings to lowercase using lowerString
						if (strstr(lowerString(searchList[i].venueName), lowerString(venueName)) == 0) {
							searchList[i].visitorInfo.userId = -1;
						}
					}


					//Display the search results
					displaySearchResults(searchList, records);

				} while (isAlphaNumber(venueName) == 0);

				system("pause");
				system("cls");
				break;
			case 2:
				//Get the visit date and time to search for the target
				do {
					printf("\t Please enter the visit day (eg: 17) > ");
					scanf("%d", &day);
					rewind(stdin);

					if (day < 1 || day > 31) {
						printf("\tPlease try again !! It must only between the range of 1 to 31 !!\n");
					}

				} while (day < 1 || day > 31);

				do {
					printf("\t Please enter the visit month (eg: MAR) > ");
					scanf("%[^\n]", month);
					rewind(stdin);

					if (isAlphabet(month) == 0) {
						printf("\tPlease try again !! It can only contains alphabet !!\n");
					}

				} while (isAlphabet(month) == 0);

				do {
					printf("\t Please enter the visit year (eg: 2021) > ");
					scanf("%d", &year);
					rewind(stdin);

					if (year < 2021) {
						printf("\tPlease try again !! Must only contain integers !!\n");
					}

				} while (year < 2021);

				do {
					printf("\t Please enter the visit time range (UP and in 24 hours system) > ");
					scanf("%d", &upRange);
					rewind(stdin);

					if (upRange < 0 || upRange > 24) {
						printf("\tPlease try again !! The time range can only between 0 to 24\n");
					}

				} while (upRange < 0 || upRange > 24);

				do {
					printf("\t Please enter the visit time range (DOWN and in 24 hours system) > ");
					scanf("%d", &downRange);
					rewind(stdin);

					VisitExitInfo searchList[50];
					int records = 0;

					if (downRange < 0 || downRange > 24) {
						printf("\tPlease try again !! The time range can only between 0 to 24\n");
					}
					else if (downRange > upRange) {
						printf("\tInvalid down range \n");
					}
					else {
						//Copy the visitExit array to searchList array
						for (int i = 0; i < visitExitCount; i++) {
							if (userId = visitExit[i].visitorInfo.userId) {
								searchList[i].visitId = visitExit[i].visitId;
								searchList[i].visitorInfo.userId = visitExit[i].visitorInfo.userId;
								strcpy(searchList[i].visitorInfo.userName, visitExit[i].visitorInfo.userName);
								strcpy(searchList[i].visitorInfo.icNum, visitExit[i].visitorInfo.icNum);
								strcpy(searchList[i].visitorInfo.phoneNum, visitExit[i].visitorInfo.phoneNum);
								strcpy(searchList[i].venueName, visitExit[i].venueName);
								searchList[i].temperature = visitExit[i].temperature;
								searchList[i].symptoms = visitExit[i].symptoms;
								searchList[i].visit.day = visitExit[i].visit.day;
								strcpy(searchList[i].visit.month, visitExit[i].visit.month);
								searchList[i].visit.year = visitExit[i].visit.year;
								searchList[i].visit.hour = visitExit[i].visit.hour;
								searchList[i].visit.min = visitExit[i].visit.min;
								searchList[i].visit.sec = visitExit[i].visit.sec;
								searchList[i].exit.day = visitExit[i].exit.day;
								strcpy(searchList[i].exit.month, visitExit[i].exit.month);
								searchList[i].exit.year = visitExit[i].exit.year;
								searchList[i].exit.hour = visitExit[i].exit.hour;
								searchList[i].exit.min = visitExit[i].exit.min;
								searchList[i].exit.sec = visitExit[i].exit.sec;
								records++;
							}
						}
					}

					for (int i = 0; i < records; i++) {
						//Check whether the visit day, month, year and hour input by users contain in the visitExit array
						if (userId != searchList[i].visitorInfo.userId) {
							searchList[i].visitorInfo.userId = -1;
						}
						else if (searchList[i].visit.day != day || strcmp(lowerString(searchList[i].visit.month), lowerString(month)) != 0 || searchList[i].visit.year != year) {

							searchList[i].visitorInfo.userId = -1;
						}
						else if (searchList[i].visit.hour > upRange || searchList[i].visit.hour < downRange) {

							searchList[i].visitorInfo.userId = -1;
						}
					}
					//Display the search results
					displaySearchResults(searchList, records);

				} while (downRange < 0 || downRange > 24);

				system("pause");
				system("cls");
				break;

			case 3:
				//Get the exit date and time to search for the target
				do {
					printf("\t Please enter the exit day (eg: 17) > ");
					scanf("%d", &day);
					rewind(stdin);

					if (day < 1 || day > 31) {
						printf("\tPlease try again !! It must only between the range of 1 and 31 !!\n");
					}

				} while (day < 1 || day > 31);

				do {
					printf("\t Please enter the exit month (eg: MAR) > ");
					scanf("%[^\n]", month);
					rewind(stdin);

					if (isAlphabet(month) == 0) {
						printf("\tPlease try again !! It can only contains alphabet !!\n");
					}

				} while (isAlphabet(month) == 0);

				do {
					printf("\t Please enter the exit year (eg: 2021) > ");
					scanf("%d", &year);
					rewind(stdin);

					if (year < 2021) {
						printf("\tPlease try again !! Must only contain integers !!\n");
					}

				} while (year < 2021);

				do {
					printf("\t Please enter the exit time range (UP and in 24 hours system) > ");
					scanf("%d", &upRange);
					rewind(stdin);

					if (upRange < 0 || upRange > 24) {
						printf("\tPlease try again !! The time range can only between 0 to 24\n");
					}

				} while (upRange < 0 || upRange > 24);

				do {
					printf("\t Please enter the exit time range (DOWN and in 24 hours system) > ");
					scanf("%d", &downRange);
					rewind(stdin);

					VisitExitInfo searchList[50];
					int records = 0;

					if (downRange < 0 || downRange > 24) {
						printf("\tPlease try again !! The time range can only between 0 to 24\n");
					}
					else if (downRange > upRange) {
						printf("\tInvalid down range \n");
					}
					else {
						//Copy the visitExit array to searchList array
						for (int i = 0; i < visitExitCount; i++) {
							if (userId = visitExit[i].visitorInfo.userId) {
								searchList[i].visitId = visitExit[i].visitId;
								searchList[i].visitorInfo.userId = visitExit[i].visitorInfo.userId;
								strcpy(searchList[i].visitorInfo.userName, visitExit[i].visitorInfo.userName);
								strcpy(searchList[i].visitorInfo.icNum, visitExit[i].visitorInfo.icNum);
								strcpy(searchList[i].visitorInfo.phoneNum, visitExit[i].visitorInfo.phoneNum);
								strcpy(searchList[i].venueName, visitExit[i].venueName);
								searchList[i].temperature = visitExit[i].temperature;
								searchList[i].symptoms = visitExit[i].symptoms;
								searchList[i].visit.day = visitExit[i].visit.day;
								strcpy(searchList[i].visit.month, visitExit[i].visit.month);
								searchList[i].visit.year = visitExit[i].visit.year;
								searchList[i].visit.hour = visitExit[i].visit.hour;
								searchList[i].visit.min = visitExit[i].visit.min;
								searchList[i].visit.sec = visitExit[i].visit.sec;
								searchList[i].exit.day = visitExit[i].exit.day;
								strcpy(searchList[i].exit.month, visitExit[i].exit.month);
								searchList[i].exit.year = visitExit[i].exit.year;
								searchList[i].exit.hour = visitExit[i].exit.hour;
								searchList[i].exit.min = visitExit[i].exit.min;
								searchList[i].exit.sec = visitExit[i].exit.sec;
								records++;
							}
						}
					}


					for (int i = 0; i < records; i++) {
						//Check whether the exit day, month, year and hour input by users contain in the visitExit array
						if (userId != searchList[i].visitorInfo.userId) {
							searchList[i].visitorInfo.userId = -1;
						}
						else if (searchList[i].exit.day != day || strcmp(lowerString(searchList[i].exit.month), lowerString(month)) != 0 || searchList[i].exit.year != year) {

							searchList[i].visitorInfo.userId = -1;
						}
						else if (searchList[i].exit.hour > upRange || searchList[i].exit.hour < downRange) {

							searchList[i].visitorInfo.userId = -1;
						}
					}
					//Display the search results
					displaySearchResults(searchList, records);

				} while (downRange < 0 || downRange > 24);

				system("pause");
				system("cls");
				break;

			case 4:
				printf("\n\tExit Search Menu\n");
				break;
			}
		}

	} while (userChoice != 4);

}

//Admin Search Record Function
void adminSearch() {
	//Variable Declaration
	int adminChoice;
	int userId;
	char name[30], venueName[30];
	int day, year, upRange, downRange;
	char month[4];

	//Get admin's choice
	do {
		//Display menu
		printf("\t  --------------------------------------------------------------------------------- \n");
		printf("\t |                                                                                 |\n");
		printf("\t |                           SEARCH THE RECORDS HERE !                             |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |              1. User ID                        2. Name                          |\n");
		printf("\t |              3. Venue Name                     4. Visit Date and Time           |\n");
		printf("\t |              5. Exit Date and Time             6. Exit Program                  |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  --------------------------------------------------------------------------------- \n");

		adminChoice = -1;
		printf("\t Please enter the number > ");
		scanf("%d", &adminChoice);
		rewind(stdin);
		//Get search information
		switch (adminChoice)
		{
		case 1:
			//Get the user id from admin to search for the target
			do {
				printf("\t Please enter the user ID > ");
				scanf("%d", &userId);
				rewind(stdin);

				VisitExitInfo searchList[50];
				int records = 0;
				if (userId < 0) {
					printf("\tPlease try again !! It must contain only integers !!\n");
				}
				else {
					//Copy the visitExit array into the searchList array
					for (int i = 0; i < visitExitCount; i++) {
						searchList[i].visitId = visitExit[i].visitId;
						searchList[i].visitorInfo.userId = visitExit[i].visitorInfo.userId;
						strcpy(searchList[i].visitorInfo.userName, visitExit[i].visitorInfo.userName);
						strcpy(searchList[i].visitorInfo.icNum, visitExit[i].visitorInfo.icNum);
						strcpy(searchList[i].visitorInfo.phoneNum, visitExit[i].visitorInfo.phoneNum);
						strcpy(searchList[i].venueName, visitExit[i].venueName);
						searchList[i].temperature = visitExit[i].temperature;
						searchList[i].symptoms = visitExit[i].symptoms;
						searchList[i].visit.day = visitExit[i].visit.day;
						strcpy(searchList[i].visit.month, visitExit[i].visit.month);
						searchList[i].visit.year = visitExit[i].visit.year;
						searchList[i].visit.hour = visitExit[i].visit.hour;
						searchList[i].visit.min = visitExit[i].visit.min;
						searchList[i].visit.sec = visitExit[i].visit.sec;
						searchList[i].exit.day = visitExit[i].exit.day;
						strcpy(searchList[i].exit.month, visitExit[i].exit.month);
						searchList[i].exit.year = visitExit[i].exit.year;
						searchList[i].exit.hour = visitExit[i].exit.hour;
						searchList[i].exit.min = visitExit[i].exit.min;
						searchList[i].exit.sec = visitExit[i].exit.sec;
						records++;
					}
				}

				for (int i = 0; i < records; i++) {
					if (userId != searchList[i].visitorInfo.userId) {
						searchList[i].visitorInfo.userId = -1;
					}
				}

				//Display search results
				displaySearchResults(searchList, records);
			} while (userId < 0);

			system("pause");
			system("cls");
			break;
		case 2:
			//Get the visitor name keyword to search for a target
			do {
				printf("\t Please enter the name > ");
				scanf("%[^\n]", name);
				rewind(stdin);

				VisitExitInfo searchList[50];
				int records = 0;

				if (isAlphabet(name) == 0) {
					printf("\tPlease try again !! It must only contain alphabets !!\n");
				}
				else {
					//Copy the visitExit array into the searchList array
					for (int i = 0; i < visitExitCount; i++) {
						searchList[i].visitId = visitExit[i].visitId;
						searchList[i].visitorInfo.userId = visitExit[i].visitorInfo.userId;
						strcpy(searchList[i].visitorInfo.userName, visitExit[i].visitorInfo.userName);
						strcpy(searchList[i].visitorInfo.icNum, visitExit[i].visitorInfo.icNum);
						strcpy(searchList[i].visitorInfo.phoneNum, visitExit[i].visitorInfo.phoneNum);
						strcpy(searchList[i].venueName, visitExit[i].venueName);
						searchList[i].temperature = visitExit[i].temperature;
						searchList[i].symptoms = visitExit[i].symptoms;
						searchList[i].visit.day = visitExit[i].visit.day;
						strcpy(searchList[i].visit.month, visitExit[i].visit.month);
						searchList[i].visit.year = visitExit[i].visit.year;
						searchList[i].visit.hour = visitExit[i].visit.hour;
						searchList[i].visit.min = visitExit[i].visit.min;
						searchList[i].visit.sec = visitExit[i].visit.sec;
						searchList[i].exit.day = visitExit[i].exit.day;
						strcpy(searchList[i].exit.month, visitExit[i].exit.month);
						searchList[i].exit.year = visitExit[i].exit.year;
						searchList[i].exit.hour = visitExit[i].exit.hour;
						searchList[i].exit.min = visitExit[i].exit.min;
						searchList[i].exit.sec = visitExit[i].exit.sec;
						records++;
					}
				}

				for (int i = 0; i < records; i++) {
					//Search both string by changing both strings to lowercase using lowerString
					if (strstr(lowerString(searchList[i].visitorInfo.userName), lowerString(name)) == 0) {
						searchList[i].visitorInfo.userId = -1;
					}
				}


				//Display search results
				displaySearchResults(searchList, records);

			} while (isAlphabet(name) == 0);

			system("pause");
			system("cls");
			break;

		case 3:
			//Get the venue id keyword to search for the target
			do {
				printf("\t Please enter the venue name > ");
				scanf("%[^\n]", venueName);
				rewind(stdin);

				VisitExitInfo searchList[50];
				int records = 0;

				if (isAlphaNumber(venueName) == 0) {
					printf("\tPlease try again !! It cannot contain any special characters !!\n");
				}
				else {
					//Copy the visitExit array into the searchList array
					for (int i = 0; i < visitExitCount; i++) {
						searchList[i].visitId = visitExit[i].visitId;
						searchList[i].visitorInfo.userId = visitExit[i].visitorInfo.userId;
						strcpy(searchList[i].visitorInfo.userName, visitExit[i].visitorInfo.userName);
						strcpy(searchList[i].visitorInfo.icNum, visitExit[i].visitorInfo.icNum);
						strcpy(searchList[i].visitorInfo.phoneNum, visitExit[i].visitorInfo.phoneNum);
						strcpy(searchList[i].venueName, visitExit[i].venueName);
						searchList[i].temperature = visitExit[i].temperature;
						searchList[i].symptoms = visitExit[i].symptoms;
						searchList[i].visit.day = visitExit[i].visit.day;
						strcpy(searchList[i].visit.month, visitExit[i].visit.month);
						searchList[i].visit.year = visitExit[i].visit.year;
						searchList[i].visit.hour = visitExit[i].visit.hour;
						searchList[i].visit.min = visitExit[i].visit.min;
						searchList[i].visit.sec = visitExit[i].visit.sec;
						searchList[i].exit.day = visitExit[i].exit.day;
						strcpy(searchList[i].exit.month, visitExit[i].exit.month);
						searchList[i].exit.year = visitExit[i].exit.year;
						searchList[i].exit.hour = visitExit[i].exit.hour;
						searchList[i].exit.min = visitExit[i].exit.min;
						searchList[i].exit.sec = visitExit[i].exit.sec;
						records++;
					}
				}

				for (int i = 0; i < records; i++) {
					//Compare both string by changing both strings to lowercase using lowerString
					if (strstr(lowerString(searchList[i].venueName), lowerString(venueName)) == 0) {
						searchList[i].visitorInfo.userId = -1;
					}
				}

				//Display search results
				displaySearchResults(searchList, records);

			} while (isAlphaNumber(venueName) == 0);

			system("pause");
			system("cls");
			break;

		case 4:
			//Get the visit date and time to search for the target
			do {
				printf("\t Please enter the visit day (eg: 17) > ");
				scanf("%d", &day);
				rewind(stdin);

				if (day < 1 || day > 31) {
					printf("\tPlease try again !! It must only between the range of 1 and 31 !!\n");
				}

			} while (day < 1 || day > 31);

			do {
				printf("\t Please enter the visit month (eg: MAR) > ");
				scanf("%[^\n]", month);
				rewind(stdin);

				if (isAlphabet(month) == 0) {
					printf("\tPlease try again !! It can only contains alphabet !!\n");
				}

			} while (isAlphabet(month) == 0);

			do {
				printf("\t Please enter the visit year (eg: 2021) > ");
				scanf("%d", &year);
				rewind(stdin);

				if (year < 2021) {
					printf("\tPlease try again !! It must only contain integers !!\n");
				}

			} while (year < 2021);

			do {
				printf("\t Please enter the visit time range (UP and in 24 hours system) > ");
				scanf("%d", &upRange);
				rewind(stdin);

				if (upRange < 0 || upRange > 24) {
					printf("\tPlease try again !! The time range can only between 0 to 24\n");
				}

			} while (upRange < 0 || upRange > 24);

			do {
				printf("\t Please enter the visit time range (DOWN and in 24 hours system) > ");
				scanf("%d", &downRange);
				rewind(stdin);

				VisitExitInfo searchList[50];
				int records = 0;

				if (downRange < 0 || downRange > 24) {
					printf("\tPlease try again !! The time range can only between 0 to 24\n");
				}
				else if (downRange > upRange) {
					printf("\tInvalid down range \n");
				}
				else {
					//Copy the visitExit array into the searchList array
					for (int i = 0; i < visitExitCount; i++) {
						searchList[i].visitId = visitExit[i].visitId;
						searchList[i].visitorInfo.userId = visitExit[i].visitorInfo.userId;
						strcpy(searchList[i].visitorInfo.userName, visitExit[i].visitorInfo.userName);
						strcpy(searchList[i].visitorInfo.icNum, visitExit[i].visitorInfo.icNum);
						strcpy(searchList[i].visitorInfo.phoneNum, visitExit[i].visitorInfo.phoneNum);
						strcpy(searchList[i].venueName, visitExit[i].venueName);
						searchList[i].temperature = visitExit[i].temperature;
						searchList[i].symptoms = visitExit[i].symptoms;
						searchList[i].visit.day = visitExit[i].visit.day;
						strcpy(searchList[i].visit.month, visitExit[i].visit.month);
						searchList[i].visit.year = visitExit[i].visit.year;
						searchList[i].visit.hour = visitExit[i].visit.hour;
						searchList[i].visit.min = visitExit[i].visit.min;
						searchList[i].visit.sec = visitExit[i].visit.sec;
						searchList[i].exit.day = visitExit[i].exit.day;
						strcpy(searchList[i].exit.month, visitExit[i].exit.month);
						searchList[i].exit.year = visitExit[i].exit.year;
						searchList[i].exit.hour = visitExit[i].exit.hour;
						searchList[i].exit.min = visitExit[i].exit.min;
						searchList[i].exit.sec = visitExit[i].exit.sec;
						records++;
					}
				}
				for (int i = 0; i < records; i++) {
					//Check whether the exit day, month, year and hour input by users contain in the visitExit array
					if (searchList[i].visit.day != day || strcmp(lowerString(searchList[i].visit.month), lowerString(month)) != 0 || searchList[i].visit.year != year) {

						searchList[i].visitorInfo.userId = -1;
					}
					else if (searchList[i].visit.hour > upRange || searchList[i].visit.hour < downRange) {

						searchList[i].visitorInfo.userId = -1;
					}

				}


				displaySearchResults(searchList, records);

			} while (downRange < 0 || downRange > 24);

			system("pause");
			system("cls");
			break;

		case 5:
			//Get the exit date and time to search for the target
			do {
				printf("\t Please enter the exit day (eg: 17) > ");
				scanf("%d", &day);
				rewind(stdin);

				if (day < 1 || day > 31) {
					printf("\tPlease try again !! It can only between the range of 1 and 31 !!\n");
				}

			} while (day < 1 || day > 31);

			do {
				printf("\t Please enter the exit month (eg: MAR) > ");
				scanf("%[^\n]", month);
				rewind(stdin);

				if (isAlphabet(month) == 0) {
					printf("\tPlease try again !! It can only contains alphabet !!\n");
				}

			} while (isAlphabet(month) == 0);

			do {
				printf("\t Please enter the exit year (eg: 2021) > ");
				scanf("%d", &year);
				rewind(stdin);

				if (year < 2021) {
					printf("\tPlease try again !! Must only contain integers !!\n");
				}

			} while (year < 2021);

			do {
				printf("\t Please enter the exit time range (UP and in 24 hours system) > ");
				scanf("%d", &upRange);
				rewind(stdin);

				if (upRange < 0 || upRange > 24) {
					printf("\tPlease try again !! The time range can only between 0 to 24\n");
				}

			} while (upRange < 0 || upRange > 24);

			do {
				printf("\t Please enter the exit time range (DOWN and in 24 hours system) > ");
				scanf("%d", &downRange);
				rewind(stdin);

				VisitExitInfo searchList[50];
				int records = 0;

				if (downRange < 0 || downRange > 24) {
					printf("\tPlease try again !! The time range can only between 0 to 24\n");
				}
				else if (downRange > upRange) {
					printf("\tInvalid down range \n");
				}
				else {
					//Copy the visitExit array into the searchList array
					for (int i = 0; i < visitExitCount; i++) {
						searchList[i].visitId = visitExit[i].visitId;
						searchList[i].visitorInfo.userId = visitExit[i].visitorInfo.userId;
						strcpy(searchList[i].visitorInfo.userName, visitExit[i].visitorInfo.userName);
						strcpy(searchList[i].visitorInfo.icNum, visitExit[i].visitorInfo.icNum);
						strcpy(searchList[i].visitorInfo.phoneNum, visitExit[i].visitorInfo.phoneNum);
						strcpy(searchList[i].venueName, visitExit[i].venueName);
						searchList[i].temperature = visitExit[i].temperature;
						searchList[i].symptoms = visitExit[i].symptoms;
						searchList[i].visit.day = visitExit[i].visit.day;
						strcpy(searchList[i].visit.month, visitExit[i].visit.month);
						searchList[i].visit.year = visitExit[i].visit.year;
						searchList[i].visit.hour = visitExit[i].visit.hour;
						searchList[i].visit.min = visitExit[i].visit.min;
						searchList[i].visit.sec = visitExit[i].visit.sec;
						searchList[i].exit.day = visitExit[i].exit.day;
						strcpy(searchList[i].exit.month, visitExit[i].exit.month);
						searchList[i].exit.year = visitExit[i].exit.year;
						searchList[i].exit.hour = visitExit[i].exit.hour;
						searchList[i].exit.min = visitExit[i].exit.min;
						searchList[i].exit.sec = visitExit[i].exit.sec;
						records++;
					}
				}

				for (int i = 0; i < records; i++) {
					//Check whether the exit day, month, year and hour input by users contain in the visitExit array
					if (searchList[i].exit.day != day || strcmp(lowerString(searchList[i].exit.month), lowerString(month)) != 0 || searchList[i].exit.year != year) {

						searchList[i].visitorInfo.userId = -1;
					}
					else if (searchList[i].exit.hour > upRange || searchList[i].exit.hour < downRange) {

						searchList[i].visitorInfo.userId = -1;
					}
				}

				displaySearchResults(searchList, records);

			} while (downRange < 0 || downRange > 24);

			system("pause");
			system("cls");
			break;

		case 6:
			printf("\n\tExit search program !!\n");
			break;
		default:
			printf("\tPlease try again !! Please enter 1, 2, 3, 4, 5 or 6 only !!\n");
			break;
		}

	} while (adminChoice != 6);

}

//Display search results
void displaySearchResults(VisitExitInfo searchList[50], int records) {
	int flag = 0;
	printf("\n\n");
	printf("\t +-----------+-------------+----------------+---------------+-----------------+---------------+---------------+-----------+---------------+--------------+---------------+-------------+\n");
	printf("\t |Visit ID   |User ID      | Name           | IC NO.        |Phone NO.        | Venue Name    | Temperature   | Symptoms  | Visit Date    | Visit Time   | Exit Date     | Exit Time   |\n");
	printf("\t +-----------+-------------+----------------+---------------+-----------------+---------------+---------------+-----------+---------------+--------------+---------------+-------------+\n");

	for (int i = 0; i < records; i++) {
		if (searchList[i].visitorInfo.userId != -1) {
			flag = 1;
			printf("\t |%-9d  |%-9d    | %-14s | %-13s | %-15s | %-10s    | %.2f         | %c         | %02d %s %04d   | %02d:%02d:%02d     | %02d %s %04d   | %02d:%02d:%02d    |\n",
				searchList[i].visitId,
				searchList[i].visitorInfo.userId,
				searchList[i].visitorInfo.userName,
				searchList[i].visitorInfo.icNum,
				searchList[i].visitorInfo.phoneNum,
				upperString(searchList[i].venueName),
				searchList[i].temperature,
				searchList[i].symptoms,
				searchList[i].visit.day,
				upperString(searchList[i].visit.month),
				searchList[i].visit.year,
				searchList[i].visit.hour,
				searchList[i].visit.min,
				searchList[i].visit.sec,
				searchList[i].exit.day,
				upperString(searchList[i].exit.month),
				searchList[i].exit.year,
				searchList[i].exit.hour,
				searchList[i].exit.min,
				searchList[i].exit.sec);
			printf("\t +-----------+-------------+----------------+---------------+-----------------+---------------+---------------+-----------+---------------+--------------+---------------+-------------+\n");
		}
		else {
			continue;
		}
	}
	if (!flag)
	{
		printf("\n\t No records found\n\n");
	}
}

//Modify Record
void modifyVisitExit() {
	int modifyVisitId;
	int option, newDay, newYear, newHr, newMin, newSec;
	float newTemp;
	char newId[30], newMth[4];
	char newSymp;
	int validity = 0;

	report();

	//Get the visit id that the admin wants to modify 
	do {
		printf("\t Please enter the visit id that you want to modify > ");
		scanf("%d", &modifyVisitId);
		rewind(stdin);
		for (int i = 0; i < visitExitCount; i++) {
			if (visitExit[i].visitId == modifyVisitId) {
				validity = 1;
				break;
			}
		}
		if (validity == 0) {
			printf("\t Invalid visit id !! Please enter again !!\n");
		}
	} while (validity == 0);

	//Display modify menu
	do {
		printf("\t  ---------------------------------------------------------------------------------\n");
		printf("\t |                                                                                 |\n");
		printf("\t |                          MODIFY YOUR RECORD HERE !                              |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |              1. Venue Name                        2. Temperature                |\n");
		printf("\t |              3. Symptoms                          4. Visit Date                 |\n");
		printf("\t |              5. Visit Time                        6. Exit Date                  |\n");
		printf("\t |              7. Exit Time                         8. Exit                       |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  --------------------------------------------------------------------------------- \n");

		//Get admin option
		do {
			printf("\t Please enter your option  > ");
			scanf("%d", &option);
			rewind(stdin);

			if (option > 8 || option < 1) {
				printf("\tPlease try again !! Please only enter one number from 1, 2, 3, 4, 5, 6, 7 or 8 only !!\n");
			}

		} while (option > 8 || option < 1);

		//Modify the visitExit array according to the admin's choice
		switch (option) {
		case 1:
			do {
				printf("\t New Venue Name > ");
				scanf("%[^\n]", newId);
				rewind(stdin);

				if (isAlphaNumber(newId) == 0) {
					printf("\tPlease try again !! It must not contain any special characters !!\n");
				}

			} while (isAlphaNumber(newId) == 0);

			for (int i = 0; i < visitExitCount; i++) {
				if (visitExit[i].visitId == modifyVisitId) {
					strcpy(visitExit[i].venueName, newId);
				}
			}
			printf("\t Successfully modified !!\n");
			break;

		case 2:
			do {
				printf("\t New Temperature > ");
				scanf("%f", &newTemp);
				rewind(stdin);

				if (newTemp < 35 && newTemp > 40) {
					printf("Please try again !! It must only between the range of 35 to 40 degrees Celsius !!\n");
				}

			} while (newTemp < 35 && newTemp > 40);

			for (int i = 0; i < visitExitCount; i++) {
				if (visitExit[i].visitId == modifyVisitId) {
					visitExit[i].temperature = newTemp;
				}
			}
			printf("\t Successfully modified !!\n");
			break;

		case 3:
			do {
				printf("\t New Symptoms > ");
				scanf("%c", &newSymp);
				rewind(stdin);

				if (newSymp != 'N' && newSymp != 'n' && newSymp != 'Y' && newSymp != 'y') {
					printf("\tPlease try again !! It must only be the alphabet of Y or N !!\n");
				}

			} while (newSymp != 'N' && newSymp != 'n' && newSymp != 'Y' && newSymp != 'y');

			for (int i = 0; i < visitExitCount; i++) {
				if (visitExit[i].visitId == modifyVisitId) {
					visitExit[i].symptoms = newSymp;
				}
			}
			printf("\t Successfully modified !!\n");
			break;

		case 4:
			do {
				printf("\t New Visit Date (01 FEB 2021) > ");
				scanf("%d %s %d", &newDay, &newMth, &newYear);
				rewind(stdin);

				if (newDay < 1 && newDay>31 || isAlphabet(newMth) || newYear < 2021) {
					printf("\tPlease try again !! Please enter according to the format shown above!!\n");
				}

			} while (newDay < 1 && newDay>31 || isAlphabet(newMth) || newYear < 2021);

			for (int i = 0; i < visitExitCount; i++) {
				if (visitExit[i].visitId == modifyVisitId) {
					visitExit[i].visit.day = newDay;
					strcpy(visitExit[i].visit.month, newMth);
					visitExit[i].visit.year = newYear;
				}
			}
			printf("\t Successfully modified !!\n");
			break;

		case 5:
			do {
				printf("\t New Visit Time (12 35 40) > ");
				scanf("%d %d %d", &newHr, &newMin, &newSec);
				rewind(stdin);

				if (newHr < 0 && newHr>24 || newMin < 0 && newMin>60 || newSec < 0 && newSec>60) {
					printf("\tPlease try again !! Please enter according to the format shown above!!\n");
				}

			} while (newHr < 0 && newHr>24 || newMin < 0 && newMin>60 || newSec < 0 && newSec>60);

			for (int i = 0; i < visitExitCount; i++) {
				if (visitExit[i].visitId == modifyVisitId) {
					visitExit[i].visit.hour = newHr;
					visitExit[i].visit.min = newMin;
					visitExit[i].visit.sec = newSec;
				}
			}

			printf("\t Successfully modified !!\n");
			break;

		case 6:
			do {
				printf("\t New Exit Date (01 FEB 2021) > ");
				scanf("%d %s %d", &newDay, &newMth, &newYear);
				rewind(stdin);

				if (newDay < 1 && newDay>31 || isAlphabet(newMth) || newYear < 2021) {
					printf("\tPlease try again !! Please enter according to the format shown above!!\n");
				}

			} while (newDay < 1 && newDay>31 || isAlphabet(newMth) || newYear < 2021);

			for (int i = 0; i < visitExitCount; i++) {
				if (visitExit[i].visitId == modifyVisitId) {
					visitExit[i].exit.day = newDay;
					strcpy(visitExit[i].exit.month, newMth);
					visitExit[i].exit.year = newYear;
				}
			}

			printf("\t Successfully modified !!\n");
			break;

		case 7:
			do {
				printf("\t New Exit Time (12 35 40) > ");
				scanf("%d %d %d", &newHr, &newMin, &newSec);
				rewind(stdin);

				if (newHr < 0 && newHr>24 || newMin < 0 && newMin>60 || newSec < 0 && newSec>60) {
					printf("\tPlease try again !! Please enter according to the format shown above!!\n");
				}

			} while (newHr < 0 && newHr>24 || newMin < 0 && newMin>60 || newSec < 0 && newSec>60);

			for (int i = 0; i < visitExitCount; i++) {
				if (visitExit[i].visitId == modifyVisitId) {
					visitExit[i].exit.hour = newHr;
					visitExit[i].exit.min = newMin;
					visitExit[i].exit.sec = newSec;
				}
			}
			printf("\t Successfully modified !!\n");
			break;

		case 8:
			printf("\t Exit Modification Menu !! \n");
			return;
		}

	} while (option != 8);

}


//History Function
//Display the user's history of the current day 
void history(int userId) {

	printf("\t ------------- \n");
	printf("\t |  History  | \n");
	printf("\t ------------- \n");
	printf("\t +-----------+-------------+----------------+---------------+-----------------+---------------+---------------+-----------+---------------+--------------+---------------+-------------+\n");
	printf("\t |Visit ID   |User ID      | Name           | IC NO.        |Phone NO.        | Venue Name    | Temperature   | Symptoms  | Visit Date    | Visit Time   | Exit Date     | Exit Time   |\n");
	printf("\t +-----------+-------------+----------------+---------------+-----------------+---------------+---------------+-----------+---------------+--------------+---------------+-------------+\n");


	for (int i = 0; i < visitExitCount; i++) {
		if (userId == visitExit[i].visitorInfo.userId) {
			printf("\t |%-9d  |%-9d    | %-14s | %-13s | %-15s | %-10s    | %.2f         | %c         | %02d %s %04d   | %02d:%02d:%02d     | %02d %s %04d   | %02d:%02d:%02d    |\n",
				visitExit[i].visitId,
				visitExit[i].visitorInfo.userId,
				visitExit[i].visitorInfo.userName,
				visitExit[i].visitorInfo.icNum,
				visitExit[i].visitorInfo.phoneNum,
				visitExit[i].venueName,
				visitExit[i].temperature,
				visitExit[i].symptoms,
				visitExit[i].visit.day,
				visitExit[i].visit.month,
				visitExit[i].visit.year,
				visitExit[i].visit.hour,
				visitExit[i].visit.min,
				visitExit[i].visit.sec,
				visitExit[i].exit.day,
				visitExit[i].exit.month,
				visitExit[i].exit.year,
				visitExit[i].exit.hour,
				visitExit[i].exit.min,
				visitExit[i].exit.sec);
			printf("\t +-----------+-------------+----------------+---------------+-----------------+---------------+---------------+-----------+---------------+--------------+---------------+-------------+\n");

		}

	}

}

//Report Function
//Display the report of the visitor records for admin
void report() {

	printf("\t ------------- \n");
	printf("\t |  Report   | \n");
	printf("\t ------------- \n");

	printf("\t +-----------+-------------+----------------+---------------+-----------------+---------------+---------------+-----------+---------------+--------------+---------------+-------------+\n");
	printf("\t |Visit ID   |User ID      | Name           | IC NO.        |Phone NO.        | Venue Name    | Temperature   | Symptoms  | Visit Date    | Visit Time   | Exit Date     | Exit Time   |\n");
	printf("\t +-----------+-------------+----------------+---------------+-----------------+---------------+---------------+-----------+---------------+--------------+---------------+-------------+\n");

	for (int i = 0; i < visitExitCount; i++) {
		printf("\t |%-9d  |%-9d    | %-14s | %-13s | %-15s | %-10s    | %.2f         | %c         | %02d %s %04d   | %02d:%02d:%02d     | %02d %s %04d   | %02d:%02d:%02d    |\n",
			visitExit[i].visitId,
			visitExit[i].visitorInfo.userId,
			visitExit[i].visitorInfo.userName,
			visitExit[i].visitorInfo.icNum,
			visitExit[i].visitorInfo.phoneNum,
			visitExit[i].venueName,
			visitExit[i].temperature,
			visitExit[i].symptoms,
			visitExit[i].visit.day,
			visitExit[i].visit.month,
			visitExit[i].visit.year,
			visitExit[i].visit.hour,
			visitExit[i].visit.min,
			visitExit[i].visit.sec,
			visitExit[i].exit.day,
			visitExit[i].exit.month,
			visitExit[i].exit.year,
			visitExit[i].exit.hour,
			visitExit[i].exit.min,
			visitExit[i].exit.sec);
		printf("\t +-----------+-------------+----------------+---------------+-----------------+---------------+---------------+-----------+---------------+--------------+---------------+-------------+\n");
	}


}

