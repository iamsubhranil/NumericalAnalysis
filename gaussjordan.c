#include <stdio.h>
#include <math.h>

#define numVar 4

double pmat[numVar][numVar + 1] = {{10, -7, 3, 5, 6},
                                    {5, -9, -2, 4, 7},
                                    {3, 1, 4, 11, 2},
                                    {-6, 8, -1, -4, 5}};

void printMatrix(){
    int i, j;
    for(i = 0;i < numVar;i++){
        for(j = 0;j < (numVar + 1);j++){
            printf(" %g ", pmat[i][j]);
        }
        printf("\n");
    }
}

void manipulateRow(int rowNum, int colNum){
    printf("\nOperating row : %d", (rowNum + 1));
    while(colNum < rowNum
            || (colNum > rowNum && colNum < numVar)){
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
    int i = 0;
    printf("\nGiven pivotted matrix : \n");
    printMatrix();
    while(i < numVar){
        manipulateRow(i, 0);
        i++;
    }
    i = 0;
    while(i < numVar){
        manipulateRow(i, i+1);
        i++;
    }
    printf("\n");
    printf("\nGenerated solution matrix : \n");
    printMatrix();
    double solution[numVar];
    for(i = numVar - 1;i >= 0;i--){
        solution[i] = pmat[i][numVar]/pmat[i][i];
    }
    printf("\nSolution to the given system of equations : \n");
    for(i = 0;i < numVar;i++){
        printf("x%d = %.4f\n", i, solution[i]);
    }
}
