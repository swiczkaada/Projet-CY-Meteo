#include <stdio.h>
#include <stdlib.h>

#include "../head/arbre.h"

/*********************************************/
/*** Gestion d'arbres binaires dynamiques ***/
/*********************************************/

/**********************************
* Fonctions utiles sur les arbres *
**********************************/

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int estVide(PArbre a) {
    return (a == ARBRENULL);
}

int estFeuille(PArbre a) {
    return (a && !(a->fg || a->fd) ? 1 : 0);
}
Element racine(PArbre a) {
    return (a ? a->elmt : ELEMENTNULL);
}

PArbre modifierRacine(PArbre a, Element e) {
    if (a) a->elmt = e;
        return a;
}

PArbre filsGauche(PArbre a) {
    return a->fg;
}
PArbre filsDroit(PArbre a) {
    return a->fd;
}
PArbre filsMilieu(PArbre a) {
    return a->fm;
}

int existeFilsGauche(PArbre a) {
    return (a && filsGauche(a));
}

int existeFilsDroit(PArbre a) {
    return (a && filsDroit(a));
}

/*
* -1 si vide
* 0 si feuille
* 1+ max de la hauteur des sous-arbres
*/
int hauteurArbre(PArbre a) {
    if (estVide(a)) return -1;
    return 1 + max(hauteurArbre(filsGauche(a)), hauteurArbre(filsDroit(a)));}

/*
* Nombre de noeuds internes de l'arbre
*/
int tailleArbre(PArbre a) {
    if (estVide(a) || estFeuille(a)) return 0;
    return 1 + tailleArbre(filsGauche(a)) + tailleArbre(filsDroit(a));
}

int nbFeuilles(PArbre a) {
    if (estVide(a)) return 0;
    if (estFeuille(a)) return 1;
    return nbFeuilles(filsGauche(a)) + nbFeuilles(filsDroit(a));
}

/*
* Nombre de fils du noeud
* retourne 0 si a est vide ou sans fils
*/
int degreNoeud(PArbre a) {
    return (a ? (existeFilsGauche(a) ? 1 : 0) + (existeFilsDroit(a) ? 1 : 0) : 0);
}



/***************************************
* Fonctions de modification des arbres *
***************************************/

PArbre creerArbre(Element e, Element f, float g, Element h, char *i, Element j) {
    PArbre a = malloc(sizeof(Arbre));
    if (a == NULL) {
        printf("***ERREUR ALLOCATION MALLOC***\n");
        exit(4);
    }

    if (i) {
        a->i = malloc(sizeof(char) * 128);
        if (!a->i) {
            printf("ERREUR ALLOCATION MALLOC\n");
            exit(4);
        }
        sprintf(a->i, "%s", i);
    }

    // *a = (Arbre) { .elmt = e, .f = f, .g = g, .h = h, .j = j, .fg = ARBRENULL, .fd = ARBRENULL, .equilibre = 0, .hauteur = 0 };
    *a = (Arbre) { e, f, g, h, j, ARBRENULL, ARBRENULL, ARBRENULL, 0, 0 };
    return a;
}

/*
PArbre ajouterFilsGauche(PArbre a, Element e) {
    if (! (estVide(a) || existeFilsGauche(a)))
    a->fg = creerArbre(e);
    return a;
}
*/

/*
PArbre ajouterFilsDroit(PArbre a, Element e) {
    if (! (estVide(a) || existeFilsDroit(a)))
    a->fd = creerArbre(e);
    return a;
}
*/

PArbre supprimerFilsGauche(PArbre a) {
    if (! estVide(a) && existeFilsGauche(a)) {
        if (existeFilsGauche(a->fg)) supprimerFilsGauche(a->fg);
        if (existeFilsDroit(a->fg)) supprimerFilsDroit(a->fg);
        free(a->fg);
        a->fg = NULL;
    }
    return a;
}

PArbre supprimerFilsDroit(PArbre a) {
    if (! estVide(a) && existeFilsDroit(a)) {
    if (existeFilsGauche(a->fd)) supprimerFilsGauche(a->fd);
    if (existeFilsDroit(a->fd)) supprimerFilsDroit(a->fd);
    free(a->fd);
    a->fd = NULL;
    }
    return a;
}

/**********************************
* Affichage de l'arbre
**********************************/

void traiter(Element e) {
    printf("%ld ", e);
}
void parcoursPrefixe(PArbre a) {
    if (! estVide(a)) {
        traiter(a->elmt);
        parcoursPrefixe(filsGauche(a));
        parcoursPrefixe(filsDroit(a));
    }
}

void parcoursInfixe(PArbre a) {
    if (! estVide(a)) {
        parcoursInfixe(filsGauche(a));
        traiter(a->elmt);
        parcoursInfixe(filsDroit(a));
    }
}
void parcoursPostfixe(PArbre a) {
    if (! estVide(a)) {
        parcoursPostfixe(filsGauche(a));
        parcoursPostfixe(filsDroit(a));
        traiter(a->elmt);
    } 
}


/*************************/