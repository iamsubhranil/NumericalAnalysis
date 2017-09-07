#include "polynomial.h"
#include "fraction.h"
#include "input.h"
#include <stdio.h>

int main(){
    double ** table = takeInput(0);
    if(table == NULL)
        return 1;

    double *arguments = table[0];
    double *entries = table[1];
    int count = (int)table[2][0];

    Polynomial matrix[count][count];
    int row, column;
    for(row = 0;row < count;row++){
        for(column = 0;column < count;column++){
            Polynomial x;
            if(row == column){
                x = poly_new(1, 1);
                poly_concat(x, poly_constant(-arguments[column]));
            }
            else
                x = poly_constant(arguments[row] - arguments[column]);

            matrix[row][column] = x;
        }
    }

    /*for(row = 0;row < count;row++){
        for(column = 0;column < count;column++){
            poly_print(matrix[row][column]);
            printf(" ");
        }
        printf("\n");
    }
    */

    Polynomial row_product[count];

    for(row = 0;row < count;row++){
        Polynomial result = matrix[row][0];
        for(column = 1;column < count;column++)
            result = poly_multiply(result, matrix[row][column]);

        row_product[row] = result;
    }

    /*printf("\nRow product : ");
    for(row = 0;row < count;row++){
        poly_print(row_product[row]);
        printf("\n");
    }
    */

    Polynomial wx = poly_new(1, 0);
    for(row = 0;row < count;row++){
        Polynomial now = poly_new(1, 1);
        poly_concat(now, poly_constant(-arguments[row]));
        wx = poly_multiply(wx, now);
    }

    Fraction yrdr[count];

    for(row = 0;row < count;row++){
        yrdr[row] = frac_new(poly_constant(entries[row]), row_product[row]);
    }

    double value = getInterpolatedValue(arguments, count, 0);
    double wxr = poly_eval(wx, value), add = 0;
    for(row = 0;row < count;row++)
        add += frac_eval(yrdr[row], value);
    double res = add*wxr;
    printf("\nf(%g) : %g\n", value, res);

    return 0;
}
