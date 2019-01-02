#ifndef HEURISTIKE_H
#define HEURISTIKE_H

int uMici(int tabla[24], int potez);
int zatvorenaMicaPrvaFaza(int tabla[24], int igracNaPotezu, int potez);
int zatvorenaMicaDrugaITrecaFaza(int tabla[24], int igracNaPotezu, int potez[3]);
int zatvaraMicuDrugaFaza(int tabla[24], int pozicija);
int blokiranaFigura(int tabla[24], int pozicija);
void brojBlokiranih(int tabla[24], int rezultat[4]);
void brojFigura(int tabla[24], int rezultat[2]);
void miceIOtvoreneMice(int tabla[24], int rezultat[3]);
int brojFiguraUMicamaPrvaFaza(int tabla[24]);
int dvaITriKonfiguracija(int tabla[24], int pozicija);
void brojDvaITriKonfiguracija(int tabla[24], int rezultat[2]);
int slobodnaMestaOkoPozicije(int tabla[24], int pozicija);
int sloboda(int tabla[24]);


#endif // HEURISTIKE_H
