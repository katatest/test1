#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "roman.h"

#define MAX_BUFF 64

// I
// V 5
// X 10
// L 50
// C 100
// D 500
// M 1000

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

static const char *hundreds_to_nume(int curr)
{
	char *res = malloc(sizeof(char) * MAX_BUFF);
	char *ptr = res;
	int count = 0;
    int extra = 0;

    int mid = 500;
    int scale = 100;

	snprintf(res, MAX_BUFF, "%d", curr);

	if(curr == mid) {
		res[0] = 'D';
		res[1] = '\0';
	} else if(curr > mid) {
        switch(curr) {
            case 900:
			    res[0] = 'C';
			    res[1] = 'M';
			    res[2] = '\0';
                break;
            default:
	            extra = curr - mid;
                int tot = extra / scale;
		        count = 1;
		        res[0] = 'D';
		        while(count <= tot) {
		        	res[count] = 'C';
                    count++;
		        }
                break;
        }
	} else if(curr < mid) {
        //int lscale = (4 * scale);
        switch(curr) {
            case 400:
			    res[0] = 'C';
			    res[1] = 'D';
			    res[2] = '\0';
                break;
            default:
			    count = 0;
                int tot = curr / scale;
			    while(count < tot) {
			    	res[count] = 'C';
                    count++;
			    }
                res[count] = '\0';
                break;
        }
	} else {
		res[0] = '\0';
	}

	return(ptr);
}

static const char *thousands_to_nume(int curr)
{
	char *res = malloc(sizeof(char) * MAX_BUFF);
	char *ptr = res;
	int count = 0;

    int scale = 1000;

	snprintf(res, MAX_BUFF, "%d", curr);

    count = 0;
    int tot = curr / scale;
    while(count < tot) {
        res[count] = 'M';
        count++;
    }
    res[count] = '\0';

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
	char *str_num = malloc(sizeof(char) * MAX_BUFF);
	char *r = NULL;
    int next = 0;
    int curr;

	snprintf(str_num, MAX_BUFF, "%d", num);

	char *ptr = &str_num[0];
	int count = 0;
	while(*ptr != '\0') {
		ptr++;
		count++;
	}
	if(count > 0) count--;

	curr = ((str_num[0] - '0') * pow(10, count));

    if(curr == 0) {
        return("\0");
    } else if(curr < 10) {
        r = strdup(singles_to_nume(curr));
    } else if(curr < 100) {
        r = strdup(tens_to_nume(curr));
    } else if(curr < 1000) {
        r = strdup(hundreds_to_nume(curr));
    } else if(curr >= 1000) {
        r = strdup(thousands_to_nume(curr));
    }

	next = num - curr;
    const char *n = strdup(int_to_nume(next));
    if(!realloc(r, (sizeof(r) + sizeof(n) + 1))) {
        exit(-1);
    }
    strcat(r, n);

    if(n != NULL) free((char *)n);
    if(str_num != NULL) free(str_num);

    return(r);
}

