#include "polynomial.h"
#include <stdlib.h>
#include <stdio.h>

#include "fraction.h"

struct Frac{
    Polynomial numerator;
    Polynomial denominator;
};

struct Frac * frac_new(Polynomial n, Polynomial d){
    struct Frac * nf = (struct Frac *)malloc(sizeof(struct Frac));
    nf->numerator = n;
    nf->denominator = d;
    return nf;
}

double frac_eval(struct Frac *f, double value){
    double n = poly_eval(f->numerator, value);
    double d = poly_eval(f->denominator, value);
    return n/d;
}

void frac_print(struct Frac *f){
    printf("(");
    poly_print(f->numerator);
    printf(") / (");
    poly_print(f->denominator);
    printf(") ");
}

struct Frac * frac_dup(struct Frac *old){
    return frac_new(old->numerator, old->denominator);
}

struct Frac * frac_add(struct Frac * a, struct Frac *b){
    if(a == NULL && b == NULL)
        return frac_new(poly_constant(0), poly_constant(1));
    if(a == NULL)
        return frac_dup(b);
    else if(b == NULL)
        return frac_dup(a);

    struct Frac *ret = NULL;
    if(a->denominator == b->denominator){
        ret = frac_new(poly_add(a->numerator, b->numerator), a->denominator);
    }
    else{
        Polynomial n1 = poly_multiply(a->numerator, b->denominator);
        Polynomial n2 = poly_multiply(b->numerator, a->denominator);
        Polynomial n = poly_add(n1, n2);
        Polynomial d = poly_multiply(a->denominator, b->denominator);
        
        ret = frac_new(n, d);
    }

    return ret;
}

struct Frac * frac_multiply(struct Frac *a, struct Frac *b){
    return frac_new(poly_multiply(a->numerator, b->numerator), poly_multiply(a->denominator, b->denominator));
}
