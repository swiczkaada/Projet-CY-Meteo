#ifndef ARBRE_H
#define ARBRE_H

#define ELEMENTNULL 0
#define ARBRENULL NULL

typedef long Element;


typedef struct arb{
    Element elmt;
    Element f;
    float g;
    Element h;
    Element j;
    struct arb *fg;
    struct arb *fm;
    struct arb *fd;
    int equilibre;
    int hauteur;
    char *i;
}Arbre;

typedef Arbre* PArbre;

int max(int a, int b);
int min(int a, int b);

PArbre filsGauche(PArbre a);
PArbre filsDroit(PArbre a);
PArbre filsMilieu(PArbre a);

int hauteurArbre(PArbre a);
int tailleArbre(PArbre a);
int nbFeuilles(PArbre a);
int degreNoeud(PArbre a);
int degreArbre(PArbre a);
int estVide(PArbre a);
int estFeuille(PArbre a);
int existeFilsGauche(PArbre a);
int existeFilsDroit(PArbre a);

Element racine(PArbre a);
PArbre modifierRacine(PArbre a, Element elmt);

PArbre creerArbre(Element e, Element f, float g, Element h, char *i, Element j);

// PArbre ajouterFilsGauche(PArbre a, Element elmt);
// PArbre ajouterFilsDroit(PArbre a, Element elmt);
PArbre supprimerFilsGauche(PArbre a);
PArbre supprimerFilsDroit(PArbre a);

void traiter(Element a);
void parcoursPrefixe(PArbre a);
void parcoursInfixe(PArbre a);
void parcoursPostfixe(PArbre a);
// void parcoursLargeur(PArbre a);


#endif 