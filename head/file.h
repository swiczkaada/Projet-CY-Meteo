#ifndef FILE_H
#define FILE_H

#include "arbre.h"

// Structure Chainon
typedef struct chainon {
    Element e;
    Element f;
    float g;
    Element h;
    char *i;
    Element j;
    struct chainon *s;
}Chainon;

// manipulation de liste

// insertion

Chainon *creationChainon(Element e, Element f, float g, Element h, char *i, Element j);
// Chainon *insertionDebut(Chainon *pliste, PArbre e);
// Chainon *insertionFin(Chainon *pliste, PArbre e);
// Chainon *insertionOrdre(Chainon *pliste, PArbre e, int ordre);
// insertion croissant

// Suppression

Chainon *suppressionDebut(Chainon *pliste);
Chainon *suppressionFin(Chainon *pliste);
// Chainon *suppressionElem(Chainon *pliste, PArbre e);
Chainon *nettoyerListe(Chainon *pliste);


// Fonctions de tri du projet



Chainon *insertionCroissant(Chainon *pliste, Element e, Element f, float g, Element h, char *i);

Chainon *insertionListeAltitude(Chainon *pliste, Element e, Element f, float g, Element h, char *i);
Chainon *insertionListeHumidite(Chainon *pliste, Element e, Element f, float g, Element h, char *i);
Chainon *insertionListeVent(Chainon *pliste, Element e, Element f, float g, Element h, char *i, Element j);
Chainon *insertionListeP1(Chainon *pliste, Element e, Element f, float g, Element h, char *i, Element j);
Chainon *insertionListeP2(Chainon *pliste, Element e, Element f, float g, Element h, char *i, Element j);
Chainon *insertionListeP3(Chainon *pliste, Element e, Element f, float g, Element h, char *i, Element j);


typedef struct filedyn {
    Chainon *tete;
    Chainon *queue;
}FileDyn;


typedef struct filestat {
    PArbre *tab;
    int taille;
    int tete;
    int queue;
}FileStat;


// file dynamique


FileDyn creerFileDyn();
int verificationFileDyn(FileDyn *f);
int enfilerDyn(FileDyn *f, PArbre e);
int defilerDyn(FileDyn *f, PArbre *e);




// file statique

FileStat creerFileStat(int taille);
int verificationFileStat(FileStat *f);
int enfilerStat(FileStat *f, PArbre e);
int defilerStat(FileStat *f, PArbre *e);

#endif