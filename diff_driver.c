#include "diff.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(){
    double * entries = NULL, **fdiff;
    int temp = 0;
    char input[100], *remain = NULL;
    input[0] = 'a';
    printf("\nEnter the entries for f(x), enter 'e' to stop >\n");
    while(input[0] != 'e'){
        remain = NULL;
        printf("f(x%d) = ", temp);
        scanf("%s", input);
        if(input[0] == 'e')
            break;
        double value = strtold(input, &remain);
        if(strlen(remain) > 0){
            printf("\n[Error] Bad entry %s!\n", input);
            continue;
        }
        entries = (double *)realloc(entries, sizeof(double) * ++temp);
        entries[temp - 1] = value;
    }
    fdiff = calculateDifference(entries, temp);
    if(fdiff == NULL)
        return 1;
    printTable(entries, temp, fdiff, 0);
    printf("\n\n");
    printTable(entries, temp, fdiff, 1);
    printf("\n");
    return 0;
}
