#include "polynomial.h"
#include "diff.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

int main(){
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
        return 1;
    }
    if(checkDiff(arguments, count)){
        printf("\n[Error] Please enter equidistant arguments!\n");
        return 2;
    }

    double h = arguments[1] - arguments[0];
    Polynomial n = newPolynomial((double)1/h, 1);
    poly_concat(n, newPolynomial(-(arguments[0]/h), 0));

    double ** difftable = calculateDifference(entries, count);
    int temp = 0;

    Polynomial result = newPolynomial(entries[0], 0);
    while(temp < (count - 1)){
        Polynomial comb = poly_comb(temp + 1);
        comb = poly_replace(comb, n);
        comb = poly_multiply(comb, newPolynomial(difftable[temp][0], 0));
        result = poly_add(result, comb);
        temp++;
    }
    printf("\nGenerated equation from the given dataset is : ");
    poly_print(result);
    printf("\n");
    return 0;
}