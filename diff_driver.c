#include "diff.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(){
    int * entries = NULL, temp = 0, **fdiff;
    char input[100], *remain = NULL;
    input[0] = 'a';
    printf("\nEnter the entries for f(x), enter 'e' to stop >\n");
    while(input[0] != 'e'){
        remain = NULL;
        printf("f(x%d) = ", temp);
        scanf("%s", input);
        if(input[0] == 'e')
            break;
        int value = strtoll(input, &remain, 10);
        if(strlen(remain) > 0){
            printf("\n[Error] Bad integer value %s!\n", input);
            continue;
        }
        entries = (int *)realloc(entries, sizeof(int) * ++temp);
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
