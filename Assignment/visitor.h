

//main
void visitorMain() {

	tarucMenu();
}
int visitorMenu() {
	int choice;
	do {
		showAnnouncement();
		printf("\t  --------------------------------------------------------------------------------- \n");
		printf("\t |                                                                                 |\n");
		printf("\t |                      TARUC SEJAHTERA (SEARCH VISITOR PANEL)                     |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |           1. Search Visitor                     2. Display Visitor              |\n");
		printf("\t |           3. Delete Visitor                     4. Check User Health Status     |\n");
		printf("\t |           5. Display High Risk User             6. Exit Programme               |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  --------------------------------------------------------------------------------- \n");
		printf("\n\t Action? > ");
		scanf("%d", &choice);
		rewind(stdin);
		if (choice < 1 || choice > 6) {
			system("cls");
			printf("\t Invalid action. Please type again!\n");
		}
		else {
			switch (choice) {
			case 1: // Search Visitor
				system("cls");
				searchUser();
				system("pause");
				system("cls");
				break;
			case 2:// Display Visitor
				system("cls");
				displayUser();
				system("pause");
				system("cls");
				break;
			case 3:// Delete Visitor
				system("cls");
				deleteAcc();
				system("pause");
				system("cls");
				break;
			case 4:// Check User Health Status
				system("cls");
				checkUserHealthStatus();
				system("pause");
				system("cls");
				break;
			case 5:// Display High Risk User
				system("cls");
				displayHighRiskUser();
				system("pause");
				system("cls");
				break;
			case 6:
				return 0;
			}
		}
	} while (choice != 6);
}

void readPersonalFile() {
	FILE* fptr;
	fptr = fopen("visitor.bin", "rb");

	while (fread(&visitorList[visitorCount].userId, sizeof(int), 1, fptr) != 0)
	{

		fread(&visitorList[visitorCount].userName, sizeof(char), 50, fptr);
		fread(&visitorList[visitorCount].firstName, sizeof(char), 30, fptr);
		fread(&visitorList[visitorCount].lastName, sizeof(char), 50, fptr);
		fread(&visitorList[visitorCount].phoneNum, sizeof(char), 12, fptr);
		fread(&visitorList[visitorCount].state, sizeof(char), 20, fptr);
		fread(&visitorList[visitorCount].icNum, sizeof(char), 13, fptr);
		fread(&visitorList[visitorCount].password, sizeof(char), 9, fptr);
		fread(&visitorList[visitorCount].gender, sizeof(char), 1, fptr);

		visitorCount++;
	}

	fclose(fptr);
}

void writePersonalFile() {
	FILE* fptr;
	fptr = fopen("visitor.bin", "wb");
	if (fptr == NULL || fptr == 0) {
		printf("Unable to open the file\n");
		exit(-1);
	}
	for (int x = 0; x < visitorCount; x++)
	{
		if (visitorList[x].userId != -1)
		{
			fwrite(&visitorList[x].userId, sizeof(int), 1, fptr);
			fwrite(&visitorList[x].userName, sizeof(char), 50, fptr);
			fwrite(&visitorList[x].firstName, sizeof(char), 30, fptr);
			fwrite(&visitorList[x].lastName, sizeof(char), 50, fptr);
			fwrite(&visitorList[x].phoneNum, sizeof(char), 12, fptr);
			fwrite(&visitorList[x].state, sizeof(char), 20, fptr);
			fwrite(&visitorList[x].icNum, sizeof(char), 13, fptr);
			fwrite(&visitorList[x].password, sizeof(char), 9, fptr);
			fwrite(&visitorList[x].gender, sizeof(char), 1, fptr);
		}
	}
	fclose(fptr);
}

// function TARUC MENU
void tarucMenu() {
	int choice;

	printf("\n\n\t              W E L C O M E     T O     T A R U C     S E J A H T E R A           \n\n");
	printf("\t  __________________________________________________________________________________\n");
	printf("\t |                                                                                  |\n");
	printf("\t |                       HERE IS THE MENU FOR YOU TO CHOOSE !                       |\n");
	printf("\t |__________________________________________________________________________________|\n");
	printf("\t |                                        |                                         |\n");
	printf("\t |      - 1 -    L   O   G   I   N        |     - 2 -    R  E  G  I  S T  E  R      |\n");
	printf("\t |                                        |                                         |\n");
	printf("\t |       # Already Have An Account        |       # Does Not Have Any Account       |\n");
	printf("\t |                                        |                                         |\n");
	printf("\t |________________________________________|_________________________________________|\n");
	do
	{
		printf("\n\n\t Please Enter Your Choice ( 1 or 2 ) : ");
		scanf("%d", &choice);
		rewind(stdin);
		if (choice == 1)
		{
			login();
		}
		else if (choice == 2)
		{
			registerVisitor();
		}
		else
		{
			printf("\t Please Try Again. Just allow to insert number 1 or 2.\n");
		}
	} while (choice != 1 && choice != 2);

}

//    function LOGIN    
void login() {

	char firstName[30], lastName[50], phoneNum[12], state[20],
		icNum[14], password[10], gender;
	int rowRecord = 0;
	int num1;
	int flag = 0;
	int count = 3;
	visitor filteredList[50];
	system("cls");
	printf("\n\n\n\t .........  T A R U C     S E J A H T E R A     L  O  G  I  N     P  A  G E  ........\n\n");
	while (1)
	{
		printf("\n\t Username : ");
		scanf("%[^\n]", &visitorName);
		rewind(stdin);

		for (int i = 0; i < visitorCount; i++) {
			if (strcmp(visitorList[i].userName, visitorName) == 0) {
				flag = 1; // if user name exist in record
				break;
			}
		}

		if (flag == 0 || isAlphaNumber(visitorName) == 0) {
			if (count < 1) {
				printf("\n\t Register Your Account Again !");
				printf("\n\t Wish To Register Again ? ( -1-  Yes   -2- No ) > ");
				scanf("%d", &num1);
				switch (num1) {
				case 1:
					registerVisitor();
				case 2:
					exitTaruc();
					return;
				}


			}
			printf("\t Invalid username or password. Please Try Again. Just Have %d Chances Only\n", count);
			count--;

			continue;
		}
		break;
	}

	count = 3;

	while (1)
	{
		flag = 0;
		printf("\n\t Password (8 digits only) : ");
		scanf("%9s", &password);
		rewind(stdin);
		for (int i = 0; i < visitorCount; i++) {
			if (strcmp(visitorList[i].userName, visitorName) == 0 && strcmp(visitorList[i].password, password) == 0) {
				flag = 1; // match cases
				currentVisitorInfo.gender = visitorList[i].gender;
				strcpy(currentVisitorInfo.firstName, visitorList[i].firstName);
				strcpy(currentVisitorInfo.icNum, visitorList[i].icNum);
				strcpy(currentVisitorInfo.lastName, visitorList[i].lastName);
				strcpy(currentVisitorInfo.password, visitorList[i].password);
				strcpy(currentVisitorInfo.phoneNum, visitorList[i].phoneNum);
				strcpy(currentVisitorInfo.state, visitorList[i].state);
				currentVisitorInfo.userId = visitorList[i].userId;
				strcpy(currentVisitorInfo.userName, visitorList[i].userName);
				break;
			}
		}
		if (flag == 0 || isAlphaNumber(password) == 0) {
			if (count < 1) {
				printf("\n\t Register Your Account Again !");
				printf("\n\t Wish To Register Again ? ( -1-  Yes   -2- No ) > ");
				scanf("%d", &num1);
				rewind(stdin);
				switch (num1) {
				case 1:
					registerVisitor();
				case 2:
					exitTaruc();
					return;
				}


			}
			printf("\t Invalid username or password. Please Try Again. Just Have %d Chances Only\n", count);
			count--;


			continue;
		}
		break;
	}
	aftLoginMenu();
}

