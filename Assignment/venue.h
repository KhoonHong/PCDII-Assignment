
//Main Menu//
void venueAdminMenu() {

	int choice;

	printf("\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                       TARUC SEJAHTERA (VENUE INFORMATION)                       |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |         1. Search for Venues                    2. Display All Venues           |\n");
	printf("\t |         3. Modify Venues                        4. Set availability             |\n");
	printf("\t |         5. Check availability                   6. Add Venues                   |\n");
	printf("\t |         7. Delete Venue                         8. Exit Programme               |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
	//Selection from 1-7//
	do {
		printf("\t Action? > ");
		scanf("%d", &choice);
		rewind(stdin);
		if (choice < 1 || choice > 8) {
			printf("\t Invalid action. Please type again!\n");
		}
		else {
			switch (choice) {
			case 1:
				system("cls");
				searchVenInfo();
				system("pause");
				system("cls");
				printf("\t  --------------------------------------------------------------------------------- \n");
				printf("\t |                                                                                 |\n");
				printf("\t |                       TARUC SEJAHTERA (VENUE INFORMATION)                       |\n");
				printf("\t |                                                                                 |\n");
				printf("\t |         1. Search for Venues                    2. Display All Venues           |\n");
				printf("\t |         3. Modify Venues                        4. Set availability             |\n");
				printf("\t |         5. Check availability                   6. Add Venues                   |\n");
				printf("\t |         7. Delete Venue                         8. Exit Programme               |\n");
				printf("\t |                                                                                 |\n");
				printf("\t  --------------------------------------------------------------------------------- \n");
				break;
			case 2:
				system("cls");
				displayVenInfo();
				system("pause");
				system("cls");
				printf("\t  --------------------------------------------------------------------------------- \n");
				printf("\t |                                                                                 |\n");
				printf("\t |                       TARUC SEJAHTERA (VENUE INFORMATION)                       |\n");
				printf("\t |                                                                                 |\n");
				printf("\t |         1. Search for Venues                    2. Display All Venues           |\n");
				printf("\t |         3. Modify Venues                        4. Set availability             |\n");
				printf("\t |         5. Check availability                   6. Add Venues                   |\n");
				printf("\t |         7. Delete Venue                         8. Exit Programme               |\n");
				printf("\t |                                                                                 |\n");
				printf("\t  --------------------------------------------------------------------------------- \n");
				break;
			case 3:
				system("cls");
				modVenInfo();
				system("pause");
				system("cls");
				printf("\t  --------------------------------------------------------------------------------- \n");
				printf("\t |                                                                                 |\n");
				printf("\t |                       TARUC SEJAHTERA (VENUE INFORMATION)                       |\n");
				printf("\t |                                                                                 |\n");
				printf("\t |         1. Search for Venues                    2. Display All Venues           |\n");
				printf("\t |         3. Modify Venues                        4. Set availability             |\n");
				printf("\t |         5. Check availability                   6. Add Venues                   |\n");
				printf("\t |         7. Delete Venue                         8. Exit Programme               |\n");
				printf("\t |                                                                                 |\n");
				printf("\t  --------------------------------------------------------------------------------- \n");
				break;
			case 4:
				system("cls");
				setVenAvail();
				system("pause");
				system("cls");
				printf("\t  --------------------------------------------------------------------------------- \n");
				printf("\t |                                                                                 |\n");
				printf("\t |                       TARUC SEJAHTERA (VENUE INFORMATION)                       |\n");
				printf("\t |                                                                                 |\n");
				printf("\t |         1. Search for Venues                    2. Display All Venues           |\n");
				printf("\t |         3. Modify Venues                        4. Set availability             |\n");
				printf("\t |         5. Check availability                   6. Add Venues                   |\n");
				printf("\t |         7. Delete Venue                         8. Exit Programme               |\n");
				printf("\t |                                                                                 |\n");
				printf("\t  --------------------------------------------------------------------------------- \n");
				break;
			case 5:
				system("cls");
				checkVenAvail();
				system("pause");
				system("cls");
				printf("\t  --------------------------------------------------------------------------------- \n");
				printf("\t |                                                                                 |\n");
				printf("\t |                       TARUC SEJAHTERA (VENUE INFORMATION)                       |\n");
				printf("\t |                                                                                 |\n");
				printf("\t |         1. Search for Venues                    2. Display All Venues           |\n");
				printf("\t |         3. Modify Venues                        4. Set availability             |\n");
				printf("\t |         5. Check availability                   6. Add Venues                   |\n");
				printf("\t |         7. Delete Venue                         8. Exit Programme               |\n");
				printf("\t |                                                                                 |\n");
				printf("\t  --------------------------------------------------------------------------------- \n");
				break;
			case 6:
				system("cls");
				addVenue();
				system("pause");
				system("cls");
				printf("\t  --------------------------------------------------------------------------------- \n");
				printf("\t |                                                                                 |\n");
				printf("\t |                       TARUC SEJAHTERA (VENUE INFORMATION)                       |\n");
				printf("\t |                                                                                 |\n");
				printf("\t |         1. Search for Venues                    2. Display All Venues           |\n");
				printf("\t |         3. Modify Venues                        4. Set availability             |\n");
				printf("\t |         5. Check availability                   6. Add Venues                   |\n");
				printf("\t |         7. Delete Venue                         8. Exit Programme               |\n");
				printf("\t |                                                                                 |\n");
				printf("\t  --------------------------------------------------------------------------------- \n");
				break;
			case 7:
				system("cls");
				delVenInfo();
				system("pause");
				system("cls");
				printf("\t  --------------------------------------------------------------------------------- \n");
				printf("\t |                                                                                 |\n");
				printf("\t |                       TARUC SEJAHTERA (VENUE INFORMATION)                       |\n");
				printf("\t |                                                                                 |\n");
				printf("\t |         1. Search for Venues                    2. Display All Venues           |\n");
				printf("\t |         3. Modify Venues                        4. Set availability             |\n");
				printf("\t |         5. Check availability                   6. Add Venues                   |\n");
				printf("\t |         7. Delete Venue                         8. Exit Programme               |\n");
				printf("\t |                                                                                 |\n");
				printf("\t  --------------------------------------------------------------------------------- \n");
				break;
			case 8:
				printf("\t Bye Bye!\n\n");
			}
		}
	} while (choice != 8);
}

//Write info into text file//
void writeVenInfo() {
	FILE* fptr;
	fptr = fopen("Venue.txt", "w");
	if (fptr == NULL)
	{
		printf("\t Unable to open the file\n");
		exit(-1);
	}
	int n = 0;
	

	for (n = 0; n < venInfoCount; n++) {
		fprintf(fptr, "%d|%d|%d|%d|%s|%d|%d|%d|%s|%s\n",
			ven[n].openHours,
			ven[n].openMin,
			ven[n].closeHours,
			ven[n].closeMin,
			ven[n].nameVen,
			ven[n].currentCap,
			ven[n].maxCap,
			ven[n].venAvail,
			ven[n].category,
			ven[n].incharge);
	}
	fclose(fptr);
}

//Read info from text file//
void readVenInfo() {
	FILE* fptr;
	fptr = fopen("Venue.txt", "r");
	if (fptr == NULL)
	{
		printf("\t Unable to open the file\n");
		exit(-1);
	}
	while (fscanf(fptr, "%d|%d|%d|%d|%[^|]|%d|%d|%d|%[^|]|%[^\n]\n",
		&ven[venInfoCount].openHours,
		&ven[venInfoCount].openMin,
		&ven[venInfoCount].closeHours,
		&ven[venInfoCount].closeMin,
		ven[venInfoCount].nameVen,
		&ven[venInfoCount].currentCap,
		&ven[venInfoCount].maxCap,
		&ven[venInfoCount].venAvail,
		ven[venInfoCount].category,
		ven[venInfoCount].incharge) != EOF) 
	{
		venInfoCount++;
	}

}

//Search function for venue//
void searchVenInfo() {
	char name[30];
	printf("\t Please enter venue name: ");
	scanf("%[^\n]", name);
	rewind(stdin);

	printf("\n\t +----------+-------------------+------------+-------------+-------------+-------------+--------------------+-------------------------------+----------------------+\n");
	printf("\t |  Index   |       Venue       |    Open    |    Close    |   Current   |   Maximum   |       Venue        |       Person In Charge        |       Category       |\n");
	printf("\t |          |                   |    Time    |    Time     |     Pax     |     Pax     |    Availability    |                               |                      |\n");
	printf("\t +----------+-------------------+------------+-------------+-------------+-------------+--------------------+-------------------------------+----------------------+\n");
	int n = 0;
	for (n = 0; n < venInfoCount; n++) {
		if (strstr(lowerString(ven[n].nameVen), lowerString(name)) != 0) {
			if (ven[n].venAvail == 0) {
				printf("\t |  %03d     | %-17s |    %02d:%02d   |    %02d:%02d    |     %03d     |     %03d     | Not Available      | %-29s | %-20s |\n",
					n + 1,
					upperString(ven[n].nameVen),
					ven[n].openHours,
					ven[n].openMin,
					ven[n].closeHours,
					ven[n].closeMin,
					ven[n].currentCap,
					ven[n].maxCap,
					ven[n].incharge,
					ven[n].category);
			}
			else {
				printf("\t |  %03d     | %-17s |    %02d:%02d   |    %02d:%02d    |     %03d     |     %03d     | Available          | %-29s | %-20s |\n",
					n + 1,
					upperString(ven[n].nameVen),
					ven[n].openHours,
					ven[n].openMin,
					ven[n].closeHours,
					ven[n].closeMin,
					ven[n].currentCap,
					ven[n].maxCap,
					ven[n].incharge,
					ven[n].category);
			}
		}
	}

	printf("\t +----------+-------------------+------------+-------------+-------------+-------------+--------------------+-------------------------------+----------------------+\n");
}

//Display info from text file//
int displayVenInfo() {
	int i;
	printf("\n\t +----------+-------------------+------------+-------------+-------------+-------------+--------------------+-------------------------------+----------------------+\n");
	printf("\t |  Index   |       Venue       |    Open    |    Close    |   Current   |   Maximum   |       Venue        |       Person In Charge        |       Category       |\n");
	printf("\t |          |                   |    Time    |    Time     |     Pax     |     Pax     |    Availability    |                               |                      |\n");
	printf("\t +----------+-------------------+------------+-------------+-------------+-------------+--------------------+-------------------------------+----------------------+\n");
	for (i = 0; i < venInfoCount; i++) {


		if (ven[i].venAvail == 0) {
			printf("\t |  %03d     | %-17s |    %02d:%02d   |    %02d:%02d    |     %03d     |     %03d     | Not Available      | %-29s | %-20s |\n",
				i + 1,
				upperString(ven[i].nameVen),
				ven[i].openHours,
				ven[i].openMin,
				ven[i].closeHours,
				ven[i].closeMin,
				ven[i].currentCap,
				ven[i].maxCap,
				ven[i].incharge,
				ven[i].category);
		}
		else {
			printf("\t |  %03d     | %-17s |    %02d:%02d   |    %02d:%02d    |     %03d     |     %03d     | Available          | %-29s | %-20s |\n",
				i + 1,
				upperString(ven[i].nameVen),
				ven[i].openHours,
				ven[i].openMin,
				ven[i].closeHours,
				ven[i].closeMin,
				ven[i].currentCap,
				ven[i].maxCap,
				ven[i].incharge,
				ven[i].category);
		}


		printf("\t +----------+-------------------+------------+-------------+-------------+-------------+--------------------+-------------------------------+----------------------+\n");

	}
	return i;
}

//Get Venue name that is cuurently visited by the user//
int getVenName(char name[]) {
	int upperLimit = displayVenInfo();
	int index;
	do {
		printf("\t Please select the venue you currently visiting (Index) > ");
		scanf("%d", &index);
		rewind(stdin);
		if (index < 1 || index > upperLimit) {
			printf("\t Invalid Choice, Please try again.\n");
		}
		
	} while (index < 1 || index > upperLimit);
	strcpy(name, ven[index-1].nameVen);
	DateTime currentTime = getCurrentDateTime();
	if (ven[index - 1].venAvail == 0) {
		return -1;
	}
	else if (ven[index - 1].currentCap >= ven[index - 1].maxCap) {
		return -2;
	}
	else if (currentTime.hour > ven[index - 1].closeHours) {
		return -3;
	}
	else if (currentTime.hour == ven[index - 1].closeHours) {
		if (currentTime.min >= ven[index - 1].closeMin) {
			return -3;
		}
	}
}

void delVenInfo() {
	int row;
	int upperLimit = displayVenInfo();
	int indexNumber;
	do {

		printf("\n\t Which venue you want to delete? (Specify index or -1 to leave) > ");
		scanf("%d", &row);
		rewind(stdin);
		if (row == -1) {
			break;
		}else if (row > upperLimit || row < 0) {
			printf("\n\t Invalid venue! Please specify the index accordingly! ");
		}
	} while (row > upperLimit || row < 0);//Change number back one number//
	row--;
	for (int i = row; i < venInfoCount - 1; i++) {
		ven[i] = ven[i + 1];
	}
	venInfoCount--;
	printf("\t Venue deleted.\n");
}

//Modify venue info//
void modVenInfo() {
	char name[30], newName[30], incharge[40], category[30];
	int oldName;
	int changeChoice;
	int row;
	int openingHr, openingMin, closingHr, closingMin;
	int maxVen, newMax;
	int upperLimit = displayVenInfo();
	int indexNumber;
	do {

		printf("\n\t Which venue you want to modify? (Specify index and -1 to leave) > ");
		scanf("%d", &row);
		rewind(stdin);
		if (row == -1) {
			return;
		}
		else if (row > upperLimit || row < 0) {
			printf("\n\t Invalid venue! Please specify the index accordingly! ");
		}
	} while (row > upperLimit || row < 0);
	row--;
	do {
		printf("\n\n\t ....................  M O D I F Y     V E N U E     P A G E  ..................... \n\n");
		printf("\t  --------------------------------------------------------------------------------- \n");
		printf("\t |                                                                                 |\n");
		printf("\t |                              CHANGE VENUE OPTIONS                               |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |             1. Venue Name                         2. Operating Hours            |\n");
		printf("\t |             3. Maximum Capacity                   4. Person In Charge           |\n");
		printf("\t |             5. Category                           6. Exit                       |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  --------------------------------------------------------------------------------- \n");
		printf("\n\t Which data field you want to change > ");
		scanf("%d", &changeChoice);
		rewind(stdin);
		switch (changeChoice) {
		case 1:
			//Change venue's name//
			do {
				printf("\n\t Enter the new name of this venue: ");
				scanf("%[^\n]", newName);
				rewind(stdin);
			} while (isAlphaNumber(newName) == 0);
			strcpy(ven[row].nameVen, newName);
			printf("\n\t The venue name has been changed.\n");
			break;

		case 2:
			//Change opening hour of venue//
			do {
				
				printf("\n\t Opening hour of the venue(24-hr system): ");
				scanf("%d", &openingHr);
				rewind(stdin);
			} while (openingHr > 24 || openingHr < 0);

			//Change opening minute of venue//
			do {
				printf("\t Opening minutes of the venue: ");
				scanf("%d", &openingMin);
				rewind(stdin);
			} while (openingMin > 60 || openingMin < 0);

			//Change closing hour of venue//
			do {
				printf("\t Closing hour of the venue(24-hr system): ");
				scanf("%d", &closingHr);
				rewind(stdin);
			} while (closingHr > 24 || closingHr < 0);

			//Change closing minute of venue//
			do {
				printf("\t Closing minutes of the venue: ");
				scanf("%d", &closingMin);
				rewind(stdin);
			} while (closingMin > 60 || closingMin < 0);

			printf("\n\t Operating hours of this venue has been changed.\n");
			ven[row].openHours = openingHr;
			ven[row].openMin = openingMin;
			ven[row].closeHours = closingHr;
			ven[row].closeMin = closingMin;
			break;
		case 3:
			//Change max capacity of a venue//
			do {
				
				printf("\n\t Enter the new max capacity: ");
				scanf("%d", &newMax);
				rewind(stdin);
			} while (newMax < 0 || newMax > 200);
			ven[row].maxCap = newMax;

			printf("\t Max capacity of this venue has been changed.\n");

			break;
		case 4:
			do {
				printf("\t Person In Charge of the venue: ");
				scanf("%[^\n]", incharge);
				rewind(stdin);
				if (isAlphaNumber(incharge) != 0) {
					strcpy(ven[row].incharge, incharge);
				}
			} while (isAlphaNumber(incharge) == 0);

			printf("The person in charge of the venue has been changed.");
			break;

		case 5:
			do {
				printf("\t Category of the venue: ");
				scanf("%[^\n]", category);
				rewind(stdin);
				if (isAlphaNumber(incharge) != 0) {
					strcpy(ven[row].category, category);
				}
			} while (isAlphaNumber(category) == 0);
			printf("The category of this venue has been changed.");
			break;
		case 6:
			printf("\t Done! \n");
			break;
		default:
			printf("\t Invalid choice! Please try again!\n");

		}
	} while (changeChoice != 6);
}

//Set venue availability//
void setVenueAvail(char* name) {
	int availChoice, availStatus;
	int row = -1;
	for (int i = 0; i < venInfoCount; i++) {
		char lowercase[30];
		strcpy(lowercase, ven[i].nameVen);
		if (strcmp(lowerString(lowercase), lowerString(name)) == 0) { // if match found
			row = i;
		}
	}
	if (ven[row].venAvail == 0) { // set to available
		ven[row].venAvail = 1;
	}
	else {
		ven[row].venAvail = 0; // set to unavailable
	}
}

//Set venue availability//
void setVenAvail() {
	int availChoice, availStatus;
	int upperlimit = displayVenInfo();
	char name[30];
	int row;
	do {
		printf("\n\t Which venue you want to change availability? (Specify index) > ");
		scanf("%d", &row);
		rewind(stdin);
		if (row > upperlimit || row < 1) {
			printf("\n\t Invalid venue, please specific its index!");
		}
	} while (row > upperlimit || row < 1);
	row--;
	if (ven[row].venAvail == 0) {
		ven[row].venAvail = 1;
		printf("\t %s is now available!\n", ven[row].nameVen);
	}
	else {
		ven[row].venAvail = 0;
		printf("\t %s is now not available!\n", ven[row].nameVen);
	}

	printf("\t The status of this venue has been changed. Have a great day.\n");
}

//Check venue availability//
void checkVenAvail() {
	char name[30];
	int row = -1;
	do {
		printf("Which venue you want to check availability? (Specify name) > ");
		scanf("%[^\n]", name);
		rewind(stdin);
		for (int i = 0; i < venInfoCount; i++) {
			char lowercase[30];
			strcpy(lowercase, ven[i].nameVen);
			if (strcmp(lowerString(lowercase), lowerString(name)) == 0) {
				row = i;
			}
		}
		if (row == -1) {
			printf("Name not found, please try again! \n");
		}
	} while (row == -1);
	if (ven[row].venAvail == 0) {
		printf("This venue is not available at the moment.\n");
	}
	else if (ven[row].venAvail == 1) {
		printf("This venue is available.\n");
	};
}

//Add new venue//
void addVenue() {
	char newVenName[50], choice, incharge[40], category[30];
	int newVenHr, newVenMin, newCloseHr, newCloseMin, newMaxCap;

	do {
		//Read User Input
		
		printf("\n\n\t ....................  N E W     V E N U E     R E C O R D S  ..................... \n");
		int flag = 0;
		do {
			printf("\n\t Venue Name: ");
			scanf("%49[^\n]", newVenName);
			rewind(stdin);
			if (isAlphaNumber(newVenName) == 0) {
				printf("\t Venue name cannot any special character and spacing!\n\n");
			}
			for (int i = 0; i < venInfoCount; i++) {
				if (strcmp(ven[i].nameVen, newVenName) == 0) {
					printf("\t Venue exist, please try another name!\n\n");
					flag = 1;
					break;
				}
			}
		} while (isAlphaNumber(newVenName) == 0 || flag == 1);

		do {
			printf("\t Opening Hour of the venue: ");
			scanf("%d", &newVenHr);
			rewind(stdin);
		} while (newVenHr > 24 || newVenHr < 0);

		do {
			printf("\t Opening min of the venue: ");
			scanf("%d", &newVenMin);
			rewind(stdin);
		} while (newVenMin > 60 || newVenMin < 0);

		do {
			printf("\t Closing hour of the venue: ");
			scanf("%d", &newCloseHr);
			rewind(stdin);
		} while (newCloseHr > 24 || newCloseHr < 0);

		do {
			printf("\t Closing Min of the venue: ");
			scanf("%d", &newCloseMin);
			rewind(stdin);
		} while (newCloseMin > 60 || newCloseMin < 0);

		do {
			printf("\t Max Capacity of the venue: ");
			scanf("%d", &newMaxCap);
			rewind(stdin);
		} while (newMaxCap < 0 || newMaxCap > 200);

		do {
			printf("\t Person In Charge of the venue: ");
			scanf("%[^\n]", incharge);
			rewind(stdin);
		} while (isAlphaNumber(incharge) == 0);

		do {
			printf("\t Category of the venue: ");
			scanf("%[^\n]", category);
			rewind(stdin);
		} while (isAlphaNumber(category) == 0);

		//Write user input into admin array.
		strcpy(ven[venInfoCount].nameVen, newVenName);
		ven[venInfoCount].openHours = newVenHr;
		ven[venInfoCount].openMin = newVenMin;
		ven[venInfoCount].closeHours = newCloseHr;
		ven[venInfoCount].closeMin = newCloseMin;
		ven[venInfoCount].maxCap = newMaxCap;
		ven[venInfoCount].currentCap = 0;
		strcpy(ven[venInfoCount].incharge, incharge);
		strcpy(ven[venInfoCount].category, category);

		venInfoCount++;
		printf("\t Venue added.\n");
		printf("\t Do you want to add another?(Y|N): ");
		scanf("%c", &choice);
		rewind(stdin);
	} while (choice == 'Y' || choice == 'y');
}