#ifndef FRACTION_H
#define FRACTION_H

#include "polynomial.h"

typedef struct Frac* Fraction;

Fraction frac_new(Polynomial numerator, Polynomial denominator);
double frac_eval(Fraction f, double value);
Fraction frac_add(Fraction a, Fraction b);
Fraction frac_multiply(Fraction a, Fraction b);
void frac_print(Fraction a);
Fraction frac_dup(Fraction old);

#endif
