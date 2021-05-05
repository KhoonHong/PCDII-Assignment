// Maximum number of records
#define RECORDS 100

// Maximum amount of users
#define USERS 50

/*=================*/
/* Global Variable */
/*=================*/
int sanitizeRecordCount = 0; // Declare to store struct array record total count
int sanitizeUserCount = 0;
int currentUserCount; // Current user row count in user

/*====================*/
/* Sanitize Structure */
/*====================*/

// Sanitize Records
// 1. start Time, end Time - (hour, minute)
// 2. daymonthyear - (day, month, year)
// 3. venue
// 4. email - act as primary key
// 5. record id

typedef struct
{
	int hour, minute;
}Time;

typedef struct
{
	int day, month, year;
}Date;

typedef struct
{
	Time startTime, endTime;
	Date dayMonthYear;
	char venue[20], email[40];
	int id;
}Sanitize;

// Sanitize Users
// 1. location - ( city, state, country, street, zipcode)
// 2. company name
// 3. person-in-charge
// 4. email 
// 5. registeration no.
// 6. phone no.
// 7. fax
// 8. password
// 9. user id

typedef struct
{
	int zipCode;
	char city[30], state[30], country[30], street[40];
}Address;

typedef struct
{
	Address location;
	char name[20], inCharge[20], email[40], registerNo[20], phoneNo[15], fax[15], password[20];
}Company_info;

typedef struct
{
	Company_info info;
	int id;
}User;

/*====================*/
/* Structure Variable */
/*====================*/
Sanitize sanitizeRecords[RECORDS]; // User records

User sanitizeUsers[USERS]; // User info

/*======================*/
/* (function) Read File */
/*======================*/
void sanitizeRead()
{
	// Opens the file "SanitizeRecords.txt" and "SanitizeUsers.txt"
	FILE* fptr, * fptr1;
	fptr = fopen("SanitizeRecords.txt", "r");
	fptr1 = fopen("SanitizeUsers.txt", "r");

	// Print error if the file can't be opened
	if (fptr == NULL || fptr1 == NULL)
	{
		printf("\tUnable to open file\n");
		exit(-1);
	}

	// Read from file "SanitizeRecords.txt" to array
	// Check if file have reached EOF(end of file)
	while (fscanf(fptr, "%d|%d|%d|%d|%d|%d|%d|%d|%[^|]|%s\n",
		&sanitizeRecords[sanitizeRecordCount].id, //int
		&sanitizeRecords[sanitizeRecordCount].startTime.hour, //int
		&sanitizeRecords[sanitizeRecordCount].startTime.minute, //int
		&sanitizeRecords[sanitizeRecordCount].endTime.hour, //int
		&sanitizeRecords[sanitizeRecordCount].endTime.minute, //int
		&sanitizeRecords[sanitizeRecordCount].dayMonthYear.day, //int
		&sanitizeRecords[sanitizeRecordCount].dayMonthYear.month, //int
		&sanitizeRecords[sanitizeRecordCount].dayMonthYear.year, //int
		&sanitizeRecords[sanitizeRecordCount].venue, //char
		&sanitizeRecords[sanitizeRecordCount].email) != EOF) //char
	{
		// Increment variable "sanitizeRecordCount" by one
		sanitizeRecordCount++;
	}

	// Read from file "SanitizeUsers.txt" to array
	// Check if file have reached EOF(end of file)
	while (fscanf(fptr1, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%s\n",
		&sanitizeUsers[sanitizeUserCount].id, //int
		&sanitizeUsers[sanitizeUserCount].info.phoneNo, //char
		&sanitizeUsers[sanitizeUserCount].info.fax, //char
		&sanitizeUsers[sanitizeUserCount].info.name, //char
		&sanitizeUsers[sanitizeUserCount].info.inCharge, //char
		&sanitizeUsers[sanitizeUserCount].info.email, //char
		&sanitizeUsers[sanitizeUserCount].info.registerNo, //char
		&sanitizeUsers[sanitizeUserCount].info.location.city, //char
		&sanitizeUsers[sanitizeUserCount].info.location.state, //char
		&sanitizeUsers[sanitizeUserCount].info.location.country, //char
		&sanitizeUsers[sanitizeUserCount].info.location.street, //char
		&sanitizeUsers[sanitizeUserCount].info.location.zipCode, //int
		&sanitizeUsers[sanitizeUserCount].info.password) != EOF) //char
	{
		// Increment variable "sanitizeUserCount" by one
		sanitizeUserCount++;
	}
	// Closes the file "SanitizeRecords.txt" and "SanitizeUsers.txt"
	fclose(fptr);
	fclose(fptr1);
}

/*==========================*/
/* (function) Delete Record */
/*==========================*/
void sanitizeRecordDelete()
{
	int idInput; // Declare "idInput" to store user input

	sanitizeAdminDisplay(); // Call function to display sanitize record in table form

	do
	{
		printf("\n\t Please enter the sanitization record ID to delete: ");
		scanf("%d", &idInput);
		rewind(stdin);


		for (int x = 0; x < sanitizeRecordCount; x++) // Iterate through struct array "sanitizeRecords"
		{
			// Compare user input with struct array "sanitizeRecords"
			if (idInput == sanitizeRecords[x].id)
			{
				// Iterate from found ID to end of array of struct array "sanitizeRecords"
				for (int y = x; y < sanitizeRecordCount - 1; y++)
				{
					sanitizeRecords[y] = sanitizeRecords[y + 1]; // Fill up deleted space in array
					sanitizeRecords[y].id = y + 1; // Add 1 to each iteration of struct array variable "id"
				}

				sanitizeRecordCount--;

				sanitizeAdminDisplay();

				printf("\n\t The following record has been successfully deleted\n\n");
				return;
			}
			else // If 
			{
				continue; // Skip current iteration of the loop & continue next iteration
			}
		}
		printf("\n\t Can't find the specified sanitization record ID in record...\n\t Please enter the sanitization record ID correctly!");

	} while (1); // Declared for validation purpose
}

/*==========================*/
/* (function) Delete User   */
/*==========================*/
void sanitizeUserDelete()
{
	char email[40] = "", confirmation[10];
	int flag = 0;
	sanitizeAdminAccDisplay();

	do
	{
		printf("\n\t Please enter the user E-mail to delete: ");
		scanf("%35s", &email);
		rewind(stdin);

		printf("\n\t Warning! All records related to this account will be removed too!\n\n\t Please type 'yes' to proceed > "); // prompt comfirmation
		scanf("%10s", &confirmation);

		if (!(strcmp(lowerString(confirmation), "yes") == 0)) // check user input for confirmation
		{
			continue;
		}

		for (int x = 0; x < sanitizeUserCount; x++) // Iterate through struct array "sanitizeUsers"
		{
			// Compare user input with struct array "sanitizeUsers" (email)
			if (strcmp(sanitizeUsers[x].info.email, email) == 0)
			{
				// Iterate from found ID to end of array of struct array "sanitizeUsers"
				for (int y = x; y < sanitizeUserCount - 1; y++)
				{
					sanitizeUsers[y] = sanitizeUsers[y + 1]; // Fill up deleted space in array
					sanitizeUsers[y].id = y + 1; // Add 1 to each iteration of struct array variable "id"
				}

				sanitizeUserCount--;
				flag = 1; // indicate remove success in users
				break;
			}
		}

		int limiter = sanitizeRecordCount; // place static variable for for loop limiter 

		for (int x = 0; x < limiter; x++)
		{
			// Compare user input with struct array "sanitizeUsers" (email)
			if (strcmp(sanitizeRecords[x].email, email) == 0)
			{
				// Iterate from found ID to end of array of struct array "sanitizeRecords"
				for (int y = x; y < sanitizeRecordCount - 1; y++)
				{
					sanitizeRecords[y] = sanitizeRecords[y + 1]; // Fill up deleted space in array
					sanitizeRecords[y].id = y + 1; // Add 1 to each iteration of struct array variable "id"
				}

				sanitizeRecordCount--;

				flag = 1; // indicate remove success in records
			}
		}

		if (flag == 1) // if user is successfully deleted
		{
			sanitizeAdminAccDisplay();

			printf("\n\t The following user has been successfully deleted\n\n");
			return;
		}

		printf("\n\t Can't find any match of email in record...\n\t Please enter the user's email correctly!\n");

	} while (1); // Declared for validation purpose
}


/*=======================*/
/* (function) Write File */
/*=======================*/
void sanitizeWrite()
{
	// Opens the file "SanitizeRecords.txt" and "SanitizeUsers.txt"
	FILE* fptr, * fptr1;
	fptr = fopen("SanitizeRecords.txt", "w");
	fptr1 = fopen("SanitizeUsers.txt", "w");

	// Print error if the file can't be opened
	if (fptr == NULL || fptr1 == NULL)
	{
		printf("\t\nUnable to open file...\n");
		exit(-1);
	}

	// Write from array to file "SanitizeRecords.txt"
	for (int x = 0; x < sanitizeRecordCount; x++)
	{
		fprintf(fptr, "%d|%d|%d|%d|%d|%d|%d|%d|%s|%s\n",
			sanitizeRecords[x].id, //int
			sanitizeRecords[x].startTime.hour, //int
			sanitizeRecords[x].startTime.minute, //int
			sanitizeRecords[x].endTime.hour, //int
			sanitizeRecords[x].endTime.minute, //int
			sanitizeRecords[x].dayMonthYear.day, //int
			sanitizeRecords[x].dayMonthYear.month, //int
			sanitizeRecords[x].dayMonthYear.year, //int
			sanitizeRecords[x].venue, //char
			sanitizeRecords[x].email); //char
	}

	// Write from array to file "SanitizeUser.txt"
	for (int x = 0; x < sanitizeUserCount; x++)
	{
		fprintf(fptr1, "%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%d|%s\n",
			sanitizeUsers[x].id, //int
			sanitizeUsers[x].info.phoneNo, //char
			sanitizeUsers[x].info.fax, //char
			sanitizeUsers[x].info.name, //char
			sanitizeUsers[x].info.inCharge, //char
			sanitizeUsers[x].info.email, //char
			sanitizeUsers[x].info.registerNo, //char
			sanitizeUsers[x].info.location.city, //char
			sanitizeUsers[x].info.location.state, //char
			sanitizeUsers[x].info.location.country, //char
			sanitizeUsers[x].info.location.street, //char
			sanitizeUsers[x].info.location.zipCode, //int
			sanitizeUsers[x].info.password); //char
	}

	// Closes the file "SanitizeRecords.txt" and "sanitizeUsers.txt"
	fclose(fptr);
	fclose(fptr1);
}

