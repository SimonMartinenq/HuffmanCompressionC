#include <stdio.h>
#include <stdlib.h>

#include "affichage_console.h"

// Fonction pour afficher le nombre de charactère dans un fichier
int nombre_char_fichier(char* nameFile) {
    FILE* fichier = fopen(nameFile, "r");
    
    char letter;
    if (fichier != NULL) {
        int value = 0;
        while (fscanf(fichier, "%c", &letter) == 1) {
            value++;
        }
        return value;
    }
    else return -1;
}


void afficher_liste(Element* liste) {
    if (liste != NULL) {
        printf("(%c;%I64d)-> ", liste->letter, liste->occurrence);
        afficher_liste(liste->next);
    }
    else if (liste == NULL) {
        printf("NULL\n");
    }
}

// FONCTION DE TEST
void afficher_listeN (listeN* liste){
    if (liste != NULL){
        if (liste->data != NULL){
            printf("(%c,%d)->", liste->data->letter, liste->data->occurence);
        }else {
            printf("(NULL)->");
        }
        afficher_listeN(liste->next);
    }
}

void affichage_arbre(Noeud* arbre){
    if(NULL != arbre){
        printf("  (%c|%d)  : ", arbre->letter, arbre->occurence);
        if (arbre->gauche != NULL){
            printf("gauche %c ", arbre->gauche->letter); 
        }else{
            printf("NULL "); 
        }
        if (arbre->droite != NULL){
            printf("droite %c \n", arbre->droite->letter); 
        }else{
            printf("NULL\n"); 
        }
        affichage_arbre(arbre->gauche);
        affichage_arbre(arbre->droite);
    }
}


void afficherTab (const Noeud* tab, int taille){
    if (tab != NULL){
        for (size_t i = 0; i < taille; i++){
            printf("[%c,%d] ", tab[i].letter, tab[i].occurence);
        }
        printf("\n");
    }else{
        printf("NULL\n");
    }
}

void afficher_AVL (Arbre_AVL* arbre){
    if(NULL != arbre){
        printf("  (%c|%s)  : ", arbre->letter, arbre->codeBinaire);
        if (arbre->gauche != NULL){
            printf("gauche %c ", arbre->gauche->letter); 
        }else{
            printf("NULL "); 
        }
        if (arbre->droite != NULL){
            printf("droite %c \n", arbre->droite->letter); 
        }else{
            printf("NULL\n"); 
        }
        afficher_AVL(arbre->gauche);
        afficher_AVL(arbre->droite);
    }
}

