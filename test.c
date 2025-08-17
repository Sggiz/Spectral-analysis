#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lib/signal.h"

int main() {
    Sig *sig0 = sinSig(12, 5., 0., PI/2);
    Sig *sig1 = sinSig(19, 1., 0.1, PI/2);

    Sig *test_signal = windowSig(sig0, sig1);

    printSig(sig1);
    printSig(test_signal);

    return 0;
}