/*============*/
/* Admin Main */
/*============*/
// Admin base function which contain the core procedure in operating the admin module
int adminMain(Admin* adminList, int adminCount) {

	char currentUsername[21];

	/*=============*/
	/* Admin Login */
	/*=============*/
	// Read the username and password to match it with the pairs in the admin array
	int loginFail = 3;
	int status;
	int choice;
	do {
		status = adminLogin(adminList, adminCount, currentUsername);
		if (status) {
			// Login Success
			printf("\t Login Succesful!\n\n");
		}
		else if (loginFail >= 1) {
			// Login Failed! Username and password does not match any combination in the files.
			printf("\t Login failed! Please try again.\n\n");
			loginFail--;
		}
		else {
			// User reached his/her attempts limit.
			printf("\t Connection Aborted.\n\n");
			exit(-100);
		}
	} while (status == 0);


	/*===================*/
	/* Show Announcement */
	/*===================*/
	// Print the announcement to the screen before operation start.
	system("cls");
	showAnnouncement();


	/*================*/
	/* Choose Options */
	/*================*/
	// The user is allowed to operate every option until he/she choose to exit the program.
	do {
		choice = displayAdminMenu();
		switch (choice) {
		case 1:
			// Go to admin sub menu.
			system("cls");
			displayAdminSubMenu(adminList, &adminCount, currentUsername);
			system("cls");
			break;
		case 2:
			// Go to announcement module
			system("cls");
			displayAnnouncementSubMenu();
			system("cls");
			break;
		case 3:
			// Go to visit exit module
			system("cls");
			visitExitMenu();
			system("cls");
			break;
		case 4:
			// Go to sanitize admin module
			system("cls");
			sanitizeAdmin();
			system("cls");
			break;
		case 5:
			// Go to visitor module
			system("cls");
			visitorMenu();
			system("cls");
			break;
		case 6:
			// Go to venue admin module
			system("cls");
			venueAdminMenu();
			system("cls");
			break;
		case 7:
			// Exit Program
			printf("\t Bye bye!!\n");
			break;
		default: 
			// Invalid options, choice out of range.
			printf("\t Invalid choice please try again!!\n\n");
		}
	} while (choice != 7);
	return adminCount;
	// writeNewAdmin();
	//adminCount = addAdmin(adminList, adminCount);
}


/*=================*/
/* Read Admin File */
/*=================*/
// Load the admin data from the binary file to the array file.
int readAdminFile(Admin* adminList, int adminCount) {
	FILE* fptr;
	fptr = fopen("admin.bin", "rb");

	// Check whether file is openable.
	if (fptr == NULL) {
		printf("\t Cannot open admin.bin\n");
		exit(-100);
	}

	// Read the file from the admin.bin
	while (fread(&adminList[adminCount].username, sizeof(char), 21, fptr) != 0) {
		fread(&adminList[adminCount].password, sizeof(char), 41, fptr);
		fread(&adminList[adminCount].adminId, sizeof(int), 1, fptr);
		fread(&adminList[adminCount].contact, sizeof(char), 12, fptr);
		fread(&adminList[adminCount].first_name, sizeof(char), 21, fptr);
		fread(&adminList[adminCount].last_name, sizeof(char), 21, fptr);
		fread(&adminList[adminCount].department, sizeof(char), 31, fptr);
		fread(&adminList[adminCount].position, sizeof(char), 31, fptr);
		fread(&adminList[adminCount].lastlogin.day, sizeof(int), 1, fptr);
		fread(&adminList[adminCount].lastlogin.month, sizeof(char), 4, fptr);
		fread(&adminList[adminCount].lastlogin.year, sizeof(int), 1, fptr);
		fread(&adminList[adminCount].lastlogin.hour, sizeof(int), 1, fptr);
		fread(&adminList[adminCount].lastlogin.min, sizeof(int), 1, fptr);
		fread(&adminList[adminCount].lastlogin.sec, sizeof(int), 1, fptr);

		// Force change the username to all lower case.
		for (int i = 0; i < strlen(adminList[adminCount].username); i++) {
			adminList[adminCount].username[i] = tolower(adminList[adminCount].username[i]);
		}
		adminCount++;
	}

	fclose(fptr);
	return adminCount;
}