int userSearchConditions(int condition[8]) {

	// Print choice menu

	printf("\t  ---------------------------------------------------------------------------------\n");
	printf("\t |                                                                                 |\n");
	printf("\t |                                SEARCH USER INFO                                 |\n");
	printf("\t |             1. User Id                               2. Username                |\n");
	printf("\t |             3. First Name                            4. Last Name               |\n");
	printf("\t |             5. Contact No                            6. Ic Number               |\n");
	printf("\t |             7. State                                 8. Search Now              |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");

	int choice;

	// Read user selected choice
	do {
		printf("\n\t Please select the condition > ");
		scanf("%d", &choice);
		rewind(stdin);

		if (choice > 8 || choice < 1) {
			printf("\t Invalid choice. Please try again!\n");
		}
		else if (choice == 8) {
			printf("\t Start searching!\n");
		}
		else if (condition[choice - 1] == 0) {
			printf("\t Added condition\n");
			condition[choice - 1] = 1;
		}
		else {
			printf("\t Condition exist!\n");

		}

	} while (choice != 8 || (choice > 8 && choice < 1));
	return 0;
}



//----------Search User
// Search the user base on the filter condition.
void searchUser() {

	int condition[8] = { 0,0,0,0,0,0,0,0 };
	userSearchConditions(condition);
	int userIDUp, userIDDown;
	char username[20], first_Name[20], last_Name[20], phone_Num[12], state_st[20], ic_No[13];
	int rowRecords = 0;
	visitor filteredList[50];


	// Load the visitorList into the filteredList to prepare for filteration
	for (int i = 0; i < visitorCount; i++) {
		if (visitorList[i].userId != -1) {
			strcpy(filteredList[i].userName, visitorList[i].userName);
			strcpy(filteredList[i].phoneNum, visitorList[i].phoneNum);
			filteredList[i].userId = visitorList[i].userId;
			strcpy(filteredList[i].firstName, visitorList[i].firstName);
			strcpy(filteredList[i].lastName, visitorList[i].lastName);
			strcpy(filteredList[i].icNum, visitorList[i].icNum);
			strcpy(filteredList[i].state, visitorList[i].state);
			filteredList[i].gender = visitorList[i].gender;
			rowRecords++;
		}

	}

	// Read the upper limit and lower limit of the user ID range
	if (condition[0] == 1) {
		printf("\n\t Target User ID Upper Range (Included) > ");
		scanf("%d", &userIDUp);
		rewind(stdin);
		do {
			printf("\n\t Target User ID Lower Range (Included) > ");
			scanf("%d", &userIDDown);
			rewind(stdin);
			if (userIDDown > userIDUp) {
				printf("\t Invalid lower range!\n");
			}
		} while (userIDDown > userIDUp);
		for (int i = 0; i < rowRecords; i++) {
			if (filteredList[i].userId > userIDUp || filteredList[i].userId < userIDDown) {
				filteredList[i].userId = -1;
			}
		}
	}

	// Read the username keyword that is going to use to match the target
	if (condition[1] == 1) {
		printf("\n\t Username keyword > ");
		scanf("%[^\n]", username);
		rewind(stdin);
		for (int i = 0; i < rowRecords; i++) {
			char lowercases[50] = "";
			strcpy(lowercases, filteredList[i].userName);
			if (strstr(lowerString(lowercases), lowerString(username)) == 0) {
				filteredList[i].userId = -1;
			}
		}
	}

	// Read the firstname keyword that is going to use to match the target
	if (condition[2] == 1) {
		printf("\n\t Firstname Keyword > ");
		scanf("%[^\n]", lowerString(first_Name));
		rewind(stdin);
		for (int i = 0; i < rowRecords; i++) {
			char lowercase[20];
			strcpy(lowercase, filteredList[i].firstName);
			if (strstr(lowerString(lowercase), lowerString(first_Name)) == 0) {
				filteredList[i].userId = -1;
			}
		}
	}

	// Read the lastname keyword that is going to use to match the target
	if (condition[3] == 1) {
		printf("\n\t Lastname Keyword > ");
		scanf("%[^\n]", last_Name);
		rewind(stdin);
		for (int i = 0; i < rowRecords; i++) {
			char lowercase[20];
			strcpy(lowercase, filteredList[i].lastName);
			if (strstr(lowerString(lowercase), lowerString(last_Name)) == 0) {
				filteredList[i].userId = -1;
			}
		}
	}

	// Read the contact keyword that is going to use to match the target
	if (condition[4] == 1) {
		printf("\n\t Contact Number > ");
		scanf("%[^\n]", phone_Num);
		rewind(stdin);
		for (int i = 0; i < rowRecords; i++) {
			char lowercase[12];
			strcpy(lowercase, filteredList[i].phoneNum);
			if (strstr(lowerString(lowercase), lowerString(phone_Num)) == 0) {
				filteredList[i].userId = -1;
			}
		}
	}

	// Read the department keyword that is going to use match the target
	if (condition[5] == 1) {
		printf("\n\t IC Number > ");
		scanf("%[^\n]", ic_No);
		rewind(stdin);
		for (int i = 0; i < rowRecords; i++) {
			char lowercase[31];
			strcpy(lowercase, filteredList[i].icNum);
			if (strstr(lowerString(lowercase), lowerString(ic_No)) == 0) {
				filteredList[i].userId = -1;
			}
		}
	}

	// Read the position keyword that is going to use match the target
	if (condition[6] == 1) {
		printf("\n\t State Keyword > ");
		scanf("%[^\n]", state_st);
		rewind(stdin);
		for (int i = 0; i < rowRecords; i++) {
			char lowercase[31];
			strcpy(lowercase, filteredList[i].state);
			if (strstr(lowerString(lowercase), lowerString(state_st)) == 0) {
				filteredList[i].userId = -1;
			}
		}
	}

	printUserSearchResult(filteredList, rowRecords);
}


