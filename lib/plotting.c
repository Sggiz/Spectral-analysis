#include "plotting.h"

void plotSig(Sig* sig) {
    printf("Signal (%d) plotting\n", sig->len);

    char buffer[NB_PIXELS];

    int i;
    for (i=0; i<NB_PIXELS; i++) {
        buffer[i]= ' ';
    }

    float max = maxSig(sig), min = minSig(sig);

    for (i=0; i<sig->len; i++) {
        int x = (int)(WIN_WIDTH * i/sig->len);
        int y = WIN_HEIGHT-1 -(int)(WIN_HEIGHT * (sig->s[i] - min)/(max-min));

        if  (0<=x && x<WIN_WIDTH && 0<=y && y<WIN_HEIGHT)
            buffer[y*WIN_WIDTH + x] = plotting_char;
    }

    for (i=0; i<NB_PIXELS; i++) {
        putchar(buffer[i]);

        if (i % WIN_WIDTH == WIN_WIDTH-1)
            putchar('\n');
    }
}