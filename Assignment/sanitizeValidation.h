#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#pragma warning(disable:6091)
#pragma warning(disable:4996)

/*=====================*/
/* Sanitize Validation */
/* By: Khoon Hong      */
/*=====================*/
// This header file contains function for sanitize validation.


/*======================*/
/* Function Declaration */
/*======================*/
int validTimeHr(int num);
int validTimeMin(int num);
int validDate(int day, int month, int year);
int validPhone(char* str);
int validFax(char* str);
int validEmail(char* str);
int validPersonInCharge(char* str);
int validVenueCompName(char* str); // Validate company name & venue name
int validRegNo(char* str);
int validCity(char* str);
int validState(char* str);
int validCountry(char* str);
int validStreet(char* str);

// Function will return 1 as valid input, return 0 as invalid input

/*==================*/
/* Check Input Hour */
/*==================*/
int validTimeHr(int num)
{
	if (num > -1 && num < 24)
	{
		return 1;
	}
	return 0;
}


/*====================*/
/* Check Input Minute */
/*====================*/
int validTimeMin(int num)
{
	if (num > -1 && num < 60)
	{
		return 1;
	}
	return 0;
}


/*==================*/
/* Check Input Date */
/*==================*/
int validDate(int day, int month, int year)
{
	//check year
	if (year >= 1900 && year <= 9999)
	{
		//check month
		if (month >= 1 && month <= 12)
		{
			//check days
			if ((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
			{
				return 1;
			}
			else if ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11))
			{
				return 1;
			}
			else if ((day >= 1 && day <= 28) && (month == 2))
			{
				return 1;
			}
			else if (day == 29 && month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
			{
				return 1;
			}
			else
			{
				return 0; // Day is invalid
			}
		}
		else
		{
			return 0; // Month is invalid
		}
	}
	else
	{
		return 0; // Year is invalid
	}
}


/*=======================*/
/* Check Input Phone No. */
/*=======================*/
int validPhone(char* str)
{
	if (isNotEmpty(str))
	{
		if (!(containSpace(str)))
		{
			if (isInteger(str))
			{
				if (str[0] == '0') // Check if phone no. starts with '0'
				{
					if (strlen(str) < 12 && strlen(str) > 9) // Check length of phone no.
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

/*=====================*/
/* Check Input Fax No. */
/*=====================*/
int validFax(char* str)
{
	if (isNotEmpty(str))
	{
		if (!(containSpace(str)))
		{
			if (isInteger(str))
			{
				if (str[0] == '0')
				{
					if (strlen(str) == 9)
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


/*====================*/
/* Check Input E-mail */
/*====================*/
int validEmail(char* str)
{
	char string[100];
	char front[50] = "", back[50] = "";
	int flag = 0;
	strcpy(string, str); // Copy email from parameter to variable

	for (int i = 0; i < strlen(string); i++) // Check for '@'
	{
		if (string[i] == '@')
		{
			flag = 1; // '@' is found
			break;
		}
	}

	if (flag == 0) // '@' is not found
	{
		return 0;
	}

	// Extract the first token (split string)
	int counter = 0;
	char* token;
	char* rest = string;
	while (token = strtok_s(rest, "@", &rest))
	{
		if (!(counter)) // extract email prefix
		{
			sprintf(front, "%s", token);
			counter++;
		}
		else // extract email domain
		{
			sprintf(back, "%s", token);
		}
	}

	if (!(isalnum(front[strlen(front) - 1])) || !(isalnum(front[0])))
	{
		return 0;
	}

	// Check email prefix format
	for (int i = 0; i < strlen(front); i++)
	{
		if (!(isalnum(front[i]) == 0) || front[i] == '_' || front[i] == '-' || front[i] == '.')
		{
			continue;
		}
		else
		{
			return 0;
		}
	}
	for (int x = 0; x < strlen(front) - 1; x++)
	{
		if (front[x] == '_' || front[x] == '-' || front[x] == '.')
		{
			if ((front[x] == front[x + 1]) || !(isalnum(front[x + 1]))) // Check for double occurance of '_' , '-' , '.'
			{
				return 0;
			}
		}
	}

	char domain[20] = "";
	// Split email domain into two parts
	flag = 0;

	if (back[strlen(back)-1] == '.')
	{
		return 0;
	}

	for (int i = 0; i < strlen(back); i++) // Check for '.'
	{
		if (back[i] == '.')
		{
			flag = 1;
		}
	}
	if (flag == 0)
	{
		return 0;
	}

	char* token1;
	char* rest1 = back;
	while ((token1 = strtok_s(rest1, ".", &rest1))) // extract email domain into parts
	{
		strcpy(domain, token1);
		if (strlen(domain) <= 1) // Domain must have at least 2 char
		{
			return 0;
		}
		for (int i = 0; i < strlen(domain); i++)
		{
			if (!(isalnum(back[i]) == 0) || domain[i] == '-') // check if domain char is alnum or dash
			{
				continue;
			}
			else
			{
				return 0;
			}
		}
	}
	return 1;
}

/*======================*/
/* Check Input Password */
/*======================*/
int validPassword(char* str)
{
	if (strlen(str) >= 8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*===================================*/
/* Check Input Person-In-Charge Name */
/*===================================*/
int validPersonInCharge(char* str)
{
	if (isNotEmpty(str))
	{
		if (isAlphabet(str))
		{
			return 1;
		}
	}
	return 0;
}


/*===================================*/
/* Check Input Venue or Company Name */
/*===================================*/
int validVenueCompName(char* str)
{
	if (isNotEmpty(str))
	{
		return 1;
	}
	return 0;
}


/*===============================*/
/* Check Input Registeration No. */
/*===============================*/
int validRegNo(char* str)
{
	if (isNotEmpty(str))
	{
		if (!(containSpace(str)))
		{
			if (isInteger(str))
			{
				return 1;
			}
		}
	}
	return 0;
}


/*==================*/
/* Check Input City */
/*==================*/
int validCity(char* str)
{
	if (isNotEmpty(str))
	{
		return 1;
	}
	return 0;
}


/*===================*/
/* Check Input State */
/*===================*/
int validState(char* str)
{
	if (isNotEmpty(str))
	{
		return 1;
	}
	return 0;
}


/*=====================*/
/* Check Input Country */
/*=====================*/
int validCountry(char* str)
{
	if (isNotEmpty(str))
	{
		if (!(isInteger(str)))
		{
			return 1;
		}
	}
	return 0;
}


/*====================*/
/* Check Input Street */
/*====================*/
int validStreet(char* str)
{
	if (isNotEmpty(str))
	{
		return 1;
	}
	return 0;
}