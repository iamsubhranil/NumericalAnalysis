#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

typedef struct Poly{
    double coeff;
    int exp;
    struct Poly *next;
} Poly;
typedef Poly* Polynomial;

Polynomial poly_add(Polynomial a, Polynomial b); // Adds two polynomials
Polynomial poly_multiply(Polynomial a, Polynomial b); // Multiplies two polynomials
void poly_print(Polynomial a); // Prints a polynomial
Polynomial poly_dup(Polynomial a); // Duplicates one term pointed by the polynomial
Polynomial newPolynomial(double coeff, int exp); // Creates a new polynomial with given coefficient and exponent
void poly_concat(Polynomial a, Polynomial b); // Appends term b to expression a
double poly_eval(Polynomial a, double value); // Evaluate a polynomial based on the given value
Polynomial combination(int r); // Generates an nCr polynomial based on the given r, it can be later evaluated using poly_eval

#endif
