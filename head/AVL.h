#ifndef AVL_H
#define AVL_H


#include "ABR.h"


PArbre rotationGauche(PArbre a);
PArbre rotationDroite(PArbre a);
PArbre doubleRotationGauche(PArbre a);
PArbre doubleRotationDroite(PArbre a);

PArbre equilibrerAVL(PArbre a);

PArbre insereAVL(PArbre a, Element e, Element f, float g, Element h, char *i, int *_h);


PArbre insereAVLAltitude(PArbre a, Element e, Element f, float g, Element h, char *i, int *_h);
PArbre insereAVLHumidite(PArbre a, Element e, Element f, float g, Element h, char *i, int *_h);
PArbre insereAVLVent(PArbre a, Element e, Element f, float g, Element h, char *i, Element j, int *_h);

PArbre insereAVLP1(PArbre a, Element e, Element f, float g, Element h, char *i, Element j, int *_h);
PArbre insereAVLP2(PArbre a, Element e, Element f, float g, Element h, char *i, Element j, int *_h);
PArbre insereAVLP3(PArbre a, Element e, Element f, float g, Element h, char *i, Element j, int *_h);

#endif