/*==================*/
/* Write Admin File */
/*==================*/
// Write the array of the admin data into the admin binary file
int writeAdminFile(Admin* adminList, int adminCount) {
	FILE* fptr;
	fptr = fopen("admin.bin", "wb");

	// Check whether the admin.bin is writable
	if (fptr == NULL || fptr == 0) {
		printf("\t Cannot write admin.bin\n");
	}

	// Write the array into the admin.bin
	for (int i = 0; i < adminCount; i++) {
		if (adminList[i].adminId != -1) {
			fwrite(&adminList[i].username, sizeof(char), 21, fptr);
			fwrite(&adminList[i].password, sizeof(char), 41, fptr);
			fwrite(&adminList[i].adminId, sizeof(int), 1, fptr);
			fwrite(&adminList[i].contact, sizeof(char), 12, fptr);
			fwrite(&adminList[i].first_name, sizeof(char), 21, fptr);
			fwrite(&adminList[i].last_name, sizeof(char), 21, fptr);
			fwrite(&adminList[i].department, sizeof(char), 31, fptr);
			fwrite(&adminList[i].position, sizeof(char), 31, fptr);
			fwrite(&adminList[i].lastlogin.day, sizeof(int), 1, fptr);
			fwrite(&adminList[i].lastlogin.month, sizeof(char), 4, fptr);
			fwrite(&adminList[i].lastlogin.year, sizeof(int), 1, fptr);
			fwrite(&adminList[i].lastlogin.hour, sizeof(int), 1, fptr);
			fwrite(&adminList[i].lastlogin.min, sizeof(int), 1, fptr);
			fwrite(&adminList[i].lastlogin.sec, sizeof(int), 1, fptr);
		}
	}
	fclose(fptr);
	return adminCount;
}


/*=============*/
/* Admin Login */
/*=============*/
// Check whether the details is match with the admin.bin
// Set the login time to the array
int adminLogin(Admin* adminList, int adminCount, char currentUsername[]) {
	char username[21], password[41];
	int hours, minutes, seconds, day, month, year;

	// Get the current timestamp
	DateTime currentDateTime = getCurrentDateTime();
	hours = currentDateTime.hour;
	minutes = currentDateTime.min;
	seconds = currentDateTime.sec;

	day = currentDateTime.day;
	year = currentDateTime.year;

	// Read the login details
	printf("\n\n\n\t ...................  A D M I N     L  O  G  I  N      P  A  G E  ..................\n\n");
	printf("\t Username: ");
	scanf("%20s", username);
	rewind(stdin);

	printf("\t Password: ");
	scanf("%40s", password);
	rewind(stdin);

	// Convert the username to lower case
	lowerString(username);
	char listUsername[21];

	// Matching the input with the array
	for (int i = 0; i < adminCount; i++) {

		// Converting username to all lower case before matching username and password.
		strcpy(listUsername, adminList[i].username);
		lowerString(listUsername);

		// Match username and password
		if (strcmp(listUsername, username) == 0 &&
			strcmp(adminList[i].password, password) == 0) {

			// Add the username to current session details
			strcpy(currentUsername, username);

			// Store current session into the array for records
			adminList[i].lastlogin.year = year;
			strcpy(adminList[i].lastlogin.month, currentDateTime.month);
			adminList[i].lastlogin.day = day;
			adminList[i].lastlogin.hour = hours;
			adminList[i].lastlogin.min = minutes;
			adminList[i].lastlogin.sec = seconds;

			return 1;
		}
	}
	return 0;
}



/*====================*/
/* Display Admin Menu */
/*====================*/
// It will show what the admin can do and allow them to choose
int displayAdminMenu() {
	int choice;

	// Display the admin menu layout.
	printf("\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                          TARUC SEJAHTERA (ADMIN PANEL)                          |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |             1. Admin                              2. Announcement               |\n");
	printf("\t |             3. Visit/Exit                         4. Sanitization               |\n");
	printf("\t |             5. Visitor                            6. Venue                      |\n");
	printf("\t |             7. Exit Programme                                                   |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");

	// Recieve user action choice and reject it if out of range.
	do {
		printf("\t Action? > ");
		scanf("%d", &choice);
		rewind(stdin);
		if (choice < 1 || choice > 7) {
			printf("\t Invalid action. Please type again!\n");
		}
	} while (choice < 1 || choice > 7);

	return choice;
}

void displayAnnouncementSubMenu() {
	int choice;
	// The begin of announcement module.
	do {
		choice = -1;
		// Print the announcement menu.
		printf("\t  --------------------------------------------------------------------------------- \n");
		printf("\t |                                                                                 |\n");
		printf("\t |                           TARUC SEJAHTERA (ADMIN PANEL)                         |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |    1. Modify Announcement      2. Show Announcement        3. Exit Programme    |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  --------------------------------------------------------------------------------- \n");
		printf("\t Action? > ");
		scanf("%d", &choice);
		rewind(stdin);

		// Run the coresponding actions and reject it if out of range.
		if (choice < 1 || choice > 3) {
			system("cls");
			printf("\t Invalid action. Please type again!\n");
		}
		else {
			switch (choice) {
			case 1: // Modify announcement
				system("cls");
				modifyAnnouncement();
				system("pause");
				system("cls");
				break;
			case 2:// Show announcement
				system("cls");
				showAnnouncement();
				system("pause");
				system("cls");
				break;
			case 3:
				return;
			}
		}
	} while (choice != 3);

}

