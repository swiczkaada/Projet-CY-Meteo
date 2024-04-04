
#include <stdio.h>
#include <string.h>

#include "../head/ABR.h"


int recherche(PArbre a, Element e) {
    if (!a) return 0;
    if (e < a->elmt) return recherche(filsGauche(a), e);
    else if (e < a->elmt) return recherche(filsDroit(a), e);
    return 1;
}



PArbre insereABR(PArbre a, Element e, Element f, float g, Element h, char *i, float j) {
    if (!a) return creerArbre(e, f, g, h, i, j);
    if (e < a->elmt) a->fg = insereABR(filsGauche(a), e, f, g, h, i, j);
    else if (e > a->elmt) a->fd = insereABR(filsDroit(a), e, f, g, h, i, j);
    else a->fm = insereABR(a->fm, e, f, g, h, i, j);
    return a;
}



// Tri par altitude
PArbre insereABRAltitude(PArbre a, Element e, Element f, float g, Element h, char *i) {
    if (!a) return creerArbre(e, f, g, h, i, 0.0);
    
    else if (e < a->elmt) a->fg = insereABRAltitude(filsGauche(a), e, f, g, h, i);
    
    else if (e > a->elmt) a->fd = insereABRAltitude(filsDroit(a), e, f, g, h, i);

    else {
        if (f == a->f) return a;
        else a->fm = insereABRAltitude(filsMilieu(a), e, f, g, h, i);
    }   
    return a;
}

// Tri par station
PArbre insereABRHumidite(PArbre a, Element e, Element f, float g, Element h, char *i) {
    if (!a) return creerArbre(e, f, g, h, i, .0);
    
    else if (f < a->f) a->fg = insereABRHumidite(filsGauche(a), e, f, g, h, i);
    
    else if (f > a->f) a->fd = insereABRHumidite(filsDroit(a), e, f, g, h, i);
    
    else {
        if (e > a->elmt) a->elmt = e;
    }       
    return a;
}

// Tri par station
PArbre insereABRVent(PArbre a, Element e, Element f, float g, Element h, char *i, Element j) {
    if (!a) return creerArbre(e, f, g, h, i, j);
    
    else if (e < a->elmt) a->fg = insereABRVent(filsGauche(a), e, f, g, h, i, j);
    
    else if (e > a->elmt) a->fd = insereABRVent(filsDroit(a), e, f, g, h, i, j);
    
    else {
        // ajout des valeurs
        a->f += f;
        a->g += g;

        // iterations
        a->h++;
        a->j++;
    }        
    return a;
}

// Tri par station
PArbre insereABRP1(PArbre a, Element e, Element f, float g, Element h, char *i, Element j) {
    if (!a) return creerArbre(e, f, g, f, i, f);
    
    else if (e < a->elmt) a->fg = insereABRP1(filsGauche(a), e, f, g, h, i, j);
    
    else if (e > a->elmt) a->fd = insereABRP1(filsDroit(a), e, f, g, h, i, j);

    else {
        a->f += f;
        a->g++;
        if (f < a->h) a->h = f;
        if (f > a->j) a->j = f;
    }          
    return a;
}

// Tri par date
PArbre insereABRP2(PArbre a, Element e, Element f, float g, Element h, char *i, Element j) {
    if (!a) return creerArbre(e, f, g, h, i, j);
    
    else if (strcmp(i, a->i) < 0) a->fg = insereABRP2(filsGauche(a), e, f, g, h, i, j);
    
    else if (strcmp(i, a->i) > 0) a->fd = insereABRP2(filsDroit(a), e, f, g, h, i, j);
    
    else if (strcmp(i, a->i) == 0) {
        a->f += f;
        a->g++;
    }        
    else {
        return a;
    }
    return a;
}

// Tri par station
PArbre insereABRP3(PArbre a, Element e, Element f, float g, Element h, char *i, Element j) {
    if (!a) return creerArbre(e, f, g, h, i, j);
    
    else if (strcmp(i, a->i) < 0) a->fg = insereABRP3(filsGauche(a), e, f, g, h, i, j);
    
    else if (strcmp(i, a->i) > 0) a->fd = insereABRP3(filsDroit(a), e, f, g, h, i, j);
    
    else a->fm = insereABRP3(filsMilieu(a), e, f, g, h, i, j);
            
    return a;
}
