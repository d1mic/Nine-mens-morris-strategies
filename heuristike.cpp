#include "heuristike.h"


/*
proverava da li se figura na toj poziciji nalazi u mici
vraca 1 ako da, 0 ako ne
*/
int uMici(int tabla[24], int potez) {
  switch (potez) {
    case 0:
      if ((tabla[0] == tabla[1] && tabla[0] == tabla[2]) || (tabla[0] == tabla[9] && tabla[0] == tabla[21]))
        return 1;
      else
        return 0;

    case 1:
      if ((tabla[1] == tabla[0] && tabla[1] == tabla[2]) || (tabla[1] == tabla[4] && tabla[1] == tabla[7]))
        return 1;
      else
        return 0;

    case 2:
      if ((tabla[2] == tabla[1] && tabla[2] == tabla[0]) || (tabla[2] == tabla[14] && tabla[2] == tabla[23]))
        return 1;
      else
        return 0;

    case 3:
      if ((tabla[3] == tabla[4] && tabla[3] == tabla[5]) || (tabla[3] == tabla[10] && tabla[3] == tabla[18]))
        return 1;
      else
        return 0;

    case 4:
      if ((tabla[4] == tabla[1] && tabla[4] == tabla[7]) || (tabla[4] == tabla[3] && tabla[4] == tabla[5]))
        return 1;
      else
        return 0;

    case 5:
      if ((tabla[5] == tabla[3] && tabla[5] == tabla[4]) || (tabla[5] == tabla[13] && tabla[13] == tabla[20]))
        return 1;
      else
        return 0;

    case 6:
      if ((tabla[6] == tabla[7] && tabla[6] == tabla[8]) || (tabla[6] == tabla[11] && tabla[6] == tabla[15]))
        return 1;
      else
        return 0;

    case 7:
      if ((tabla[7] == tabla[6] && tabla[7] == tabla[8]) || (tabla[7] == tabla[4] && tabla[7] == tabla[1]))
        return 1;
      else
        return 0;

    case 8:
      if ((tabla[8] == tabla[7] && tabla[8] == tabla[6]) || (tabla[8] == tabla[12] && tabla[8] == tabla[17]))
        return 1;
      else
        return 0;

    case 9:
      if ((tabla[9] == tabla[10] && tabla[9] == tabla[11]) || (tabla[9] == tabla[0] && tabla[9] == tabla[21]))
        return 1;
      else
        return 0;

    case 10:
      if ((tabla[10] == tabla[9] && tabla[10] == tabla[11]) || (tabla[10] == tabla[3] && tabla[10] == tabla[18]))
        return 1;
      else
        return 0;

    case 11:
      if ((tabla[11] == tabla[10] && tabla[11] == tabla[9]) || (tabla[11] == tabla[6] && tabla[11] == tabla[15]))
        return 1;
      else
        return 0;

    case 12:
      if ((tabla[12] == tabla[13] && tabla[12] == tabla[14]) || (tabla[12] == tabla[8] && tabla[12] == tabla[17]))
        return 1;
      else
        return 0;

    case 13:
      if ((tabla[13] == tabla[5] && tabla[13] == tabla[20]) || (tabla[13] == tabla[12] && tabla[13] == tabla[14]))
        return 1;
      else
        return 0;

    case 14:
      if ((tabla[14] == tabla[2] && tabla[14] == tabla[23]) || (tabla[14] == tabla[13] && tabla[14] == tabla[12]))
        return 1;
      else
        return 0;

    case 15:
      if ((tabla[15] == tabla[16] && tabla[15] == tabla[17]) || (tabla[15] == tabla[11] && tabla[15] == tabla[6]))
        return 1;
      else
        return 0;

    case 16:
      if ((tabla[16] == tabla[15] && tabla[16] == tabla[17]) || (tabla[16] == tabla[19] && tabla[16] == tabla[22]))
        return 1;
      else
        return 0;

    case 17:
      if ((tabla[17] == tabla[16] && tabla[17] == tabla[15]) || (tabla[17] == tabla[12] && tabla[17] == tabla[8]))
        return 1;
      else
        return 0;

    case 18:
      if ((tabla[18] == tabla[19] && tabla[18] == tabla[20]) || (tabla[18] == tabla[10] && tabla[18] == tabla[3]))
        return 1;
      else
        return 0;

    case 19:
      if ((tabla[19] == tabla[16] && tabla[19] == tabla[22]) || (tabla[19] == tabla[18] && tabla[19] == tabla[20]))
        return 1;
      else
        return 0;

    case 20:
      if ((tabla[20] == tabla[13] && tabla[20] == tabla[5]) || (tabla[20] == tabla[19] && tabla[20] == tabla[18]))
        return 1;
      else
        return 0;

    case 21:
      if ((tabla[21] == tabla[22] && tabla[21] == tabla[23]) || (tabla[21] == tabla[9] && tabla[21] == tabla[0]))
        return 1;
      else
        return 0;

    case 22:
      if ((tabla[22] == tabla[19] && tabla[22] == tabla[16]) || (tabla[22] == tabla[21] && tabla[22] == tabla[23]))
        return 1;
      else
        return 0;

    case 23:
      if ((tabla[23] == tabla[21] && tabla[23] == tabla[22]) || (tabla[23] == tabla[14] && tabla[23] == tabla[2]))
        return 1;
      else
        return 0;

    default:
      return 0;
  }
}