void displayAdminSubMenu(Admin* adminList, int* adminCount, char currentUsername[]) {
	int choice;
	// Display admin sub modules
	do {
		choice = -1;
		printf("\t  --------------------------------------------------------------------------------- \n");
		printf("\t |                                                                                 |\n");
		printf("\t |                          TARUC SEJAHTERA (ADMIN PANEL)                          |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |         1. Display Admin Profile                  2. Modify Admin               |\n");
		printf("\t |         3. Delete Admin                           4. Add Admin                  |\n");
		printf("\t |         5. List Admin                             6. Search Admin               |\n");
		printf("\t |         7. Exit Programme                                                       |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  --------------------------------------------------------------------------------- \n");
		printf("\t Action? > ");
		scanf("%d", &choice);
		rewind(stdin);
		
		// Run coresponding actions or reject if out of range.
		if (choice < 1 || choice > 7) {
			system("cls");
			printf("\t Invalid action. Please type again!\n");
		}
		else {

			switch (choice) {
			case 1:
				// Display current admin profile
				system("cls");
				displayAdminProfile(adminList, *adminCount, currentUsername);
				system("pause");
				system("cls");
				break;
			case 2:
				// Modify Admin
				system("cls");
				modifyAdmin(adminList, *adminCount);
				system("pause");
				system("cls");
				break;
			case 3:
				// Delete Admin
				system("cls");
				deleteAdmin(adminList, *adminCount, currentUsername);
				system("pause");
				system("cls");
				break;
			case 4:
				// Add admin
				system("cls");
				*adminCount = addAdmin(adminList, *adminCount);
				system("pause");
				system("cls");
				break;
			case 5:
				// List admin account
				system("cls");
				listAdmin(adminList, *adminCount);
				system("pause");
				system("cls");
				break;
			case 6:
				// Search admin
				system("cls");
				searchAdmin(adminList, *adminCount);
				system("pause");
				system("cls");
				break;
			case 7:
				return;
			}
		}
	} while (choice != 7);


}


/*=======================*/
/* Display Admin Profile */
/*=======================*/
// Display the current admin's profile and informations.
void displayAdminProfile(Admin* adminList, int adminCount, char currentUsername[]) {
	char listUsername[21];
	for (int i = 0; i < adminCount; i++) {

		strcpy(listUsername, adminList[i].username);
		lowerString(listUsername);
		char name[30] = "";
		strcat(name, adminList[i].first_name);
		strcat(name, " ");
		strcat(name, adminList[i].last_name);
		// Check every row in the array and display only the set that match the username.
		if (strcmp(listUsername, currentUsername) == 0) {

			printf("\n\n\t              H E R E    I S    Y O U R    A D M I N    D E T A I L S    !          \n");
			printf("\t  --------------------------------------------------------------------------------- \n");
			printf("\t |                              PERSONAL ADMIN DETAILS                             |\n");
			printf("\t |---------------------------------------------------------------------------------|\n");
			printf("\t |                                                                                 |\n");
			printf("\t |   Name         > %-29s                                  |\n", name);
			printf("\t |                                                                                 |\n");
			printf("\t |   Contact No.  > %-14s                                                 |\n", adminList[i].contact);
			printf("\t |                                                                                 |\n");
			printf("\t |   Department   > %-14s                                                 |\n", adminList[i].department);
			printf("\t |                                                                                 |\n");
			printf("\t |   Position     > %-24s                                       |\n", adminList[i].position);
			printf("\t |=================================================================================|\n");
			printf("\t |                                                                                 |\n");
			printf("\t |   Username     >  %-15s                                               |\n", adminList[i].username);
			printf("\t |                                                                                 |\n");
			printf("\t |   User Id      >  %-15d                                               |\n", adminList[i].adminId);
			printf("\t |                                                                                 |\n");
			printf("\t |---------------------------------------------------------------------------------|\n");
			printf("\t |   Last Login  >   %2d-%s-%d %02d:%02d:%02d                                          |\n", adminList[i].lastlogin.day,
				adminList[i].lastlogin.month,
				adminList[i].lastlogin.year,
				adminList[i].lastlogin.hour,
				adminList[i].lastlogin.min,
				adminList[i].lastlogin.sec);
			printf("\t  --------------------------------------------------------------------------------- \n");
			return;
		}
		
	}
	// Username does not match any records in the array.
	printf("\t No Records found!\n");
}



