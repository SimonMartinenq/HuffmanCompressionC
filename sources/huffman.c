#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "huffman.h"

#define OCTET 8


// Fonction qui crée un fichier en binaire à partir d'un texte
int ecriture_fichier_binaire(char* namefileIn, char* namefileOut) {
    FILE* file = fopen(namefileIn, "r+");
    FILE* out = fopen(namefileOut, "w+");
    if (file != NULL) {
        char binaryCode[9];
        char letter;
        while (fscanf(file, "%c", &letter) == 1) {
            for (size_t i = 0; i < OCTET; i++) {
                if (letter >= pow(2, OCTET - (i + 1))) {
                    binaryCode[i] = '1';
                    letter -= pow(2, OCTET - (i + 1));
                }else {
                    binaryCode[i] = '0';
                }
            }
            binaryCode[OCTET] = '\0';
            fprintf(out, "%s", binaryCode);
        }
        fclose(file);
        fclose(out);
        return 1;
    }
    else {
        return 0;
    }
}

/***************************************HUFFMAN************************************/

Element* creation_LSC_occurrence(char* nameFile) {
    FILE* file = fopen(nameFile, "r");
    Element* liste = NULL;
    char let;

    if (file != NULL) {
        liste = (Element*)malloc(sizeof(Element));
        fscanf(file, "%c", &let);
        liste->letter = let;
        liste->occurrence = 1;
        liste->next = NULL;

        while (fscanf(file, "%c", &let) == 1) {
            Element* tmp = liste;
            while (tmp->next != NULL && tmp->letter != let) {
                tmp = tmp->next;
            }
            if (tmp->letter == let) {
                tmp->occurrence++;
            }else {
                Element* new_elem = malloc(sizeof(Element));
                new_elem->letter = let;
                new_elem->occurrence = 1;
                new_elem->next = NULL;
                tmp->next = new_elem;
            }
        }
        fclose(file);
    }
    return liste;
}

listeN* creation_liste_noeud (const Element* liste){
    if (liste != NULL){
        listeN* listeF = NULL;
        listeN* tmp = NULL;
        int boolean = 0;
        while(liste != NULL){
            listeN* nouv_elem  = malloc(sizeof(listeN));
            if(boolean == 0){ // retenir le premier element de la liste
                listeF = nouv_elem;
                boolean = 1;
            }
            Noeud* noeud = malloc(sizeof(Noeud));
            noeud->letter = liste->letter;
            noeud->occurence = liste->occurrence;
            noeud->droite = NULL;
            noeud->gauche = NULL;
            nouv_elem->data = noeud;
            nouv_elem->next = NULL;
            if (tmp != NULL){
                tmp->next = nouv_elem;
            }
            tmp = nouv_elem;
            liste = liste->next;
        }
        return listeF;
    }
    return NULL;
}

// Fonction de recherche du min d'une liste
listeN* minimum_liste_noeud (listeN* liste){
    if (liste != NULL){
        while(liste->data == NULL){
            liste = liste->next;
        }
        size_t min = liste->data->occurence;
        listeN* ListeMin = liste;
        liste = liste->next;
        while (liste != NULL){
            if (NULL != liste->data){
                if (min >= liste->data->occurence){
                    ListeMin = liste;
                    min = liste->data->occurence;
                }
            }
            liste = liste->next;
        }
        return ListeMin;
    }
    return NULL;
}



Noeud* creation_arbre_huffman (Element* liste){
    if (NULL != liste){
        listeN* l_noeud = malloc(sizeof(l_noeud));
        // Création d'une liste de Noeud
        l_noeud = creation_liste_noeud(liste);
        size_t taille_liste= 0, pos_courant =0;
        listeN* tmp = l_noeud;
        while(tmp != NULL){
            tmp = tmp->next;
            taille_liste++;
        }
        do{
            Noeud* noeud_somme = malloc(sizeof(Noeud));
            // Premier minimum
            listeN* min = minimum_liste_noeud(l_noeud);
            noeud_somme->letter = '|'; // Ne contiendra pas de lettre
            noeud_somme->gauche = min->data;
            min->data = NULL;
            // Deuxième minimum 
            min = minimum_liste_noeud(l_noeud);
            noeud_somme->droite = min->data;
            min->data = noeud_somme;

            noeud_somme->occurence = noeud_somme->gauche->occurence + noeud_somme->droite->occurence;
        }while (++pos_courant < taille_liste-1 );
        // On libère les elements de la liste
        listeN* arbreFinal = NULL;
        while (l_noeud != NULL){
            if (l_noeud->data != NULL){
                arbreFinal = l_noeud; 
                l_noeud = l_noeud->next;
            }else{
                listeN* old = l_noeud; 
                l_noeud = l_noeud->next;
                free(old); 
            }
        }
        return arbreFinal->data;
    }
    return NULL;
}



