#include "fourier.h"

// Information retrieval

float getDfSpectre(Spectre* spect) {
    return spect->fs / spect->len;
}


// Padding assistance

int supBase2(int n) {
    return (int)pow(2., ceilf(log2f(n)));
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


static float complex* _constr_FFT(Sig* sig) {
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
    int p = supBase2(N) - N;

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


// Spectrogramms

int getIndexSpectrogramm(Spectrogramm* sg, int n, int p) {
    if (n<0 || n>=sg->n_len || p<0 || p>=sg->p_len)
        exit(EXIT_FAILURE);

    return n * sg->p_len + p;
}

float getValueSpectrogramm(Spectrogramm* sg, int n, int p) {
    return sg->s[getIndexSpectrogramm(sg, n, p)];
}

Spectrogramm* constructSpectrogramm(Sig* sig, int win_len, int hop) {
    if (win_len<1 || hop<1) exit(EXIT_FAILURE);

    int n_len = sig->len / hop;
    int p_len = supBase2(win_len);

    float* s = malloc(n_len * p_len * sizeof(float));
    Spectrogramm* sg = malloc(sizeof(Spectrogramm));
    sg->s = s;

    if (sg==NULL) exit(EXIT_FAILURE);
    
    sg->n_len = n_len;
    sg->p_len = p_len;
    sg->fs = sig->fs;
    sg->dt = hop/sig->fs;
    
    int n, p;
    for (n=0; n<n_len; n++) {
        Sig* extracted_sig = extractSig(sig, hop*n, win_len);
        Spectre* spect = computeFFT(extracted_sig);

        for (p=0; p<p_len; p++) {
            sg->s[getIndexSpectrogramm(sg, n, p)] = spect->s[p];
        }

        free(extracted_sig);
        free(spect);
    }

    return sg;
}

void printSpectrogramm(Spectrogramm* sg) {
    printf("Spectrogramm of size (n,p) = (%d,%d) :\n", sg->n_len, sg->p_len);
    int n, p;
    for (n=0; n<sg->n_len; n++) {
        printf("%d :", n);
        for (p=0; p<sg->p_len; p++) {
            printf(" %.0f", sg->s[getIndexSpectrogramm(sg, n, p)]);
        }
        printf("\n");
    }
}