//1 ako zatvara micu, 0 ako ne
//mora mu se proslediti legalan potez
//f-ja nam ipak nece trebati ali neka ostane za svaki slucaj
int zatvorenaMicaPrvaFaza(int tabla[24], int igracNaPotezu, int potez) {
    tabla[potez] = igracNaPotezu;
    int povratnaVrednost = uMici(tabla, potez);
    tabla[potez] = 0;
    return povratnaVrednost;
}


/*
 * Proverava da li odigrani potez zatvara micu
 * vraca 1 ako zatvara micu, 0 ako ne
 * potez[0] je pozicija sa koje pomeramo figuru, potez[1] je pozicija na koju pomeramo figuru
 * f-ji se mora proslediti legalan potez
*/
int zatvorenaMicaDrugaITrecaFaza(int tabla[24], int igracNaPotezu, int potez[3]) {
    tabla[potez[0]] = 0;
    tabla[potez[1]] = igracNaPotezu;
    int povratnaVrednost = uMici(tabla, potez[1]);
    tabla[potez[1]] = 0;
    tabla[potez[0]] = igracNaPotezu;
    return povratnaVrednost;
}


//vraca 1 ako zatvara micu, 0 ako ne
//ne sluzi za proveru da li je upravo zatvorena mica vec samo gleda da li neka pozicija zatvara micu
//tj. da li postoji otovorena mica
int zatvaraMicuDrugaFaza(int tabla[24], int pozicija) {
    switch (pozicija) {
        case 0:
            if ((tabla[1] == 0 && tabla[4] == tabla[0] && tabla[7] == tabla[0]) ||
                (tabla[9] == 0 && tabla[10] == tabla[0] && tabla[11] == tabla[0]))
                return 1;
            else
                return 0;

        case 1:
            if ((tabla[0] == 0 && tabla[9] == tabla[1] && tabla[21] == tabla[1]) ||
                (tabla[2] == 0 && tabla[14] == tabla[1] && tabla[23] == tabla[1]) ||
                (tabla[4] == 0 && tabla[3] == tabla[1] && tabla[5] == tabla[1]))
                return 1;
            else
                return 0;

        case 2:
            if ((tabla[1] == 0 && tabla[4] == tabla[2] && tabla[7] == tabla[2]) ||
                (tabla[14] == 0 && tabla[13] == tabla[2] && tabla[12] == tabla[2]))
                return 1;
            else
                return 0;

        case 3:
            if ((tabla[4] == 0 && tabla[1] == tabla[3] && tabla[7] == tabla[3]) ||
                (tabla[10] == 0 && tabla[9] == tabla[3] && tabla[11] == tabla[3]))
                return 1;
            else
                return 0;

        case 4:
            if ((tabla[1] == 0 && tabla[0] == tabla[4] && tabla[2] == tabla[4]) ||
                (tabla[3] == 0 && tabla[10] == tabla[4] && tabla[18] == tabla[4]) ||
                (tabla[5] == 0 && tabla[13] == tabla[4] && tabla[20] == tabla[4]) ||
                (tabla[7] == 0 && tabla[6] == tabla[4] && tabla[8] == tabla[4]))
                return 1;
            else
                return 0;

        case 5:
            if ((tabla[4] == 0 && tabla[1] == tabla[5] && tabla[7] == tabla[5]) ||
                (tabla[13] == 0 && tabla[12] == tabla[5] && tabla[14] == tabla[5]))
                return 1;
            else
                return 0;

        case 6:
            if ((tabla[7] == 0 && tabla[4] == tabla[6] && tabla[1] == tabla[6]) ||
                (tabla[11] == 0 && tabla[10] == tabla[6] && tabla[9] == tabla[6]))
                return 1;
            else
                return 0;

        case 7:
            if ((tabla[4] == 0 && tabla[3] == tabla[7] && tabla[5] == tabla[7]) ||
                (tabla[6] == 0 && tabla[11] == tabla[7] && tabla[15] == tabla[7]) ||
                (tabla[8] == 0 && tabla[12] == tabla[7] && tabla[17] == tabla[7]))
                return 1;
            else
                return 0;

        case 8:
            if ((tabla[7] == 0 && tabla[4] == tabla[8] && tabla[1] == tabla[8]) ||
                (tabla[12] == 0 && tabla[13] == tabla[8] && tabla[14] == tabla[8]))
                return 1;
            else
                return 0;

        case 9:
            if ((tabla[10] == 0 && tabla[18] == tabla[9] && tabla[3] == tabla[9]) ||
                (tabla[0] == 0 && tabla[1] == tabla[9] && tabla[2] == tabla[9]) ||
                (tabla[21] == 0 && tabla[22] == tabla[9] && tabla[23] == tabla[9]))
                return 1;
            else
                return 0;

        case 10:
            if ((tabla[9] == 0 && tabla[0] == tabla[10] && tabla[21] == tabla[10]) ||
                (tabla[3] == 0 && tabla[4] == tabla[10] && tabla[5] == tabla[10]) ||
                (tabla[18] == 0 && tabla[19] == tabla[10] && tabla[20] == tabla[10]) ||
                (tabla[11] == 0 && tabla[15] == tabla[10] && tabla[6] == tabla[10]))
                return 1;
            else
                return 0;

        case 11:
            if ((tabla[10] == 0 && tabla[3] == tabla[11] && tabla[18] == tabla[11]) ||
                (tabla[6] == 0 && tabla[7] == tabla[11] && tabla[8] == tabla[11]) ||
                (tabla[15] == 0 && tabla[16] == tabla[11] && tabla[17] == tabla[11]))
                return 1;
            else
                return 0;

        case 12:
            if ((tabla[8] == 0 && tabla[7] == tabla[12] && tabla[6] == tabla[12]) ||
                (tabla[17] == 0 && tabla[16] == tabla[12] && tabla[15] == tabla[12]) ||
                (tabla[13] == 0 && tabla[5] == tabla[12] && tabla[20] == tabla[12]))
                return 1;
            else
                return 0;

        case 13:
            if ((tabla[12] == 0 && tabla[17] == tabla[13] && tabla[8] == tabla[13]) ||
                (tabla[20] == 0 && tabla[19] == tabla[13] && tabla[18] == tabla[13]) ||
                (tabla[5] == 0 && tabla[4] == tabla[13] && tabla[3] == tabla[13]) ||
                (tabla[14] == 0 && tabla[2] == tabla[13] && tabla[23] == tabla[13]))
                return 1;
            else
                return 0;

        case 14:
            if ((tabla[13] == 0 && tabla[5] == tabla[14] && tabla[20] == tabla[14]) ||
                (tabla[2] == 0 && tabla[1] == tabla[14] && tabla[0] == tabla[14]) ||
                (tabla[23] == 0 && tabla[22] == tabla[14] && tabla[21] == tabla[14]))
                return 1;
            else
                return 0;

        case 15:
            if ((tabla[11] == 0 && tabla[10] == tabla[15] && tabla[9] == tabla[15]) ||
                (tabla[16] == 0 && tabla[19] == tabla[15] && tabla[22] == tabla[15]))
                return 1;
            else
                return 0;

        case 16:
            if ((tabla[19] == 0 && tabla[18] == tabla[16] && tabla[20] == tabla[16]) ||
                (tabla[15] == 0 && tabla[11] == tabla[16] && tabla[6] == tabla[16]) ||
                (tabla[17] == 0 && tabla[12] == tabla[16] && tabla[8] == tabla[16]))
                return 1;
            else
                return 0;

        case 17:
            if ((tabla[16] == 0 && tabla[19] == tabla[17] && tabla[22] == tabla[17]) ||
                (tabla[12] == 0 && tabla[13] == tabla[17] && tabla[14] == tabla[17]))
                return 1;
            else
                return 0;

        case 18:
            if ((tabla[10] == 0 && tabla[9] == tabla[18] && tabla[11] == tabla[18]) ||
                (tabla[19] == 0 && tabla[16] == tabla[18] && tabla[22] == tabla[18]))
                return 1;
            else
                return 0;

        case 19:
            if ((tabla[16] == 0 && tabla[17] == tabla[19] && tabla[15] == tabla[19]) ||
                (tabla[18] == 0 && tabla[10] == tabla[19] && tabla[3] == tabla[19]) ||
                (tabla[20] == 0 && tabla[13] == tabla[19] && tabla[5] == tabla[19]) ||
                (tabla[22] == 0 && tabla[21] == tabla[19] && tabla[23] == tabla[19]))
                return 1;
            else
                return 0;

        case 20:
            if ((tabla[19] == 0 && tabla[22] == tabla[20] && tabla[16] == tabla[20]) ||
                (tabla[13] == 0 && tabla[12] == tabla[20] && tabla[14] == tabla[20]))
                return 1;
            else
                return 0;

        case 21:
            if ((tabla[9] == 0 && tabla[10] == tabla[21] && tabla[11] == tabla[21]) ||
                (tabla[22] == 0 && tabla[19] == tabla[21] && tabla[16] == tabla[21]))
                return 1;
            else
                return 0;

        case 22:
            if ((tabla[19] == 0 && tabla[18] == tabla[22] && tabla[20] == tabla[22]) ||
                (tabla[21] == 0 && tabla[9] == tabla[22] && tabla[0] == tabla[22]) ||
                (tabla[23] == 0 && tabla[14] == tabla[22] && tabla[2] == tabla[22]))
                return 1;
            else
                return 0;

        case 23:
            if ((tabla[22] == 0 && tabla[19] == tabla[23] && tabla[16] == tabla[23]) ||
                (tabla[14] == 0 && tabla[13] == tabla[23] && tabla[12] == tabla[23]))
                return 1;
            else
                return 0;
    }
}



