#include "visitExit.h"


void main() {

	/*============*/
	/* Admin List */
	/*============*/
	// List of admin account and details
	Admin adminList[30];

	/*=============*/
	/* Admin Count */
	/*=============*/
	// Count of the admin account
	int adminCount = 0;
	
	adminCount = readAdminFile(adminList, adminCount);
	readVisitExit();
	readVenInfo();
	sanitizeRead();
	readPersonalFile();


	switch (welcomePage()) {
	case 1:
		system("cls");
		visitorMain();
		break;
	case 2:
		system("cls");
		adminCount = adminMain(adminList, adminCount, sanitizeRecords, sanitizeUsers);
		break;
	default:
		system("cls");
		sanitizeFrontPage();
	}

	adminCount = writeAdminFile(adminList, adminCount);
	writeVisitExit();

	writeVenInfo();
	sanitizeWrite();
	writePersonalFile();
}


int welcomePage() {
	int choice;

	printf("\t                           T A R U C     S E J A H T E R A                            \n");
	printf("\t  --------------------------------------------------------------------------------- \n");
	printf("\t |                                                                                 |\n");
	printf("\t |                WELCOME TO TUNKU ABDUL RAHMAN UNIVERSITY COLLEGE                 |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |---------------------------------------------------------------------------------|\n");
	printf("\t |                                                                                 |\n");
	printf("\t |      Type of user:                                                              |\n");
	printf("\t |                                                                                 |\n");
	printf("\t |      1. Visitor                                                                 |\n");
	printf("\t |      2. Admin                                                                   |\n");
	printf("\t |      3. Sanitize Company Representative                                         |\n");
	printf("\t |                                                                                 |\n");
	printf("\t  --------------------------------------------------------------------------------- \n");

	do {
		printf("\t Who are you? > ");
		scanf("%d", &choice);
		if (choice < 1 || choice > 3) {
			printf("\t Invalid choice! Please try again.\n");
		}
	} while (choice < 1 || choice > 3);
	return choice;
}