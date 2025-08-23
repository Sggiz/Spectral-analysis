#ifndef PLOTTING_INCLUDED_CHECK
#define PLOTTING_INCLUDED_CHECK

#include <stdio.h>
#include <stdlib.h>

#include "signal.h"

#define WIN_WIDTH 140
#define WIN_HEIGHT 20
#define NB_PIXELS WIN_HEIGHT  * WIN_WIDTH

char plotting_char = '#';

void plotSig(Sig* sig);


#include "plotting.c"
#endif