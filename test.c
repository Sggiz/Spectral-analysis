#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lib/signal.h"
#include "lib/fourier.h"

int main() {
    Sig *sig0 = sinSig(12, 1, 5., 0., PI/2);
    Sig *sig1 = sinSig(10, 10, 1., 4, 0);
    float freq = 1., amp[]={0.5,5,3,1}, phi[]={PI/2,0,0, PI};
    Sig *sig2 = harmonicSig(100, 100, 4, freq, amp, phi);

    printSig(computeNaiveFourier(sig2));
    printSig(computeFFT(sig2));

    free(sig0);
    free(sig1);
    free(sig2);

    return 0;
}