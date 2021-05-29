#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../includes/requetes.h"

#define MAX_DATE 6

// Cette fonction convertit une chaine de caractère au format M/D en une date
Date convert_md_to_date(char s_date[MAX_DATE]) {
	Date d;
	char* tmp = NULL;
	tmp = strtok(s_date, "/");
	d.month = atoi(tmp);
	tmp = strtok(NULL, " ");
	d.day = atoi(tmp);

	return d;
}
