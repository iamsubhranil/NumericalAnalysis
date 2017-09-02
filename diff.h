#ifndef DIFF_H
#define DIFF_H

double ** calculateDifference(double *entries, int elength);

void printTable(double *entries, int elength, double ** table, int type); // type : 0 => forward difference, 1 => backward difference

#endif
