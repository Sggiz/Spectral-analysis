#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lib/signal.h"

int main() {
    Sig *sig0 = sinSig(12, 1, 5., 0., PI/2);
    Sig *sig1 = sinSig(19, 1, 1., 0.1, PI/2);
    float amp[] = {5,3,1}, omega[] = {1,2,3}, phi[] = {0, 0, PI};
    Sig *sig2 = harmonicSig(20, 100, 3, amp, omega, phi);

    Sig *test_signal = multSig(sig0, sig1);

    printSig(test_signal);
    printSig(reverseSig(test_signal));
    printSig(sig2);

    return 0;
}