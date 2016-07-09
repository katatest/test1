#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "roman.h"

#define MAX_BUFF 64

// I V X L C D M


static char *handle_singles(int curr, char big, char little)
{
	char res[MAX_BUFF];
	char *ptr = res;
	int count;

	snprintf(res, MAX_BUFF, "%d", curr);

	if(curr == 5) {
		res[0] = big;
		res[1] = '\0';
	} else if(curr > 5) {
		int extra = curr - 5;
		count = 1;
		res[0] = big;
		while(count <= extra) {
			res[count] = little;
		}
	} else if(curr < 5) {
		if(curr == 4) {
			res[0] = little;
			res[1] = big;
			res[2] = '\0';
		} else {
			int extra = 5 - curr;
			count = 0;
			while(count < extra) {
				res[1] = big;
			}
		}
	} else {
		res[0] = '\0';
	}

	return(ptr);
}

void radd(char *first, char *second)
{
	printf("%s : %s\n", first, second);
}

void rsubtract(void)
{
	printf("SUBTRACTING....\n");
}

int nume_to_int(char *nume)
{
	return(5);
}

char *int_to_nume(int num)
{
	char *string_num = malloc(sizeof(char) * MAX_BUFF);
	char res[MAX_BUFF];
	char *r = res;
	snprintf(string_num, MAX_BUFF, "%d", num);

	res[0] = '\0';

	char *ptr = &string_num[0];
	int count = 0;
	while(*ptr != '\0') {
		printf("---> %s : %d\n", ptr, count);
		ptr++;
		count++;
	}
	if(count > 0) count--;
	printf("-------> %d : %s\n", count, string_num);

	int current = ((string_num[0] - '0') * pow(10, count));
	printf("Current --> %d : %d\n", current, count);

	if(current == 0) {
		res[0] = '\0';
	} else if(current <= 9) {
		//handle_singles(current);
		handle_singles(current, 'V', 'I');
	} else if(current <= 49) {
		handle_singles(current, 'X', 'V');
	} else if(current <= 99) {
		//handle_hundreds(current);
		handle_singles(current, 'V', 'I');
	} else if(current <= 499) {
		//handle_fivehundreds(current);
		handle_singles(current, 'V', 'I');
	} else if(current <= 999) {
		//handle_thousands(current);
		handle_singles(current, 'V', 'I');
	} else if(current > 999) {
	} else {
		res[0] = '\0';
	}

	int next = num - current;
	printf("----------> %d\n", next);

	if(count > 0) {
		printf("%s\n", int_to_nume(next));
	}

	return(r);
}

