#ifndef DIFF_H
#define DIFF_H

int ** calculateDifference(int *entries, int elength);

void printTable(int *entries, int elength, int ** table, int type); // type : 0 => forward difference, 1 => backward difference

#endif