//ako je ta neka figura blokirana vraca 1, ako nije blokirana vraca 0
int blokiranaFigura(int tabla[24], int pozicija) {
  switch (pozicija) {
    case 0:
      if (tabla[1] != 0 && tabla[9] != 0)
        return 1;
      else
        return 0;

    case 1:
      if(tabla[0] != 0 && tabla[2] != 0 && tabla[4] != 0)
        return 1;
      else
        return 0;

    case 2:
      if(tabla[1] != 0 && tabla[14] != 0)
        return 1;
      else
        return 0;

    case 3:
      if(tabla[10] != 0 && tabla[4] != 0)
        return 1;
      else
        return 0;

    case 4:
      if(tabla[3] != 0 && tabla[7] != 0 && tabla[5] != 0 && tabla[1] != 0)
        return 1;
      else
        return 0;

    case 5:
      if(tabla[4] != 0 && tabla[13] != 0)
        return 1;
      else
        return 0;

    case 6:
      if(tabla[11] != 0 && tabla[7] != 0)
        return 1;
      else
        return 0;

    case 7:
      if(tabla[6] != 0 && tabla[8] != 0 && tabla[4] != 0)
        return 1;
      else
        return 0;

    case 8:
      if(tabla[7] != 0 && tabla[12] != 0)
        return 1;
      else
        return 0;

    case 9:
      if(tabla[0] != 0 && tabla[21] != 0 && tabla[10] != 0)
        return 1;
      else
        return 0;

    case 10:
      if(tabla[9] != 0 && tabla[11] != 0 && tabla[3] != 0 && tabla[18] != 0)
        return 1;
      else
        return 0;

    case 11:
      if(tabla[10] != 0 && tabla[15] != 0 && tabla[6] != 0)
        return 1;
      else
        return 0;

    case 12:
      if(tabla[8] != 0 && tabla[13] != 0 && tabla[17] != 0)
        return 1;
      else
        return 0;

    case 13:
      if(tabla[12] != 0 && tabla[5] != 0 && tabla[14] != 0 && tabla[20] != 0)
        return 1;
      else
        return 0;

    case 14:
      if(tabla[2] != 0 && tabla[13] != 0 && tabla[23] != 0)
        return 1;
      else
        return 0;

    case 15:
      if(tabla[11] != 0 && tabla[16] != 0)
        return 1;
      else
        return 0;

    case 16:
      if(tabla[15] != 0 && tabla[17] != 0 && tabla[19] != 0)
        return 1;
      else
        return 0;

    case 17:
      if(tabla[16] != 0 && tabla[12] != 0)
        return 1;
      else
        return 0;

    case 18:
      if(tabla[10] != 0 && tabla[19] != 0)
        return 1;
      else
        return 0;

    case 19:
      if(tabla[16] != 0 && tabla[18] != 0 && tabla[22] != 0 && tabla[20] != 0)
        return 1;
      else
        return 0;

    case 20:
      if(tabla[19] != 0 && tabla[13] != 0)
        return 1;
      else
        return 0;

    case 21:
      if(tabla[9] != 0 && tabla[22] != 0)
        return 1;
      else
        return 0;

    case 22:
      if(tabla[19] != 0 && tabla[21] != 0 && tabla[23] != 0)
        return 1;
      else
        return 0;

    case 23:
      if(tabla[22] != 0 && tabla[14] != 0)
        return 1;
      else
        return 0;
  }
}


