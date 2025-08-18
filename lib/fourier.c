#include "fourier.h"

// Information retrieval

float getDfSpectre(Spectre* spect) {
    return spect->fs / spect->len;
}


// Fourier transforms

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


float complex* _constr_FFT(Sig* sig) {
    // Ensure sig's length is of the form N = 2^b
    int N = sig->len;

    float complex* spect = malloc(N * sizeof(float complex));
    
    if (spect==NULL) exit(EXIT_FAILURE);

    if (N==1) {
        spect[0] = sig->s[0];
        return spect;
    }

    float complex omega = cexpf(-2*PI/N * I);

    Sig* sig_even = emptySig(N/2, 0.);
    Sig* sig_odd = emptySig(N/2, 0.);

    int i;
    for (i=0; i<N/2; i++) {
        sig_even->s[i] = sig->s[2*i];
        sig_odd->s[i] = sig->s[2*i + 1];
    }

    float complex* spect_even = _constr_FFT(sig_even);
    float complex* spect_odd = _constr_FFT(sig_odd);

    int k;
    for (k=0; k<N; k++) {
        spect[k] = 
            spect_even[k % (N/2)] 
            + cpowf(omega, k) * spect_odd[k % (N/2)];
    }

    free(spect_even);
    free(spect_odd);

    return spect;
}

Spectre* computeFFT(Sig* sig) {
    Sig* padded_sig = NULL;

    int N = sig->len;
    int b = ceilf(log2f(N));
    int p = (int)pow(2., b) - N;

    if (p==0) padded_sig = sig;
    else {
        padded_sig = paddingSig(sig, p);
    }

    float complex* complex_spectre = _constr_FFT(padded_sig);

    Spectre* spect = emptySig(N + p, sig->fs);
    int k;
    for (k=0; k<N+p; k++) {
        spect->s[k] = cabsf(complex_spectre[k]);
    }

    free(complex_spectre);

    return spect;
}