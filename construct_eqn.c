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
    Polynomial n = poly_new((double)1/h, 1);
    poly_concat(n, poly_new(-(arguments[0]/h), 0));

    double ** difftable = calculateDifference(entries, count);
    int temp = 0;

    Polynomial result = poly_new(entries[0], 0);
    while(temp < (count - 1)){
        Polynomial comb = poly_comb(temp + 1);
        comb = poly_replace(comb, n);
        comb = poly_multiply(comb, poly_new(difftable[temp][0], 0));
        result = poly_add(result, comb);
        temp++;
    }
    printf("\nGenerated equation from the given dataset is : ");
    poly_print(result);

    while(1){
        printf("\nEnter the value of x : ");
        scanf("%s", einput);
        rem = NULL;
        double v = strtold(einput, &rem);
        if(strlen(rem) > 0){
            printf("\n[Error] Not a valid numeric value : %s", einput);
            continue;
        }
        if(v < arguments[0] || v > arguments[count - 1]){
            printf("\n[Error] Value of x must be interpolated between %g and %g!", arguments[0], arguments[count -1]);
            continue;
        }
        int temp = 0;
        while(temp < count){
            if(arguments[temp] == v){
                printf("\n[Error] Value of x must be non-tabulated!");
                break;
            }
            temp++;
        }
        if(temp != count)
            continue;

        double res = poly_eval(result, v);
        printf("\nf(%g) = %g\n", v, res);
        break;
    }
    return 0;
}