/*==============*/
/* Modify Admin */
/*==============*/
// Modify the admin record in the admin array
void modifyAdmin(Admin* adminList, int adminCount) {
	listAdmin(adminList, adminCount);

	int userChoice, adminChoice = -1, choice;
	char answer[50] = "";

	// Read the selected admin id.
	do {
		printf("\t Which admin you want to modify? > ");
		scanf("%d", &userChoice);
		rewind(stdin);

		// Check the row number of the targeted admin records.
		for (int i = 0; i < adminCount; i++) {
			if (adminList[i].adminId == userChoice) {
				adminChoice = i;
			}
		}
		if (adminChoice == -1) {
			printf("\t Invalid ID, please try again!\n");
		}
	} while (adminChoice == -1);


	// Modify the admin array according to the user response
	do {
		choice = modifyAdminMenu();
		rewind(stdin);
		switch (choice) {
		case 1: // Edit First name.
			do {

				printf("\n\n\t                         Please key in the NEW INFORMATION                       \n");
				printf("\t ----------------------------------------------------------------------------------\n");
				printf("\t New First Name > ");
				scanf("%20[^\n]", answer);
				rewind(stdin);

				// Firstname must contain only alphabet
				if (isAlphabet(answer) == 0) {
					printf("\t ERROR: Invalid new first name!\n");
				}
				else if (isNotEmpty(answer) == 0) {
					printf("\t ERROR: You can leave it blank!\n");
				}else
				{

					strcpy(adminList[adminChoice].first_name, answer);
					printf("\t Changed successfully\n\n");
				}

			} while (isAlphabet(answer) == 0 || isNotEmpty(answer) == 0);
			break;
		case 2: // Edit last name
			do {
				printf("\n\n\t                         Please key in the NEW INFORMATION                       \n");
				printf("\t ----------------------------------------------------------------------------------\n");
				printf("\t New Last Name > ");
				scanf("%20[^\n]", answer);
				rewind(stdin);

				// Last name must contain only alphabet
				if (isAlphabet(answer) == 0) {
					printf("\t ERROR: Invalid new last name!\n");
				}
				else if (isNotEmpty(answer) == 0) {
					printf("\t ERROR: You can leave it blank!\n");
				}
				else {
					strcpy(adminList[adminChoice].last_name, answer);
					printf("\t Changed successfully\n\n");
				}


			} while (isAlphabet(answer) == 0 || isNotEmpty(answer) == 0);
			break;
		case 3: // Edit new department
			do {
				printf("\n\n\t                         Please key in the NEW INFORMATION                       \n");
				printf("\t ----------------------------------------------------------------------------------\n");
				printf("\t New Department > ");
				scanf("%30[^\n]", answer);
				rewind(stdin);

				// Department name must contain only alphabet
				if (isAlphabet(answer) == 0) {
					printf("\t ERROR: Invalid new department!\n");
				}
				else if (isNotEmpty(answer) == 0) {
					printf("\t ERROR: You can leave it blank!\n");
				}
				else {
					strcpy(adminList[adminChoice].department, answer);
					printf("\t Changed successfully\n\n");
				}


			} while (isAlphabet(answer) == 0 || isNotEmpty(answer) == 0);
			break;
		case 4: // Edit new position
			do {
				printf("\n\n\t                         Please key in the NEW INFORMATION                       \n");
				printf("\t ----------------------------------------------------------------------------------\n");
				printf("\t New Position > ");
				scanf("%30[^\n]", answer);
				rewind(stdin);

				// Position must contain only alphabet
				if (isAlphabet(answer) == 0) {
					printf("\t ERROR: Invalid new position!\n");
				}
				else if (isNotEmpty(answer) == 0) {
					printf("\t ERROR: You can leave it blank!\n");
				}
				else {

					strcpy(adminList[adminChoice].position, answer);
					printf("\t Changed successfully\n\n");
				}

			} while (isAlphabet(answer) == 0 || isNotEmpty(answer) == 0);
			break;
		case 5: // Edit new contact
			do {
				printf("\n\n\t                         Please key in your NEW INFORMATION                       \n");
				printf("\t -----------------------------------------------------------------------------------\n");
				printf("\t New Contact > ");
				scanf("%11[^\n]", answer);
				rewind(stdin);

				// Contact no should not contain space and should have only numbers.
				if (containSpace(answer) == 1 && isInteger(answer) == 0) {
					printf("\t ERROR: Invalid new contact!\n");
				}
				else if (isNotEmpty(answer) == 0) {
					printf("\t ERROR: You can leave it blank!\n");
				}
				else {

					strcpy(adminList[adminChoice].contact, answer);
					printf("\t Changed successfully\n\n");
				}

			} while ((containSpace(answer) == 1 && isInteger(answer) == 0) || isNotEmpty(answer) == 0);
			break;
		case 6:
			printf("\n\n\t Exited admin modification!\n\n");
			return;
		}
	} while (choice != 6);
}



/*=====================*/
/* Display Modify Menu */
/*=====================*/
// Display the chocie for modifying the admin account.
int modifyAdminMenu() {
	int choice;

	// Display the menu
	printf("\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                          TARUC SEJAHTERA (ADMIN PANEL)                          |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |              1. First Name                        2. Last Name                  |\n");
	printf("\t |              3. Department                        4. Position                   |\n");
	printf("\t |              5. Contact                           6. Exit                       |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");

	// Read the choice and reject if it is out of range.
	do {
		printf("\t What you want to modify? > ");
		scanf("%d", &choice);
		if (choice < 1 || choice > 6) {
			printf("\t Invalid choice! Please specific again!\n");
		}
	} while (choice < 1 || choice > 6);
	return choice;
}