/*=====================================*/
/* (function) Sanitization Filter Menu */
/*=====================================*/
void sanitizeFilterMenu()
{
	printf("\n\n\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                            SANITIZATION FILTER MENU                             |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |             1. Venue                              2. Date                       |\n");
	printf("\t |             3. Start Time                         4. End Time                   |\n");
	printf("\t |             5. Phone Number                       6. Fax                        |\n");
	printf("\t |             7. Company Name                       8. Person-In-Charge           |\n");
	printf("\t |             9. E-mail                             10. Registeration No.         |\n");
	printf("\t |             11. Address                           12. Confirm Selection         |\n");
	printf("\t |             13. Exit                                                            |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
}


/*======================================================*/
/* (function) Table Line Formatting for filter function */
/*======================================================*/
void sanitizeRowLine(int casesCount, int arr[])
{
	printf("\n\t +");
	printf("----"); // ID

	// Prints in straight line
	for (int x = 0; x < casesCount; x++)
	{
		switch (arr[x])
		{
		case 1:
			printf("+----------------"); // Venue
			break;
		case 2:
			printf("+------------"); // Date
			break;
		case 3:
			printf("+------------"); // Start Time
			break;
		case 4:
			printf("+----------"); // End Time
			break;
		case 5:
			printf("+--------------"); // Phone No
			break;
		case 6:
			printf("+-----------"); // Fax
			break;
		case 7:
			printf("+-----------------"); // Company Name
			break;
		case 8:
			printf("+------------------"); // Person-in-charge
			break;
		case 9:
			printf("+----------------------------------"); // E-mail
			break;
		case 10:
			printf("+----------"); // Registeration No.
			break;
		case 11:
			printf("+----------------------------------"); // Address
		}
	}
	printf("+\n");
}

/*=====================================*/
/* (function) Sanitization Data filter */
/*=====================================*/
// The filter function filter sanitization data based on users selection into table with selected headers.
// (eg. Date, Venue and Fax only)
void sanitizeFilter()
{
	int filterMenuStore[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // Store menu selection into array

	// "filterMenu" store scanned menu input from user
	// "flag" to check whether condition is passed or not
	// "casesCount" store length of "filterMenuStore"
	int filterMenu, flag = 0, casesCount = 0;

	sanitizeFilterMenu();
	do
	{
		printf("\n\t Please enter any value \n\t(You can select more than one criteria) > ");
		scanf("%d", &filterMenu);
		rewind(stdin);

		switch (filterMenu)
		{
		case 1: // If menu selection is 1,2,3,4,5,6,10,11,12,13,14
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
			// Loop through all the values in the array "casesCount"
			for (int x = 0; x < casesCount; x++)
			{
				// Check if the value passed into "filterMenu" is already in the array "filterMenuStore"
				if (filterMenu == filterMenuStore[x])
				{
					printf("\n\t This parameter have already been selected!\n\n\t Please key in another appopriate number...\n");
					// Assign 1 to flag as to indicate this if condition have been passed successfully
					flag = 1;
					break;
				}
			}

			if (flag == 1) // If input is rejected
			{
				flag = 0;
				continue;
			}

			// Store user's menu input into array
			filterMenuStore[casesCount] = filterMenu;
			printf("\n\t Parameter Added...\n");

			casesCount++;

			// If all cases have been selected
			if (casesCount == 11)
			{
				flag = 1;
			}

			break;
		case 12:
			if (casesCount == 0) // Check if any condition have been selected
			{
				printf("\n\t No filter condition selected...\n");
				continue;
			}
			flag = 1; // break out of while loop
			break;
		case 13: // Exit function
			return;
		default:
			printf("\n\t Invalid Selection...");
		}
	} while (flag == 0);

	printf("\n\n"); // Formatting

	int printCount = 0;
	for (int i = 0; i < casesCount; i++) // calculate space needed for title alignment
	{
		switch (filterMenuStore[i])
		{
		case 1: printCount += 18; break; // spacing count
		case 2: printCount += 14; break;
		case 3: printCount += 14; break;
		case 4: printCount += 12; break;
		case 5: printCount += 16; break;
		case 6: printCount += 13; break;
		case 7: printCount += 19; break;
		case 8: printCount += 20; break;
		case 9: printCount += 35; break;
		case 10: printCount += 13; break;
		case 11: printCount += 32; break;
		}
	}

	for (int i = 0; i < printCount / 2; i++) // title align with the table
	{
		printf(" ");
	}

	printf("\t Sanitization Filter\n");

	// Prints out table formating and column heads
	sanitizeRowLine(casesCount, filterMenuStore);

	printf("\t | ID ");

	// Print out heading of the table
	for (int x = 0; x < casesCount; x++)
	{
		switch (filterMenuStore[x])
		{
		case 1:
			printf("|     Venue      ");
			break;
		case 2:
			printf("|    Date    ");
			break;
		case 3:
			printf("| Start Time ");
			break;
		case 4:
			printf("| End Time ");
			break;
		case 5:
			printf("|   Phone No.  ");
			break;
		case 6:
			printf("|    Fax    ");
			break;
		case 7:
			printf("|  Company Name   ");
			break;
		case 8:
			printf("| Person-in-charge ");
			break;
		case 9:
			printf("|               E-mail             ");
			break;
		case 10:
			printf("| Reg No.  ");
			break;
		case 11:
			printf("|             Address              ");
			break;
		}
	}
	printf("|");

	char address[80]; // Store compiled variable(street, zipcode, city, state, country)

	// Prints out every row of data
	for (int rows = 0; rows < sanitizeRecordCount; rows++)
	{
		// Formatting for data table
		sanitizeRowLine(casesCount, filterMenuStore);

		printf("\t | %2d ", sanitizeRecords[rows].id);

		// Printing out data depending on user choices
		for (int x = 0; x < casesCount; x++)
		{
			switch (filterMenuStore[x]) // use array values as parameter of switch case
			{
			case 1:
				// Venue
				if (!(strcmp(sanitizeRecords[rows].venue, "-1") == 0)) // if current record is not an empty record (-1 is empty record)
				{
					printf("| %-14s ", sanitizeRecords[rows].venue); 
				}
				else
				{
					printf("|       -      "); // prints out - to indicate empty record
				}

				break;
			case 2:
				// Date
				if (sanitizeRecords[rows].dayMonthYear.day != -1 ||
					sanitizeRecords[rows].dayMonthYear.month != -1 ||
					sanitizeRecords[rows].dayMonthYear.year != -1) // if neither day,month or year is empty record
				{
					printf("| %-2d/%2d/%-4d ",
						sanitizeRecords[rows].dayMonthYear.day,
						sanitizeRecords[rows].dayMonthYear.month,
						sanitizeRecords[rows].dayMonthYear.year);
				}
				else
				{
					printf("|      -     ");
				}

				break;
			case 3:
				// Start Time
				if (sanitizeRecords[rows].startTime.hour != -1 || sanitizeRecords[rows].startTime.minute != -1) // if start time hour or minute is not empty record
				{
					printf("|    %02d:%02d   ",
						sanitizeRecords[rows].startTime.hour,
						sanitizeRecords[rows].startTime.minute);
				}
				else
				{
					printf("|     -      ");
				}

				break;
			case 4:
				// End Time
				if (sanitizeRecords[rows].endTime.hour != -1 || sanitizeRecords[rows].endTime.minute != -1) // if end time hour or minute is not empty record
				{
					printf("|   %02d:%02d  ",
						sanitizeRecords[rows].endTime.hour,
						sanitizeRecords[rows].endTime.minute);
				}
				else
				{
					printf("|     -    ");
				}

				break;
			case 5:
				// Phone No
				for (int i = 0; i < sanitizeUserCount; i++)
				{
					if (strcmp(sanitizeUsers[i].info.email, sanitizeRecords[rows].email) == 0) // if found matches of same email from user accounts and records
					{
						printf("| %-12s ", sanitizeUsers[i].info.phoneNo);
						break;
					}
				}

				break;
			case 6:
				// Fax
				for (int i = 0; i < sanitizeUserCount; i++)
				{
					if (strcmp(sanitizeUsers[i].info.email, sanitizeRecords[rows].email) == 0)
					{
						printf("| %-9s ", sanitizeUsers[i].info.fax);
						break;
					}
				}
				break;
			case 7:
				// Company Name
				for (int i = 0; i < sanitizeUserCount; i++)
				{
					if (strcmp(sanitizeUsers[i].info.email, sanitizeRecords[rows].email) == 0)
					{
						printf("| %-15s ", sanitizeUsers[i].info.name);
						break;
					}
				}
				break;
			case 8:
				// Person-in-charge
				for (int i = 0; i < sanitizeUserCount; i++)
				{
					if (strcmp(sanitizeUsers[i].info.email, sanitizeRecords[rows].email) == 0)
					{
						printf("| %-16s ", sanitizeUsers[i].info.inCharge);
						break;
					}
				}
				break;
			case 9:
				// E-mail
				for (int i = 0; i < sanitizeUserCount; i++)
				{
					if (strcmp(sanitizeUsers[i].info.email, sanitizeRecords[rows].email) == 0)
					{
						printf("| %-32s ", sanitizeUsers[i].info.email);
						break;
					}
				}
				break;
			case 10:
				//Registeration No.
				for (int i = 0; i < sanitizeUserCount; i++)
				{
					if (strcmp(sanitizeUsers[i].info.email, sanitizeRecords[rows].email) == 0)
					{
						printf("| %-8s ", sanitizeUsers[i].info.registerNo);
						break;
					}
				}
				break;
			case 11:
				// Address
				for (int i = 0; i < sanitizeUserCount; i++)
				{
					if (strcmp(sanitizeUsers[i].info.email, sanitizeRecords[rows].email) == 0)
					{
						sprintf(address, "%-5d %-10s, %-12s",
							sanitizeUsers[i].info.location.zipCode,
							sanitizeUsers[i].info.location.city,
							sanitizeUsers[i].info.location.state); // prints zipcode, city and state into buffer named 'address'
						printf("| %-32s ", address); 
						break;
					}
				}
			}
		}
		printf("|"); // Formatting

		if (rows != sanitizeRecordCount - 1) // Check if 
		{
			printf("\n\t |    ");
			for (int i = 0; i < casesCount; i++) // Alignment formating for filter table
			{
				switch (filterMenuStore[i])
				{
				case 1: printf("|                "); break;
				case 2: printf("|            "); break;
				case 3: printf("|            "); break;
				case 4: printf("|          "); break;
				case 5: printf("|              "); break;
				case 6: printf("|           "); break;
				case 7: printf("|                 "); break;
				case 8: printf("|                  "); break;
				case 9: printf("|                                  "); break;
				case 10: printf("|          "); break;
				case 11: printf("|                                  "); break;
				}
			}
			printf("|");
		}
	}
	sanitizeRowLine(casesCount, filterMenuStore);
	printf("\n\n");
}

/*===============================*/
/* (function)Sanitization Search */
/*===============================*/
void sanitizeSearch()
{
	// 'menu' is to store scanned menu input from user
	// 'menueStore' is an array to store unique user selection
	int menu, menuStore[17] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	
	int casesCount = 0, flag = 0; // 'casesCount' is to store the number of times that the user has selected

	int printableID[RECORDS]; // to record which table header to print out after search

	int arrDate, upDate, lowDate;

	// assign all values in array to 0
	for (int i = 0; i < sanitizeRecordCount; i++)
	{
		printableID[i] = 0;
	}

	sanitizeSearchMenu();
	do
	{
		printf("\n\t Please enter any value \n\t(You can select more than one criteria) > ");
		scanf("%d", &menu);
		rewind(stdin);

		switch (menu)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
			// Loop through all the values in the array "casesCount"
			for (int x = 0; x < casesCount; x++)
			{
				// Check if the value passed into "menu" is already in the array "menuStore"
				if (menu == menuStore[x])
				{
					printf("\n\t This parameter have already been selected!\n\tPlease key in another appopriate number...");
					// Assign 1 to flag as to indicate this event
					flag = 1;
					break;
				}
			}

			if (flag == 1) // If input is rejected
			{
				flag = 0;
				continue;
			}

			// Store user's menu input into array
			menuStore[casesCount] = menu;
			printf("\n\t Parameter Added...\n");

			casesCount++;

			// If all cases have been selected
			if (casesCount == 16)
			{
				flag = 1;
			}
			break;
		case 18:
			return;
		case 17:
			if (casesCount == 0) // Check if any condition have been selected
			{
				printf("\n\t No condition selected...\n");
				continue;
			}
			flag = 1; // break out of while loop
			break;
		default:
			printf("\n\t Invalid Selection...");
		}
	} while (flag == 0);

	char venue[20] = "", phoneNo[15] = "", fax[15] = "", companyName[20] = "", inCharge[20] = "", regNo[20] = "", email[40] = ""; // temporary input storage for validation 
	char state[30] = "", city[30] = "", street[40] = "", country[30] = "";
	flag = 0;
	int upDay, upMonth, upYear, lowDay, lowMonth, lowYear, upID, lowID, upZipCode, lowZipCode;
	int upStartHr, upStartMin, lowStartHr, lowStartMin, upEndHr, upEndMin, lowEndHr, lowEndMin;

	int upStartTotal, lowStartTotal; // Store upper and lower range into total min (input)
	int startTotal; // Store array iteration into total min

	int upEndTotal, lowEndTotal; // Store upper and lower range into total min (input)
	int endTotal; // Store array iteration into total min

	for (int i = 0; i < casesCount; i++) // loop through user selection array
	{
		flag = 0;
		switch (menuStore[i])
		{
		case 1: // Venue
			do
			{
				printf("\n\t Venue Keyword > ");
				scanf("%18[^\n]", &venue);
				rewind(stdin);
				if (!(validVenueCompName(venue))) // validate venue name
				{
					printf("\n\t Please input any keyword...\n");
					flag = 1;
				}
			} while (flag == 1); // prompt user to re-enter if flag equals to 1

			for (int i = 0; i < sanitizeRecordCount; i++) // loop through records array
			{
				char lowercase[20];
				strcpy(lowercase, sanitizeRecords[i].venue); // copy venue name from records array to 'lowercase'
				if (strstr(lowerString(lowercase), lowerString(venue)) == 0) // if keyword entered by user matches the array records
				{
					printableID[i] = 1; // Place a marker to print that record from array
				}
			}
			break;
		case 2: // Date

			do
			{
				do
				{
					flag = 0;
					printf("\n\t Date (Upper Range) dd/mm/yyyy > ");
					scanf("%d/%d/%d", &upDay, &upMonth, &upYear);
					rewind(stdin);
					if (!(validDate(upDay, upMonth, upYear)))
					{
						printf("\n\t Date entered invalid...\n");
						flag = 1;
					}
				} while (flag == 1);

				do
				{
					flag = 0;
					printf("\n\t Date (Lower Range) dd/mm/yyyy > ");
					scanf("%d/%d/%d", &lowDay, &lowMonth, &lowYear);
					rewind(stdin);
					if (!(validDate(lowDay, lowMonth, lowYear)))
					{
						printf("\n\t Date entered invalid...\n");
						flag = 1;
					}
				} while (flag == 1);


				upDate = (upYear * 10000) + (upMonth * 100) + upDay; // calculation of inputted date into days for comparism
				lowDate = (lowYear * 10000) + (lowMonth * 100) + lowDay;

				if (lowDate > upDate) // if upper date is lower than lower date
				{
					printf("\n\t Invalid Upper/Lower Range Date...\n");
					flag = 1;
				}
			} while (flag == 1);

			for (int i = 0; i < sanitizeRecordCount; i++)
			{
				arrDate = (sanitizeRecords[i].dayMonthYear.year * 10000) +
					(sanitizeRecords[i].dayMonthYear.month * 100) +
					sanitizeRecords[i].dayMonthYear.day; // calculation of array records date into days for comparism

				if (upDate < arrDate || lowDate > arrDate) // if array records date is within the range of 'upDate' and 'lowDate'
				{
					printableID[i] = 1;
				}
			}

			break;
		case 3: // Phone No
			do
			{
				flag = 0;
				printf("\n\t Phone No > ");
				scanf("%14[^\n]", &phoneNo);
				rewind(stdin);

			} while (flag == 1);

			flag = 0;
			for (int x = 0; x < sanitizeUserCount; x++)
			{
				if (strstr(sanitizeUsers[x].info.phoneNo, phoneNo) == 0) // check fax
				{
					for (int i = 0; i < sanitizeRecordCount; i++)
					{
						if (strcmp(sanitizeUsers[x].info.email, sanitizeRecords[i].email) == 0)
						{
							printableID[i] = 1;
							flag = 1;
							break;
						}
					}
				}
				if (flag)
				{
					break;
				}
			}

			break;
		case 4: // Fax
			do
			{
				flag = 0;
				printf("\n\t Fax No > ");
				scanf("%14[^\n]", &fax);
				rewind(stdin);

			} while (flag == 1);

			flag = 0;
			for (int x = 0; x < sanitizeUserCount; x++)
			{
				if (strstr(sanitizeUsers[x].info.fax, fax) == 0) // check fax
				{
					for (int i = 0; i < sanitizeRecordCount; i++)
					{
						if (strcmp(sanitizeUsers[x].info.email, sanitizeRecords[i].email) == 0)
						{
							printableID[i] = 1;
							flag = 1;
							break;
						}
					}
				}
				if (flag)
				{
					break;
				}
			}

			break;
		case 5: // Company Name
			do
			{
				flag = 0;
				printf("\n\t Company Name Keyword > ");
				scanf("%18[^\n]", &companyName);
				rewind(stdin);
				if (!(validVenueCompName(companyName)))
				{
					printf("\n\t Please input any keyword...\n");
					flag = 1;
				}
			} while (flag == 1);

			flag = 0;
			for (int x = 0; x < sanitizeUserCount; x++)
			{
				char lowercase[20];
				strcpy(lowercase, sanitizeUsers[x].info.name);
				if (strstr(lowerString(lowercase), lowerString(companyName)) == 0) // check company
				{
					for (int i = 0; i < sanitizeRecordCount; i++)
					{
						if (strcmp(sanitizeUsers[x].info.email, sanitizeRecords[i].email) == 0)
						{
							printableID[i] = 1;
							flag = 1;
							break;
						}
					}
				}
				if (flag)
				{
					break;
				}
			}

			break;
		case 6: // Person-In-Charge
			do
			{
				flag = 0;
				printf("\n\t Person-In-Charge Keyword > ");
				scanf("%18[^\n]", &inCharge);
				rewind(stdin);
				if (!(validPersonInCharge(inCharge)))
				{
					printf("\n\t Name must be alphabetical...\n");
					flag = 1;
				}
			} while (flag == 1);

			flag = 0;
			for (int x = 0; x < sanitizeUserCount; x++)
			{
				char lowercase[20];
				strcpy(lowercase, sanitizeUsers[x].info.inCharge);
				if (strstr(lowerString(lowercase), lowerString(inCharge)) == 0) // check person in charge
				{
					for (int i = 0; i < sanitizeRecordCount; i++)
					{
						if (strcmp(sanitizeUsers[x].info.email, sanitizeRecords[i].email) == 0)
						{
							printableID[i] = 1;
							flag = 1;
							break;
						}
					}
				}
				if (flag)
				{
					break;
				}
			}

			break;
		case 7: // Start Time
			do
			{
				do
				{
					flag = 0;
					printf("\n\t Start Time in 24-hours format (Upper Range) xx:xx > ");
					scanf("%d:%d", &upStartHr, &upStartMin);
					rewind(stdin);
					if (!(validTimeHr(upStartHr) && validTimeMin(upStartMin))) // if either start time hour or minute is invalid 
					{
						printf("\n\t Invalid Time...\n");
						flag = 1;
					}
				} while (flag == 1);

				do
				{
					flag = 0;
					printf("\n\t Start Time in 24-hours format (Lower Range) xx:xx > ");
					scanf("%d:%d", &lowStartHr, &lowStartMin);
					rewind(stdin);
					if (!(validTimeHr(lowStartHr) && validTimeMin(lowStartMin)))
					{
						printf("\n\t Invalid Time...\n");
						flag = 1;
					}
				} while (flag == 1);

				upStartTotal = upStartHr * 60 + upStartMin; // calculate hours and minutes to only minutes
				lowStartTotal = lowStartHr * 60 + lowStartMin;

				if (upStartTotal < lowStartTotal) // if upper time is lower than lower time
				{
					printf("\n\t Invalid Upper/Lower Range Time...\n");
					flag = 1;
				}

			} while (flag == 1);

			for (int i = 0; i < sanitizeRecordCount; i++) // loop through records array
			{
				startTotal = sanitizeRecords[i].startTime.hour * 60 + sanitizeRecords[i].startTime.minute; // calculate hours and minutes to only minutes

				if (upStartTotal < startTotal || lowStartTotal > startTotal) // if record array time is within the range of upper time and lower time
				{
					printableID[i] = 1;
				}
			}
			break;
		case 8: // End Time
			do
			{
				do
				{
					flag = 0;
					printf("\n\t End Time (Upper Range) xx:xx > ");
					scanf("%d:%d", &upEndHr, &upEndMin);
					rewind(stdin);
					if (!(validTimeHr(upEndHr) && validTimeMin(upEndMin)))
					{
						printf("\n\t Invalid Time...\n");
						flag = 1;
					}
				} while (flag == 1);

				do
				{
					flag = 0;
					printf("\n\t End Time (Lower Range) xx:xx > ");
					scanf("%d:%d", &lowEndHr, &lowEndMin);
					rewind(stdin);
					if (!(validTimeHr(lowEndHr) && validTimeMin(lowEndMin)))
					{
						printf("\n\t Invalid Time...\n");
						flag = 1;
					}
				} while (flag == 1);

				upEndTotal = upEndHr * 60 + upEndMin;
				lowEndTotal = lowEndHr * 60 + lowEndMin;

				if (upEndTotal < lowEndTotal)
				{
					printf("\n\t Invalid Upper/Lower Range Time...\n");
					flag = 1;
				}

			} while (flag == 1);

			for (int i = 0; i < sanitizeRecordCount; i++)
			{
				endTotal = sanitizeRecords[i].endTime.hour * 60 + sanitizeRecords[i].endTime.minute;

				if (upEndTotal >= endTotal || lowEndTotal <= endTotal)
				{
					printableID[i] = 1;
				}
			}

			break;
		case 9: // E-mail
			do
			{
				flag = 0;
				printf("\n\t E-mail Keyword > ");
				scanf("%38[^\n]", &email);
				rewind(stdin);
				if (!(isNotEmpty(email)))
				{
					printf("\n\t Please input any keyword...\n");
					flag = 1;
				}
			} while (flag == 1);

			flag = 0;
			for (int x = 0; x < sanitizeUserCount; x++)
			{
				if (strstr(sanitizeRecords[x].email, email) == 0) // check within range
				{
					for (int i = 0; i < sanitizeRecordCount; i++)
					{
						if (strcmp(sanitizeUsers[x].info.email, sanitizeRecords[i].email) == 0)
						{
							printableID[i] = 1;
							flag = 1;
							break;
						}
					}
				}
				if (flag)
				{
					break;
				}
			}

			break;
		case 10: // Reg. No.
			do
			{
				flag = 0;
				printf("\n\t Registeration No. > ");
				scanf("%18[^\n]", &regNo);
				rewind(stdin);
				if (!(validRegNo(regNo)))
				{
					printf("\n\t Invalid Registeration No.\n");
					flag = 1;
				}
			} while (flag == 1);

			flag = 0;
			for (int x = 0; x < sanitizeUserCount; x++)
			{
				if (strstr(sanitizeUsers[x].info.registerNo, regNo) == 0) // check within range
				{
					for (int i = 0; i < sanitizeRecordCount; i++)
					{
						if (strcmp(sanitizeUsers[x].info.email, sanitizeRecords[i].email) == 0)
						{
							printableID[i] = 1;
							flag = 1;
							break;
						}
					}
				}
				if (flag)
				{
					break;
				}
			}

			break;
		case 11: // City
			do
			{
				flag = 0;
				printf("\n\t City Keyword > ");
				scanf("%18[^\n]", &city);
				rewind(stdin);
				if (!(validCity(city)))
				{
					printf("\n\t Invalid City...\n");
					flag = 1;
				}
			} while (flag == 1);

			flag = 0;
			for (int x = 0; x < sanitizeUserCount; x++)
			{
				char lowercase[30];
				strcpy(lowercase, sanitizeUsers[x].info.location.city);
				if (strstr(lowerString(lowercase), lowerString(city)) == 0) // check within range
				{
					for (int i = 0; i < sanitizeRecordCount; i++)
					{
						if (strcmp(sanitizeUsers[x].info.email, sanitizeRecords[i].email) == 0)
						{
							printableID[i] = 1;
							flag = 1;
							break;
						}
					}
				}
				if (flag)
				{
					break;
				}
			}

			break;
		case 12: // State
			do
			{
				flag = 0;
				printf("\n\t State Keyword > ");
				scanf("%18[^\n]", &state);
				rewind(stdin);
				if (!(validState(state)))
				{
					printf("\n\t Invalid State...\n");
					flag = 1;
				}
			} while (flag == 1);

			flag = 0;
			for (int x = 0; x < sanitizeUserCount; x++)
			{
				char lowercase[30];
				strcpy(lowercase, sanitizeUsers[x].info.location.state);
				if (strstr(lowerString(lowercase), lowerString(state)) == 0) // check within range
				{
					for (int i = 0; i < sanitizeRecordCount; i++)
					{
						if (strcmp(sanitizeUsers[x].info.email, sanitizeRecords[i].email) == 0)
						{
							printableID[i] = 1;
							flag = 1;
							break;
						}
					}
				}
				if (flag)
				{
					break;
				}
			}

			break;
		case 13: // Country
			do
			{
				flag = 0;
				printf("\n\t Country Keyword > ");
				scanf("%18[^\n]", &country);
				rewind(stdin);
				if (!(validCountry(country)))
				{
					printf("\n\t Invalid Country...\n");
					flag = 1;
				}
			} while (flag == 1);

			flag = 0;
			for (int x = 0; x < sanitizeUserCount; x++)
			{
				char lowercase[30];
				strcpy(lowercase, sanitizeUsers[x].info.location.country);
				if (strstr(lowerString(lowercase), lowerString(country)) == 0) // check within range
				{
					for (int i = 0; i < sanitizeRecordCount; i++)
					{
						if (strcmp(sanitizeUsers[x].info.email, sanitizeRecords[i].email) == 0)
						{
							printableID[i] = 1;
							flag = 1;
							break;
						}
					}
				}
				if (flag)
				{
					break;
				}
			}

			break;
		case 14: // Street
			do
			{
				flag = 0;
				printf("\n\t Street Keyword > ");
				scanf("%28[^\n]", &street);
				rewind(stdin);
				if (!(validStreet(street)))
				{
					printf("\n\t Invalid Street...\n");
					flag = 1;
				}
			} while (flag == 1);

			flag = 0;
			for (int x = 0; x < sanitizeUserCount; x++)
			{
				char lowercase[30];
				strcpy(lowercase, sanitizeUsers[x].info.location.street);
				if (strstr(lowerString(lowercase), lowerString(street)) == 0) // check street
				{
					for (int i = 0; i < sanitizeRecordCount; i++)
					{
						if (strcmp(sanitizeUsers[x].info.email, sanitizeRecords[i].email) == 0)
						{
							printableID[i] = 1;
							flag = 1;
							break;
						}
					}
				}
				if (flag)
				{
					break;
				}
			}

			break;
		case 15: // Zip Code

			do
			{
				flag = 0;
				printf("\n\t Zip Code (Upper Range) > ");
				scanf("%5d", &upZipCode);
				rewind(stdin);

				printf("\n\t Zip Code (Lower Range) > ");
				scanf("%5d", &lowZipCode);
				rewind(stdin);

				if (upZipCode < lowZipCode) // if upper zipCode is lower than lower zipCode
				{
					printf("\n\t Invalid Upper/Lower Zip Code Range...\n");
					continue;
				}
				else if (!(upZipCode == 0 || lowZipCode == 0)) // if input is not numerical
				{
					printf("\n\t Please key in zip code...\n");
					flag = 1;
				}
			} while (flag == 1);

			flag = 0;
			for (int x = 0; x < sanitizeUserCount; x++)
			{
				if (upZipCode >= sanitizeUsers[x].info.location.zipCode &&
					lowZipCode <= sanitizeUsers[x].info.location.zipCode) // check within range
				{
					for (int i = 0; i < sanitizeRecordCount; i++)
					{
						if (strcmp(sanitizeUsers[x].info.email, sanitizeRecords[i].email) == 0)
						{
							printableID[i] = 1;
							flag = 1;
							break;
						}
					}
				}
				if (flag)
				{
					break;
				}
			}

			break;
		case 16: // ID
			do
			{
				do
				{
					flag = 0;
					printf("\n\t ID (Upper Range) > ");
					scanf("%2d", &upID);
					rewind(stdin);
					if (upID < 0 || upID > sanitizeRecordCount) // if id entered is 
					{
						printf("\n\t Invalid ID...\n");
						flag = 1;
					}
				} while (flag == 1);

				do
				{
					flag = 0;
					printf("\n\t ID (Lower Range) > ");
					scanf("%2d", &lowID);
					rewind(stdin);
					if (lowID < 0 || lowID > sanitizeRecordCount)
					{
						printf("\n\t Invalid ID...\n");
						flag = 1;
					}
				} while (flag == 1);

				if (upID < lowID)
				{
					printf("\n\t Invalid Upper/Lower ID Range...\n");
					flag = 1;
				}

			} while (flag == 1);

			for (int i = 0; i < sanitizeRecordCount; i++) 
			{
				if (sanitizeRecords[i].id > upID || sanitizeRecords[i].id < lowID) 
				{
					printableID[i] = 1;
				}
			}
		}
	}

	char address[80];
	flag = 0;  // Check if any search results is outputted

	printf("\n\t Searching for matching results");
	Sleep(700); // delay program by 700 ms
	printf(".");
	Sleep(700);
	printf(".");
	Sleep(700);
	printf(".\n");

	printf("\n\n                                                                        S A N I T I Z A T I O N     S E A R C H     R E S U L T S\n");
	printf("\n\t+-----+----------------+------------+------------+----------+--------------+-----------+-----------------+------------------+--------------------------------+----------+----------------------------------+\n");
	printf("\t| ID. |     Venue      |    Date    | Start Time | End Time |   Phone No   |    Fax    |   Company Name  | Person-in-charge |              E-mail            | Reg No.  |              Address             |\n");
	printf("\t+-----+----------------+------------+------------+----------+--------------+-----------+-----------------+------------------+--------------------------------+----------+----------------------------------+\n");

	for (int i = 0; i < sanitizeRecordCount; i++) // loop through array record
	{
		if (printableID[i] != 1) // check whether to print this record or not
		{
			flag = 1; // reset marker

			printf("\t| %-3d ", sanitizeRecords[i].id);

			// Don't display venue and date if variable value is -1
			if (!(strcmp(sanitizeRecords[i].venue, "-1") == 0))
			{
				printf("| %-14s ", sanitizeRecords[i].venue);
			}
			else
			{
				printf("|       -      ");
			}

			if (sanitizeRecords[i].dayMonthYear.day != -1 ||
				sanitizeRecords[i].dayMonthYear.month != -1 ||
				sanitizeRecords[i].dayMonthYear.year != -1)
			{
				printf("| %-2d/%2d/%-4d ",
					sanitizeRecords[i].dayMonthYear.day,
					sanitizeRecords[i].dayMonthYear.month,
					sanitizeRecords[i].dayMonthYear.year);
			}
			else
			{
				printf("|      -     ");
			}

			// Don't display start time and end time if variable value is -1
			if (sanitizeRecords[i].startTime.hour != -1 || sanitizeRecords[i].startTime.minute != -1)
			{
				printf("|    %02d:%02d   ",
					sanitizeRecords[i].startTime.hour,
					sanitizeRecords[i].startTime.minute);
			}
			else
			{
				printf("|      -     ");
			}

			if (sanitizeRecords[i].endTime.hour != -1 || sanitizeRecords[i].endTime.minute != -1)
			{
				printf("|   %02d:%02d  ",
					sanitizeRecords[i].endTime.hour,
					sanitizeRecords[i].endTime.minute);
			}
			else
			{
				printf("|     -    ");
			}

			for (int x = 0; x < sanitizeUserCount; x++)
			{
				if (strcmp(sanitizeRecords[i].email, sanitizeUsers[x].info.email) == 0) // if email in array records matches email in array accounts
				{
					printf("| %-12s | %-9s | %-15s | %-16s | %-30s | %-8s ",
						sanitizeUsers[x].info.phoneNo,
						sanitizeUsers[x].info.fax,
						sanitizeUsers[x].info.name,
						sanitizeUsers[x].info.inCharge,
						sanitizeUsers[x].info.email,
						sanitizeUsers[x].info.registerNo);

					sprintf(address, "%-5d %-10s, %-12s",
						sanitizeUsers[x].info.location.zipCode,
						sanitizeUsers[x].info.location.city,
						sanitizeUsers[x].info.location.state); // prints zipCode, city and state into buffer named 'address'

					printf("|  %-31s |\n", address);
					break;
				}
			}

			if (i != sanitizeRecordCount - 1)
			{
				printf("\t|     |                |            |            |          |              |           |                 |                  |                                |          |                                  |\n");
			}
		}
	}

	printf("\t+-----+----------------+------------+------------+----------+--------------+-----------+-----------------+------------------+--------------------------------+----------+----------------------------------+\n\n");

	if (flag == 0) // print msg if no records were printed out
	{
		printf("\n\tNo Search Result Found...\n");
	}
}

/*==================================*/
/* (function) Search Menu for Admin */
/*==================================*/
void sanitizeSearchMenu()
{
	printf("\n\n\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                            SANITIZATION SEARCH MENU                             |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |             1. Venue                              2. Date                       |\n");
	printf("\t |             3. Phone Number                       4. Fax                        |\n");
	printf("\t |             5. Company Name                       6. Person-In-Charge           |\n");
	printf("\t |             7. Start Time                         8. End Time                   |\n");
	printf("\t |             9. E-mail                             10. Registeration No.         |\n");
	printf("\t |             11. City                              12. State                     |\n");
	printf("\t |             13. Country                           14. Street                    |\n");
	printf("\t |             15. Zip Code                          16. ID                        |\n");
	printf("\t |             17. Confirm Selection                 18. Exit                      |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
}


/*=================================*/
/* (function)Sanitization Check-In */
/*=================================*/
void sanitizeCheckIn()
{
	char venue[20] = "", lowercase[30] = ""; // declared as temp storage
	int flag = 0; // declare a marker

	DateTime time = getCurrentDateTime(); // get current datetime from header file 'universal.h'

	do
	{
		sanitizeUserDisplay();

		flag = 0; // reset marker

		printf("\n\t Enter your venue name > ");
		scanf("%18[^\n]", venue);
		rewind(stdin);

		for (int i = 0; i < sanitizeRecordCount; i++) // check venue exists in record
		{
			strcpy(lowercase, sanitizeRecords[i].venue);

			if (strcmp(lowerString(lowercase), lowerString(venue)) == 0) // venue found in record
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0) // if venue not found
		{
			printf("\n\t Invalid Venue Name...\n");
		}

	} while (flag == 0);

	printf("\n\t Searching for matching results");
	Sleep(700); // delay program by 700 ms
	printf(".");
	Sleep(700);
	printf(".");
	Sleep(700);
	printf(".\n");

	flag = 0;

	for (int i = 0; i < sanitizeRecordCount; i++) // loop through array records
	{
		if (strcmp(sanitizeRecords[i].venue, "-1") == 0) // skip this row if not yet recorded (-1 == uninitialized)
		{
			continue;
		}

		if (strcmp(sanitizeRecords[i].email, sanitizeUsers[currentUserCount].info.email) == 0) // Check current session email match with record
		{
			strcpy(lowercase, sanitizeRecords[i].venue);
			if (sanitizeRecords[i].startTime.hour == -1 &&
				strcmp(lowerString(lowercase), lowerString(venue)) == 0) // if start time is uninitialized and venue in array record matches with inputted venue
			{
				printf("\n\t Results found!\n");

				setVenueAvail(venue); // set venue to unavailable in venue module
				sanitizeRecords[i].startTime.hour = time.hour; // assign current time to the start time hour and minute
				sanitizeRecords[i].startTime.minute = time.min;

				printf("\n\t Check in successful!\n\n");
				return;
			}
		}
	}

	if (flag == 0) // if venue is not found
	{
		printf("\n\t Invalid Venue...\n\n");
		return;
	}
}

/*==================================*/
/* (function)Sanitization Check-Out */
/*==================================*/
void sanitizeCheckOut()
{
	char venue[20] = "", lowercase[30] = ""; // declared as temp storage
	int flag = 0; // declare a marker

	DateTime time = getCurrentDateTime(); // get current datetime from header file 'universal.h'

	do
	{
		sanitizeUserDisplay();

		flag = 0; // reset marker

		printf("\n\t Enter your venue name > ");
		scanf("%18[^\n]", venue);
		rewind(stdin);

		for (int i = 0; i < sanitizeRecordCount; i++) // check venue exists in record
		{
			strcpy(lowercase, sanitizeRecords[i].venue);

			if (strcmp(lowerString(lowercase), lowerString(venue)) == 0) // venue found in record
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			printf("\n\t Invalid Venue Name...\n");
		}
	} while (flag == 0);

	printf("\n\t Searching for matching results");
	Sleep(700);
	printf(".");
	Sleep(700);
	printf(".");
	Sleep(700);
	printf(".\n");

	flag = 0;

	for (int i = 0; i < sanitizeRecordCount; i++)
	{
		if (sanitizeRecords[i].startTime.hour == -1 && sanitizeRecords[i].startTime.minute == -1) // check if user not yet check in
		{
			continue;
		}

		if (strcmp(sanitizeRecords[i].email, sanitizeUsers[currentUserCount].info.email) == 0) // check for email between array records and accounts
		{
			strcpy(lowercase, sanitizeRecords[i].venue);
			if (sanitizeRecords[i].endTime.hour == -1 &&
				strcmp(lowerString(lowercase), lowerString(venue)) == 0)
			{
				printf("\n\t Results found!\n");

				setVenueAvail(venue); // set venue to available in venue module

				sanitizeRecords[i].endTime.hour = time.hour; // assign current time to end time hour and minute
				sanitizeRecords[i].endTime.minute = time.min;

				printf("\n\t Check out successful!\n\n");
				return;
			}
		}
	}
	if (flag == 0) // if venue not found
	{
		printf("\n\t Invalid Venue...\n\n");
		return;
	}
}

/*================================*/
/* (function)Sanitization Booking */
/*================================*/
void sanitizeBook()
{
	char venue[20] = "", lowercase[30] = ""; // declared as temp storage
	int day, month, year;
	int flag = 0; // declared as marker

	DateTime time = getCurrentDateTime(); // get current datetime from header file 'universal.h'

	printf("\n\t\t Venue List\n\t\t============\n"); // prints out venue names from header file 'venue.h'
	for (int i = 0; i < venInfoCount; i++)
	{
		printf("\n\t %d. %s\n", i + 1, ven[i].nameVen);
	}

	do
	{
		flag = 0;
		printf("\n\n\t Enter the venue name > ");
		scanf("%18[^\n]", venue);
		rewind(stdin);

		if (!(validVenueCompName(venue))) // validate venue name
		{
			printf("\n\t Invalid Venue Name...\n");
			continue;
		}

		for (int i = 0; i < venInfoCount; i++)  // Check if venue name exists
		{
			strcpy(lowercase, ven[i].nameVen);
			if (strcmp(lowerString(lowercase), lowerString(venue)) == 0) // venue found
			{
				flag = 1;
				strcpy(sanitizeRecords[sanitizeRecordCount].venue, ven[i].nameVen);  // Update validated venue into array (into new slot)
				break;
			}
		}

		if (flag == 0)
		{
			printf("\n\t Venue entered not in the list...\n");  // check flag determine error msg
			continue;
		}

	} while (flag == 0);

	// For data marking purposes

	sanitizeRecords[sanitizeRecordCount].startTime.hour = -1;  // '-1' indicates as null
	sanitizeRecords[sanitizeRecordCount].startTime.minute = -1;
	sanitizeRecords[sanitizeRecordCount].endTime.hour = -1;
	sanitizeRecords[sanitizeRecordCount].endTime.minute = -1;

	strcpy(sanitizeRecords[sanitizeRecordCount].email, sanitizeUsers[currentUserCount].info.email); // copy email address from users account to records

	do
	{
		flag = 0;
		printf("\n\t Enter date (dd/mm/yyyy) > ");
		scanf("%d/%d/%d", &day, &month, &year);
		rewind(stdin);

		// the first part validate the format of the date
		// the second part validate if the date is in the past or is in the future
		if (!(validDate(day, month, year)) || ((year * 10000) + (month * 100) + day) < ((time.year * 10000) + (time.intMonth * 100) + time.day))
		{
			printf("\n\t Invalid Date...\n");
			flag = 1;
		}

	} while (flag == 1);


	sanitizeRecords[sanitizeRecordCount].dayMonthYear.day = day; // Update validated day month year into array (into new slot)
	sanitizeRecords[sanitizeRecordCount].dayMonthYear.month = month;
	sanitizeRecords[sanitizeRecordCount].dayMonthYear.year = year;

	sanitizeRecords[sanitizeRecordCount].id = sanitizeRecordCount + 1; // assign id number to the new record 

	sanitizeRecordCount++; // increment records count by 1

	printf("\n\t Booking added successfully...");
	sanitizeUserDisplay();
	printf("\n\n");
}

/*=======================================================*/
/* (function) Summarize Venue Sanitization Status by days*/
/*=======================================================*/
void sanitizeSummary()
{
	DateTime time = getCurrentDateTime(); // get current datetime from header file 'universal.h'
	int flag = 0; // declared as marker 

	int currentDay = (time.year * 10000) + (time.intMonth * 100) + time.day; // declare and assign date to days
	int checkDay = 0; // store array record date in days

	printf("\n\n\t ..........................  S U M M A R Y     P A G E  ........................... \n\n");

	for (int x = 0; x < sanitizeRecordCount; x++)
	{
		checkDay = (sanitizeRecords[x].dayMonthYear.year * 10000) + 
		(sanitizeRecords[x].dayMonthYear.month * 100) + 
		sanitizeRecords[x].dayMonthYear.day; // assign date to days

		if (sanitizeRecords[x].startTime.hour == -1 &&
			sanitizeRecords[x].startTime.minute == -1 &&
			sanitizeRecords[x].endTime.hour == -1 &&
			sanitizeRecords[x].endTime.minute == -1 &&
			strcmp(sanitizeRecords[x].venue, "-1") == 0)
		{
			continue; // venue not yet inserted
		}

		// Current status - after booking (awaiting for sanitization)
		else if (sanitizeRecords[x].startTime.hour == -1 &&
			sanitizeRecords[x].startTime.minute == -1 &&
			sanitizeRecords[x].endTime.hour == -1 &&
			sanitizeRecords[x].endTime.minute == -1 &&
			currentDay < checkDay)   // if booking date isnt yet past current date
		{
			printf("\n\t The venue <%s> will be sanitized in %d", sanitizeRecords[x].venue,
				abs(diffDays(sanitizeRecords[x].dayMonthYear.day,
					sanitizeRecords[x].dayMonthYear.month,
					sanitizeRecords[x].dayMonthYear.year)));
			
			flag = 1;

			if ((abs(diffDays(sanitizeRecords[x].dayMonthYear.day,
				sanitizeRecords[x].dayMonthYear.month,
				sanitizeRecords[x].dayMonthYear.year))) == 1) // check when to print 's' or no 's'
			{
				printf(" day\n");
			}
			else
			{
				printf(" days\n");
			}
		}
		// Current status - after check in (sanitizing)
		else if (sanitizeRecords[x].endTime.hour == -1 && sanitizeRecords[x].endTime.minute == -1 && currentDay < checkDay) // if booking date isnt yet past current date
		{
			printf("\n\t The venue <%s> is currently being sanitized\n", sanitizeRecords[x].venue);
			flag = 1;
		}
		// Current status - after check out (already sanitized)
		else
		{
			printf("\n\t The venue <%s> was sanitized %d", sanitizeRecords[x].venue,
				diffDays(sanitizeRecords[x].dayMonthYear.day,
					sanitizeRecords[x].dayMonthYear.month,
					sanitizeRecords[x].dayMonthYear.year));
			flag = 1;

			if ((abs(diffDays(sanitizeRecords[x].dayMonthYear.day,
				sanitizeRecords[x].dayMonthYear.month,
				sanitizeRecords[x].dayMonthYear.year))) == 1)  // check when to print 's' or no 's'
			{
				printf(" day ago\n");
			}
			else
			{
				printf(" days ago\n");
			}
		}
	}
	if (flag == 0) // if no records is found
	{
		printf("\n\t No records found...\n");
	}
	printf("\n\t =========================================================\n\n");
}

/*=====================================================================================*/
/* (function) Calculate the difference of days between parameter date and current date */
/*=====================================================================================*/
int diffDays(int day, int month, int year)
{

	DateTime time = getCurrentDateTime(); // get current datetime from header file 'universal.h'

	int day1 = day, mon1 = month, year1 = year, day2 = time.day, mon2 = time.intMonth, year2 = time.year; // assign values from parameter to variables
	int ref, dd1, dd2;

	ref = year1;
	if (year2 < year1)
		ref = year2;
	dd1 = 0;
	dd1 = subDiffDays(mon1); // get numbers of days from month
	for (int i = ref; i < year1; i++)
	{
		if (i % 4 == 0) // calculate leap year
			dd1 += 1;
	}
	dd1 = dd1 + day1 + (year1 - ref) * 365; // calculate parameter passed date
	dd2 = 0;
	for (int i = ref; i < year2; i++)
	{
		if (i % 4 == 0) // calculate leap year
			dd2 += 1;
	}
	dd2 = subDiffDays(mon2) + dd2 + day2 + ((year2 - ref) * 365); // calculate current date

	return abs(dd2 - dd1);
}

/*=========================================================*/
/* (function) Sub function to calculate difference of days */
/*=========================================================*/
int subDiffDays(int x)
{
	int y = 0;
	switch (x)
	{
	case 1: y = 0; break;
	case 2: y = 31; break;
	case 3: y = 59; break;
	case 4: y = 90; break;
	case 5: y = 120; break;
	case 6: y = 151; break;
	case 7: y = 181; break;
	case 8: y = 212; break;
	case 9: y = 243; break;
	case 10:y = 273; break;
	case 11:y = 304; break;
	case 12:y = 334;
	}
	return(y);
}

/*===========================================*/
/* (function) Account Modification for Admin */
/*===========================================*/
void sanitizeAdminUserModify()
{
	int modifyMenu, sanitizeChoice = -1;
	char city[30] = "", state[30] = "", country[30] = "", street[40] = "", password[20] = "";
	char compName[20] = "", inCharge[20] = "", email[40] = "", registerNo[20] = "", phoneNo[15] = "", fax[15] = "";  // Declared to store temp values for validation
	int zipCode = 0;
	int flag = 0;
	char checkEmail[40] = "";

	sanitizeAdminAccDisplay();

	do {
		do
		{
			flag = 0;
			printf("\n\t Which account would you like to modify? (Input E-mail of choice) > ");
			scanf("%38s", &checkEmail);
			rewind(stdin);

			if (!(validEmail(checkEmail))) // validate email input
			{
				printf("\n\t Invalid Input...\n");
				flag = 1;
			}
		} while (flag == 1);

		for (int i = 0; i < sanitizeUserCount; i++) 
		{
			if (strcmp(sanitizeUsers[i].info.email, checkEmail) == 0) // if matches found
			{
				sanitizeChoice = i; // assigned to match array account index
				break;
			}
		}
	} while (sanitizeChoice == -1);

	do {
		sanitizeAdminUserMod();
		printf("\n\n\t Please enter a number > ");  // Selection menu input
		scanf("%d", &modifyMenu);
		rewind(stdin);

		switch (modifyMenu)
		{
		case 1:
			do
			{
				flag = 0;
				printf("\n\t New Phone No. > ");
				scanf("%14[^\n]", phoneNo);
				rewind(stdin);

				if (!(validPhone(phoneNo)))
				{
					printf("\n\t Invalid Phone No...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[sanitizeChoice].info.phoneNo, phoneNo); // validated phone number replace old string in array

			sanitizeAdminAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 2:
			do
			{
				flag = 0;
				printf("\n\t New Fax No. > ");
				scanf("%14[^\n]", fax);
				rewind(stdin);

				if (!(validFax(fax)))
				{
					printf("\n\t Invalid Fax No...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[sanitizeChoice].info.fax, fax); // validated fax number replace old string in array

			sanitizeAdminAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 3:
			do
			{
				flag = 0;
				printf("\n\t New Company Name > ");
				scanf("%18[^\n]", compName);
				rewind(stdin);

				if (!(validVenueCompName(compName)))
				{
					printf("\n\t Invalid Company Name...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[sanitizeChoice].info.name, compName); // validated company name replace old string in array

			sanitizeAdminAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 4:
			do
			{
				flag = 0;
				printf("\n\t New Person-In-Charge Name > ");
				scanf("%18[^\n]", inCharge);
				rewind(stdin);

				if (!(validPersonInCharge(inCharge)))
				{
					printf("\n\t Invalid Name...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[sanitizeChoice].info.inCharge, inCharge); // validated person-in-charge name replace old string in array

			sanitizeAdminAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 5:
			do
			{
				flag = 0;
				printf("\n\t New E-mail > ");
				scanf("%38s", &email);
				rewind(stdin);

				if (!(validEmail(email)))
				{
					printf("\n\t Invalid E-mail...\n");
					flag = 1;
				}

			} while (flag == 1);



			for (int i = 0; i < sanitizeRecordCount; i++)  // change each records email 
			{
				if (strcmp(sanitizeRecords[i].email, sanitizeUsers[sanitizeChoice].info.email) == 0)
				{
					strcpy(sanitizeRecords[i].email, email); 
				}
			}

			strcpy(sanitizeUsers[sanitizeChoice].info.email, email); // validated email replace old string in array

			sanitizeAdminAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;

		case 6:
			do
			{
				flag = 0;
				printf("\n\t New Registeration No. > ");
				scanf("%14s", &registerNo);
				rewind(stdin);

				if (!(validRegNo(registerNo)))
				{
					printf("\n\t Invalid Registeration No...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[sanitizeChoice].info.registerNo, registerNo); // validated company registeration number replace old string in array

			sanitizeAdminAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;

		case 7:
			do
			{
				flag = 0;
				printf("\n\t New City > ");
				scanf("%18[^\n]", &city);
				rewind(stdin);

				if (!(validCity(city)))
				{
					printf("\n\t Invalid City Name...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[sanitizeChoice].info.location.city, city); // validated city name replace old string in array

			sanitizeAdminAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 8:
			do

			{
				flag = 0;
				printf("\n\t New State > ");
				scanf("%18[^\n]", &state);
				rewind(stdin);

				if (!(validState(state)))
				{
					printf("\n\t Invalid State Name...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[sanitizeChoice].info.location.state, state); // validated state name replace old string in array

			sanitizeAdminAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 9:
			do
			{
				flag = 0;
				printf("\n\t New Country > ");
				scanf("%18[^\n]", &country);
				rewind(stdin);

				if (!(validCountry(country)))
				{
					printf("\n\t Invalid Country Name...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[sanitizeChoice].info.location.country, country); // validated country name replace old string in array

			sanitizeAdminAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 10:
			do
			{
				flag = 0;
				printf("\n\t New Street > ");
				scanf("%38[^\n]", &street);
				rewind(stdin);

				if (!(validStreet(street)))
				{
					printf("\n\t Invalid Street Name...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[sanitizeChoice].info.location.street, street); // validated street name replace old string in array

			sanitizeAdminAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 11:
			do
			{
				printf("\n\t New Zip Code > ");
				scanf("%d", &zipCode);
				rewind(stdin);

				if (zipCode == 0)
				{
					printf("\n\t Invalid Zip Code");
				}

			} while (zipCode == 0);

			sanitizeUsers[sanitizeChoice].info.location.zipCode = zipCode; // validated zipcode replace old value in array

			sanitizeAdminAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 12:
			do
			{
				flag = 0;
				printf("\n\t New Password > ");
				scanf("%18s", &password);
				rewind(stdin);

				if (!(validPassword(password)))
				{
					printf("\n\t Weak password combination...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[sanitizeChoice].info.password, password); // validated password replace old string in array

			sanitizeAdminAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 13:
			break;
		default:
			printf("\n\t Invalid Selection...");
		}
	} while (modifyMenu != 13);
}

/*================================================*/
/* (function) Records Modification Menu for Admin */
/*================================================*/
void sanitizeAdminRecMod()
{
	printf("\n\n\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                        SANITIZATION ADMIN MODIFY MENU                           |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |          1. Venue                 2. Date                 3. Exit               |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
}

/*================================================*/
/* (function) Account Modification Menu for Admin */
/*================================================*/
void sanitizeAdminUserMod()
{
	printf("\n\n\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                        SANITIZATION ADMIN MODIFY MENU                           |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |             1. Phone No                           2. Fax                        |\n");
	printf("\t |             3. Company Name                       4. Person-In-Charge           |\n");
	printf("\t |             5. E-mail                            6. Registeration No.           |\n");
	printf("\t |             7. City                               8. State                      |\n");
	printf("\t |             9. Country                            10. Street                    |\n");
	printf("\t |             11. Zip Code                          12. Password                  |\n");
	printf("\t |             13. Exit                                                            |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
}

/*===========================================*/
/* (function) Records Modification for Admin */
/*===========================================*/
void sanitizeAdminRecordModify()
{
	int modifyMenu, id, sanitizeChoice = -1;
	char venue[20] = "";   // Declared to store temp values for validation
	int day, month, year;
	int flag = 0;

	sanitizeAdminDisplay();

	do {
		printf("\n\t Which sanitization Record ID would you like to modify? > ");
		scanf("%d", &id);
		rewind(stdin);
		for (int i = 0; i < id; i++) 
		{
			if (sanitizeRecords[i].id == id)  // if matching id found in array records
			{
				sanitizeChoice = i; 
			}
		}
		if (sanitizeChoice == -1) {
			printf("\n\t Invalid ID, please try again!\n");
		}
	} while (sanitizeChoice == -1);

	do {
		sanitizeAdminRecMod();
		printf("\n\n\t Please enter a number > ");  // Selection menu input
		scanf("%d", &modifyMenu);
		rewind(stdin);

		switch (modifyMenu)
		{
		case 1:
			do
			{
				flag = 0;
				printf("\n\t New Venue > ");
				scanf("%18[^\n]", venue);
				rewind(stdin);
				if (!(validVenueCompName(venue)))
				{
					printf("\n\tInvalid Venue Name...\n");
					flag = 1;
				}
			} while (flag == 1);

			strcpy(sanitizeRecords[sanitizeChoice].venue, venue); // validated venue name replace old string in array
			sanitizeAdminDisplay();
			printf("\n\t Changes made successfully\n\n");

			break;
		case 2:
			do
			{
				flag = 0;
				printf("\n\t New Date (dd/mm/yyyy) > ");
				scanf("%d/%d/%d", &day, &month, &year);
				rewind(stdin);

				if (!(validDate(day, month, year)))
				{
					printf("\n\t Date Invalid...\n");
					flag = 1;
				}

			} while (flag == 1);

			sanitizeRecords[sanitizeChoice].dayMonthYear.day = day; // validated day, month and year replace old value in array
			sanitizeRecords[sanitizeChoice].dayMonthYear.month = month;
			sanitizeRecords[sanitizeChoice].dayMonthYear.year = year;

			sanitizeAdminDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 3:
			break;
		default:
			printf("\n\t Invalid Selection...");
		}
	} while (modifyMenu != 3);
}

/*==========================================*/
/* (function) Records Modification for User */
/*==========================================*/
void sanitizeUserRecModify()
{
	int modifyMenu, id, sanitizeChoice = -1;
	char venue[20] = "";   // Declared to store temp values for validation
	int day, month, year;
	int flag = 0; // declared as marker

	sanitizeUserDisplay();

	do {
		printf("\n\t Which sanitization Record ID would you like to modify? > ");
		scanf("%d", &id);
		rewind(stdin);
		for (int i = 0; i < id; i++) {
			if (sanitizeRecords[i].id == id &&
				strcmp(sanitizeRecords[i].email, sanitizeUsers[currentUserCount].info.email) == 0) // compare input id with array id and records email with user account email
			{
				sanitizeChoice = i; // assign current loop index to variable
			}
		}
		if (sanitizeChoice == -1) {
			printf("\n\t Invalid ID, please try again!\n");
		}
	} while (sanitizeChoice == -1);


	do {
		sanitizeUserRecMod();
		printf("\n\n\t Please enter a number > ");  // Selection menu input
		scanf("%d", &modifyMenu);
		rewind(stdin);

		switch (modifyMenu)
		{
		case 1:
			do
			{
				flag = 0;
				printf("\n\t New Venue > ");
				scanf("%18[^\n]", venue);
				rewind(stdin);
				if (!(validVenueCompName(venue)))
				{
					printf("\n\t Invalid Venue Name...\n");
					flag = 1;
				}
			} while (flag == 1);

			strcpy(sanitizeRecords[sanitizeChoice].venue, venue); // validated venue name replace old string in array
			sanitizeUserDisplay();
			printf("\n\t Changes made successfully\n\n");

			break;
		case 2:
			do
			{
				flag = 0;
				printf("\n\t New Date (dd/mm/yyyy) > ");
				scanf("%d/%d/%d", &day, &month, &year);
				rewind(stdin);

				if (!(validDate(day, month, year)))
				{
					printf("\n\t Date Invalid...\n");
					flag = 1;
				}

			} while (flag == 1);

			sanitizeRecords[sanitizeChoice].dayMonthYear.day = day; // validated day, month and year replace old value in array
			sanitizeRecords[sanitizeChoice].dayMonthYear.month = month;
			sanitizeRecords[sanitizeChoice].dayMonthYear.year = year;

			sanitizeUserDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 3:
			break;
		default:
			printf("\n\t Invalid Selection...");
		}
	} while (modifyMenu != 3);
}

/*==========================================*/
/* (function) Account Modification for User */
/*==========================================*/
void sanitizeUserAccModify()
{
	int modifyMenu, id;
	char city[30] = "", state[30] = "", country[30] = "", street[40] = "", password[20] = "";
	char compName[20] = "", inCharge[20] = "", email[40] = "", registerNo[20] = "", phoneNo[15] = "", fax[15] = "";  // Declared to store temp values for validation
	int zipCode = 0;
	int flag = 0;

	do {
		sanitizeUserAccMod();
		printf("\n\n\t Please enter a number > ");  // Selection menu input
		scanf("%d", &modifyMenu);
		rewind(stdin);

		switch (modifyMenu)
		{
		case 1:
			do
			{
				flag = 0; // reset marker
				printf("\n\t New Phone No. > ");
				scanf("%14[^\n]", phoneNo);
				rewind(stdin);

				if (!(validPhone(phoneNo))) // validate input
				{
					printf("\n\t Invalid Phone No...\n");
					flag = 1; // continue loop
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[currentUserCount].info.phoneNo, phoneNo); // validated phone number replace old string in array
			sanitizeUserAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 2:
			do
			{
				flag = 0;
				printf("\n\t New Fax No. > ");
				scanf("%14[^\n]", fax);
				rewind(stdin);

				if (!(validFax(fax)))
				{
					printf("\n\t Invalid Fax No...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[currentUserCount].info.fax, fax); // validated fax number replace old string in array
			sanitizeUserAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 3:
			do
			{
				flag = 0;
				printf("\n\t New Company Name > ");
				scanf("%18[^\n]", compName);
				rewind(stdin);

				if (!(validVenueCompName(compName)))
				{
					printf("\n\t Invalid Company Name...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[currentUserCount].info.name, compName); // validated company name replace old string in array
			sanitizeUserAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 4:
			do
			{
				flag = 0;
				printf("\n\t New Person-In-Charge Name > ");
				scanf("%18[^\n]", inCharge);
				rewind(stdin);

				if (!(validPersonInCharge(inCharge)))
				{
					printf("\n\t Invalid Name...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[currentUserCount].info.inCharge, inCharge); // validated person-in-charge name replace old string in array
			sanitizeUserAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 5:
			do
			{
				flag = 0;
				printf("\n\t New E-mail > ");
				scanf("%38s", &email);
				rewind(stdin);

				if (!(validEmail(email)))
				{
					printf("\n\t Invalid E-mail...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[currentUserCount].info.email, email); // validated email replace old string in array
			sanitizeUserAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 6:
			do
			{
				flag = 0;
				printf("\n\t New Registeration No. > ");
				scanf("%14s", &registerNo);
				rewind(stdin);

				if (!(validRegNo(registerNo)))
				{
					printf("\n\t Invalid Registeration No...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[currentUserCount].info.registerNo, registerNo); // validated company registeration number replace old string in array
			sanitizeUserAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 7:
			do
			{
				flag = 0;
				printf("\n\t New City > ");
				scanf("%18[^\n]", &city);
				rewind(stdin);

				if (!(validCity(city)))
				{
					printf("\n\t Invalid City Name...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[currentUserCount].info.location.city, city); // validated city name replace old string in array
			sanitizeUserAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 8:
			do
			{
				flag = 0;
				printf("\n\t New State > ");
				scanf("%18[^\n]", &state);
				rewind(stdin);

				if (!(validState(state)))
				{
					printf("\n\t Invalid State Name...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[currentUserCount].info.location.state, state); // validated state name replace old string in array
			sanitizeUserAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 9:
			do
			{
				flag = 0;
				printf("\n\t New Country > ");
				scanf("%18[^\n]", &country);
				rewind(stdin);

				if (!(validCountry(country)))
				{
					printf("\n\t Invalid Country Name...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[currentUserCount].info.location.country, country); // validated country name replace old string in array
			sanitizeUserAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 10:
			do
			{
				flag = 0;
				printf("\n\t New Street > ");
				scanf("%38[^\n]", &street);
				rewind(stdin);

				if (!(validStreet(street)))
				{
					printf("\n\t Invalid Street Name...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[currentUserCount].info.location.street, street); // validated street neme replace old string in array
			sanitizeUserAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 11:
			do
			{
				printf("\n\t New Zip Code > ");
				scanf("%d", &zipCode);
				rewind(stdin);

				if (zipCode == 0)
				{
					printf("\n\t Invalid Zip Code");
				}

			} while (zipCode == 0);

			sanitizeUsers[currentUserCount].info.location.zipCode = zipCode; // validated zipcode replace old value in array
			sanitizeUserAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 12:
			do
			{
				flag = 0;
				printf("\n\t New Password > ");
				scanf("%18s", &password);
				rewind(stdin);

				if (!(validPassword(password)))
				{
					printf("\n\t Weak password combination...\n");
					flag = 1;
				}

			} while (flag == 1);

			strcpy(sanitizeUsers[currentUserCount].info.password, password); // validated password replace old string in array
			sanitizeUserAccDisplay();
			printf("\n\t Changes made successfully\n\n");
			break;
		case 13: // Exit
			break;
		default:
			printf("\n\t Invalid Selection...");
		}
	} while (modifyMenu != 13); // break if user selects 13
}

/*===============================================*/
/* (function) Account Modification Menu for User */
/*===============================================*/
void sanitizeUserAccMod()
{
	printf("\n\n\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                        SANITIZATION USER MODIFY MENU                            |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |             1. Phone No                           2. Fax                        |\n");
	printf("\t |             3. Company Name                       4. Person-In-Charge           |\n");
	printf("\t |             5. E-mail                             6. Registeration No.          |\n");
	printf("\t |             7. City                               8. State                      |\n");
	printf("\t |             9. Country                            10. Street                    |\n");
	printf("\t |             11. Zip Code                          12. Password                  |\n");
	printf("\t |             13. Exit                                                            |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
}

/*===============================================*/
/* (function) Records Modification Menu for User */
/*===============================================*/
void sanitizeUserRecMod()
{
	printf("\n\n\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                        SANITIZATION USER MODIFY MENU                            |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |           1. Venue               2. Date                3. Exit                 |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
}

/*==========================================*/
/* (function) Display Records info for User */
/*==========================================*/
void sanitizeUserDisplay()
{
	char address[80];
	int flag = 0;

	printf("\n\n\t                                                   S A N I T I Z A T I O N     R E C O R D S\n	");
	printf("\n\t +-----+----------------+------------+------------+----------+--------------+-----------------+------------------+----------------------------------+\n");
	printf("\t | ID. |     Venue      |    Date    | Start Time | End Time |   Phone No   |   Company Name  | Person-in-charge |              E-mail              |\n");
	printf("\t +-----+----------------+------------+------------+----------+--------------+-----------------+------------------+----------------------------------+\n");

	for (int x = 0; x < sanitizeRecordCount; x++)
	{
		if (strcmp(sanitizeUsers[currentUserCount].info.email, sanitizeRecords[x].email) == 0) // only show current session user info
		{
			flag = 1; // indicates record exists

			printf("\t | %-3d ", sanitizeRecords[x].id);

			// Don't display venue and date if variable value is -1
			if (strcmp(sanitizeRecords[x].venue, "-1"))
			{
				printf("| %-14s ", sanitizeRecords[x].venue);
			}
			else
			{
				printf("|        -       ");
			}

			if (sanitizeRecords[x].dayMonthYear.day != -1 ||
				sanitizeRecords[x].dayMonthYear.month != -1 ||
				sanitizeRecords[x].dayMonthYear.year != -1)
			{
				printf("| %-2d/%2d/%-4d ",
					sanitizeRecords[x].dayMonthYear.day,
					sanitizeRecords[x].dayMonthYear.month,
					sanitizeRecords[x].dayMonthYear.year);
			}
			else
			{
				printf("|      -     ");
			}

			// Don't display start time and end time if variable value is -1
			if (sanitizeRecords[x].startTime.hour != -1 || sanitizeRecords[x].startTime.minute != -1)
			{
				printf("|    %02d:%02d   ",
					sanitizeRecords[x].startTime.hour,
					sanitizeRecords[x].startTime.minute);
			}
			else
			{
				printf("|      -     ");
			}

			if (sanitizeRecords[x].endTime.hour != -1 || sanitizeRecords[x].endTime.minute != -1)
			{
				printf("|   %02d:%02d  ",
					sanitizeRecords[x].endTime.hour,
					sanitizeRecords[x].endTime.minute);
			}
			else
			{
				printf("|     -    ");
			}

			printf("| %-12s | %-15s | %-16s | %-32s |\n",
				sanitizeUsers[currentUserCount].info.phoneNo,
				sanitizeUsers[currentUserCount].info.name,
				sanitizeUsers[currentUserCount].info.inCharge,
				sanitizeUsers[currentUserCount].info.email);

			// if now is not the last record to be printed out
			if (x != sanitizeRecordCount - 1)
			{
				printf("\t |     |                |            |            |          |              |                 |                  |                                  |\n");
			}
		}
	}
	printf("\t +-----+----------------+------------+------------+----------+--------------+-----------------+------------------+----------------------------------+\n\n");

	if (!(flag))
	{
		printf("\n\tNo records found...\n\n");
	}
}

/*===========================================*/
/* (function) Display Account info for Admin */
/*===========================================*/
void sanitizeAdminAccDisplay()
{
	char address[80];
	printf("\n\n                                                   S A N I T I Z A T I O N     A C C O U N T S\n	");
	printf("\n\t +-----+--------------+-----------+-----------------+------------------+----------------------------------+----------+-------------------------------------+\n");
	printf("\t | ID. |   Phone No   |    Fax    |   Company Name  | Person-in-charge |              E-mail              | Reg No.  |              Address                |\n");
	printf("\t +-----+--------------+-----------+-----------------+------------------+----------------------------------+----------+-------------------------------------+\n");

	for (int x = 0; x < sanitizeUserCount; x++) // loop through array account list
	{
		printf("\t | %-3d ", sanitizeUsers[x].id);


		printf("| %-12s | %-9s | %-15s | %-16s | %-32s | %-8s ",
			sanitizeUsers[x].info.phoneNo,
			sanitizeUsers[x].info.fax,
			sanitizeUsers[x].info.name,
			sanitizeUsers[x].info.inCharge,
			sanitizeUsers[x].info.email,
			sanitizeUsers[x].info.registerNo);

		sprintf(address, "%-5d %-10s, %-12s",
			sanitizeUsers[x].info.location.zipCode,
			sanitizeUsers[x].info.location.city,
			sanitizeUsers[x].info.location.state); // print zipCode, city and state into buffer named 'address'

		printf("| %-35s |\n", address);

		// if currently is not the last record to be printed out
		if (x != sanitizeUserCount - 1)
		{
			printf("\t |     |              |           |                 |                  |                                  |          |                                     |\n");
		}
	}
	printf("\t +-----+--------------+-----------+-----------------+------------------+----------------------------------+----------+-------------------------------------+\n\n");
}

/*==========================================*/
/* (function) Display Account info for User */
/*==========================================*/
void sanitizeUserAccDisplay()
{
	char address[80];
	printf("\n\n\t                                                   S A N I T I Z A T I O N     A C C O U N T\n");
	printf("\n\t +-----+--------------+-----------+-----------------+------------------+----------------------------------+----------+-------------------------------------+\n");
	printf("\t | ID. |   Phone No   |    Fax    |   Company Name  | Person-in-charge |              E-mail              | Reg No.  |              Address                |\n");
	printf("\t +-----+--------------+-----------+-----------------+------------------+----------------------------------+----------+-------------------------------------+\n");

	for (int x = 0; x < sanitizeUserCount; x++)
	{
		if (strcmp(sanitizeUsers[currentUserCount].info.email, sanitizeUsers[x].info.email) == 0) // will only print the current session user's account
		{
			printf("\t | %-3d ", sanitizeUsers[x].id);


			printf("| %-12s | %-9s | %-15s | %-16s | %-32s | %-8s ",
				sanitizeUsers[x].info.phoneNo,
				sanitizeUsers[x].info.fax,
				sanitizeUsers[x].info.name,
				sanitizeUsers[x].info.inCharge,
				sanitizeUsers[x].info.email,
				sanitizeUsers[x].info.registerNo);

			sprintf(address, "%-5d %-10s, %-12s",
				sanitizeUsers[x].info.location.zipCode,
				sanitizeUsers[x].info.location.city,
				sanitizeUsers[x].info.location.state); // print zipCode, city and state into buffer named 'address'

			printf("| %-35s |\n", address);
		}
	}
	printf("\t +-----+--------------+-----------+-----------------+------------------+----------------------------------+----------+-------------------------------------+\n\n");
}

/*======================================*/
/* (function) Display Records for Admin */
/*======================================*/
void sanitizeAdminDisplay()
{
	printf("\n\n\t                                                   S A N I T I Z A T I O N     R E C O R D S\n	");
	printf("\n\t +-----+----------------+------------+------------+----------+--------------+-----------------+------------------+----------------------------------+\n");
	printf("\t | ID. |     Venue      |    Date    | Start Time | End Time |   Phone No   |   Company Name  | Person-in-charge |              E-mail              |\n");
	printf("\t +-----+----------------+------------+------------+----------+--------------+-----------------+------------------+----------------------------------+\n");

	for (int x = 0; x < sanitizeRecordCount; x++)
	{
		printf("\t | %-3d ", sanitizeRecords[x].id);

		// Don't display venue and date if variable value is -1
		if (strcmp(sanitizeRecords[x].venue, "-1"))
		{
			printf("| %-14s ", sanitizeRecords[x].venue);
		}
		else
		{
			printf("|        -       ");
		}

		if (sanitizeRecords[x].dayMonthYear.day != -1 ||
			sanitizeRecords[x].dayMonthYear.month != -1 ||
			sanitizeRecords[x].dayMonthYear.year != -1)
		{
			printf("| %-2d/%2d/%-4d ",
				sanitizeRecords[x].dayMonthYear.day,
				sanitizeRecords[x].dayMonthYear.month,
				sanitizeRecords[x].dayMonthYear.year);
		}
		else
		{
			printf("|      -     ");
		}

		// Don't display start time and end time if variable value is -1
		if (sanitizeRecords[x].startTime.hour != -1 || sanitizeRecords[x].startTime.minute != -1)
		{
			printf("|    %02d:%02d   ",
				sanitizeRecords[x].startTime.hour,
				sanitizeRecords[x].startTime.minute);
		}
		else
		{
			printf("|      -     ");
		}

		if (sanitizeRecords[x].endTime.hour != -1 || sanitizeRecords[x].endTime.minute != -1)
		{
			printf("|  %02d:%02d   ",
				sanitizeRecords[x].endTime.hour,
				sanitizeRecords[x].endTime.minute);
		}
		else
		{
			printf("|     -    ");
		}

		for (int i = 0; i < sanitizeUserCount; i++) // loop through array account 
		{
			if (strcmp(sanitizeRecords[x].email, sanitizeUsers[i].info.email) == 0) // found matches between records and user accounts
			{
				printf("| %-12s | %-15s | %-16s | %-32s |",
					sanitizeUsers[i].info.phoneNo,
					sanitizeUsers[i].info.name,
					sanitizeUsers[i].info.inCharge,
					sanitizeUsers[i].info.email);
				break;
			}
		}
		// if currently is not the last record to be printed out 
		if (x != sanitizeRecordCount - 1)
		{
			printf("\n\t |     |                |            |            |          |              |                 |                  |                                  |\n");
		}
	}
	printf("\n\t +-----+----------------+------------+------------+----------+--------------+-----------------+------------------+----------------------------------+\n\n");
}

/*==================*/
/* (function) Admin */
/*==================*/
int sanitizeAdmin()
{
	int adminMenu; // store menu choice
	char confirm; // store prompt confirmation reply
	system("cls"); // clear console screen during runtime
	sanitizeAdminMenu();
	do
	{
		adminMenu = 0;

		printf("\n\n\t Please enter a number > ");
		scanf("%d", &adminMenu);
		rewind(stdin);
		system("cls");

		switch (adminMenu)
		{
		case 1:
			sanitizeAdminRecordModify(); // modify records as admin
			system("pause");
			system("cls");
			break;
		case 2:
			sanitizeRecordDelete(); // delete records as admin
			system("pause");
			system("cls");
			break;
		case 3:
			sanitizeFilter(); // filter records as admin
			system("pause");
			system("cls");
			break;
		case 4:
			sanitizeSearch(); // search records as admin
			system("pause");
			system("cls");
			break;
		case 5:
			sanitizeAdminDisplay(); // display records as admin
			system("pause");
			system("cls");
			break;
		case 6:
			sanitizeSummary(); // summarize venue status
			system("pause");
			system("cls");
			break;
		case 7:
			sanitizeAdminUserModify(); // modify user account as admin
			system("pause");
			system("cls");
			break;
		case 8:
			sanitizeUserDelete(); // delete user account as admin
			system("pause");
			system("cls");
			break;
		case 9:
			sanitizeAdminAccDisplay(); // display user accounts as admin
			system("pause");
			system("cls");
			break;
		case 10:
			do
			{
				printf("\n\t Are you sure you want to exit Sanitization Admin Menu? (Y/N) > ");
				scanf("%c", &confirm);
				rewind(stdin);
				if (confirm == 'Y' || confirm == 'y') // will exit function
				{
					return 1; // return 1 as exit success
				}
				else if (confirm == 'N' || confirm == 'n') // return to admin console menu
				{
					adminMenu = -1; // assign -1 as to prevent loop break
				}
				else
				{
					printf("\n\t Invalid Input...\n");
				}
			} while (confirm != 'N' && confirm != 'n');
			break;
		default:
			printf("\n\t Invalid Selection...\n");
		}
		sanitizeAdminMenu();
	} while (adminMenu != 10); // will break while loop when 'adminMenu' is 10
}

/*=======================*/
/* (function) Admin Menu */
/*=======================*/
void sanitizeAdminMenu()
{
	printf("\n\n\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                             SANITIZATION ADMIN MENU                             |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |             1. Modify Record                     2. Delete Record               |\n");
	printf("\t |             3. Filter                            4. Search                      |\n");
	printf("\t |             5. Display Record                    6. Summary                     |\n");
	printf("\t |             7. Modify Account                    8. Delete Account              |\n");
	printf("\t |             9. Display Account                   10. Exit                       |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
}

/*=================*/
/* (function) User */
/*=================*/
void sanitizeUser()
{
	int userMenu;
	char confirm; // yes or no
	do
	{
		userMenu = 0;
		system("cls");
		sanitizeUserMenu();
		printf("\n\n\t Please enter a number > ");
		scanf("%d", &userMenu);
		rewind(stdin);
		system("cls");

		switch (userMenu)
		{
		case 1:
			sanitizeCheckIn(); // check in venue as user 
			system("pause");
			system("cls");
			break;
		case 2:
			sanitizeCheckOut(); // check out venue as user
			system("pause");
			system("cls");
			break;
		case 3:
			sanitizeBook(); // book venue as user
			system("pause");
			system("cls");
			break;
		case 4:
			sanitizeSummary(); // summarize venue status 
			system("pause");
			system("cls");
			break;
		case 5:
			sanitizeUserAccModify(); // modify current session user account
			system("pause");
			system("cls");
			break;
		case 6:
			sanitizeUserRecModify(); // modify current session user records
			system("pause");
			system("cls");
			break;
		case 7:
			sanitizeUserDisplay(); // display current session user records
			system("pause");
			system("cls");
			break;
		case 8:
			sanitizeUserAccDisplay(); // display current session user account
			system("pause");
			system("cls");
			break;
		case 9:

			do
			{
				printf("\n\t Are you sure you want to exit Sanitization User Menu? (Y/N) > ");
				scanf("%c", &confirm);
				rewind(stdin);
				if (confirm == 'Y' || confirm == 'y') // will exit function
				{
					return; // return as exit success
				}
				else if (confirm == 'N' || confirm == 'n') // return to admin console menu
				{
					userMenu = -1; // assign -1 as to prevent loop break
				}
				else
				{
					printf("\n\t Invalid Input...\n");
				}
			} while (confirm != 'N' && confirm != 'n');
			break;

			break;
		default:
			printf("\n\t Invalid Selection...\n");
			system("pause");
		}
	} while (userMenu != 9);
}

/*======================*/
/* (function) User Menu */
/*======================*/
void sanitizeUserMenu()
{
	printf("\n\n\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                             SANITIZATION USER MENU                              |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |             1. Check In                          2. Check Out                   |\n");
	printf("\t |             3. Book                              4. Summary                     |\n");
	printf("\t |             5. Modify Account                    6. Modify Record               |\n");
	printf("\t |             7. Display Record                    8. Display Account             |\n");
	printf("\t |             9. Exit                                                             |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
}

/*=============================*/
/* (function) Module Main Menu */
/*=============================*/
void sanitizeFrontPage()
{
	int choice, flag = 0;
	char confirm; // yes or no

	do
	{
		system("cls");
		printf("\n\n\t  --------------------------------------------------------------------------------- \n");
		printf("\t |                                                                                 |\n");
		printf("\t |                             SANITIZATION FRONT PAGE                             |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |          1. Log In                2. Sign Up                3. Exit             |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  --------------------------------------------------------------------------------- \n");

		printf("\n\t Please enter a number > ");
		scanf("%d", &choice);
		rewind(stdin);

		switch (choice)
		{
		case 1: // Login
			system("cls");
			if (sanitizeLogin()) // if login return true = login successful 
			{
				system("pause");
				sanitizeUser();
			}
			break;
		case 2: // Sign Up
			sanitizeSignUp();
			break;
		case 3:  // Exit function
			do
			{
				printf("\n\t Are you sure you want to exit Sanitization Main Menu? (Y/N) > ");
				scanf("%c", &confirm);
				rewind(stdin);
				if (confirm == 'Y' || confirm == 'y') // exit sanitization module
				{
					return; // exit function
				}
				else if (confirm == 'N' || confirm == 'n') // return to starting of function
				{
					break;
				}
				else
				{
					printf("\n\t Invalid Input...\n");
				}
			} while (confirm != 'N' && confirm != 'n');

			break;
		default:
			printf("\n\t Please key in an appopriate value...\n\n");
			system("pause");
		}
	} while (1);
}

/*==========================*/
/* (function) Login account */
/*==========================*/
int sanitizeLogin()
{
	char email[40], password[20];
	int flag = 0, count = 2;
	do
	{
		printf("\n\t Please enter your credentials here:\n");
		do
		{
			flag = 0;
			printf("\n\t E-mail : ");
			scanf("%35s", &email);
			rewind(stdin);
			if (!(validEmail(email))) // validate email
			{
				printf("\n\t Invalid E-mail...\n");
				flag = 1; // loop again to retake input
			}
		} while (flag == 1);

		do
		{
			flag = 0;
			printf("\n\t Password : ");
			scanf("%18s", &password);
			rewind(stdin);
			if (!(validPassword(password))) // Validate password length 
			{
				printf("\n\t Weak password combination...\n"); 
				flag = 1;
			}
		} while (flag == 1);

		for (int i = 0; i < sanitizeUserCount; i++)
		{
			// check email and password matches the accounts info
			if (strcmp(sanitizeUsers[i].info.email, email) == 0 && strcmp(sanitizeUsers[i].info.password, password) == 0)
			{
				printf("\n\t Access Granted...\n\n");
				currentUserCount = i;  // Store current login user row in record
				return 1;  // return 1 for successful login
			}
		}
		printf("\n\t Access Denied...\n\n\t%d chances remaining...\n", count);

		count--; // 3 chances counter
	} while (count != -1);
	printf("\n\n\t You will be redirected back to the front page...\n");
	return 0; // return 0 as failed login
}

/*============================*/
/* (function) Sign Up account */
/*============================*/
void sanitizeSignUp()
{
	char city[30] = "", state[30] = "", country[30] = "", street[40] = "", password[20] = "";
	char compName[20] = "", inCharge[20] = "", email[40] = "", registerNo[20] = "", phoneNo[15] = "", fax[15] = ""; // store input into temp variable for validation
	int flag = 0, zipCode;
	do
	{
		flag = 0;
		printf("\n\tEnter Your E-mail > ");
		scanf("%35[^\n]", &email);
		rewind(stdin);
		if (!(validEmail(email)))  // E-mail validation
		{
			printf("\n\t Invalid E-mail...\n");
			flag = 1; // retake input from user
		}

		for (int i = 0; i < sanitizeUserCount; i++) // Check if email already exists
		{
			if (strcmp(sanitizeUsers[i].info.email, email) == 0)
			{
				printf("\n\t The User <%s> Already Exists...\n", sanitizeUsers[i].info.inCharge);
				flag = 1;
			}
		}
	} while (flag == 1);

	strcpy(sanitizeUsers[sanitizeUserCount].info.email, email); // add new validated email into array

	do
	{
		flag = 0;
		printf("\n\t Enter Your password (within 8 - 18 character count) > ");
		scanf("%18s", &password);
		rewind(stdin);
		if (!(validPassword(password)))  // Password validation
		{
			printf("\n\t Weak Password Combination...\n");
			flag = 1;
		}
	} while (flag == 1);

	strcpy(sanitizeUsers[sanitizeUserCount].info.password, password); // add new validated password into array

	do
	{
		flag = 0;
		printf("\n\t Enter phone no. (digits only / no dash) > ");
		scanf("%14[^\n]", &phoneNo);
		rewind(stdin);
		if (!(validPhone(phoneNo)))
		{
			printf("\n\t Invalid Phone No...\n");
			flag = 1;
		}
	} while (flag == 1);

	strcpy(sanitizeUsers[sanitizeUserCount].info.phoneNo, phoneNo); // add new validated phone no into array

	do
	{
		flag = 0;
		printf("\n\t Enter fax no. (digits only / no dash) > ");
		scanf("%14[^\n]", &fax);
		rewind(stdin);
		if (!(validFax(fax)))
		{
			printf("\n\t Invalid Fax No...\n");
			flag = 1;
		}
	} while (flag == 1);

	strcpy(sanitizeUsers[sanitizeUserCount].info.fax, fax); // add new validated fax no into array

	do
	{
		flag = 0;
		printf("\n\t Enter company name > ");
		scanf("%18[^\n]", &compName);
		rewind(stdin);
		if (!(validVenueCompName(compName)))
		{
			printf("\n\t Invalid Company Name...\n");
			flag = 1;
		}
	} while (flag == 1);

	strcpy(sanitizeUsers[sanitizeUserCount].info.name, compName); // add new validated company name into array

	do
	{
		flag = 0;
		printf("\n\t Enter your name here > ");
		scanf("%18[^\n]", &inCharge);
		rewind(stdin);
		if (!(validPersonInCharge(inCharge)))
		{
			printf("\n\t Invalid Name...\n");
			flag = 1;
		}
	} while (flag == 1);

	strcpy(sanitizeUsers[sanitizeUserCount].info.inCharge, inCharge); // add new validated person-in-charge name into array

	do
	{
		flag = 0;
		printf("\n\t Enter company registeration no. (9 digits) > ");
		scanf("%18[^\n]", &registerNo);
		rewind(stdin);
		if (!(validRegNo(registerNo)))
		{
			printf("\n\t Invalid Registeration No...\n");
			flag = 1;
		}

		for (int i = 0; i < sanitizeUserCount; i++)
		{
			if (strcmp(sanitizeUsers[i].info.registerNo, registerNo) == 0) // if company no already exist
			{
				printf("\n\t Company already registered...\n");
				flag = 1;
			}
		}

	} while (flag == 1);

	strcpy(sanitizeUsers[sanitizeUserCount].info.registerNo, registerNo); // add new validated registeration number into array

	do
	{
		flag = 0;
		printf("\n\t Enter company address (street) > ");
		scanf("%38[^\n], ", &street);
		rewind(stdin);
		if (!(validStreet(street)))
		{
			printf("\n\t Please enter anything...\n");
			flag = 1;
		}
	} while (flag == 1);

	strcpy(sanitizeUsers[sanitizeUserCount].info.location.street, street); // add new validated street name into array

	do
	{
		printf("\n\t Enter company address (zipcode) > ");
		scanf("%5d", &zipCode);
		rewind(stdin);
		if (zipCode == 0)
		{
			printf("\n\t Invalid Zipcode...\n");
		}
	} while (zipCode == 0);

	sanitizeUsers[sanitizeUserCount].info.location.zipCode = zipCode; // add new validated zip code into array

	do
	{
		flag = 0;
		printf("\n\t Enter company address (city) > ");
		scanf("%28[^\n], ", &city);
		rewind(stdin);
		if (!(validCity(city)))
		{
			printf("\n\t Invalid City Name...\n");
			flag = 1;
		}
	} while (flag == 1);

	strcpy(sanitizeUsers[sanitizeUserCount].info.location.city, city); // add new validated city name into array

	do
	{
		flag = 0;
		printf("\n\t Enter company address (state) > ");
		scanf("%28[^\n], ", &state);
		rewind(stdin);
		if (!(validState(state)))
		{
			printf("\n\t Invalid State Name...\n");
			flag = 1;
		}
	} while (flag == 1);

	strcpy(sanitizeUsers[sanitizeUserCount].info.location.state, state); // add new validated state name into array

	do
	{
		flag = 0;
		printf("\n\t Enter company address (country) > ");
		scanf("%28[^\n], ", &country);
		rewind(stdin);
		if (!(validCountry(country)))
		{
			printf("\n\t Invalid Country Name...\n");
			flag = 1;
		}
	} while (flag == 1);

	strcpy(sanitizeUsers[sanitizeUserCount].info.location.country, country); // add new validated country name into array

	sanitizeUsers[sanitizeUserCount].id = sanitizeUserCount + 1; // assign id for the new account

	sanitizeUserCount++; // increment by 1 for the user count
}