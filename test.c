#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lib/signal.h"
#include "lib/fourier.h"
#include "lib/plotting.h"

int main() {
    Sig *sig0 = sinSig(12, 1, 5., 0., PI/2);
    Sig *sig1 = sinSig(30, 10, 1., 4, 0);

    float freq = 1., amp[]={0.5,5,3,1}, phi[]={PI/2,0,0, PI};
    Sig *sig2 = harmonicSig(128, 100, 4, freq, amp, phi);

    Spectre* F_sig2 = NULL;
    // F_sig2 = computeNaiveFourier(sig2);
    F_sig2 = computeFFT(sig2);

    printSig(F_sig2);

    Spectrogramm* SG_sig2 = constructSpectrogramm(sig2, 10
        , 5);
    printSpectrogramm(SG_sig2);

    printf("\n\n");

    plotSig(sig0);
    plotSig(sig1);
    plotSig(sig2);
    plotSig(F_sig2);

    free(sig0);
    free(sig1);
    free(sig2);
    free(F_sig2);
    
    free(SG_sig2->s);
    free(SG_sig2);

    return 0;
}