/* Print User Search Result */
// Print the filtered result on the screen nicely.
void printUserSearchResult(visitor* filteredList, int rowRecords) {

	printf("\n\n\t +-----------+------------------+----------------------+----------------------+---------------------+--------------------------+--------------------+------------+\n");
	printf("\t |  User ID  |     Username     |      First Name      |       Last Name      |      IC Number      |       Phone Number       |        State       |   Gender   |\n");
	printf("\t +-----------+------------------+----------------------+----------------------+---------------------+--------------------------+--------------------+------------+\n");
	for (int i = 0; i < rowRecords; i++) {
		if (filteredList[i].userId != -1) {
			printf("\t | %-9d | %-16s | %-20s | %-20s | %-19s : %-24s | %-18s | %c          |\n",
				filteredList[i].userId,
				filteredList[i].userName,
				filteredList[i].firstName,
				filteredList[i].lastName,
				filteredList[i].icNum,
				filteredList[i].phoneNum,
				filteredList[i].state,
				filteredList[i].gender);

		}
		else {
			continue;
		}
	}
	printf("\t +-----------+------------------+----------------------+----------------------+---------------------+--------------------------+--------------------+------------+\n");
}

//   function REGISTER
void registerVisitor()
{

	char firstName[30], lastName[50], userName[50], password[9], phone[13], state[20], icNumber[14], gender;
	int userId, stateNum;

	printf("\n\n\n\t ----------------   V I S I T O R     R E G I S T E R     F O R M   ----------------\n\n");
	while (1)
	{
		printf("\t Please Enter Your FIRST NAME : ");
		scanf("%29[^\n]", &firstName);
		rewind(stdin);
		if (isAlphabet(firstName) == 0)
		{
			printf("\t Please Try Again. Must Only Contain Alphabets¡£\n");
			continue;
		}
		break;
	}
	while (1)
	{
		printf("\n\t Please Enter Your LAST NAME : ");
		scanf("%49[^\n]", &lastName);
		rewind(stdin);
		if (isAlphabet(lastName) == 0)
		{
			printf("\t Please Try Again. Must Only Contain Alphabets Without Spacing\n");
			continue;
		}
		break;
	}
	while (1)
	{
		printf("\n\t Please Enter Your PHONE NUMBER (except'-') : ");
		scanf("%12s", &phone);
		rewind(stdin);
		if (isInteger(phone) == 0)
		{
			printf("\t Invalid Phone Number. Try again without '-' and must be numeric \n");
			continue;
		}
		else if (strlen(phone) < 10 || strlen(phone) > 11) {
			printf("\t Phone Number must be exactly 10 or 11 digit!\n");
			continue;
		}
		break;
	}
	while (1)
	{
		printf("\n\t Please Enter Your IC NUMBER (except'-') : ");
		scanf("%13s", &icNumber);
		rewind(stdin);
		if (isInteger(icNumber) == 0)
		{
			printf("\t Invalid IC Number. Try again without '-' and must be numeric \n");
			continue;
		}
		else if (strlen(icNumber) != 12) {
			printf("\t IC Number must be exactly 12 digit!\n");
			continue;
		}
		break;
	}

	printf("\n\t  ---------------------------------------------------------------------------------\n");
	printf("\t |                                                                                 |\n");
	printf("\t |         1. Johor                 2. Kedah                  3. Kelantan          |\n");
	printf("\t |         4. Malacca               5. Negeri Sembilan        6. Pahang            |\n");
	printf("\t |         7. Penang                8. Perak                  9. Perlis            |\n");
	printf("\t |        10. Sabah                11. Sarawak               12. Selangor          |\n");
	printf("\t |        13. Terengganu                                                           |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  ---------------------------------------------------------------------------------\n");

	do {
		printf("\n\t Please Enter Your STATE Number : ");
		scanf("%d", &stateNum);
		rewind(stdin);
		if (stateNum < 1 || stateNum > 13)
		{
			printf("\t Invalid Number. Please try again! \n");
			continue;
		}
	} while (stateNum < 1 || stateNum > 13);
	switch (stateNum) {
	case 1:strcpy(visitorList[visitorCount].state, "Johor");
		break;
	case 2:strcpy(visitorList[visitorCount].state, "Kedah");
		break;
	case 3:strcpy(visitorList[visitorCount].state, "Kelantan");
		break;
	case 4:strcpy(visitorList[visitorCount].state, "Malacca");
		break;
	case 5: strcpy(visitorList[visitorCount].state, "Negeri Sembilan");
		break;
	case 6: strcpy(visitorList[visitorCount].state, "Pahang");
		break;
	case 7: strcpy(visitorList[visitorCount].state, "Penang");
		break;
	case 8:strcpy(visitorList[visitorCount].state, "Perak");
		break;
	case 9:strcpy(visitorList[visitorCount].state, "Perlis");
		break;
	case 10:strcpy(visitorList[visitorCount].state, "Sabah");
		break;
	case 11:strcpy(visitorList[visitorCount].state, "Sarawak");
		break;
	case 12: strcpy(visitorList[visitorCount].state, "Selangor");
		break;
	case 13: strcpy(visitorList[visitorCount].state, "Terengganu");
		break;
	}
	while (1)
	{
		printf("\n\t Please Enter Your Gender ( M = Male || F = Female ) : ");
		scanf("%c", &gender);
		rewind(stdin);
		if (gender != 'M' && gender != 'F')
		{
			printf("\t Please Try Again. Must Only Contain Alphabet M or F.\n");
			continue;
		}
		break;
	}

	while (1)
	{
		int flag = 0;
		printf("\n\t Please Enter Your USERNAME : ");
		scanf("%49[^\n]", &userName);
		rewind(stdin);
		if (isAlphabet(userName) == 0 || containSpace(userName) == 1)
		{
			printf("\t Please Try Again. Cannot have any spacing, symbols and number\n");
			continue;
		}
		for (int i = 0; i < visitorCount; i++) {
			if (strcmp(visitorList[i].userName, userName) == 0) {
				flag = 1;
				printf("\t Username exist! Please try another user name!\n");
				break;
			}
		}
		if (flag == 0) {
			break;
		}
	}
	while (1)
	{
		printf("\n\t Please Enter Your Password ( 8 digits ) : ");
		scanf("%9s", &password);
		rewind(stdin);
		if (isInteger(password) == 0)
		{
			printf("\t Invalid password Please Try Again\n");
			continue;
		}
		else if (strlen(password) != 8) {
			printf("\t Password must be exactly 8 digit!\n");
			continue;
		}
		break;
	}
	int passCount = 0;
	if ((visitorCount - 1) < 0) {
		userId = 1;
	}
	else {
		userId = visitorList[visitorCount - 1].userId + 1;
		for (int i = visitorCount - 1; i > 0; i--) {
			if (visitorList[i].userId != -1) {
				userId = visitorList[i].userId + passCount + 1;
				break;
			}
			else {
				passCount++;
				continue;
			}
		}
	}

	strcpy(visitorList[visitorCount].userName, userName);
	strcpy(visitorList[visitorCount].firstName, firstName);
	strcpy(visitorList[visitorCount].lastName, lastName);
	strcpy(visitorList[visitorCount].phoneNum, phone);
	strcpy(visitorList[visitorCount].icNum, icNumber);
	strcpy(visitorList[visitorCount].password, password);
	visitorList[visitorCount].gender = gender;
	visitorList[visitorCount].userId = userId;

	visitorCount++;

	printf("\n\n\t            Thanks  For  Register  And  Try  To  Login  Again  ^_^                ");
	printf("\n\t ---------------------------------------------------------------------------------\n\n\n");
	system("pause");
	system("cls");
	writePersonalFile();
	login();
}

