#ifndef SIGNAL_INCLUDED_CHECK
#define SIGNAL_INCLUDED_CHECK

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592

typedef struct {
    int len;
    float s[];
} Sig;

Sig* emptySig(int len);
Sig* initSig(int len, float fun(int));
Sig* emptySig(int len);
Sig* initSig(int len, float fun(int)); 
Sig* zeroSig(int len);
Sig* sinSig(int len, float amp, float omega, float phi);

Sig* addSig(Sig* s, Sig* r);
Sig* multSig(Sig* sig, Sig* window);

void printSig(Sig *sig);

#include "signal.c"
#endif