#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

int checkDiff(double *arguments, int length){
    double cd = arguments[1] - arguments[0], ncd = 0;
    int temp = 2;
    while(temp < length){
        ncd = arguments[temp] - arguments[temp - 1];
        if(ncd != cd)
            return 1;
        temp++;
    }
    return 0;
}

double ** takeInput(){
    double *entries = NULL, *arguments = NULL;
    int count  = 0;
    char ainput[100], einput[100], *rem;
    printf("\nEnter each entry in the form `argument (space) entry`, enter e when done :");
    ainput[0] = 'a';
    while(1){
        printf("\nx%d f(x%d) = ", count, count);
        scanf("%s", ainput);
        if(ainput[0] == 'e')
            break;
        scanf("%s", einput);
        double avalue = strtold(ainput, &rem);
        if(strlen(rem) > 0){
            printf("\n[Error] Bad argument %s!", ainput);
            continue;
        }
        double evalue = strtold(einput, &rem);
        if(strlen(rem) > 0){
            printf("\n[Error] Bad entry %s!", einput);
            continue;
        }
        entries = (double *)realloc(entries, sizeof(double) * ++count);
        arguments = (double *)realloc(arguments, sizeof(double) * count);
        entries[count - 1] = evalue;
        arguments[count -1] = avalue;
    }
    if(count < 3){
        printf("\n[Error] Please enter atleast 3 argument entry pair!");
        return NULL;
    }
    if(checkDiff(arguments, count)){
        printf("\n[Error] Please enter equidistant arguments!\n");
        return NULL;
    }
    double ** argentry = (double **)malloc(sizeof(double *) * 3);
    argentry[0] = arguments;
    argentry[1] = entries;
    argentry[2] = (double *)malloc(sizeof(double));
    argentry[2][0] = count;
    return argentry;
}

double getInterpolatedValue(double *arguments, int count){
    char *rem, einput[100];
    double value = 0;
    while(1){
        printf("\nEnter the value of x : ");
        scanf("%s", einput);
        rem = NULL;
        value = strtold(einput, &rem);
        if(strlen(rem) > 0){
            printf("\n[Error] Not a valid numeric value : %s", einput);
            continue;
        }
        if(value < arguments[0] || value > arguments[count - 1]){
            printf("\n[Error] Value of x must be interpolated between %g and %g!", arguments[0], arguments[count -1]);
            continue;
        }
        int temp = 0;
        while(temp < count){
            if(arguments[temp] == value){
                printf("\n[Error] Value of x must be non-tabulated!");
                break;
            }
            temp++;
        }
        if(temp != count)
            continue;
    }
    return value;
}