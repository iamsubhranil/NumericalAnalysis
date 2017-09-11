#include "polynomial.h"
#include "utility.h"
#include <stdio.h>

int main(){
    printf("\n[Enter all polynomials as f(x)!]");
    printf("\nEnter first polynomial : ");
    char *buffer;
    readline(&buffer, stdin);
    Polynomial p1 = poly_parse(buffer, 'x');
    printf("\nEnter second polynomial : ");
    buffer = NULL;
    readline(&buffer, stdin);
    Polynomial p2 = poly_parse(buffer, 'x');
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
    printf("\nEnter another polynomial to replace each term of p1 with : ");
    buffer = NULL;
    readline(&buffer, stdin);
    Polynomial p = poly_parse(buffer, 'x');
    res = poly_replace(p1, p);
    printf("\nf(x) = ");
    poly_print(p1);
    printf("\nnewX = ");
    poly_print(p);
    printf("\nf(");
    poly_print(p);
    printf(") = ");
    poly_print(res);
    printf("\nEnter the value of x to evaluate p1 : ");
    double d;
    scanf("%lf", &d);
    printf("\nResult : %g", poly_eval(p1, d));
    printf("\n");
    return 0;
}