// Fonction qui permet de crée le dictionnaire propre à un arbre de huffman
void ecriture_dictionnaire_fichier (char* Nomfichier, Noeud* arbre, char* codeBinaire, int pos){
    if(arbre != NULL){
        if(arbre->gauche == NULL && arbre->droite == NULL){
            FILE* fichier = fopen(Nomfichier, "a");
            if (fichier != NULL){
                codeBinaire[pos] = '\0';
                fprintf(fichier,"%c : %s\n",arbre->letter,codeBinaire);
            }
            fclose(fichier);
        }else {
            codeBinaire[pos] = '0';
            ecriture_dictionnaire_fichier(Nomfichier, arbre->gauche, codeBinaire, pos+1);
            codeBinaire[pos] ='1';
            ecriture_dictionnaire_fichier(Nomfichier, arbre->droite, codeBinaire, pos+1);
        }
    }
}

//F
void ecriture_fichier_binaire_huffman (char* nomFichierTexte, char* nomFichierBinaire, char* nomFichierDictionnaire){
    FILE* fichierE = fopen(nomFichierTexte, "r");
    if (fichierE != NULL){
        FILE* fichierS = fopen(nomFichierBinaire, "w+");
        FILE* fichierDico = fopen(nomFichierDictionnaire, "r");
        if (fichierS != NULL && fichierDico != NULL){
            char lettre, lettreChercher, codeBinaire;

            while ((lettre = fgetc(fichierE)) != EOF){
                do{
                    // On parcours le fichier dictionnaire pour trouver le code binaire correspondant à la lettre du fichier texte
                    if ((lettreChercher = fgetc(fichierDico)) != EOF && lettre == lettreChercher){
                        fseek(fichierDico, 3 , SEEK_CUR); // Permet de déplacer le curseur de deux cases vers la droite
                        while ((codeBinaire = fgetc(fichierDico)) != '\n'){
                            fprintf(fichierS,"%c", codeBinaire);
                        }
                    }else {
                        while (fgetc(fichierDico) != '\n'); // Permet de déplacer le curseur jusqu'a la fin de la ligne
                    }
                }while( lettre != lettreChercher);
                rewind(fichierDico); // Permet de replacer le curseur du fichier du dictonnaire au début
            }
            fclose(fichierS);
            fclose(fichierDico); 
        }else{
            printf("Erreur lors de l'ouverture des fichiers !\n");
        }
        fclose(fichierE);
    }
}


// Fonction qui fait appel au toute les fonctions pour compresser
void compression_fichier_huffman (char* nomFichierTexte, char* nomFichierBinaire, char* nomFichierDictionnaire){
    FILE* fichierE = fopen(nomFichierTexte, "r");
    if (fichierE != NULL){
        // Creation de l'arbre et du dictionnaire pour travailler
        Element* liste = creation_LSC_occurrence(nomFichierTexte);
        Noeud* arbreH = creation_arbre_huffman(liste);
        char codeBinaire[BUFSIZ];
        FILE* fic = fopen(nomFichierBinaire, "w"); // Pour ecraser ce qu'il y a dans le fichier
        fclose(fic);
        // Ecriture du dictionnaire propre à notre arbre de Huffman
        ecriture_dictionnaire_fichier(nomFichierDictionnaire, arbreH, codeBinaire, 0);
        // Codage avec le code de Huffman
        ecriture_fichier_binaire_huffman(nomFichierTexte, nomFichierBinaire, nomFichierDictionnaire);
        fclose(fichierE);
    }
}

// Fonction qui fait appel au toute les fonctions pour décompresser
void decompression_fichier_huffman (char* nomFichierBinaire, char* nomFichierTexte, const Noeud* arbre){
    FILE* fichierE = fopen(nomFichierBinaire, "r");
    FILE* fichierS = fopen(nomFichierTexte, "w+");
    if (fichierE != NULL && fichierS != NULL){
        char lettre;
        const Noeud* tmp = arbre;
        while ((lettre = fgetc(fichierE)) != EOF){
            if (lettre == '0'){
                tmp = tmp->gauche;
            }else if (lettre == '1'){
                tmp = tmp->droite;
            }else{
                printf("ERREUR : CE N'EST PAS DU BINAIRE!\n");
            }
            if (tmp->droite == NULL && tmp->gauche == NULL){
                fprintf(fichierS,"%c", tmp->letter);
                tmp = arbre;
            }
        }
        fclose(fichierE); 
        fclose(fichierS);
    }
}
