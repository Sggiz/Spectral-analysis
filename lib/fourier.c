#include "fourier.h"

float getDfSpectre(Spectre* spect) {
    return spect->fs / spect->len;
}


Spectre* computeNaiveFourier(Sig* sig) {
    Spectre* spect = emptySig(sig->len, sig->fs);

    int k, i;
    for (k=0; k<sig->len; k++) {
        float complex c_spect_k = 0;

        for (i=0; i<sig->len; i++) {
            c_spect_k += sig->s[i] * cexpf((-2*PI*k*i)/sig->len * I);
        }

        spect->s[k] = cabsf(c_spect_k);
    }

    return spect;
}