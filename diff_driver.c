#include "diff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

int main(){
    double ** input = takeInput(1);
    if(input==NULL)
        return 1;
    double * entries = input[1], **fdiff;
    int temp = (int)input[2][0];
    
    fdiff = calculateDifference(entries, temp);
    if(fdiff == NULL)
        return 1;
    printTable(entries, temp, fdiff, 0);
    printf("\n\n");
    printTable(entries, temp, fdiff, 1);
    printf("\n");
    return 0;
}
