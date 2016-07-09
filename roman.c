#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "roman.h"

#define MAX_BUFF 64

// I V X L C D M

static const char *singles_to_nume(int curr)
{
	//char res[MAX_BUFF];
	char *res = malloc(sizeof(char) * MAX_BUFF);
	char *ptr = res;
	int count = 0;
    int extra = 0;

    //printf("--- %s Enter\n", __func__);

	snprintf(res, MAX_BUFF, "%d", curr);

	if(curr == 5) {
		res[0] = 'V';
		res[1] = '\0';
	} else if(curr > 5) {
        switch(curr) {
            case 9:
			    res[0] = 'I';
			    res[1] = 'X';
			    res[2] = '\0';
                break;
            default:
	            extra = curr - 5;
		        res[0] = 'V';
                count++;
		        while(count <= extra) {
		        	res[count] = 'I';
                    count++;
		        }
                res[count] = '\0';
                break;
        }
	} else if(curr < 5) {
        switch(curr) {
            case 4:
			    res[0] = 'I';
			    res[1] = 'V';
			    res[2] = '\0';
                break;
            default:
			    count = 0;
			    while(count < curr) {
			    	res[count] = 'I';
                    count++;
			    }
                res[count] = '\0';
                break;
        }
	} else {
		res[0] = '\0';
	}

    //printf("--- %s Exit : %s\n", __func__, ptr);

	return(ptr);
}

static const char *tens_to_nume(int curr)
{
	char *res = malloc(sizeof(char) * MAX_BUFF);
	char *ptr = res;
	int count = 0;
    int extra = 0;

    //printf("--- %s Enter\n", __func__);

	snprintf(res, MAX_BUFF, "%d", curr);

	if(curr == 50) {
		res[0] = 'L';
		res[1] = '\0';
	} else if(curr > 50) {
        switch(curr) {
            case 90:
			    res[0] = 'X';
			    res[1] = 'C';
			    res[2] = '\0';
                break;
            default:
	            extra = curr - 50;
                int tot = extra / 10;
		        count = 1;
		        res[0] = 'L';
		        while(count <= tot) {
		        	res[count] = 'X';
                    count++;
		        }
                break;
        }
	} else if(curr < 50) {
        switch(curr) {
            case 40:
			    res[0] = 'X';
			    res[1] = 'L';
			    res[2] = '\0';
                break;
            default:
			    count = 0;
                int tot = curr / 10;
			    while(count < tot) {
			    	res[count] = 'X';
                    count++;
			    }
                res[count] = '\0';
                break;
        }
	} else {
		res[0] = '\0';
	}

    //printf("--- %s Exit : %s\n", __func__, ptr);

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

const char *int_to_nume(int num)
{
	char *string_num = malloc(sizeof(char) * MAX_BUFF);
	char *r = NULL;
    int next = 0;

    //printf("\n\n");

	snprintf(string_num, MAX_BUFF, "%d", num);

	char *ptr = &string_num[0];
	int count = 0;
	while(*ptr != '\0') {
		//printf("---> %s : %d\n", ptr, count);
		ptr++;
		count++;
	}
	if(count > 0) count--;
	//printf("-------> %d : %s\n", count, string_num);

	int current = ((string_num[0] - '0') * pow(10, count));
	//printf("Current --> %d : %d\n", current, count);

    if(current == 0) {
        return("\0");
    } else if(current < 10) {
        r = strdup(singles_to_nume(current));
        //printf("SINGLES -----> %s SIZE: %lu\n", r, sizeof(r));
    } else if(current < 100) {
        r = strdup(tens_to_nume(current));
        //printf("TENS --------> %s\n", r);
    }

	next = num - current;
    const char *n = strdup(int_to_nume(next));
    realloc(r, (sizeof(r) + sizeof(n) + 1));
    strcat(r, n);

    if(string_num != NULL) {
        free(string_num);
    }

    return(r);
}

