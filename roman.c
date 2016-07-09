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

static const char *singles_to_nume(int curr);
static const char *tens_to_nume(int curr);
static const char *hundreds_to_nume(int curr);
static const char *thousands_to_nume(int curr);
static int nume_to_int(char *nume);
static const char *int_to_nume(int num);

/**
 * Convert an integer under 10 to it's roman numeral representation.
 *
 * NOTE: There's an obvious pattern in the next four functions.
 * Refactor into a single function?  Doing it the dumb way for the
 * time being.
 */
static const char *singles_to_nume(int curr)
{
    char *res = malloc(sizeof(char) * MAX_BUFF);
    char *ptr = res;
    int count = 0;
    int extra = 0;

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

/**
 * Convert integer with a multiple of 10 and under 100
 * to roman numeral string.
 */
static const char *tens_to_nume(int curr)
{
    char *res = malloc(sizeof(char) * MAX_BUFF);
    char *ptr = res;
    int count = 0;
    int extra = 0;

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
                res[count] = '\0';
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

    return(ptr);
}

/**
 * Convert integer with a multiple of 100 and under 1000
 * to roman numeral string.
 *
 * TODO: These functions could probably all be refactored into a single one.
 * We have a mid point and scale happening in each.
 */
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

/*
 * Convert integer with multiple of 1000 to roman numeral string.
 */
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

/**
 * Helper function to convert a roman numeral string to an integer value.
 */
static int nume_to_int(char *nume)
{
    int i = 0;
    int total = 0;

    while(i < strlen(nume)) {
        switch(nume[i]) {
            case 'I':
                if(nume[i + 1] == 'V') {
                    total = total + 4;
                    i++;
                } else if(nume[i + 1] == 'X') {
                    total = total + 9;
                    i++;
                } else {
                    total++;
                }
                break;
            case 'V':
                total = total + 5;
                break;
            case 'X':
                if(nume[i + 1] == 'L') {
                    total = total + 40;
                    i++;
                } else if(nume[i + 1] == 'C') {
                    total = total + 90;
                    i++;
                } else {
                    total = total + 10;
                }
                break;
            case 'L':
                total = total + 50;
                break;
            case 'C':
                if(nume[i + 1] == 'D') {
                    total = total + 400;
                    i++;
                } else if(nume[i + 1] == 'M') {
                    total = total + 900;
                    i++;
                } else {
                    total = total + 100;
                }
                break;
            case 'D':
                total = total + 500;
                break;
            case 'M':
                total = total + 1000;
                break;
            default:
                return(-1);
                break;
        }
        i++;
    }
    return(total);
}

/**
 * Helper function to convert an integer to a roman numeral string.
 *
 * Basically this handles each column of the original integer
 * independently and then aggregates the final string together
 * recursively.  Thousands, then hundreds, then tens, then singles.
 */
static const char *int_to_nume(int num)
{
    char *str_num = malloc(sizeof(char) * MAX_BUFF);
    char *numeral = NULL;
    int curr = 0;
    int next = 0;
	int count = 0;
	const char *rem;

	/* Count number of digits */
    snprintf(str_num, MAX_BUFF, "%d", num);
	count = strlen(str_num) - 1;

	/* Isolate current column. i.e. 100's or 10's */
    curr = ((str_num[0] - '0') * pow(10, count));

	/* Convert current column to string numeral */
    if(curr == 0) {
        return("\0");
    } else if(curr < 10) {
        numeral = strdup(singles_to_nume(curr));
    } else if(curr < 100) {
        numeral = strdup(tens_to_nume(curr));
    } else if(curr < 1000) {
        numeral = strdup(hundreds_to_nume(curr));
    } else if(curr >= 1000) {
        numeral = strdup(thousands_to_nume(curr));
    }

	/* Integer remainder for next call. */
    next = num - curr;

	/* Not tail recursing, but assuming our numbers aren't ridiculous.
		Get the remainder of the romain numeral string. */
    rem = strdup(int_to_nume(next));

	/* Resize numeral and concatenate remainder */
    if(!realloc(numeral, (sizeof(numeral) + sizeof(rem) + 1))) {
        exit(-1);
    }
    strcat(numeral, rem);

    if(rem != NULL) free((char *)rem);
    if(str_num != NULL) free(str_num);

    return(numeral);
}

/**
 * Add two roman numeral strings together.
 *
 * Returns: Pointer to string with resultant roman numeral.
 */
const char *radd(char *first, char *second)
{
    int one, two, total;

    one = nume_to_int(first);
    two = nume_to_int(second);
    total = one + two;

    /* Roman numerals cannot represent zero or negative values! */
    if(one == -1 || two == -1) {
        return("Error: Non-roman numerals present");
    } else if(total == 0) {
        return("Error: No Zeros");
    }

    return(int_to_nume(total));
}

/**
 * Subtract a roman numeral string from another roman numeral string.
 *
 * Usage: Subtract second from first.
 *
 * Returns: Pointer to string with resultant roman numeral.
 */
const char *rsubtract(char *first, char *second)
{
    int one, two, total;

    one = nume_to_int(first);
    two = nume_to_int(second);
    total = one - two;

    /* Roman numerals cannot represent zero or negative values! */
    if(one == -1 || two == -1) {
        return("Error: Non-roman numerals present");
    } else if(two > one) {
        return("Error: No Negatives");
    } else if(total == 0) {
        return("Error: No Zeros");
    }

    return(int_to_nume(total));
}