//  Menu After Login 
int aftLoginMenu()
{

	int choice;
	do
	{
		printf("\n\n\t  --------------------------------------------------------------------------------- \n");
		printf("\t |                                                                                 |\n");
		printf("\t |                         TARUC SEJAHTERA (VISITOR PANEL)                         |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |       1. View Personal Account                 2. Edit Personal Account         |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |       3. Visit / Exit Venue                    4. Exit From TARUC Sejatera      |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  --------------------------------------------------------------------------------- \n");

		printf("\n\t Enter your selection ( 1, 2, 3 or 4) : ");
		scanf("%d", &choice);
		rewind(stdin);
		switch (choice)
		{
		case 1:
			system("cls");
			personalAccount();
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			edit();
			system("pause");
			system("cls");
			break;
		case 3: 
			system("cls");
			visitExitMain(currentVisitorInfo.userId, currentVisitorInfo.userName, currentVisitorInfo.icNum, currentVisitorInfo.phoneNum);
			break;
		case 4:
			system("cls");
			exitTaruc();
			break;
		default:
			printf("\n\t Invalid entry. Please enter one 1,2,3 or 4\n");
		}

	} while (choice != 4);
	return 0;
}



//  display personal account
void personalAccount()
{
	int num, num1;
	for (int i = 0; i < visitorCount; i++) {
		if (strcmp(visitorList[i].userName, currentVisitorInfo.userName) == 0) {

			printf("\n\n\t          H E R E    I S    Y O U R    P E R S O N A L    D E T A I L S    !       \n");
			printf("\t  ---------------------------------------------------------------------------------- \n");
			printf("\t |                                PERSONAL DETAILS                                  |\n");
			printf("\t |----------------------------------------------------------------------------------|\n");
			printf("\t |                                        :                                         |\n");
			printf("\t |   First Name > %-14s          :   Gender > %c                            |\n", visitorList[i].firstName, visitorList[i].gender);
			printf("\t |                                        :                                         |\n");
			printf("\t |   Last Name  > %-14s          :                                         |\n", visitorList[i].lastName);
			printf("\t |==================================================================================|\n");
			printf("\t |                                        :                                         |\n");
			printf("\t |   Phone No.  >  %-14s         :   State  > %-15s              |\n", visitorList[i].phoneNum, visitorList[i].state);
			printf("\t |                                        :                                         |\n");
			printf("\t |   IC No.     > %-14s          :                                         |\n", visitorList[i].icNum);
			printf("\t |----------------------------------------------------------------------------------|\n");
			printf("\t |                            FOR ACCOUNT LOGIN DETAILS                             |\n");
			printf("\t |----------------------------------------------------------------------------------|\n");
			printf("\t |                                                                                  |\n");
			printf("\t |   Username  >  %-15s                                                   |\n", visitorList[i].userName);
			printf("\t |                                                                                  |\n");
			printf("\t |   Password  >  %-15s                                                   |\n", visitorList[i].password);
			printf("\t |                                                                                  |\n");
			printf("\t |   User Id   >  %-6d                                                            |\n", visitorList[i].userId);
			printf("\t |                                                                                  |\n");
			printf("\t |----------------------------------------------------------------------------------|\n");
			printf("\t |      # Try To Remember Your Username And Password For The Usage Of Login #       |\n");
			printf("\t  ---------------------------------------------------------------------------------- \n");
			break;
		}
	}

}

