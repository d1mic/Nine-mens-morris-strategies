#ifndef ALPHABETA_H
#define ALPHABETA_H

int max(int tabla[24], int alpha, int beta, int potez[3], int poslednjiPotezPozitivnog,
        int poslednjiPotezNegativnog, int dubina, int brojPoteza, int koef[19]);
int min(int tabla[24], int alpha, int beta, int poslednjiPotezPozitivnog,
        int poslednjiPotezNegativnog, int dubina, int brojPoteza, int koef[19]);
void alphabeta(int tabla[24], int potez[3], int dubina, int brojPoteza, int koef[19]);

#endif // ALPHABETA_H
