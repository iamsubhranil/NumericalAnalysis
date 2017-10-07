// A very bad implementation of Gauss-Seidel's method on solution to a system of linear algebric equations

#include <math.h>
#include <stdio.h>

#define fx(y,z) ((1.0/12)*(23.78 + y - (2*z)))
#define fy(x,z) ((1.0/9)*(-20.23 - (2*x) + z))
#define fz(x,y) ((1.0/7)*(17.72 - x - (4*y)))

//#define fx(y,z) ((1.0/8)*(8 - (2*y) + (2*z)))
//#define fy(x,z) ((-1.0/8)*(-4 - x - (3*z)))
//#define fz(x,y) ((1.0/9)*(12 - (2*x) - y))

#define EPSILON 0.0001

int neq(double a, double b){
    //    printf("\nDiff between %f and %f is %f\n", a, b, fabs(a-b));
    if(fabs(a-b) > EPSILON)
        return 1;
    return 0;
}

void printdouble(double d, int isfinal){
    if(d < 0)
        printf("-");
    else
        printf(" ");
    if(d < 100)
        printf("0");
    if(d < 10)
        printf("0");

    printf("%3.4f",fabs(d));

    if(isfinal)
        printf("*\t");
    else
        printf("\t");
}

int main(){
    double table[1000][3];
    table[0][0] = table[0][1] = table[0][2] = 0;
    int i = 0;
    char c = 'n';

    printf("\n  i  \t    x    \t    y    \t    z    ");
    printf("\n=====\t=========\t=========\t=========");
    do{
        if(i > 0 && i % 100 == 0){
            printf("\n\n[Warning] Number of iterations is abnormally large! It is possible that the given system of equations does not converge to a solution!");
            printf("\n[Warning] However it is also possible that the given system of equations is solvable, but is not diagonally dominant, which in turn renders it insolvable by Gauss-Seidel's method.");
            printf("\n[Input] Do you want to continue (y/n) > ");
            scanf(" %c", &c);
            if(c != 'Y' && c != 'y')
                return 1;
        }
        i++;

        printf("\n%5d\t", i);

        if(i == 1 || neq(table[i-2][0], table[i-1][0])){
            table[i][0] = fx(table[i-1][1], table[i-1][2]);
            printdouble(table[i][0], 0);
        }
        else{
            table[i][0] = table[i-1][0];
            printdouble(table[i][0], 1);
        }

        if(i == 1 || neq(table[i-2][1], table[i-1][1])){
            table[i][1] = fy(table[i-1][0], table[i-1][2]);
            printdouble(table[i][1], 0);
        }
        else{
            table[i][1] = table[i-1][1];
            printdouble(table[i][1], 1);
        }

        if(i == 1 || neq(table[i-2][2], table[i-1][2])){
            table[i][2] = fz(table[i-1][0], table[i-1][1]);
            printdouble(table[i][2], 0);
        }
        else{
            table[i][2] = table[i-1][2];
            printdouble(table[i][2], 1);
        }

    }
    while(neq(table[i-1][0], table[i][0])
            || neq(table[i-1][1], table[i][1])
            || neq(table[i-1][2], table[i][2]));

    printf("\n\nSolution to the given system of equations is : \nx = %3.4f\ny = %3.4f\nz = %3.4f\n", table[i][0], table[i][1], table[i][2]);
    return 0;
}