/*==================*/
/* List Admin Array */
/*==================*/
// Display all the admin records in the array.
void listAdmin(Admin* adminList, int adminCount) {
	printf("\t +----------+-----------------+----------------------+----------------------+-----------------+---------------------------+--------------+----------------------+\n");
	printf("\t | Admin ID | Username        | First Name           | Last Name            | Department      | Position                  | Contact      | Last Login           |\n");
	printf("\t +----------+-----------------+----------------------+----------------------+-----------------+---------------------------+--------------+----------------------+\n");
	for (int i = 0; i < adminCount; i++) {
		// Skip if the records are soft deleted.
		if (adminList[i].adminId != -1) {
			printf("\t | %-8d | %-15s | %-20s | %-20s | %-15s | %-25s | %-12s | %-02d-%s-%-04d %02d:%02d:%02d |\n",
				adminList[i].adminId,
				adminList[i].username,
				adminList[i].first_name,
				adminList[i].last_name,
				adminList[i].department,
				adminList[i].position,
				adminList[i].contact,
				adminList[i].lastlogin.day,
				adminList[i].lastlogin.month,
				adminList[i].lastlogin.year,
				adminList[i].lastlogin.hour,
				adminList[i].lastlogin.min,
				adminList[i].lastlogin.sec);
		}
		else {
			continue;
		}
	}
	printf("\t +----------+-----------------+----------------------+----------------------+-----------------+---------------------------+--------------+----------------------+\n");
}



/*======================*/
/* Delete Admin Account */
/*======================*/
// Delete the selected admin account with provided admin id
void deleteAdmin(Admin* adminList, int adminCount, char currentUsername[]) {
	listAdmin(adminList, adminCount);
	int userChoice, adminChoice = -1, choice;
	char confirm;

	// Read user chocie on which records to delete
	do {
		printf("\t Which admin you want to delete? (-1 to leave) > ");
		scanf("%d", &userChoice);
		rewind(stdin);

		if (userChoice == -1) {
			printf("\t Exiting delete function! \n");
			break;
		}

		// Searching the targeted admin records
		for (int i = 0; i < adminCount; i++) {
			if (adminList[i].adminId == userChoice) {
				if (strcmp(adminList[i].username, currentUsername) == 0) {
					printf("\t You can't remove ur own accounts!\n");
					return;
				}
				printf("\t Do you sure you want to delete? (Yes = Y/y) > ");
				scanf("%c", &confirm);
				rewind(stdin);
				if (confirm == 'y' || confirm == 'Y') {
					adminChoice = i;
					// Soft delete
					adminList[i].adminId = -1;
					printf("\t Removed Successfully\n\n");
					return;
				}
				else {
					printf("\t Please confirm before you delete\n");
					return;
				}
			}
		}
		
		// Not matched record found.
		if (adminChoice == -1) {
			printf("\t Invalid ID, please try again!\n");
		}

	} while (adminChoice == -1);
}



