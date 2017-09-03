#include "polynomial.h"
#include "diff.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "input.h"

int main(){
    
    double ** input = takeInput();
    if(input == NULL)
        return 1;
    
    int count = (int)input[2][0];
    double *arguments = input[0];
    double *entries = input[1];

    char einput[100], *rem;

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
