#include "plotting.h"

void scaledPlottingSig(Sig* sig) {

    char buffer[NB_PIXELS];

    int p;
    for (p=0; p<NB_PIXELS; p++) {
        buffer[p]= ' ';
    }

    float max = maxSig(sig), min = minSig(sig);

    int i;
    for (i=0; i<sig->len; i++) {
        int x = (int)(WIN_WIDTH * i/sig->len);
        int y = WIN_HEIGHT-1 -(int)(WIN_HEIGHT * (sig->s[i] - min)/(max-min));

        if  (0<=x && x<WIN_WIDTH && 0<=y && y<WIN_HEIGHT)
            buffer[y*WIN_WIDTH + x] = plotting_char;
    }

    printf("Signal (%d) plotting : min - %.2f --- %.2f - max\n",
        sig->len, min, max);
    
    for (p=0; p<NB_PIXELS; p++) {
        putchar(buffer[p]);

        if (p % WIN_WIDTH == WIN_WIDTH-1)
            putchar('\n');
    }
}

void directPlottingSig(Sig* sig) {
    char* buffer = malloc(WIN_HEIGHT * sig->len * sizeof(char));

    if (buffer==NULL) exit(EXIT_FAILURE);

    int p;
    for (p=0; p<WIN_HEIGHT*sig->len; p++) {
        buffer[p] = ' ';
    }

    float max = maxSig(sig), min = minSig(sig);

    int i;
    for (i=0; i<sig->len; i++) {
        int y = WIN_HEIGHT-1 -(int)(WIN_HEIGHT * (sig->s[i] - min)/(max-min));

        if  (0<=y && y<WIN_HEIGHT)
            buffer[y*sig->len + i] = plotting_char;
    }

    printf("Signal (%d) plotting : min - %.2f --- %.2f - max\n",
        sig->len, min, max);
    
    for (p=0; p<WIN_HEIGHT*sig->len; p++) {
        putchar(buffer[p]);

        if (p % sig->len == sig->len-1)
            putchar('\n');
    }

    free(buffer);
}