/*===================*/
/* Add Admin Account */
/*===================*/
// Add new admin account into the array list
int addAdmin(Admin* adminList, int adminCount) {
	char username[21] = "", password[41] = "", first_name[21] = "", last_name[21] = "", department[31] = "",
		position[31] = "", contact[13] = "", choice;
	int adminID;
	do {

		// Read User Input
		printf("\n\n\n\t ......................  N E W     A D M I N     R E C O R D S  ....................\n\n");
		int flag;
		do {
			// Read username
			flag = 0;
			printf("\t Username: ");
			scanf("%20[^\n]", username);
			rewind(stdin);

			// Validate username.
			if (containSpace(username) == 1 || isAlphaNumber(username) == 0) {
				printf("\t Username cannot contain any special character and spacing!\n\n");
			} else if (isNotEmpty(username) == 0) {
				printf("\t ERROR: You can leave it blank!\n");
			}

			// Searching existing records
			for (int i = 0; i < adminCount; i++) {
				if (strcmp(adminList[i].username, username) == 0) {
					if (adminList[i].adminId != -1) {
						// Rejects when existing records found.
						flag = 1;
						printf("\t Username exist! Please try another user name!\n");
						break;
					}
				}
			}
		} while (containSpace(username) == 1 || isAlphaNumber(username) == 0 || flag == 1 || isNotEmpty(username) == 0);

		// Read password
		do {
			printf("\t Password: ");
			scanf("%40[^\n]", password);
			rewind(stdin);
			
			// Validate password
			if (containSpace(password) == 1) {
				printf("\t Password cannot contain any spacing!\n\n");
			}
			else if (isNotEmpty(password) == 0) {
				printf("\t ERROR: You can leave it blank!\n");
			}
		} while (containSpace(password) == 1 || isNotEmpty(password) == 0);

		// Read contact no
		do {
			printf("\t Contact No: ");
			scanf("%12s", contact);
			rewind(stdin);

			// Validate contact no.
			if (containSpace(contact) == 1 || isInteger(contact) == 0) {
				printf("\t Contact No should not contain any spacing and alphabet!\n\n");
			}
			else if (strlen(contact) < 10 || strlen(contact) > 11) {
				printf("\t Contact No should contain either 10 or 11 numbers!\n");
			}
			else if (isNotEmpty(contact) == 0) {
				printf("\t ERROR: You can leave it blank!\n");
			}
		} while (containSpace(contact) == 1 || isInteger(contact) == 0 || strlen(contact) < 10 || strlen(contact) > 11 || isNotEmpty(contact) == 0);

		// Read first name
		do {
			printf("\t First Name: ");
			scanf("%20[^\n]", first_name);
			rewind(stdin);

			// Validate first name
			if (isAlphabet(first_name) == 0) {
				printf("\t First name should not contain any number!\n\n");
			}
			else if (isNotEmpty(first_name) == 0) {
				printf("\t ERROR: You can leave it blank!\n");
			}
		} while (isAlphabet(first_name) == 0 || isNotEmpty(first_name) == 0);

		// Read last name
		do {
			printf("\t Last Name: ");
			scanf("%20[^\n]", last_name);
			rewind(stdin);

			// Validate last name
			if (isAlphabet(last_name) == 0) {
				printf("\t Last name should not contain any number or special character!\n\n");
			}
			else if (isNotEmpty(last_name) == 0) {
				printf("\t ERROR: You can leave it blank!\n");
			}
		} while (isAlphabet(last_name) == 0 || isNotEmpty(last_name) == 0);

		// Read department
		do {
			printf("\t Department: ");
			scanf("%30[^\n]", department);
			rewind(stdin);

			// Validate department
			if (isAlphabet(department) == 0) {
				printf("\t Department should not contain any number or special character!\n\n");
			}
			else if (isNotEmpty(department) == 0) {
				printf("\t ERROR: You can leave it blank!\n");
			}
		} while (isAlphabet(department) == 0 || isNotEmpty(department) == 0);

		// Read position
		do {
			printf("\t Position: ");
			scanf("%30[^\n]", position);
			rewind(stdin);

			// Validate position
			if (isAlphabet(position) == 0) {
				printf("\t Position should not contain any number or special character!\n\n");
			}
			else if (isNotEmpty(position) == 0) {
				printf("\t ERROR: You can leave it blank!\n");
			}
		} while (isAlphabet(position) == 0 || isNotEmpty(position) == 0);

		// Initialize to 1 if there is no any other records.
		int passCount = 0;
		if ((adminCount - 1) < 0) {
			adminID = 1;
		}
		else {
			// Get last id
			for (int i = adminCount - 1; i > 0; i--) {
				if (adminList[i].adminId != -1) {
					adminID = adminList[i].adminId + passCount + 1;
					break;
				}
				else {
					passCount++;
					continue;
				}
			}
		}

		// Write user input into admin array.
		strcpy(adminList[adminCount].username, username);
		strcpy(adminList[adminCount].password, password);
		strcpy(adminList[adminCount].contact, contact);
		adminList[adminCount].adminId = adminID;
		strcpy(adminList[adminCount].first_name, first_name);
		strcpy(adminList[adminCount].last_name, last_name);
		strcpy(adminList[adminCount].department, department);
		strcpy(adminList[adminCount].position, position);
		adminList[adminCount].lastlogin.day = 0;
		strcpy(adminList[adminCount].lastlogin.month, "JAN");
		adminList[adminCount].lastlogin.year = 0;
		adminList[adminCount].lastlogin.hour = 0;
		adminList[adminCount].lastlogin.min = 0;
		adminList[adminCount].lastlogin.sec = 0;

		adminCount++;

		// Continue if still want to add.
		printf("\t Do you want to add another record? (Yes = y) > ");
		scanf("%c", &choice);
		rewind(stdin);

	} while (choice == 'Y' || choice == 'y');
	return adminCount;
}



/*=====================*/
/* Modify announcement */
/*=====================*/
// Modify the announcement.txt to the latest announcement.
void modifyAnnouncement() {
	// Open the announcement.txt on write mode.
	FILE* fptr;
	fptr = fopen("announcement.txt", "w");
	if (fptr == NULL) {
		printf("\t Cannot write announcement.txt\n\n");
		exit(-1);
	}

	char announcement[201] = "";

	do {
		// Read user input
		printf("\t Please enter new announcement > ");
		scanf("%200[^\n]", announcement);
		if (isNotEmpty(announcement) == 0) {
			printf("You cant leave it blank!\n");
		}
	} while (isNotEmpty(announcement) == 0);

	// Write and save
	fprintf(fptr, "[ANNOUNCEMENT] %s\n", announcement);
	fclose(fptr);
}



/*===================*/
/* Show Announcement */
/*===================*/
// Show the announcement to the admin to let them check.
void showAnnouncement() {
	// Open the announcement.txt in read mode.
	FILE* fptr;
	fptr = fopen("announcement.txt", "r");

	if (fptr == NULL) {
		printf("\t Cannot read announcement.txt\n\n");
		exit(-1);
	}

	// Read announcement
	char announcement[201];
	fscanf(fptr, "%[^\n]\n", announcement);

	// Display and close
	printf("\n\n\t%s\n", announcement);
	fclose(fptr);
}



void adminSearchConditions(int condition[7]) {

	// Print choice menu
	printf("\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                                SEARCH ADMIN INFO                                |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |                1. Admin ID                         2. Username                  |\n");
	printf("\t |                3. First Name                       4. Last Name                 |\n");
	printf("\t |                5. Contact                          6. Department                |\n");
	printf("\t |                7. Position                         8. Search Now                |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");

	int choice;

	// Read user selected choice
	do {
		printf("\t Please select the condition > ");
		scanf("%d", &choice);
		rewind(stdin);

		// Out of range
		if (choice > 8 || choice < 1) {
			printf("\t Invalid choice. Please try again!\n");
		}
		else if (choice == 8) {
			// Start search
			printf("\t Start searching!\n");
		}
		else if (condition[choice - 1] == 0) {
			// Add condition succesfully
			printf("\t Added condition\n");
			condition[choice - 1] = 1;
		}
		else {
			// Condtion is selected before.
			printf("\t Condition exist!\n");

		}

	} while (choice != 8 || (choice > 8 && choice < 1));
}



