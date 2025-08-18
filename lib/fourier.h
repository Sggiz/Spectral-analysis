#ifndef FOURIER_INCLUDED_CHECK
#define FOURIER_INCLUDED_CHECK

#include <stdlib.h>
#include <math.h>
#include <complex.h>

#include "signal.h"

typedef Sig Spectre;

float getDfSpectre(Spectre* spect);
Spectre* formatSpectre(Spectre* spect, int sig_len);

Spectre* computeNaiveFourier(Sig* sig);


#include "fourier.c"
#endif