// edit personal file
void edit()
{

	int choice, stateNum;
	char firstName[30], lastName[50], password[10], phone[13], state[20], icNumber[14], gender, userName[50];

	personalAccount();
	while (1)
		{
			printf("\n\n\t Which Part You Wish To Edit \n");
			printf("\n\t - 1 -  Personal Details        - 2 -  Account Login Details        - 3 -  Both \n");
			printf("\n\t Enter your choice ---> ");
			scanf("%d", &choice);
			rewind(stdin);
			if (choice < 1 || choice > 3)
			{
				printf("\t Invalid Number. Try again and must be numeric. \n");
				continue;
			}
			break;
		}
	
	switch (choice) {
	case 1:

		printf("\n\n\t                         Please key in your NEW INFORMATION                       \n");
				printf("\t -----------------------------------------------------------------------------------\n");
		while (1)
		{
			printf("\n\n\t Enter your new first name : ");
			scanf("%29[^\n]", &firstName);
			rewind(stdin);
			if (isAlphabet(firstName) == 0)
			{
				printf("\t Please Try Again. Must Only Contain Alphabets¡£\n");
				continue;
			}
			break;
		}
		while (1)
		{
			printf("\n\t Enter your new last name : ");
			scanf("%49[^\n]", &lastName);
			rewind(stdin);
			if (isAlphabet(lastName) == 0)
			{
				printf("\t Please Try Again. Must Only Contain Alphabets.\n");
				continue;
			}
			break;
		}
		while (1)
		{
			printf("\n\t Enter your phone number : ");
			scanf("%12s", &phone);
			rewind(stdin);
			if (isInteger(phone) == 0)
			{
				printf("\t Invalid Phone Number. Try again without '-' and must be numeric \n");
				continue;
			}
			else if (strlen(phone) < 10 || strlen(phone) > 11) {
				printf("\t Phone Number must be exactly 10 or 11 digit!\n");
				continue;
			}
			break;
		}
		while (1)
		{
			printf("\n\t Enter your IC number : ");
			scanf("%13s", &icNumber);
			rewind(stdin);
			if (isInteger(icNumber) == 0)
			{
				printf("\t Invalid IC Number. Try again without '-' and must be numeric \n");
				continue;
			}
			else if (strlen(icNumber) != 12) {
				printf("\t IC Number must be exactly 12 digit!\n");
				continue;
			}
			break;
		}

		printf("\n\t  ---------------------------------------------------------------------------------\n");
		printf("\t |                                                                                 |\n");
		printf("\t |         1. Johor                 2. Kedah                  3. Kelantan          |\n");
		printf("\t |         4. Malacca               5. Negeri Sembilan        6. Pahang            |\n");
		printf("\t |         7. Penang                8. Perak                  9. Perlis            |\n");
		printf("\t |        10. Sabah                11. Sarawak               12. Selangor          |\n");
		printf("\t |        13. Terengganu                                                           |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  ---------------------------------------------------------------------------------\n");

		do {
			printf("\n\t Please Enter Your STATE Number : ");
			scanf("%d", &stateNum);
			rewind(stdin);
			if (stateNum < 1 || stateNum > 13) {
				printf("\t Invalid Choice!!\n");
				continue;
			}
		} while (stateNum < 1 || stateNum > 13);
		switch (stateNum) {
		case 1:strcpy(state, "Johor");
			break;
		case 2:strcpy(state, "Kedah");
			break;
		case 3:strcpy(state, "Kelantan");
			break;
		case 4:strcpy(state, "Malacca");
			break;
		case 5: strcpy(state, "Negeri Sembilan");
			break;
		case 6: strcpy(state, "Pahang");
			break;
		case 7: strcpy(state, "Penang");
			break;
		case 8:strcpy(state, "Perak");
			break;
		case 9:strcpy(state, "Perlis");
			break;
		case 10:strcpy(state, "Sabah");
			break;
		case 11:strcpy(state, "Sarawak");
			break;
		case 12: strcpy(state, "Selangor");
			break;
		case 13: strcpy(state, "Terengganu");
			break;
		}

		while (1)
		{
			printf("\n\t Enter your gender ( M = Male || F = Female ) : ");
			scanf("%c", &gender);
			rewind(stdin);
			if (gender != 'M' && gender != 'F')
			{
				printf("\t Please Try Again. Must Only Contain Alphabet M or F.\n");
				continue;
			}
			break;
		}

		for (int i = 0; i < visitorCount; i++) {
			if (strcmp(visitorList[i].userName, currentVisitorInfo.userName) == 0) {
				strcpy(visitorList[i].firstName, firstName);
				strcpy(visitorList[i].lastName, lastName);
				strcpy(visitorList[i].phoneNum, phone);
				strcpy(visitorList[i].state, state);
				strcpy(visitorList[i].icNum, icNumber);
				visitorList[i].gender = gender;
				strcpy(currentVisitorInfo.firstName, firstName);
				strcpy(currentVisitorInfo.lastName, lastName);
				strcpy(currentVisitorInfo.phoneNum, phone);
				strcpy(currentVisitorInfo.state, state);
				strcpy(currentVisitorInfo.icNum, icNumber);
				currentVisitorInfo.gender = gender;
			}
		}
		printf("\n\n\t Your Information Have Been Updated !");
		break;

	case 2:
		printf("\n\n\t                         Please key in your NEW INFORMATION                       \n");
				printf("\t -----------------------------------------------------------------------------------\n");
		while (1)
		{
			int flag = 0;
			printf("\n\n\t Enter your new username : ");
			scanf("%49[^\n]", &userName);
			rewind(stdin);
			if (isAlphabet(userName) == 0 || containSpace(userName) == 1)
			{
				printf("\t Please Try Again. Cannot have any spacing, symbols and number\n");
				continue;
			}
			for (int i = 0; i < visitorCount; i++) {
				if (strcmp(visitorList[i].userName, userName) == 0) {
					if (visitorList[i].userId != -1) {
						printf("\t Username exist! Please try another user name!\n");
						flag = 1;
					}

				}
			}
			if (flag == 0) { break; }
		}
		while (1)
		{
			printf("\n\t Enter your new password : ");
			scanf("%9s", &password);
			rewind(stdin);
			if (isInteger(password) == 0)
			{
				printf("\t Invalid password Please Try Again\n");
				continue;
			}
			else if (strlen(password) != 8) {
				printf("\t Password must be exactly 8 digit!\n");
				continue;
			}
			break;
		}


		for (int i = 0; i < visitorCount; i++) {
			if (strcmp(visitorList[i].userName, currentVisitorInfo.userName) == 0) {
				strcpy(visitorList[i].userName, userName);
				strcpy(visitorList[i].password, password);
				strcpy(currentVisitorInfo.userName, userName);
				strcpy(currentVisitorInfo.password, password);
			}
		}
		printf("\n\n\t Your Information Have Been Updated !");
		break;

	case 3:
		printf("\n\n\t                         Please key in your NEW INFORMATION                       \n");
				printf("\t -----------------------------------------------------------------------------------\n");
		while (1)
		{
			printf("\n\n\t Enter your new first name : ");
			scanf("%29[^\n]", &firstName);
			rewind(stdin);
			if (isAlphabet(firstName) == 0)
			{
				printf("\t Please Try Again. Must Only Contain Alphabets¡£\n");
				continue;
			}
			break;
		}
		while (1)
		{
			printf("\n\t Enter your new last name : ");
			scanf("%49[^\n]", &lastName);
			rewind(stdin);
			if (isAlphabet(lastName) == 0)
			{
				printf("\t Please Try Again. Must Only Contain Alphabets.\n");
				continue;
			}
			break;
		}
		while (1)
		{
			printf("\n\t Enter your phone number : ");
			scanf("%12s", &phone);
			rewind(stdin);
			if (isInteger(phone) == 0)
			{
				printf("\t Invalid Phone Number. Try again without '-' and must be numeric \n");
				continue;
			}
			else if (strlen(phone) < 10 || strlen(phone) > 11) {
				printf("\t Phone Number must be exactly 10 or 11 digit!\n");
				continue;
			}
			break;
		}
		while (1)
		{
			printf("\n\t Enter your IC number : ");
			scanf("%13s", &icNumber);
			rewind(stdin);
			if (isInteger(icNumber) == 0)
			{
				printf("\t Invalid IC Number. Try again without '-' and must be numeric \n");
				continue;
			}
			else if (strlen(icNumber) == 12) {
				printf("\t IC Number must be exactly 12 digit!\n");
				continue;
			}
			break;
		}

		printf("\n\t  ---------------------------------------------------------------------------------\n");
		printf("\t |                                                                                 |\n");
		printf("\t |         1. Johor                 2. Kedah                  3. Kelantan          |\n");
		printf("\t |         4. Malacca               5. Negeri Sembilan        6. Pahang            |\n");
		printf("\t |         7. Penang                8. Perak                  9. Perlis            |\n");
		printf("\t |        10. Sabah                11. Sarawak               12. Selangor          |\n");
		printf("\t |        13. Terengganu                                                           |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  ---------------------------------------------------------------------------------\n");

		do {
			printf("\n\t Please Enter Your STATE Number : ");
			scanf("%d", &stateNum);
			rewind(stdin);
			if (stateNum < 1 || stateNum > 13) {
				printf("\t Invalid Choice!!\n");
				continue;
			}
		} while (stateNum < 1 || stateNum > 13);
		switch (stateNum) {
		case 1:strcpy(state, "Johor");
			break;
		case 2:strcpy(state, "Kedah");
			break;
		case 3:strcpy(state, "Kelantan");
			break;
		case 4:strcpy(state, "Malacca");
			break;
		case 5: strcpy(state, "Negeri Sembilan");
			break;
		case 6: strcpy(state, "Pahang");
			break;
		case 7: strcpy(state, "Penang");
			break;
		case 8:strcpy(state, "Perak");
			break;
		case 9:strcpy(state, "Perlis");
			break;
		case 10:strcpy(state, "Sabah");
			break;
		case 11:strcpy(state, "Sarawak");
			break;
		case 12: strcpy(state, "Selangor");
			break;
		case 13: strcpy(state, "Terengganu");
			break;
		}

		while (1)
		{
			printf("\n\t Enter your gender ( M = Male || F = Female ) : ");
			scanf("%c", &gender);
			rewind(stdin);
			if (gender != 'M' && gender != 'F')
			{
				printf("\t Please Try Again. Must Only Contain Alphabet M or F.\n");
				continue;
			}
			break;
		}
		while (1)
		{
			int flag = 0;
			printf("\n\n\t Enter your new username : ");
			scanf("%[^\n]", userName);
			rewind(stdin);

			if (isAlphabet(userName) == 0 || containSpace(userName) == 1)
			{
				printf("\t Please Try Again. Cannot have any spacing, symbols and number\n");
				continue;
			}
			for (int i = 0; i < visitorCount; i++) {
				if (strcmp(visitorList[i].userName, userName) == 0) {
					if (visitorList[i].userId != -1) {
						printf("\t Username exist! Please try another user name!\n");
						flag = 1;
					}
				}
			}
			if (flag == 0) { break; }
		}
		while (1)
		{
			printf("\n\t Enter your new password : ");
			scanf("%9s", &password);
			rewind(stdin);
			if (isInteger(password) == 0)
			{
				printf("\t Invalid password Please Try Again\n");
				continue;
			}
			else if (strlen(password) != 8) {
				printf("\t Password must be exactly 8 digit!\n");
				continue;
			}
			break;
		}

		for (int i = 0; i < visitorCount; i++) {
			if (strcmp(visitorList[i].userName, currentVisitorInfo.userName) == 0) {
				strcpy(visitorList[i].firstName, firstName);
				strcpy(visitorList[i].lastName, lastName);
				strcpy(visitorList[i].phoneNum, phone);
				strcpy(visitorList[i].state, state);
				strcpy(visitorList[i].icNum, icNumber);
				visitorList[i].gender = gender;
				strcpy(visitorList[i].userName, userName);
				strcpy(visitorList[i].password, password);
				strcpy(currentVisitorInfo.userName, userName);
				strcpy(currentVisitorInfo.password, password);
				strcpy(currentVisitorInfo.firstName, firstName);
				strcpy(currentVisitorInfo.lastName, lastName);
				strcpy(currentVisitorInfo.phoneNum, phone);
				strcpy(currentVisitorInfo.state, state);
				strcpy(currentVisitorInfo.icNum, icNumber);
				currentVisitorInfo.gender = gender;
			}
		}

		printf("\n\n\t Your Information Have Been Updated !");
		break;

	default:
		break;
	}
}

