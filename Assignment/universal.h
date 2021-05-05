
/*========================*/
/* Check Alphabet Number */
/*=======================*/
// The string passed inside should only contain alphabet and number only!
// Calling method: isalphanumber(str);
int isAlphaNumber(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		if (isalnum(str[i]) == 0 && str[i] != ' ') {
			return 0;
		}
	}
	return 1;
}


/*===============*/
/* Check Integer */
/*===============*/
// The string should be integer
// Calling method: isinteger(str);
int isInteger(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		if (isdigit(str[i]) == 0 && str[i] != ' ') {
			return 0;
		}
	}
	return 1;
}



/*================*/
/* Check Alphabet */
/*================*/
// The string should have alphabet only.
// Calling method: isalphabet(str);
int isAlphabet(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		if (isalpha(str[i]) == 0 && str[i] != ' ') {
			return 0;
		}
	}
	return 1;
}


/*====================*/
/* Check Float Dobule */
/*====================*/
// The string should be formatted as float and double format only
// Calling method: isFloatDouble(str);
int isFloatDouble(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '.') {
			continue;
		}
		else if (isdigit(str[i])) {
			continue;
		}
		else {
			return 0;
		}
	}
	return 1;
}


/*===========================*/
/* Check String Availability */
/*===========================*/
// The string should not empty 
// Calling method: isNotEmpty(str);
int isNotEmpty(char str[]) {
	if (str[0] == '\0') {
		return 0;
	}
	else {
		return 1;
	}
}



/*=====================*/
/* Check Contain Space */
/*=====================*/
// Return 1 if str contain space, return 0 if str does not contain space
// Calling method: containSpace(str);
int containSpace(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ' ') {
			return 1;
		}
	}
	return 0;
}



/*==============*/
/* Lower String */
/*==============*/
// It will change the original string passed into the parameter to all lowercases
// Calling method: char anyvariable[50] = lowerString(str);
char* lowerString(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		str[i] = tolower(str[i]);
	}
	return str;
}

/*==============*/
/* Upper String */
/*==============*/
// It will change the original string passed into the parameter to all lowercases
// Calling method: char anyvariable[50] = lowerString(str);
char* upperString(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		str[i] = toupper(str[i]);
	}
	return str;
}



/*=======================*/
/* Get Current Date Time */
/*=======================*/
// Load the current date and time into the structure array
// Calling method: DateTime currentDateTime = getCurrentDateTime();
DateTime getCurrentDateTime() {

	time_t now;
	time(&now);
	struct tm* local = localtime(&now);

	// Save local time and date into the variable
	DateTime currentDateTime;
	currentDateTime.hour = local->tm_hour;
	currentDateTime.min = local->tm_min;
	currentDateTime.sec = local->tm_sec;

	currentDateTime.day = local->tm_mday;
	int month = local->tm_mon +1;
	currentDateTime.intMonth = local->tm_mon + 1;
	currentDateTime.year = local->tm_year + 1900;

	switch (month) {
	case 1: // January
		strcpy(currentDateTime.month, "JAN");
		break;
	case 2: // February
		strcpy(currentDateTime.month, "FEB");
		break;
	case 3: // March
		strcpy(currentDateTime.month, "MAR");
		break;
	case 4: // April
		strcpy(currentDateTime.month, "APR");
		break;
	case 5: // May
		strcpy(currentDateTime.month, "MAY");
		break;
	case 6: // June
		strcpy(currentDateTime.month, "JUN");
		break;
	case 7: // July
		strcpy(currentDateTime.month, "JUL");
		break;
	case 8: // August
		strcpy(currentDateTime.month, "AUG");
		break;
	case 9: // September
		strcpy(currentDateTime.month, "SEP");
		break;
	case 10: // October
		strcpy(currentDateTime.month, "OCT");
		break;
	case 11: // November
		strcpy(currentDateTime.month, "NOV");
		break;
	default: // December
		strcpy(currentDateTime.month, "DEC");
		break;
	}
	return currentDateTime;
}