/*==============*/
/* Search Admin */
/*==============*/
// Search the admin base on the filter condition.
void searchAdmin(Admin* adminList, int adminCount) {

	int condition[7] = { 0,0,0,0,0,0,0 };
	adminSearchConditions(condition);
	int adminIDUp, adminIDDown;
	char username[21] = "", firstname[21] = "", lastname[21] = "", contact[13] = "", department[31] = "", position[31] = "";
	int rowRecords = 0;
	Admin filteredList[50];


	// Load the adminList into the filteredList to prepare for filteration
	for (int i = 0; i < adminCount; i++) {
		if (adminList[i].adminId != -1) {
			strcpy(filteredList[i].username, adminList[i].username);
			strcpy(filteredList[i].contact, adminList[i].contact);
			filteredList[i].adminId = adminList[i].adminId;
			strcpy(filteredList[i].first_name, adminList[i].first_name);
			strcpy(filteredList[i].last_name, adminList[i].last_name);
			strcpy(filteredList[i].department, adminList[i].department);
			strcpy(filteredList[i].position, adminList[i].position);
			filteredList[i].lastlogin.day = adminList[i].lastlogin.day;
			strcpy(filteredList[i].lastlogin.month, adminList[i].lastlogin.month);
			filteredList[i].lastlogin.year = adminList[i].lastlogin.year;
			filteredList[i].lastlogin.hour = adminList[i].lastlogin.hour;
			filteredList[i].lastlogin.min = adminList[i].lastlogin.min;
			filteredList[i].lastlogin.sec = adminList[i].lastlogin.sec;
			rowRecords++;
		}

	}

	// Read the upper limit and lower limit of the admin ID range
	if (condition[0] == 1) {
		// Read upper limit
		do {
			printf("\t Target Admin ID Upper Range (Included) > ");
			scanf("%d", &adminIDUp);
			rewind(stdin);
			if (adminIDUp < 1) {
				printf("\t Invalid upper range! Please try again.\n\n");
			}
		} while (adminIDUp < 1);

		// Read lower limit
		do {

			printf("\t Target Admin ID Lower Range (Included) > ");
			scanf("%d", &adminIDDown);
			rewind(stdin);
			if (adminIDDown < 1 || adminIDDown > adminIDUp) {
				printf("\t Invalid lower range! Please try again.\n\n");
			}
		} while (adminIDDown < 1 || adminIDDown > adminIDUp);

		// Soft delete those records not matched from filtered list
		for (int i = 0; i < rowRecords; i++) {
			if (filteredList[i].adminId > adminIDUp || filteredList[i].adminId < adminIDDown) {
				filteredList[i].adminId = -1;
			}
		}
	}

	// Read the username keyword that is going to use to match the target
	if (condition[1] == 1) {
		// Read the username keyword.
		do {
			printf("\t Username keyword > ");
			scanf("%20[^\n]", username);
			rewind(stdin);
			if (containSpace(username) == 1 || isAlphaNumber(username) == 0) {
				printf("\t Username will not contain any blank or special characters!\n\n");
			}
			else if (isNotEmpty(username) == 0) {
				printf("\t You can not leave it empty!\n");
			}
		} while (containSpace(username) == 1 || isAlphaNumber(username) == 0 || isNotEmpty(username) == 0);

		// Soft delete unmatched records
		for (int i = 0; i < rowRecords; i++) {
			if (strstr(lowerString(filteredList[i].username), lowerString(username)) == 0) {
				filteredList[i].adminId = -1;
			}
		}
	}

	// Read the firstname keyword that is going to use to match the target
	if (condition[2] == 1) {

		// Read the first name keyword
		do {
			printf("\t Firstname Keyword > ");
			scanf("%20[^\n]", firstname);
			rewind(stdin);
			if (isAlphabet(firstname) == 0) {
				printf("\t First name should not contain any number of special character!\n\n");
			}
			else if (isNotEmpty(firstname) == 0) {
				printf("\t You can not leave it empty!\n");
			}
		} while (isAlphabet(firstname) == 0 || isNotEmpty(firstname) == 0);

		// Soft delete unmatched records
		for (int i = 0; i < rowRecords; i++) {
			char lowercase[20];
			strcpy(lowercase, filteredList[i].first_name);
			if (strstr(lowerString(lowercase), lowerString(firstname)) == 0) {
				filteredList[i].adminId = -1;
			}
		}
	}

	// Read the lastname keyword that is going to use to match the target
	if (condition[3] == 1) {
		do {
			// Read the last name keyword
			printf("\t Lastname Keyword > ");
			scanf("%20[^\n]", lastname);
			rewind(stdin);
			if (isAlphabet(lastname) == 0) {
				printf("\t Last name should not contain any number or special character!\n\n");
			}
			else if (isNotEmpty(lastname) == 0) {
				printf("\t You can not leave it empty!\n");
			}
		} while (isAlphabet(lastname) == 0 || isNotEmpty(lastname) == 0);

		// Soft delete unmatched result
		for (int i = 0; i < rowRecords; i++) {
			char lowercase[20];
			strcpy(lowercase, filteredList[i].last_name);
			if (strstr(lowerString(lowercase), lowerString(lastname)) == 0) {
				filteredList[i].adminId = -1;
			}
		}
	}

	// Read the contact keyword that is going to use to match the target
	if (condition[4] == 1) {
		// Read contact number
		do {
			printf("\t Contact Number > ");
			scanf("%12[^\n]", contact);
			rewind(stdin);
			if (isInteger(contact) == 0 || containSpace(contact) == 1) {
				printf("\t Contact number should not contain any alphabet or special character!\n\n");
			}
			else if (strlen(contact) < 10 || strlen(contact) > 11) {
				printf("\t Contact No should contain either 10 or 11 numbers!\n");
			}
			else if (isNotEmpty(contact) == 0) {
				printf("\t You can not leave it empty!\n");
			}
		} while (isInteger(contact) == 0 || containSpace(contact) == 1 || strlen(contact) < 10 || strlen(contact) > 11 || isNotEmpty(contact) == 0);

		// Soft delete unmatched result
		for (int i = 0; i < rowRecords; i++) {
			if (strstr(filteredList[i].contact, contact) == 0) {
				filteredList[i].adminId = -1;
			}
		}
	}

	// Read the department keyword that is going to use match the target
	if (condition[5] == 1) {
		// Read department name keyword
		do {
			printf("\t Department Keyword > ");
			scanf("%30[^\n]", department);
			rewind(stdin);
			if (isAlphabet(department) == 0) {
				printf("\t Deparment name should not contain any number or special characters\n\n");
			}
			else if (isNotEmpty(department) == 0) {
				printf("\t You can not leave it empty!\n");
			}
		} while (isAlphabet(department) == 0 || isNotEmpty(department) == 0);

		// Soft delete unmatched result
		for (int i = 0; i < rowRecords; i++) {
			char lowercase[31];
			strcpy(lowercase, filteredList[i].department);
			if (strstr(lowerString(lowercase), lowerString(department)) == 0) {
				filteredList[i].adminId = -1;
			}
		}
	}

	// Read the position keyword that is going to use match the target
	if (condition[6] == 1) {

		// Read position keyword
		do {
			printf("\t Position Keyword > ");
			scanf("%30[^\n]", position);
			rewind(stdin);
			if (isAlphabet(position) == 0) {
				printf("\t Position should not contain any number or special characters\n\n");
			}
			else if (isNotEmpty(position) == 0) {
				printf("\t You can not leave it empty!\n");
			}
		} while (isAlphabet(position) == 0 || isNotEmpty(position) == 0);

		// Soft delete unmatched result
		for (int i = 0; i < rowRecords; i++) {
			char lowercase[31];
			strcpy(lowercase, filteredList[i].position);
			if (strstr(lowerString(lowercase), lowerString(position)) == 0) {
				filteredList[i].adminId = -1;
			}
		}
	}

	printAdminSearchResult(filteredList, rowRecords);
}