/*
Racuna broj blokiranih figura i broj figura za oba igraca
Rezultat upisuje u niz koji mu je prosledjen kao argument
*/
void brojBlokiranih(int tabla[24], int rezultat[4]) {
  int brojFiguraPozitivnog = 0;
  int brojFiguraNegativnog = 0;

  int blokiranihPozitivnog = 0;
  int blokiranihNegativnog = 0;

  int i;

  for (i = 0; i < 24; i++)
    if (tabla[i] == 1)
      if (blokiranaFigura(tabla, i)) {
        blokiranihPozitivnog++;
        brojFiguraPozitivnog++;
      }
      else
        brojFiguraPozitivnog++;

    else if (tabla[i] == -1) {
      if (blokiranaFigura(tabla, i)) {
        blokiranihNegativnog++;
        brojFiguraNegativnog++;
      }
      else
        brojFiguraNegativnog++;
    }


  rezultat[0] = blokiranihPozitivnog;
  rezultat[1] = blokiranihNegativnog;
  rezultat[2] = brojFiguraPozitivnog;
  rezultat[3] = brojFiguraNegativnog;
}


//racuna broj figura za svakog od igraca, rezultat upisuje u niz[2] koji dobija kao argument
//na poziciji 0 nalazi se broj figura pozitivnog igraca
//na poziciji 1 nalazi broj figura negativnog igraca
//iako kada racunamo broj blokiranih figura u jednoj for petlji radimo i broj figura
//neka ostane i ova f-ja jer mozda zatreba
void brojFigura(int tabla[24], int rezultat[2]) {
  int brojPozitivnog = 0;
  int brojNegativnog = 0;

  int i;

  for (i = 0; i < 24; i++)
    if (tabla[i] == 1)
      brojPozitivnog++;
    else if (tabla[i] == -1)
      brojNegativnog++;

  rezultat[0] = brojPozitivnog;
  rezultat[1] = brojNegativnog;
}