// Display User Account
void displayUser() {

	printf("\n\n\t +-----------+------------------+----------------------+----------------------+---------------------+--------------------------+--------------------+------------+\n");
	printf("\t |  User ID  |     Username     |      First Name      |       Last Name      |      IC Number      |       Phone Number       |        State       |   Gender   |\n");
	printf("\t |-----------+------------------+----------------------+----------------------+---------------------+--------------------------+--------------------|------------+\n");
	for (int i = 0; i < visitorCount; i++) {
		if (visitorList[i].userId != -1) {
			printf("\t | %-9d | %-16s | %-20s | %-20s | %-19s | %-24s | %-18s | %c          |\n",
				visitorList[i].userId,
				visitorList[i].userName,
				visitorList[i].firstName,
				visitorList[i].lastName,
				visitorList[i].icNum,
				visitorList[i].phoneNum,
				visitorList[i].state,
				visitorList[i].gender);

		}
		else {
			continue;
		}
	}
	printf("\t +-----------+------------------+----------------------+----------------------+---------------------+--------------------------+--------------------+------------+\n");
}

//delete account
void deleteAcc()
{
	displayUser();
	int userId;
	char choice;
	printf("\n\t Which Account You Want To Delete. Enter User ID ---> ");
	scanf("%d", &userId);
	rewind(stdin);
	for (int i = 0; i < visitorCount; i++)
	{
		if (visitorList[i].userId == userId) {
			printf("\n\t The Account Will Deleted Permanently. Comfirmed To Delete ? (Y = Yes) > ");
			scanf("%c", &choice);
			rewind(stdin);
			if (choice == 'y' || choice == 'Y') {

				visitorList[i].userId = -1;
				printf("\n\t Removed Successfully\n\n");
				displayUser();
				return;
			}
			else {
				printf("\n\t Please confirm before you delete.\n");
				return;
			}
		}
	}
}