/*===========================*/
/* Print Admin Search Result */
/*===========================*/
// Print the filtered result on the screen nicely.
void printAdminSearchResult(Admin* filteredList, int rowRecords) {
	int flag = 0;
	printf("\t +----------+-----------------+----------------------+----------------------+-----------------+---------------------------+--------------+----------------------+\n");
	printf("\t | Admin ID | Username        | First Name           | Last Name            | Department      | Position                  | Contact      | Last Login           |\n");
	printf("\t +----------+-----------------+----------------------+----------------------+-----------------+---------------------------+--------------+----------------------+\n");
	for (int i = 0; i < rowRecords; i++) {
		// Skip soft deleted records
		if (filteredList[i].adminId != -1) {
			printf("\t | %-8d | %-15s | %-20s | %-20s | %-15s | %-25s | %-12s | %-02d-%s-%-04d %02d:%02d:%02d |\n",
				filteredList[i].adminId,
				filteredList[i].username,
				filteredList[i].first_name,
				filteredList[i].last_name,
				filteredList[i].department,
				filteredList[i].position,
				filteredList[i].contact,
				filteredList[i].lastlogin.day,
				filteredList[i].lastlogin.month,
				filteredList[i].lastlogin.year,
				filteredList[i].lastlogin.hour,
				filteredList[i].lastlogin.min,
				filteredList[i].lastlogin.sec);
				flag = 1;
		}
		else {
			continue;
		}
	}
	printf("\t +----------+-----------------+----------------------+----------------------+-----------------+---------------------------+--------------+----------------------+\n");
	if (flag == 0) {
		printf("\t No records found!\n");
	}
}

