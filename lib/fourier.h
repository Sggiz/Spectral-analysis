#ifndef FOURIER_INCLUDED_CHECK
#define FOURIER_INCLUDED_CHECK

#include <stdlib.h>
#include <math.h>
#include <complex.h>

#include "signal.h"

typedef Sig Spectre;

typedef struct {
    int n_len; // width : number of spectres (of transformed windows)
    int p_len; // height : number of frequencies (common to all spectres)
    float fs; // entry signal's sampling frequency
    float dt; // time difference between two spectres (hop/fs)
    float* s; // s of len n*p
} Spectrogramm;

float getDfSpectre(Spectre* spect);

int supBase2(int n);

Spectre* computeNaiveFourier(Sig* sig);
Spectre* computeFFT(Sig* sig);

int getIndexSpectrogramm(Spectrogramm* sg, int n, int p);
float getValueSpectrogramm(Spectrogramm* sh, int n, int p);

Spectrogramm* constructSpectrogramm(Sig* sig, int win_len, int hop);

void printSpectrogramm(Spectrogramm* sg);

#include "fourier.c"
#endif