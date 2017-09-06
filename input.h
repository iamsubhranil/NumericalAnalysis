#ifndef INPUT_H
#define INPUT_H

double ** takeInput();

// Mode 1 : Take value toward the front of the argument table
// Mode 2 :  ""    ""    ""    ""  rear "" ""     ""      ""
// Mode 3 :  ""    ""    ""    "" middle " ""     ""      ""
// Mode 0 : Take any value as input
double getInterpolatedValue(double *arguments, int count, int mode);

#endif
