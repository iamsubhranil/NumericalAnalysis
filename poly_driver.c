#include "polynomial.h"
#include <stdio.h>

int main(){
    Poly * p1 = newPolynomial(10, 3);
    poly_concat(p1, newPolynomial(9, 1));
    poly_concat(p1, newPolynomial(15, 0));

    Poly * p2 = newPolynomial(15, 2);
    poly_concat(p2, newPolynomial(10, 1));
    poly_concat(p2, newPolynomial(13, 0));

    printf("\nPolynomial 1 : ");
    poly_print(p1);
    printf("\nPolynomial 2 : ");
    poly_print(p2);

    Poly * added = poly_add(p1, p2);
    printf("\np1 + p2 : ");
    poly_print(added);
    Poly * muld = poly_multiply(p1, p2);
    printf("\np1 * p2 : ");
    poly_print(muld);
    printf("\n");
    return 0;
}
