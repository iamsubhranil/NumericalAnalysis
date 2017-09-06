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

    double v = getInterpolatedValue(arguments, count, 0);

    double res = poly_eval(result, v);
    printf("\nf(%g) = %g\n", v, res);

    return 0;
}