// -------------exit Function
void exitTaruc()
{
	healthSurvey();
	printf("\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                      THANK YOU FOR USING TARUC SEJAHTERA                        |\n");
	printf("\t |            PLEASE STAY AT HOME , STAY SAFE AND TAKE CARE YOURSELF               |\n");
	printf("\t |           ALWAYS HAVE YOUR MASK ON AND PRACTICE SOCIAL DISTANCING               |\n");
	printf("\t |                          HAVE A NICE DAY AHEAD !!!                              |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");
	system("pause");
	system("cls");
}


typedef struct {
	int survey[6];
	int userId;
}SurveyDetails;

int readHealthSurvey(SurveyDetails* survey, int surveyCount) {
	FILE* fptr;
	fptr = fopen("healthSurvey.txt", "r");
	if (fptr == NULL) {
		printf("Unable to open healthSurvey.txt\n");
		exit(-1);
	}
	while (fscanf(fptr, "%d|%d|%d|%d|%d|%d|%d\n",
		&survey[surveyCount].userId,
		&survey[surveyCount].survey[0],
		&survey[surveyCount].survey[1],
		&survey[surveyCount].survey[2],
		&survey[surveyCount].survey[3],
		&survey[surveyCount].survey[4],
		&survey[surveyCount].survey[5]) != EOF) {
		surveyCount++;
	}
	fclose(fptr);
	return surveyCount;

}

void writeHealthSurvey(SurveyDetails* survey, int surveyCount) {
	FILE* fptr;
	fptr = fopen("healthSurvey.txt", "w");
	if (fptr == NULL) {
		printf("Unable to open healthSurvey.txt\n");
		exit(-1);
	}
	for (int i = 0; i < surveyCount; i++) {
		fprintf(fptr, "%d|%d|%d|%d|%d|%d|%d\n",
			survey[i].userId,
			survey[i].survey[0],
			survey[i].survey[1],
			survey[i].survey[2],
			survey[i].survey[3],
			survey[i].survey[4],
			survey[i].survey[5]);
	}
	fclose(fptr);

}

// Health Status Survey
void healthSurvey() {
	int selection;
	int total = 0;
	SurveyDetails survey[100];
	int surveyCount = 0;
	surveyCount = readHealthSurvey(survey, surveyCount);
	int indexNumber, flag = 0;
	for (int i = 0; i < surveyCount; i++) {
		if (currentVisitorInfo.userId == survey[i].userId) {
			indexNumber = i;
			flag = 1;
		}
	}
	if (flag == 0) {
		indexNumber = surveyCount;
		surveyCount++;
	}
	printf("\n\n\t .................  H E A L T H     S T A T U S     S U R V E Y  .................\n\n");
	printf("\n\t * Please Fill In This Form");
	printf("\n\n\t 1.  Are you exhibiting 2 or more symptoms as listed below?\n");
	printf("\t  ---------------------------------------------------------------------------------\n");
	printf("\t |                                                                                 |\n");
	printf("\t |  > Fever                            > Chills               > Shivering (rigor)  |\n");
	printf("\t |  > Body Ache                        > Headache             > Sore Throat        |\n");
	printf("\t |  > Nausea or vomiting               > Diarrhea             > Fatigue            |\n");
	printf("\t |  > Runny nose or nasal congestion                                               |\n");
	printf("\t  ---------------------------------------------------------------------------------\n");
	while (1) {
		printf("\n\n\t [ 1 ] Yes      [ 2 ] No    \n");
		printf("\n\t Enter 1 or 2 >  ");
		scanf("%d", &selection);
		rewind(stdin);
		if (selection != 1 && selection != 2)
		{
			printf("\t Invalid Number Please Try Again\n");
			continue;
		}
		total += selection;
		survey[indexNumber].survey[0] = selection;
		break;
	}
	printf("\n\n\t 2.  Besides the above, are you exhibiting any of symptoms listed below ?\n");
	printf("\t  ---------------------------------------------------------------------------------\n");
	printf("\t |                                                                                 |\n");
	printf("\t |              > Cough                        > Difficulty breathing              |\n");
	printf("\t |              > Loss of smell                > Loss of taste                     |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  ---------------------------------------------------------------------------------\n");
	while (1) {
		selection = 0;
		printf("\n\n\t [ 1 ] Yes      [ 2 ] No    \n");
		printf("\n\t Enter 1 or 2 >  ");
		scanf("%d", &selection);
		rewind(stdin);
		if (selection != 1 && selection != 2)
		{
			printf("\t Invalid Number Please Try Again\n");
			continue;
		}
		total += selection;
		survey[indexNumber].survey[1] = selection;
		break;
	}
	printf("\n\n\t 3.  Have you attended any event/areas associated with known COVID-19 cluster ?\n");
	while (1) {
		selection = 0;
		printf("\n\n\t [ 1 ] Yes      [ 2 ] No    \n");
		printf("\n\t Enter 1 or 2 >  ");
		scanf("%d", &selection);
		rewind(stdin);
		if (selection != 1 && selection != 2)
		{
			printf("\t Invalid Number Please Try Again\n");
			continue;
		}
		total += selection;
		survey[indexNumber].survey[2] = selection;
		break;
	}
	printf("\n\n\t 4.  Have you travelled to any country outside Malaysia within 14 days before onset of symptoms?\n");
	while (1) {
		selection = 0;
		printf("\n\n\t [ 1 ] Yes      [ 2 ] No    \n");
		printf("\n\t Enter 1 or 2 >  ");
		scanf("%d", &selection);
		rewind(stdin);
		if (selection != 1 && selection != 2)
		{
			printf("\t Invalid Number Please Try Again\n");
			continue;
		}
		total += selection;
		survey[indexNumber].survey[3] = selection;
		break;
	}
	printf("\n\n\t 5.  Have you had close contact to comfirmed or suspected case of Covid-19 within 14 days before onset of illness ?\n");
	while (1) {
		selection = 0;
		printf("\n\n\t [ 1 ] Yes      [ 2 ] No    \n");
		printf("\n\t Enter 1 or 2 >  ");
		scanf("%d", &selection);
		rewind(stdin);
		if (selection != 1 && selection != 2)
		{
			printf("\t Invalid Number Please Try Again\n");
			continue;
		}
		total += selection;
		survey[indexNumber].survey[4] = selection;
		break;
	}
	printf("\n\n\t 6.  Are you a MOH COVID-19 volunteer in the last 14 days?\n");
	while (1) {
		selection = 0;
		printf("\n\n\t [ 1 ] Yes      [ 2 ] No    \n");
		printf("\n\t Enter 1 or 2 >  ");
		scanf("%d", &selection);
		rewind(stdin);
		if (selection != 1 && selection != 2)
		{
			printf("\t Invalid Number Please Try Again\n");
			continue;
		}
		total += selection;
		survey[indexNumber].survey[5] = selection;
		break;
	}

	if (total > 10) {

		printf("\n\n\t  --------------------------------------------------------------------------------- \n");
		printf("\t |                                                                                 |\n");
		printf("\t | Health Status Level: < 10  Red Colour (High Risk) > 10  Green Colour (Low Risk) |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |                Your Health Status >  Green Colour ( Low Risk )                  |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |         Thank You For Your Response. Please Stay At Home And Stay Safe.         |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |    Have Any Uncomfortable Symptoms. Please Self-Quarantine For 14 Days Fisrt    |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  --------------------------------------------------------------------------------- \n");
	}
	else
	{
		printf("\n\n\t  --------------------------------------------------------------------------------- \n");
		printf("\t |                                                                                 |\n");
		printf("\t | Health Status Level: < 10  Red Colour (High Risk) > 10  Green Colour (Low Risk) |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |                  Your Health Status >  Red Colour ( High Risk )                 |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |              # You Must Stay At Home And Self-Quarantine For 14 Days            |\n");
		printf("\t |                                                                                 |\n");
		printf("\t |          Thank You For Your Response And Stay Healthy And Also Stay Safe.       |\n");
		printf("\t |                                                                                 |\n");
		printf("\t  --------------------------------------------------------------------------------- \n");
	}
	survey[indexNumber].userId = currentVisitorInfo.userId;
	writeHealthSurvey(survey, surveyCount);
	system("pause");
}

