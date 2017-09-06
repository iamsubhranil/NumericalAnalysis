#include "input.h"
#include "polynomial.h"
#include "diff.h"
#include <stdio.h>

static long fact(int i){
    if(i==0 || i==1)
        return 1;
    return i*fact(i-1);
}

int main(){
    printf("\nNewton's Forward Interpolation");
    printf("\n==============================\n");
    double ** input = takeInput(1);
    if(input == NULL)
        return 1;

    double *arguments = input[0];
    double *entries = input[1];
    int count = (int)input[2][0];

    double ** difftable = calculateDifference(entries, count);
    double h = arguments[1] - arguments[0];
    Polynomial u = poly_new((double)1/h, 1); //x/h
    poly_concat(u, poly_new(-(double)arguments[0]/h, 0)); //-x0/h
    Polynomial result = poly_new(entries[0], 0); //y0
    int temp = 1;
    while(temp < count){
        Polynomial co = poly_new(1, 0);
        co = poly_multiply(co, u);
        int t = 1;
        while(t < temp){
            Polynomial present = poly_add(u, poly_new(-t, 0)); // u(u-1)(u-2) 
            co = poly_multiply(co, present);
            t++;
        }
        double df = difftable[temp - 1][0]/fact(temp); // del(y0)/ r!
        co = poly_multiply(co, poly_new(df, 0)); // u(u-1)(u-2)*del(y0)/r!
        result = poly_add(result, co);
        temp++;
    }

    double value = getInterpolatedValue(arguments, count, 1);
    double res = poly_eval(result, value);
    printf("\nf(%g) : %g\n", value, res);
    return 0;
}
