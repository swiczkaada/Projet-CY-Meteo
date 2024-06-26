#ifndef MAIN_H
#define MAIN_H

#include "AVL.h"
#include "../head/file.h"


void lectureFichierAltitude(char *nom_fichier, char *nom_fichier_sortie, int mode);
void lectureFichierVent(char *nom_fichier, char *nom_fichier_sortie, int mode);
void lectureFichierHumidite(char *nom_fichier, char *nom_fichier_sortie, int mode);

void lectureFichierT1(char *nom_fichier, char *nom_fichier_sortie, int mode);
void lectureFichierT2(char *nom_fichier, char *nom_fichier_sortie, int mode);
void lectureFichierT3(char *nom_fichier, char *nom_fichier_sortie, int mode);

void lectureFichierP1(char *nom_fichier, char *nom_fichier_sortie, int mode);
void lectureFichierP2(char *nom_fichier, char *nom_fichier_sortie, int mode);
void lectureFichierP3(char *nom_fichier, char *nom_fichier_sortie, int mode);

void ecritureFichierAltitude(char *nom_fichier, PArbre a, Chainon *liste);
void ecritureFichierVent(char *nom_fichier, PArbre a, Chainon *liste);
void ecritureFichierHumidite(char *nom_fichier, PArbre a, Chainon *liste);

void ecritureFichierT1(char *nom_fichier, PArbre a, Chainon *liste);
void ecritureFichierT2(char *nom_fichier, PArbre a, Chainon *liste);
void ecritureFichierT3(char *nom_fichier, PArbre a, Chainon *liste);

void ecritureFichierP1(char *nom_fichier, PArbre a, Chainon *liste);
void ecritureFichierP2(char *nom_fichier, PArbre a, Chainon *liste);
void ecritureFichierP3(char *nom_fichier, PArbre a, Chainon *liste);


// void parcoursMilieu(PArbre a, FILE *f);
void parcoursInfixeEcritureCroissant(PArbre a, FILE *f);
void parcoursInfixeEcritureCroissantP1(PArbre a, FILE *f);
void parcoursInfixeEcritureCroissantP2(PArbre a, FILE *f);
void parcoursInfixeEcritureCroissantP3(PArbre a, FILE *f);


void parcoursInfixeEcritureDecroissant(PArbre a, FILE *f);
void parcoursInfixeEcritureDecroissantAltitude(PArbre a, FILE *f);

void parcoursListeEcritureCroissant(Chainon *l, FILE *f);
void parcoursListeEcritureCroissantP1(Chainon *l, FILE *f);
void parcoursListeEcritureCroissantP2(Chainon *l, FILE *f);
void parcoursListeEcritureDecroissant(Chainon *l, FILE *f);
void parcoursListeEcritureDecroissantAltitude(Chainon *l, FILE *f);
void parcoursListeEcritureCroissantP3(Chainon *l, FILE *f);



PArbre parcoursHumidite(PArbre a, PArbre b);
PArbre parcoursHumiditeABR(PArbre a, PArbre b);


void parcoursMoyenneVent(PArbre a);
void parcoursMoyenneP1(PArbre a);



void parcoursListeMoyenneVent(Chainon *l);
void parcoursMoyenneListeP1(Chainon *liste);
Chainon *parcoursListeHumidite(Chainon *a);

#endif