#ifndef ABR_H
#define ABR_H

#include "arbre.h"


int recherche(PArbre a, Element e);

PArbre insereABR(PArbre a, Element e, Element f, float g, Element h, char *i, float j);

PArbre insereABRAltitude(PArbre a, Element e, Element f, float g, Element h, char *i);
PArbre insereABRHumidite(PArbre a, Element e, Element f, float g, Element h, char *i);
PArbre insereABRVent(PArbre a, Element e, Element f, float g, Element h, char *i, Element j);

PArbre insereABRP1(PArbre a, Element e, Element f, float g, Element h, char *i, Element j);
PArbre insereABRP2(PArbre a, Element e, Element f, float g, Element h, char *i, Element j);
PArbre insereABRP3(PArbre a, Element e, Element f, float g, Element h, char *i, Element j);

#endif