/*
F-ja u rezultat[0] upisuje razliku broja figura u micama prvog i drugog igraca,
u rezultat[1] upisuje razliku broja otvorenih mica prvog i drugog igraca,
u rezultat[2] upisuje razliku broja trakalica prvog i drugog igraca
niz int rezultat[3] koji mu se prosledjuje mora biti {0, 0, 0}
*/
void miceIOtvoreneMice(int tabla[24], int rezultat[3]) {
    int i;
    int indikator;

    for (i = 0; i < 24; i++) {
        indikator = 0;
        if(tabla[i] == 1) {
            if (uMici(tabla, i)) {
                rezultat[0]++;
                indikator++;
            }
            if (zatvaraMicuDrugaFaza(tabla, i)) {
                rezultat[1]++;
                indikator++;
            }
            if (indikator == 2)
                rezultat[2]++;

        }
        else if (tabla[i] == -1) {
            if (uMici(tabla, i)) {
                rezultat[0]--;
                indikator++;
            }
            if (zatvaraMicuDrugaFaza(tabla, i)) {
                rezultat[1]--;
                indikator++;
            }
            if (indikator == 2)
                rezultat[2]--;
        }
    }
}


//funkcija vraca razliku broja figura u micama prvog i drugog igraca
//ova f-ja se koristi samo u prvoj fazi igri jer u njoj gledamo samo broj mica
//dok nas broj otvorenih mica trenutno ne interesuje
//radi efikasnosti u drugoj fazi igre broj mica (tj. figura u micama), otvorenih mica
//i trakalica se realizuje u jednoj for petlji
int brojFiguraUMicamaPrvaFaza(int tabla[24]) {
    int rezultat = 0;
    int i;

    for (i = 0; i < 24; i++)
        if (tabla[i] == 1 && uMici(tabla, i))
            rezultat++;
        else if (tabla[i] == -1 && uMici(tabla, i))
            rezultat--;

    return rezultat;
}


