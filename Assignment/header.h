
#pragma warning(disable:4996)
#pragma warning(disable:6091)

/* Main Function Declaration */
int welcomePage();

/*=====================*/
/* Date Time structure */
/*=====================*/
// 1. Day 
// 2. Month 
// 3. Year 
// 4. Hour 
// 5. Min 
// 6. Sec
typedef struct {
	char month[4];
	int day, year, hour, min, sec, intMonth;
}DateTime;

/*======================*/
/* Function Declaration */
/*======================*/
int isAlphaNumber(char str[]);
int isInteger(char str[]);
int isAlphabet(char str[]);
int isFloatDouble(char str[]);
int isNotEmpty(char str[]);
int containSpace(char str[]);
char* lowerString(char str[]);
DateTime getCurrentDateTime();
char* upperString(char str[]);


/*=================*/
/* Admin Structure */
/*=================*/
// 1. Username
// 2. Password
// 3. First Name
// 4. Last Name
// 5. Department
// 6. Position
// 7. Last Login Date and Time
/* Admin Structure */
typedef struct {
	char username[21], password[41], first_name[21], last_name[21], department[31],
		position[31], contact[12];
	int adminId;
	DateTime lastlogin;
}Admin;

/* Admin Function Declaration */
int adminMain(Admin* adminList, int adminCount);
int readAdminFile(Admin* adminList, int adminCount);
int writeAdminFile(Admin* adminList, int adminCount);
int adminLogin(Admin* adminList, int adminCount, char currentUsername[]);
int displayAdminMenu();
void displayAnnouncementSubMenu();
void displayAdminSubMenu(Admin* adminList, int* adminCount, char currentUsername[]);
void displayAdminProfile(Admin* adminList, int adminCount, char currentUsername[]);
void modifyAdmin(Admin* adminList, int adminCount);
int modifyAdminMenu();
void listAdmin(Admin* adminList, int adminCount);
void deleteAdmin(Admin* adminList, int adminCount, char currentUsername[]);
int addAdmin(Admin* adminList, int adminCount);
void modifyAnnouncement();
void showAnnouncement();
void adminSearchConditions(int condition[7]);
void searchAdmin(Admin* adminList, int adminCount);
void printAdminSearchResult(Admin* filteredList, int rowRecords);



/* Visitor Structure */
typedef struct {

	char userName[50],
		firstName[30],
		lastName[50],
		phoneNum[12],
		state[20],
		icNum[13],
		password[9],
		gender;

	int userId;

}Visitor;

typedef struct {

	char userName[50],
		firstName[30],
		lastName[50],
		phoneNum[12],
		state[20],
		icNum[13],
		password[9],
		gender;

	int userId;
}visitor;

/* Visitor Function Declaration */
visitor visitorList[100];
int visitorCount = 0;
char visitorName[50];
visitor currentVisitorInfo;
void readPersonalFile();
void writePersonalFile();
void tarucMenu();
void login();
void registerVisitor();
int userSearchConditions(int condition[8]);
void searchUser();
void displayUser();
void printUserSearchResult(visitor* filteredList, int rowRecords);
int aftLoginMenu();
void personalAccount();
void edit();
void deleteAcc();
void exitTaruc();
void healthSurvey();
void displayHighRiskUser();
void checkUserHealthStatus();
int visitorMenu();


/* Venue Function Declaration */
void writeVenInfo();
void readVenInfo();
void searchVenInfo();
int displayVenInfo();
int menu();
void modVenInfo();
void setVenAvail();
void setVenueAvail(char* name);
void checkVenAvail();
void addVenue();
void venueMain();
int getVenName(char name[]);
void delVenInfo();
void venueAdminMenu();
int venInfoCount = 0;

typedef struct {
	int openHours;
	int openMin;
	int closeHours;
	int closeMin;
	char nameVen[30];
	int maxCap;
	int currentCap;
	int venAvail;
	char category[30];
	char incharge[40];
} venue;
venue ven[50];



/* Visit Exit Structure */
typedef struct {
	int visitId;
	Visitor visitorInfo;
	char venueName[30];
	float temperature;
	char symptoms;
	DateTime visit;
	DateTime exit;
}VisitExitInfo;

/* Visit Exit Function Declaration */
void readVisitExit();
void writeVisitExit();
void visitExitMenu();
int displayMenu(int userId, char currentName[], char currentIcNo[], char currentPhoneNumber[]);
void visitVenue(int userId, char currentName[], char currentIcNo[], char currentPhoneNumber[]);
void exitVenue(int userId);
void searchVisitExit(int userId);
void displaySearchResults(VisitExitInfo searchList[50], int records);
void history(int userId);
void modifyVisitExit();
void report();
void adminSearch();
void visitExitMain(int userId, char currentName[], char currentIcNo[], char currentPhoneNumber[]);

/* Sanitization Function Declaration */
void sanitizeCheckIn(), sanitizeCheckOut(), sanitizeBook(); // Done
void sanitizeRead(), sanitizeWrite(); // Done
void sanitizeAdminDisplay(), sanitizeUserDisplay(); // Done
void sanitizeAdminAccDisplay(), sanitizeUserAccDisplay(); // Done
void sanitizeSummary(); // Done
void sanitizeRecordDelete(), sanitizeUserDelete(); // Done 
void sanitizeSearch(), sanitizeSearchMenu(); // Done
void sanitizeFilter(), sanitizeFilterMenu(); // Done
void sanitizeAdminRecordModify(), sanitizeAdminRecMod();
void sanitizeAdminUserModify(), sanitizeAdminUserMod();
void sanitizeUserAccModify(), sanitizeUserAccMod();
void sanitizeUserRecModify(), sanitizeUserRecMod();
void sanitizeRowLine(int casesCount, int arr[]); // Done
void sanitizeAdminMenu(); // Done
void sanitizeUser(), sanitizeUserMenu(); // Done
int diffDays(int day, int month, int year); // Done
int subDiffDays(int x); // Done
void sanitizeFrontPage(); // Done
int sanitizeLogin(); // Done
void sanitizeSignUp(); // Done