void checkUserHealthStatus() {
	SurveyDetails survey[100];
	int surveyCount = 0;
	surveyCount = readHealthSurvey(survey, surveyCount);

	displayUser();

	int choice;

	do {
		printf("\t Enter the target userID (-1 to leave) : ");
		scanf("%d", &choice);
		rewind(stdin);
		int indexNumber, flag = 0;
		for (int i = 0; i < surveyCount; i++) {
			if (choice == survey[i].userId) {
				indexNumber = i;
				flag = 1;
			}
		}
		if (flag == 1) {
			printf("\n\t User ID: %d\n", survey[indexNumber].userId);
			if (survey[indexNumber].survey[0] == 2) {
				printf("\t Symptom 1: No\n");
			}
			else {
				printf("\t Symptom 1: Yes\n");
			}
			if (survey[indexNumber].survey[1] == 2) {
				printf("\t Symptom 2: No\n");
			}
			else {
				printf("\t Symptom 2: Yes\n");
			}
			if (survey[indexNumber].survey[2] == 2) {
				printf("\t High Risk area: No\n");
			}
			else {
				printf("\t High Risk area: Yes\n");
			}
			if (survey[indexNumber].survey[3] == 2) {
				printf("\t Travel: No\n");
			}
			else {
				printf("\t Travel: Yes\n");
			}
			if (survey[indexNumber].survey[4] == 2) {
				printf("\t Close Contact: No\n");
			}
			else {
				printf("\t Close Contact: Yes\n");
			}
			if (survey[indexNumber].survey[5] == 2) {
				printf("\t MOH Volunteer: No\n");
			}
			else {
				printf("\t MOH Volunteer: Yes\n");
			}
		}
	} while (choice != -1);
	writeHealthSurvey(survey, surveyCount);
}

void displayHighRiskUser() {
	SurveyDetails survey[100];
	int surveyCount = 0;
	surveyCount = readHealthSurvey(survey, surveyCount);
	int total[100];
	for (int i = 0; i < surveyCount; i++) {
		total[i] = survey[i].survey[0] + survey[i].survey[1] + survey[i].survey[2] + survey[i].survey[3] + survey[i].survey[4] + survey[i].survey[5];
	}

	printf("\t +-----------+-------------+-------------+------------------+----------+-----------------+-----------------+ \n");
	printf("\t |  User ID  |  Symptom 1  |  Symptom 2  |  High Risk Area  |  Travel  |  Close Contact  |  MOH Volunteer  | \n");
	printf("\t +-----------+-------------+-------------+------------------+----------+-----------------+-----------------+ \n");
	for (int i = 0; i < surveyCount; i++) {
		if (total[i] < 10) {
			printf("\t |  %4d     | ", survey[i].userId);
			if (survey[i].survey[0] == 2) {
				printf("No          | ");
			}
			else {
				printf("Yes         | ");
			}
			if (survey[i].survey[1] == 2) {
				printf("No          | ");
			}
			else {
				printf("Yes         | ");
			}
			if (survey[i].survey[2] == 2) {
				printf("No               | ");
			}
			else {
				printf("Yes              | ");
			}
			if (survey[i].survey[3] == 2) {
				printf("No       | ");
			}
			else {
				printf("Yes      | ");
			}
			if (survey[i].survey[4] == 2) {
				printf("No              | ");
			}
			else {
				printf("Yes             | ");
			}
			if (survey[i].survey[5] == 2) {
				printf("No              |\n");
			}
			else {
				printf("Yes             |\n");
			}
			printf("\t +-----------+-------------+-------------+------------------+----------+-----------------+-----------------+ \n");
		}

	}

	writeHealthSurvey(survey, surveyCount);
}