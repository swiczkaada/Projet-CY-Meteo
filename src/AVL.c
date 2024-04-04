#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../head/AVL.h"
/*
int min3Element(int a, int b, int c){
        return (a < min(b,c)) ? a : min(b,c);

}

int max3Element(int a, int b, int c){
        return (a > max(b,c)) ? a : max(b,c);
}
*/

PArbre rotationGauche(PArbre a) {
    PArbre pivot = a->fd;
    int eq_a = 0, eq_p = 0;
    
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - max(eq_p, 0) - 1;
    pivot->equilibre = min(min(eq_a - 2, eq_a + eq_p - 2), eq_p - 1);
    a = pivot;
    return a;
}

PArbre rotationDroite(PArbre a) {
    PArbre pivot = a->fg;
    int eq_a = 0, eq_p = 0;

    pivot->fd = a;
    a->fg = pivot->fd;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max(max(eq_a + 2, eq_a + eq_p + 2), eq_p + 1);
    a = pivot;
    return a;
}


PArbre doubleRotationGauche(PArbre a) {
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
}

PArbre doubleRotationDroite(PArbre a) {
    a->fg = rotationGauche(a->fg);
    return rotationDroite(a);
}


PArbre equilibrerAVL(PArbre a) {
    if (a->equilibre > 1) {
        if (a->fd->equilibre >= 0) return rotationGauche(a);
        else return doubleRotationGauche(a);
    }
    else if (a->equilibre < -1) {
        if (a->fg->equilibre <= 0) return rotationDroite(a);
        else return doubleRotationDroite(a);
    }
    return a;
}



PArbre insereAVL(PArbre a, Element e, Element f, float g, Element h, char *i, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, h, i, 0.0);
    }
    else if (e < a->elmt) {
        a->fg = insereAVL(filsGauche(a), e, f, g, h, i, _h);
        *_h = -(*_h);
    }
    else if (e > a->elmt) {
        a->fd = insereAVL(filsDroit(a), e, f, g, h, i, _h);
    }
    else if (e == a->elmt) {
        a->fm = insereAVL(filsMilieu(a), e, f, g, h, i, _h);
    }
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}






// Tri par altitude
PArbre insereAVLAltitude(PArbre a, Element e, Element f, float g, Element h, char *i, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, h, i, .0);
    }
    else if (e < a->elmt) {
        a->fg = insereAVLAltitude(filsGauche(a), e, f, g, h, i, _h);
        *_h = -(*_h);
    }
    else if (e > a->elmt) {
        a->fd = insereAVLAltitude(filsDroit(a), e, f, g, h, i, _h);
    }
    else if (e == a->elmt) {
        // Si doublon de station, on ne la stocke pas
        if (f == a->f) return a;
        else a->fm = insereAVLAltitude(filsMilieu(a), e, f, g, h, i, _h);
    }        
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}

// Tri par station
PArbre insereAVLHumidite(PArbre a, Element e, Element f, float g, Element h, char *i, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, h, i, .0);
    }
    else if (f < a->f) {
        a->fg = insereAVLHumidite(filsGauche(a), e, f, g, h, i, _h);
        *_h = -(*_h);
    }
    else if (f > a->f) {
        a->fd = insereAVLHumidite(filsDroit(a), e, f, g, h, i, _h);
    }
    else if (f == a->f) {
        // Si l'humidite est plus grande que le max, c'est le nouveau max
        if (e > a->elmt) a->elmt = e;
    }        
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}

// Tri par station
PArbre insereAVLVent(PArbre a, Element e, Element f, float g, Element h, char *i, Element j, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, h, i, j);
    }
    else if (e < a->elmt) {
        a->fg = insereAVLVent(filsGauche(a), e, f, g, h, i, j, _h);
        *_h = -(*_h);
    }
    else if (e > a->elmt) a->fd = insereAVLVent(filsDroit(a), e, f, g, h, i, j, _h);
    
    else if (e == a->elmt) {
        // Ajout des valeurs
        a->f += f;
        a->g += g;

        // Iterations
        a->h++;
        a->j++;
    }        
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}

// Tri par station
PArbre insereAVLP1(PArbre a, Element e, Element f, float g, Element h, char *i, Element j, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, f, i, f);
    }
    else if (e < a->elmt) {
        a->fg = insereAVLP1(filsGauche(a), e, f, g, h, i, j, _h);
        *_h = -(*_h);
    }

    else if (e > a->elmt) a->fd = insereAVLP1(filsDroit(a), e, f, g, h, i, j, _h);
    
    else if (e == a->elmt) {
        // Moyenne
        a->f += f;
        a->g++;
        // Min et max
        if (f < a->h) a->h = f;
        if (f > a->j) a->j = f;
    }        
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}

// Tri par date
PArbre insereAVLP2(PArbre a, Element e, Element f, float g, Element h, char *i, Element j, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, h, i, j);
    }
    else if (strcmp(i, a->i) < 0) {
        a->fg = insereAVLP2(filsGauche(a), e, f, g, h, i, j, _h);
        *_h = -(*_h);
    }
    else if (strcmp(i, a->i) > 0) {
        a->fd = insereAVLP2(filsDroit(a), e, f, g, h, i, j, _h);
    }
    else if (strcmp(i, a->i) == 0) {
        // Moyenne
        a->f += f;
        a->g++;
    }        
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}

// Tri par station
PArbre insereAVLP3(PArbre a, Element e, Element f, float g, Element h, char *i, Element j, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, h, i, j);
    }
    else if (strcmp(i, a->i) < 0) {
        a->fg = insereAVLP3(filsGauche(a), e, f, g, h, i, j, _h);
        *_h = -(*_h);
    }
    else if (strcmp(i, a->i) > 0) {
        a->fd = insereAVLP3(filsDroit(a), e, f, g, h, i, j, _h);
    }
    else if (strcmp(i, a->i) == 0) {
        a->fm = insereAVLP3(filsMilieu(a), e, f, g, h, i, j, _h);
    }        
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}