/*
Proverava da li se figura nalazi u 2-konfiguraciji i vraca 1 ukoliko se nalazi, a 0 ako se ne nalazi
ako se ta figura nalazi u 3-konfiguraciji onda f-ja vraca 2
*/
int dvaITriKonfiguracija(int tabla[24], int pozicija) {
  int indikatorTriKonf = 0;

  switch (pozicija) {
    case 0:
      if ((tabla[0] == tabla[1] && tabla[2] == 0) || (tabla[0] == tabla[2] && tabla[1] == 0))
          indikatorTriKonf++;
      if ((tabla[0] == tabla[9] && tabla[21] == 0) || (tabla[0] == tabla[21] && tabla[9] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 1:
      if ((tabla[1] == tabla[4] && tabla[7] == 0) || (tabla[1] == tabla[7] && tabla[4] == 0))
          indikatorTriKonf++;
      if ((tabla[1] == tabla[0] && tabla[2] == 0) || (tabla[1] == tabla[2] && tabla[0] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 2:
      if ((tabla[2] == tabla[1] && tabla[0] == 0) || (tabla[2] == tabla[0] && tabla[1] == 0))
          indikatorTriKonf++;
      if ((tabla[2] == tabla[14] && tabla[23] == 0) || (tabla[2] == tabla[23] && tabla[14] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 3:
      if ((tabla[3] == tabla[4] && tabla[5] == 0) || (tabla[3] == tabla[5] && tabla[4] == 0))
          indikatorTriKonf++;
      if ((tabla[3] == tabla[10] && tabla[18] == 0) || (tabla[3] == tabla[18] && tabla[10] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 4:
      if ((tabla[4] == tabla[1] && tabla[7] == 0) || (tabla[4] == tabla[7] && tabla[1] == 0))
          indikatorTriKonf++;
      if ((tabla[4] == tabla[3] && tabla[5] == 0) || (tabla[4] == tabla[5] && tabla[3] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 5:
      if ((tabla[5] == tabla[4] && tabla[3] == 0) || (tabla[5] == tabla[3] && tabla[4] == 0))
          indikatorTriKonf++;
      if ((tabla[5] == tabla[13] && tabla[20] == 0) || (tabla[5] == tabla[20] && tabla[13] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 6:
      if ((tabla[6] == tabla[7] && tabla[8] == 0) || (tabla[6] == tabla[8] && tabla[7] == 0))
          indikatorTriKonf++;
      if ((tabla[6] == tabla[11] && tabla[15] == 0) || (tabla[6] == tabla[15] && tabla[11] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 7:
      if ((tabla[7] == tabla[6] && tabla[8] == 0) || (tabla[7] == tabla[8] && tabla[6] == 0))
          indikatorTriKonf++;
      if ((tabla[7] == tabla[4] && tabla[1] == 0) || (tabla[7] == tabla[1] && tabla[4] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 8:
      if ((tabla[8] == tabla[7] && tabla[6] == 0) || (tabla[8] == tabla[6] && tabla[7] == 0))
          indikatorTriKonf++;
      if ((tabla[8] == tabla[12] && tabla[17] == 0) || (tabla[8] == tabla[17] && tabla[12] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 9:
      if ((tabla[9] == tabla[0] && tabla[21] == 0) || (tabla[9] == tabla[21] && tabla[0] == 0))
          indikatorTriKonf++;
      if ((tabla[9] == tabla[10] && tabla[11] == 0) || (tabla[9] == tabla[11] && tabla[10] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 10:
      if ((tabla[10] == tabla[9] && tabla[11] == 0) || (tabla[10] == tabla[11] && tabla[9] == 0))
          indikatorTriKonf++;
      if ((tabla[10] == tabla[3] && tabla[18] == 0) || (tabla[10] == tabla[18] && tabla[3] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 11:
      if ((tabla[11] == tabla[9] && tabla[10] == 0) || (tabla[11] == tabla[10] && tabla[9] == 0))
          indikatorTriKonf++;
      if ((tabla[11] == tabla[6] && tabla[15] == 0) || (tabla[11] == tabla[15] && tabla[6] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 12:
      if ((tabla[12] == tabla[8] && tabla[17] == 0) || (tabla[12] == tabla[17] && tabla[8] == 0))
          indikatorTriKonf++;
      if ((tabla[12] == tabla[13] && tabla[14] == 0) || (tabla[12] == tabla[14] && tabla[13] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 13:
      if ((tabla[13] == tabla[12] && tabla[14] == 0) || (tabla[13] == tabla[14] && tabla[12] == 0))
          indikatorTriKonf++;
      if ((tabla[13] == tabla[5] && tabla[20] == 0) || (tabla[13] == tabla[20] && tabla[5] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 14:
      if ((tabla[14] == tabla[12] && tabla[13] == 0) || (tabla[14] == tabla[13] && tabla[12] == 0))
          indikatorTriKonf++;
      if ((tabla[14] == tabla[2] && tabla[23] == 0) || (tabla[14] == tabla[23] && tabla[2] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 15:
      if ((tabla[15] == tabla[11] && tabla[6] == 0) || (tabla[15] == tabla[6] && tabla[11] == 0))
          indikatorTriKonf++;
      if ((tabla[15] == tabla[16] && tabla[17] == 0) || (tabla[15] == tabla[17] && tabla[16] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 16:
      if ((tabla[16] == tabla[15] && tabla[17] == 0) || (tabla[16] == tabla[17] && tabla[15] == 0))
          indikatorTriKonf++;
      if ((tabla[16] == tabla[19] && tabla[22] == 0) || (tabla[16] == tabla[22] && tabla[19] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 17:
      if ((tabla[17] == tabla[15] && tabla[16] == 0) || (tabla[17] == tabla[16] && tabla[15] == 0))
          indikatorTriKonf++;
      if ((tabla[17] == tabla[12] && tabla[8] == 0) || (tabla[17] == tabla[8] && tabla[12] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 18:
      if ((tabla[18] == tabla[10] && tabla[3] == 0) || (tabla[18] == tabla[3] && tabla[10] == 0))
          indikatorTriKonf++;
      if ((tabla[18] == tabla[19] && tabla[20] == 0) || (tabla[18] == tabla[20] && tabla[19] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 19:
      if ((tabla[19] == tabla[18] && tabla[20] == 0) || (tabla[19] == tabla[20] && tabla[18] == 0))
          indikatorTriKonf++;
      if ((tabla[19] == tabla[16] && tabla[22] == 0) || (tabla[19] == tabla[22] && tabla[16] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 20:
      if ((tabla[20] == tabla[18] && tabla[19] == 0) || (tabla[20] == tabla[19] && tabla[18] == 0))
          indikatorTriKonf++;
      if ((tabla[20] == tabla[13] && tabla[5] == 0) || (tabla[20] == tabla[5] && tabla[13] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 21:
      if ((tabla[21] == tabla[9] && tabla[0] == 0) || (tabla[21] == tabla[0] && tabla[9] == 0))
          indikatorTriKonf++;
      if ((tabla[21] == tabla[22] && tabla[23] == 0) || (tabla[21] == tabla[23] && tabla[22] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 22:
      if ((tabla[22] == tabla[21] && tabla[23] == 0) || (tabla[22] == tabla[23] && tabla[21] == 0))
          indikatorTriKonf++;
      if ((tabla[22] == tabla[19] && tabla[16] == 0) || (tabla[22] == tabla[16] && tabla[19] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

    case 23:
      if ((tabla[23] == tabla[21] && tabla[22] == 0) || (tabla[23] == tabla[22] && tabla[21] == 0))
          indikatorTriKonf++;
      if ((tabla[23] == tabla[14] && tabla[2] == 0) || (tabla[23] == tabla[2] && tabla[14] == 0))
          indikatorTriKonf++;
      return indikatorTriKonf;

  }
}


/*
u rezultat[0] se upisuje razlika 2-konfiguracija dva igraca
u rezultat[1] se upisuje razlika 3-konf dva igraca
3-kofiguracija postoji ukoliko postoji figura koja pripada dvema 2-konfiguracijama
dakle ovi rezultati se mogu direktno mnoziti sa koeficijentima u f-ji evaluacije
*/

void brojDvaITriKonfiguracija(int tabla[24], int rezultat[2]) {
  int i;

  for (i = 0; i < 24; i++) {
      if (tabla[i] == 1) {
          if (dvaITriKonfiguracija(tabla, i) == 1)
              rezultat[0]++;
          else if (dvaITriKonfiguracija(tabla, i) == 2) {
              rezultat[0]++;
              rezultat[1]++;
          }
      }
      else if (tabla[i] == -1) {
          if (dvaITriKonfiguracija(tabla, i) == 1)
              rezultat[0]--;
          else if (dvaITriKonfiguracija(tabla, i) == 2) {
              rezultat[0]--;
              rezultat[1]--;
          }
      }
  }
}


int slobodnaMestaOkoPozicije(int tabla[24], int pozicija) {
    int brojac = 0;

    switch (pozicija) {
        case 0:
            if (tabla[1] == 0)
                brojac++;
            if (tabla[9] == 0)
                brojac++;
            return brojac;

        case 1:
            if (tabla[0] == 0)
                brojac++;
            if (tabla[4] == 0)
                brojac++;
            if (tabla[2] == 0)
                brojac++;
            return brojac;

        case 2:
            if (tabla[1] == 0)
                brojac++;
            if (tabla[14] == 0)
                brojac++;
            return brojac;

        case 3:
            if (tabla[10] == 0)
                brojac++;
            if (tabla[4] == 0)
                brojac++;
            return brojac;

        case 4:
            if (tabla[1] == 0)
                brojac++;
            if (tabla[3] == 0)
                brojac++;
            if (tabla[7] == 0)
                brojac++;
            if (tabla[5] == 0)
                brojac++;
            return brojac;

        case 5:
            if (tabla[4] == 0)
                brojac++;
            if (tabla[13] == 0)
                brojac++;
            return brojac;

        case 6:
            if (tabla[7] == 0)
                brojac++;
            if (tabla[11] == 0)
                brojac++;
            return brojac;

        case 7:
            if (tabla[6] == 0)
                brojac++;
            if (tabla[4] == 0)
                brojac++;
            if (tabla[8] == 0)
                brojac++;
            return brojac;

        case 8:
            if (tabla[7] == 0)
                brojac++;
            if (tabla[12] == 0)
                brojac++;
            return brojac;

        case 9:
            if (tabla[0] == 0)
                brojac++;
            if (tabla[10] == 0)
                brojac++;
            if (tabla[21] == 0)
                brojac++;
            return brojac;

        case 10:
            if (tabla[3] == 0)
                brojac++;
            if (tabla[9] == 0)
                brojac++;
            if (tabla[18] == 0)
                brojac++;
            if (tabla[11] == 0)
                brojac++;
            return brojac;

        case 11:
            if (tabla[6] == 0)
                brojac++;
            if (tabla[10] == 0)
                brojac++;
            if (tabla[15] == 0)
                brojac++;
            return brojac;

        case 12:
            if (tabla[8] == 0)
                brojac++;
            if (tabla[13] == 0)
                brojac++;
            if (tabla[17] == 0)
                brojac++;
            return brojac;

        case 13:
            if (tabla[5] == 0)
                brojac++;
            if (tabla[12] == 0)
                brojac++;
            if (tabla[20] == 0)
                brojac++;
            if (tabla[14] == 0)
                brojac++;
            return brojac;

        case 14:
            if (tabla[2] == 0)
                brojac++;
            if (tabla[13] == 0)
                brojac++;
            if (tabla[23] == 0)
                brojac++;
            return brojac;

        case 15:
            if (tabla[11] == 0)
                brojac++;
            if (tabla[16] == 0)
                brojac++;
            return brojac;

        case 16:
            if (tabla[15] == 0)
                brojac++;
            if (tabla[19] == 0)
                brojac++;
            if (tabla[17] == 0)
                brojac++;
            return brojac;

        case 17:
            if (tabla[16] == 0)
                brojac++;
            if (tabla[12] == 0)
                brojac++;
            return brojac;

        case 18:
            if (tabla[10] == 0)
                brojac++;
            if (tabla[19] == 0)
                brojac++;
            return brojac;

        case 19:
            if (tabla[16] == 0)
                brojac++;
            if (tabla[18] == 0)
                brojac++;
            if (tabla[22] == 0)
                brojac++;
            if (tabla[20] == 0)
                brojac++;
            return brojac;

        case 20:
            if (tabla[19] == 0)
                brojac++;
            if (tabla[13] == 0)
                brojac++;
            return brojac;

        case 21:
            if (tabla[9] == 0)
                brojac++;
            if (tabla[22] == 0)
                brojac++;
            return brojac;

        case 22:
            if (tabla[21] == 0)
                brojac++;
            if (tabla[19] == 0)
                brojac++;
            if (tabla[23] == 0)
                brojac++;
            return brojac;

        case 23:
            if (tabla[22] == 0)
                brojac++;
            if (tabla[14] == 0)
                brojac++;
            return brojac;
    }

}

//slobodna mesta oko figura na koja moze da se odigra u drugoj fazi. Moze odmah da se koristi u f-ji eval.
int sloboda(int tabla[24]) {
    int rezultat = 0;
    int brojac;

    for (brojac = 0; brojac < 24; brojac++)
          if (tabla[brojac] == 1)
            rezultat = rezultat + slobodnaMestaOkoPozicije(tabla, brojac);
        else if (tabla[brojac] == -1)
            rezultat = rezultat - slobodnaMestaOkoPozicije(tabla, brojac);


    return rezultat;
}

