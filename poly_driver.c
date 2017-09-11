#include "polynomial.h"
#include "utility.h"
#include <stdio.h>

int main(){
    Polynomial p1 = poly_new(3, 1);
    poly_concat(p1, poly_new(15, 0));

    Polynomial p2 = poly_new(-3, 0);
//    poly_concat(p2, poly_new(15, 0));

    printf("\nPolynomial 1 : ");
    poly_print(p1);
    printf("\nPolynomial 2 : ");
    poly_print(p2);

    Polynomial added = poly_add(p1, p2);
    printf("\np1 + p2 : ");
    poly_print(added);
    Polynomial muld = poly_multiply(p1, p2);
    printf("\np1 * p2 : ");
    poly_print(muld);
    printf("\n");
    Polynomial res = poly_pwrof(p1, 3);
    printf("\np1^3 : ");
    poly_print(res);
    printf("\n");
    Polynomial p = poly_new(3, 2);
    poly_concat(p, poly_new(2, 1));
    res = poly_replace(p1, p);
    printf("\nf(x) = ");
    poly_print(p1);
    printf("\nnewX = ");
    poly_print(p);
    printf("\nf(3x + 2) = ");
    poly_print(res);

    printf("\nEnter a polynomial : ");
    char *line = NULL;
    readline(&line, stdin);
    Polynomial convert = poly_parse(line, 'x');
    printf("\nParsed polynomial is : ");
    poly_print(convert);

    printf("\n");
    return 0;
}
