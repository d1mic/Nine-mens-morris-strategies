#ifndef PRAVILA_H
#define PRAVILA_H

int legalanPotezPrvaFaza(int tabla[24], int igracNaPotezu, int potez);
int legalnoNosenje(int tabla[24], int igracNaPotezu, int pozicija);
void moguciPoteziDrugaFaza(int tabla[24], int pozicija, int niz[4]);

#endif // PRAVILA_H
