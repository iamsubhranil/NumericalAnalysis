#include <malloc.h>
#include "polynomial.h"

struct Poly{
    double coeff;
    int exp;
    struct Poly *next;
};

struct Poly * poly_new(double coeff, int exp){
    struct Poly * p = (struct Poly *)malloc(sizeof(struct Poly));
    p->coeff = coeff;
    p->exp = exp;
    p->next = NULL;
    return p;
}

struct Poly * poly_dup(struct Poly * p){
    return poly_new(p->coeff, p->exp);
}

void poly_concat(struct Poly * root, struct Poly * newP){
    while(root->next!=NULL && root->exp > newP->exp)
        root = root->next;
    if(root->exp == newP->exp)
        root->coeff += newP->coeff;
    else{
        newP->next = root->next;
        root->next = newP;
    }
}

double pwrof(double a, int exp){
    double ret = 1;
    while(exp > 0){
        ret *= a;
        exp--;
    }
    return ret;
}

double poly_eval(struct Poly * root, double value){
    double ret = 0;
    while(root!=NULL){
        ret += (root->coeff)*pwrof(value, root->exp);
        root = root->next;
    }
    return ret;
}

static void printTerm(double coeff, int exp, int *isfirst){ 
    if(coeff == 0)
        return;

    if(coeff < 0){
        printf(" - ");
        coeff = -coeff;
    }
    else if(*isfirst==0)
        printf(" + ");

    *isfirst = 0;

    if(coeff != 1 || exp == 0)
        printf("%g", coeff);
    if(exp > 0){
        printf("x");
        if(exp > 1)
            printf("%d", exp);
    }
}

void poly_print(struct Poly * head){
    if(head==NULL){
        printf("0");
        return;
    }
    int isfirst = 1;
    printTerm(head->coeff, head->exp, &isfirst);
    struct Poly * prev = head;
    head = head->next;
    while(head != NULL){
        printTerm(head->coeff, head->exp, &isfirst);
        prev = head;
        head = head->next;
    }
}

static void addToList(struct Poly * *head, struct Poly * *prev, struct Poly * toAdd){
    if(*head == NULL){
        (*head) = toAdd;
    }
    else
        (*prev)->next = toAdd;
    (*prev) = toAdd;
}

struct Poly * poly_add(struct Poly * a, struct Poly * b){
    struct Poly * result = NULL, *prev = NULL;

    if(a == NULL && b == NULL)
        return poly_new(0, 0);
    else if(a == NULL)
        return poly_dup(b);
    else if(b == NULL)
        return poly_dup(a);

    while((a!=NULL && b!=NULL) && (a->exp != b->exp)){
        struct Poly * high;
        if(a->exp > b->exp){
            high = poly_dup(a);
        }
        else
            high = poly_dup(b);

        addToList(&result, &prev, high);

        if(a->exp > b->exp)
            a = a->next;
        else
            b = b->next;

    }
    while(a!=NULL && b!=NULL){
        struct Poly * newP = poly_new(a->coeff + b->coeff, a->exp);
        addToList(&result, &prev, newP);
        a = a->next;
        b = b->next;
    }
    while(a != NULL || b != NULL){
        struct Poly * add;
        if(a){
            add = poly_dup(a);
            a = a->next;
        }
        else{
            add = poly_dup(b);
            b = b->next;
        }
        addToList(&result, &prev, add);
    }
    return result;
}

struct Poly * poly_multiply(struct Poly * a, struct Poly * b){
    if(a==NULL || b==NULL)
        return poly_new(0, 0);

    if(b->next == NULL){
        struct Poly * ret = NULL;
        struct Poly * temp = NULL;
        while(a!=NULL){
            addToList(&ret, &temp, poly_new(a->coeff * b->coeff, a->exp + b->exp));
            a = a->next;
        }
        return ret;
    }
    else{
        struct Poly * result = poly_new(0, 0);
        while(b != NULL){
            struct Poly * tmp = poly_dup(b);
            tmp->next = NULL;
            struct Poly * back = poly_multiply(a, tmp);
            result = poly_add(result, back);
            b = b->next;
        }
        return result;
    }
}

long fact(long r){
    if(r==0 || r==1)
        return 1;
    return r*fact(r-1);
}

struct Poly * poly_comb(int r){
    if(r==0)
        return poly_new(1, 0);
    struct Poly * first = poly_new((double)1/fact(r), 1);
    int t = 1;
    while(t < r){
        struct Poly * n = poly_new(1, 1);
        poly_concat(n, poly_new(-t, 0));
        first = poly_multiply(first, n);
        t++;
    }
    return first;
}

struct Poly * poly_pwrof(struct Poly * a, int exp){
    struct Poly * result = poly_new(1, 0);
    while(exp-->0)
        result = poly_multiply(result, a);
    return result;
}

struct Poly * poly_replace(struct Poly * old, struct Poly * newP){
    if(old == NULL || newP == NULL)
        return NULL;

    struct Poly * result = poly_new(0, 0);

    while(old != NULL){
        result = poly_add(result, poly_multiply(poly_new(old->coeff, 0), poly_pwrof(newP, old->exp)));
        old = old->next;
    }
    return result;
}
