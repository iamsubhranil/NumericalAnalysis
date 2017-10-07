#include <stdio.h>

#define numVar 3

double pmat[numVar][numVar + 1] = {{8,2,-2,8},
                                    {1,-8,3,-4},
                                    {2,1,9,12}};

void printMatrix(){
    int i, j;
    for(i = 0;i < numVar;i++){
        for(j = 0;j < (numVar + 1);j++){
            printf(" %g ", pmat[i][j]);
        }
        printf("\n");
    }
}

void manipulateRow(int rowNum){
    int colNum = 0;
    printf("\nOperating row : %d", (rowNum + 1));
    while(colNum < rowNum){
        printf("\n\tElement : %d( = %g)", colNum + 1, pmat[rowNum][colNum]);
        printf("\n\t\tPrinciple diagonal element : %g", pmat[colNum][colNum]);
        double multiplier = -(pmat[rowNum][colNum] / pmat[colNum][colNum]);
        printf("\n\t\tMultiplier : %g\n\t\t", multiplier);
        int i = 0;
        while(i < (numVar + 1)){
            printf("%g -> ", pmat[rowNum][i]);
            if(i == colNum)
                pmat[rowNum][i] = 0;
            else
                pmat[rowNum][i] = (multiplier*pmat[colNum][i]) + pmat[rowNum][i];
            printf("%g, ", pmat[rowNum][i]);
            i++;
        }
        colNum++;
    }
}

int main(){
    int i = 1;
    printf("\nGiven pivotted matrix : \n");
    printMatrix();
    while(i < numVar){
        manipulateRow(i);
        i++;
    }
    printf("\n");
    printf("\nGenerated solution matrix : \n");
    printMatrix();
    double solution[numVar];
    for(i = numVar - 1;i >= 0;i--){
        double rhs = pmat[i][numVar]; // constant
        int nextel = i + 1;
        while(nextel < numVar){ // backtracking
            rhs -= (pmat[i][nextel] * solution[nextel]);
            nextel++;
        }
        solution[i] = rhs/pmat[i][i];
    }
    printf("\nSolution to the given system of equations : \n");
    for(i = 0;i < numVar;i++){
        printf("x%d = %.4f\n", i, solution[i]);
    }
}
