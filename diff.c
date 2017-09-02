#include <stdio.h>
#include <malloc.h>

#include "diff.h"

double ** calculateDifference(double *entries, int length){
    if(length < 2){
        printf("\n[Error:Fwd] Atleast two entries are required to calculate the difference!");
        return NULL;
    }

    double ** table = (double **)malloc(sizeof(double *) * (length - 1));
    int prevCount = length, i = 0;
    double *array = entries;
    while(prevCount > 1){
        prevCount--;
        table[i] = (double *)malloc(sizeof(double) * prevCount);
        int temp = 0;
        while(temp < prevCount){
            table[i][temp] = array[temp + 1] - array[temp];
            temp++;
        }
        array = table[i];
        i++;
    }
    return table;
}

void printTable(double *entries, int elength, double ** table, int type){
    int numDiff = elength - 1,  temp = 0, temp1 = 0;
    printf("\n         ");
    while(temp < numDiff){
        if(type == 0) // Forward difference
            printf(" .%2d    ", (temp + 1));
        else // Backward difference
            printf(" \\'/%2d  ", (temp + 1));
        temp++;
    }
    temp = 0;
    printf("\n   y     ");
    while(temp < numDiff){
        if(type == 0) // Forward difference
            printf("/_\\  y  ");
        else // Backward differnce
            printf("  ' y   ");
        temp++;
    }
    printf("\n=======  ");
    temp = 0;
    while(temp < numDiff){
        printf("======  ");
        temp++;
    }
    while(temp1 < elength){
        printf("\n%7g  ", entries[temp1]);
        temp = 0;
        while(temp < numDiff){
            int len = elength - temp - 1;
            if(len > temp1)
                printf("%6g  ", table[temp][temp1]);
            temp++;
        }
        temp1++;
    }
}
