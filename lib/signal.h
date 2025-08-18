#ifndef SIGNAL_INCLUDED_CHECK
#define SIGNAL_INCLUDED_CHECK

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI acosf(-1)

typedef struct {
    int len;
    float fs;
    float s[];
} Sig;

Sig* emptySig(int len, float fs);
Sig* initSig(int len, float fs, float fun(float));
Sig* zeroSig(int len, float fs);
Sig* sinSig(int len, float fs, float amp, float freq, float phi);
Sig* harmonicSig(int len, float fs, int nb_harmonics, float fond_freq, float amp[], float phi[]);

Sig* addSig(Sig* s, Sig* r);
Sig* multSig(Sig* sig, Sig* window);
Sig* convolutionSig(Sig* sig, Sig* window);

Sig* extractSig(Sig* sig, int start_index, int extract_length);

Sig* reverseSig(Sig* sig);

void printSig(Sig *sig);

#include "signal.c"
#endif