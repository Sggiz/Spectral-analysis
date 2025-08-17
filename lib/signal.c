#include "signal.h"

// Initialisation functions

Sig* emptySig(int len) {
    Sig *sig = malloc(sizeof(sig) + len * sizeof(*sig->s));
    sig->len = len;
    return sig;
}

Sig* initSig(int len, float fun(int)) {
    Sig *sig = emptySig(len);
    int i;
    for (i=0; i<len; i++) {
        sig->s[i] = fun(i);
    }
    return sig;
}

Sig* zeroSig(int len) {
    Sig *sig = emptySig(len);
    int i;
    for (i=0; i<len; i++) {
        sig->s[i] = 0.f;
    }
    return sig;
}

Sig* sinSig(int len, float amp, float omega, float phi) {
    Sig *sig = emptySig(len);
    int i;
    for (i=0; i<len; i++) {
        sig->s[i] = amp * sinf( omega * i + phi);
    }
    return sig;
}


// Signal interactions

Sig* addSig(Sig* s, Sig* r) {
    int max_len = fmax(s->len, r->len);
    Sig *sig = emptySig(max_len);

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
    int max_len = fmax(sig->len, window->len);
    int min_len = fmin(sig->len, window->len);
    Sig *new_sig = emptySig(max_len);

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


// Windowing

Sig* extractSig(Sig* sig, int start_index, int extract_length) {
    Sig *new_sig = emptySig(extract_length);

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


// Printing

void printSig(Sig *sig) {
    printf("Signal with length %d :\n", sig->len);
    int i;
    for (i=0; i<sig->len; i++) {
        printf("%.2f ", sig->s[i]);
    }
    printf("\n");
}