#include "signal.h"

// Initialisation functions

Sig* emptySig(int len, float fs) {
    Sig *sig = malloc(sizeof(sig) + len * sizeof(*sig->s));

    if (sig==NULL) exit(EXIT_FAILURE);

    sig->len = len;
    sig->fs = fs;
    return sig;
}

Sig* initSig(int len, float fs, float fun(float)) {
    Sig *sig = emptySig(len, fs);
    int i;
    for (i=0; i<len; i++) {
        sig->s[i] = fun(i/fs);
    }
    return sig;
}

Sig* zeroSig(int len, float fs) {
    Sig *sig = emptySig(len, fs);
    int i;
    for (i=0; i<len; i++) {
        sig->s[i] = 0.f;
    }
    return sig;
}

Sig* sinSig(int len, float fs, float amp, float freq, float phi) {
    Sig *sig = emptySig(len, fs);
    int i;
    for (i=0; i<len; i++) {
        sig->s[i] = amp * sinf( 2*PI*freq * i/fs + phi );
    }
    return sig;
}

Sig* harmonicSig(int len, float fs, int nb_harmonics, float fond_freq, float amp[], float phi[]) {
    Sig *sig = zeroSig(len, fs);
    int p, i;
    for (i=0; i<len; i++) {
        for (p=0; p<nb_harmonics; p++) {
            sig->s[i] += amp[p] * sinf( 2*PI*fond_freq*p * i/fs + phi[p] );
        }
    }
    return sig;
}


// Information retrieval

int getTruncatedLength(Sig* sig) {
    int N = sig->len;
    while (N>0 && sig->s[N-1] == 0) {
        N--;
    }
    return N;
}


// Signal interactions

Sig* addSig(Sig* s, Sig* r) {
    if (s->fs != r->fs) exit(EXIT_FAILURE);

    int max_len = fmax(s->len, r->len);
    Sig *sig = emptySig(max_len, s->fs);

    int i;
    for (i=0; i<max_len; i++) {
        if (i < s->len) {
            sig->s[i] = s->s[i];
        }
        else {
            sig->s[i] = 0.f;
        }

        if (i < r->len) {
            sig->s[i] += r->s[i];
        }
    }

    return sig;
}

Sig* multSig(Sig*  sig, Sig* window) {
    if (sig->fs != window->fs) exit(EXIT_FAILURE);

    int max_len = fmax(sig->len, window->len);
    int min_len = fmin(sig->len, window->len);
    Sig *new_sig = emptySig(max_len, sig->fs);

    int i;
    for (i=0; i<max_len; i++) {
        if (i < min_len) {
            new_sig->s[i] = sig->s[i] * window->s[i];
        }
        else {
            new_sig->s[i] = 0.f;
        }
    }

    return new_sig;
}

Sig* convolutionSig(Sig* sig, Sig* window) {
    if (sig->fs != window->fs) exit(EXIT_FAILURE);
    
    int max_len = fmax(sig->len, window->len);
    Sig *new_sig = emptySig(max_len, sig->fs);

    int i;
    for (i=0; i<max_len; i++) {
        if (i < sig->len && (max_len - 1 - i) < window->len) {
            new_sig->s[i] = sig->s[i] * window->s[max_len - 1 - i];
        }
        else {
            new_sig->s[i] = 0.f;
        }
    }

    return new_sig;
}


// Windowing

Sig* extractSig(Sig* sig, int start_index, int extract_length) {
    Sig *new_sig = emptySig(extract_length, sig->fs);

    int i;
    for (i=start_index; i<start_index+extract_length; i++) {
        if (i < sig->len) {
            new_sig->s[i] = sig->s[i];
        }
        else {
            new_sig->s[i] = 0.f;
        }
    }

    return new_sig;
}

// Basic transformations

Sig* reverseSig(Sig* sig) {
    Sig *new_sig = emptySig(sig->len, sig->fs);

    int i;
    for (i=0; i<sig->len; i++) {
        new_sig->s[i] = sig->s[ sig->len - 1 - i ];
    }

    return new_sig;
}

Sig* paddingSig(Sig* sig, int p) {
    int len = sig->len + p;
    Sig* padded_sig = emptySig(len, sig->fs);

    int i;
    for (i=0; i<sig->len; i++) {
        padded_sig->s[i] = sig->s[i];
    }
    for (i=sig->len; i<len; i++) {
        padded_sig->s[i] = 0.;
    }

    return padded_sig;
}


// Printing

void printSig(Sig *sig) {
    printf("Signal with length %d and fs=%.0f:\n", sig->len, sig->fs);
    int i;
    for (i=0; i<sig->len; i++) {
        printf("%.2f ", sig->s[i]);
    }
    printf("\n");
}