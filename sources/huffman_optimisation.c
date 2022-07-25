#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman_optimisation.h"
#include "affichage_console.h" // En option pour

/***********************************OPTIMISATION***************************************/

// Fonction qui accompagne qsort
int compare_dichotomie(const void * a, const void * b){
    Noeud const* pa=(Noeud*)a;
    Noeud const* pb=(Noeud*)b;

    return strcmp(&(pa->letter),&(pb->letter));
}

// Ajout par une recherche dichotomique 
void ajout_dichotomie (Noeud** tab_Noeud, int* taille, char caractere){
    if (NULL == *tab_Noeud){
        // Allocation d'un nouveau Noeud
        *tab_Noeud = malloc(sizeof(Noeud));
        (*tab_Noeud)->letter = caractere;
        (*tab_Noeud)->occurence = 1;
        (*tab_Noeud)->droite = NULL;
        (*tab_Noeud)->gauche = NULL;
        (*taille)++;
    }else{
        int pos = ((*taille)-1)/2; // On se placer au milieu
        int min = 0, max = (*taille) - 1;
        int ajout = 0;
        do{
            if ((*tab_Noeud)[pos].letter == caractere){
                (*tab_Noeud)[pos].occurence += 1; // Si il sont egaux, on ajoute une occurrence
                min = max;
                ajout = 1;
            }else if ((*tab_Noeud)[pos].letter < caractere){
                min = pos;
                if (max - min % 2 != 0){
                    pos = ((max - min)+1) / 2 + min;
                }else {
                    pos = (max - min) / 2 + min;
                }
                if (pos == (*taille)-2 && (*tab_Noeud)[(*taille)-1].letter == caractere){
                    (*tab_Noeud)[(*taille)-1].occurence += 1;
                    ajout = 1;
                }
            }else if ((*tab_Noeud)[pos].letter > caractere){
                max = pos;
                if (pos == 1 && (*tab_Noeud)[0].letter == caractere){
                    (*tab_Noeud)[0].occurence += 1;
                    ajout = 1;
                }else{
                    pos = max - ((max - min)/2);
                }
            }
        } while (max - min > 1); // Tant que la dichotomie n'est pas fini
        // Si le caractère n'étant pas présent pas de le tableau on l'ajoute à la fin
        if (ajout == 0){
            *tab_Noeud = realloc(*tab_Noeud, (*taille+1)* sizeof(Noeud));
            (*tab_Noeud)[*taille].letter = caractere;
            (*tab_Noeud)[*taille].occurence = 1;
            (*taille)++;
        }
        // Trie du tableau en fonction des caractères
        qsort(*tab_Noeud, *taille, sizeof(Noeud), compare_dichotomie);
    }
}

// Fonction qui accompagne qsort
int compare_occurence(const void * a, const void * b){
  Noeud* pa=(Noeud*)a;
  Noeud* pb=(Noeud*)b;
  return pa->occurence - pb->occurence;
}

void trie_tableau(Noeud * tableau, size_t taille){
    qsort(tableau,taille, sizeof(Noeud),compare_occurence);
}


/**************************************************************************/
// Fonction pour vérifier si la file est vide
int est_vide (listeN* file){
    if (file != NULL && file->data != NULL){
        return 0;
    }
    return 1;
}

// Fonction pour enlever un element à la file 
void defiler_elem (listeN** file){
    if (file != NULL){
        listeN* old = *file;
        (*file) = (*file)->next;
        free(old);
    }
}

// Fonction pour ajouter un element à la file 
void enfiler_elem (listeN** file, Noeud* dataNoeud){
    if (file != NULL){
        if ((*file) == NULL){
            (*file) = malloc(sizeof(listeN)); 
            (*file)->data = dataNoeud; 
            (*file)->next = NULL;
        }else if ((*file)->data == NULL){
            (*file)->data = dataNoeud; 
            (*file)->next = NULL;
        }else {
            enfiler_elem(&((*file)->next), dataNoeud);
        }
    }
}

Noeud* creation_arbre_file (Noeud* tableau, int taille_tab){
    if (tableau != NULL){
        //Création des files
        listeN* fileTab = malloc(sizeof(listeN));
        listeN* fileStockage = malloc(sizeof(listeN));
        fileStockage->data = NULL; 
        fileStockage->next = NULL; 
        
        // On remplis fileTab avec les éléments du tableau
        listeN* tmp = NULL;
        for (size_t i = 0; i < taille_tab; i++){
            Noeud* nouveau = malloc(sizeof(Noeud));
            nouveau->occurence = tableau[i].occurence;
            nouveau->letter = tableau[i].letter;
            nouveau->gauche = NULL;
            nouveau->droite = NULL;
            if (NULL == tmp){
                fileTab->data = nouveau;
                fileTab->next = NULL;
                tmp = fileTab;
            }else{
                listeN* nouv_elem = malloc(sizeof(listeN));
                nouv_elem->data = nouveau;
                nouv_elem->next = NULL;
                tmp->next = nouv_elem;
                tmp = tmp->next;
            }
        }
        while (fileTab != NULL){
            // On crée un noeud et on remplis ses sous-arbre gauche et droit
            Noeud* noeudParent = malloc (sizeof(Noeud));
            
            if (est_vide(fileStockage) == 1){
                noeudParent->gauche = fileTab->data;
                defiler_elem(&fileTab);
                noeudParent->droite = fileTab->data;
                defiler_elem(&fileTab);
            }
            // Si les occurrences sont egaux ou plus petite on prend pioche dans la file : fileTab
            else if (fileTab->data->occurence <= fileStockage->data->occurence){
                noeudParent->gauche = fileTab->data;
                defiler_elem(&fileTab);
                if (fileTab != NULL && fileStockage != NULL && fileTab->data->occurence <= fileStockage->data->occurence){
                    noeudParent->droite = fileTab->data;
                    defiler_elem(&fileTab);
                }else {
                    noeudParent->droite = fileStockage->data;
                    defiler_elem(&fileStockage);
                }
            }
            else{
                noeudParent->gauche = fileStockage->data;
                defiler_elem(&fileStockage);
                if (est_vide(fileStockage) == 1){
                    noeudParent->droite = fileTab->data;
                    defiler_elem(&fileTab); 
                }else if (fileTab != NULL && fileStockage != NULL && fileTab->data->occurence <= fileStockage->data->occurence){
                    noeudParent->droite = fileTab->data;
                    defiler_elem(&fileTab);
                }else {
                    noeudParent->droite = fileStockage->data;
                    defiler_elem(&fileStockage);
                }
            }
            noeudParent->occurence = noeudParent->gauche->occurence +  noeudParent->droite->occurence; 
            noeudParent->letter = '|'; 
            enfiler_elem(&fileStockage, noeudParent);
        }
        // Si il reste plusieurs noeud à la suite dans la deuxième file : fileStockage, on les fusion dans des noeuds
        if (fileTab == NULL && fileStockage->next != NULL){
            while (fileStockage->next != NULL){
                Noeud* noeudParent = malloc (sizeof(Noeud));
                noeudParent->gauche = fileStockage->data;
                defiler_elem(&fileStockage);
                noeudParent->droite = fileStockage->data;
                defiler_elem(&fileStockage);
                noeudParent->letter = '|'; 
                noeudParent->occurence = noeudParent->gauche->occurence + noeudParent->droite->occurence; 
                enfiler_elem(&fileStockage, noeudParent); 
            }
        }
        return fileStockage->data;
    }
    return NULL;
}


/*******************************************************************/
//Calcul la profondeur d'un noeud
int profondeur_noeud (const Arbre_AVL* arbre){
    if (NULL == arbre){
        return 0;
    }else {
        if ((1 + profondeur_noeud(arbre->gauche)) > (1 + profondeur_noeud(arbre->droite))){
            return 1 + profondeur_noeud(arbre->gauche); 
        }else {
            return 1 + profondeur_noeud(arbre->droite); 
        }
    }
}

int balanceFactor (const Arbre_AVL* arbre){
    if (arbre == NULL){
        return 0;
    }else if (arbre->gauche == NULL && arbre->droite == NULL){
        return 0; 
    }else {
        int cote_gauche = profondeur_noeud(arbre->gauche); 
        int cote_droit = profondeur_noeud(arbre->droite);
        return cote_droit - cote_gauche ; //on fait la différence des profondeurs
    }
}

void rotation_DD (Arbre_AVL** arbre){
    Arbre_AVL* tmp = *arbre; 
    tmp = tmp->droite; 
    if (tmp->gauche != NULL){
        (*arbre)->droite = tmp->gauche;
        tmp->gauche = (*arbre); 
    }else {
        tmp->gauche = (*arbre); 
        (*arbre)->droite = NULL;
    }
    (*arbre) = tmp; 
} 

void rotation_GG (Arbre_AVL** arbre){
    Arbre_AVL* tmp = *arbre; 
    tmp = tmp->gauche; 
    if (tmp->droite != NULL){
        (*arbre)->gauche = tmp->droite;
        tmp->droite = (*arbre); 
    }else{
        tmp->droite = (*arbre); 
        (*arbre)->gauche = NULL;
    }
    (*arbre) = tmp; 
} 

void rotation_DG (Arbre_AVL** arbre){
    Arbre_AVL* tmp = *arbre;
    tmp = tmp->droite; 
    if (tmp->gauche != NULL){
        Arbre_AVL* old = tmp; 
        tmp = tmp->gauche; 
        old->gauche = tmp->droite; 
        tmp->droite = (*arbre)->droite; 
        (*arbre)->droite = tmp->gauche; 
        tmp->gauche = (*arbre); 
        (*arbre) = tmp;
    }
} 

void rotation_GD (Arbre_AVL** arbre){
    Arbre_AVL* tmp = *arbre;
    tmp = tmp->gauche; 
    if (tmp->droite != NULL){
        Arbre_AVL* old = tmp; 
        tmp = tmp->droite; 
        old->droite = tmp->gauche; 
        tmp->gauche = (*arbre)->gauche;
        (*arbre)->gauche = tmp->droite;
        tmp->droite = (*arbre);  
        (*arbre) = tmp;
    }
} 


//L
void creation_AVL (const Noeud* arbre,Arbre_AVL** arbreAVL, char* codeBinaire, int pos){
    if (arbre != NULL){
        if (arbre->gauche == NULL && arbre->droite == NULL){
            // Création du Noeud de l'AVL
            Arbre_AVL* nouv_AVL = malloc(sizeof(Arbre_AVL)); 
            nouv_AVL->letter = arbre->letter;
            nouv_AVL->gauche = NULL; 
            nouv_AVL->droite = NULL; 
            codeBinaire[pos] = '\0'; 
            //Calcul de la taille d'une chaine de caractère
            int taille = strlen(codeBinaire);
            nouv_AVL->codeBinaire = malloc(taille * sizeof(char));
            for (size_t i = 0; i <= taille; i++){
                nouv_AVL->codeBinaire[i] = codeBinaire[i]; 
            }            
            if (*arbreAVL == NULL){
                *arbreAVL = nouv_AVL;
            }else{
                Arbre_AVL* tmp = *arbreAVL; 
                // Parcours de l'AVL pour savoir où mettre le nouveau noeud
                while (tmp != NULL){
                    if(nouv_AVL->letter < tmp->letter){
                        if (tmp->gauche == NULL){
                            tmp->gauche = nouv_AVL;
                            tmp = tmp->gauche;  
                        }
                        tmp = tmp->gauche; 
                    }else {
                        if (tmp->droite == NULL){
                            tmp->droite = nouv_AVL; 
                            tmp = tmp->droite;
                        }
                        tmp = tmp->droite;
                    }
                }
            }
            // Un AVL doit constamment être équilibré
            equilibrage_AVL(arbreAVL); 
        }else{
            // Un déplacement à gauche est 
            codeBinaire[pos] = '0'; 
            creation_AVL(arbre->gauche, arbreAVL, codeBinaire, pos+1); 
            codeBinaire[pos] = '1'; 
            creation_AVL(arbre->droite, arbreAVL, codeBinaire, pos+1); 
        }
    }
}

void equilibrage_AVL (Arbre_AVL** arbre){
    if (*arbre != NULL){
        equilibrage_AVL(&((*arbre)->gauche)); 
        equilibrage_AVL(&((*arbre)->droite));
        int bf = balanceFactor(*arbre);
        // Si le balance Factor n'est pas 1, 0 ou -1 alors il faut rééquilibré l'arbre
        if (bf > 1 || bf < -1 ){
            do{
                if (bf > 0){ // Je sais que si bf est positif il y a plus de noeud à droite
                    if (balanceFactor((*arbre)->droite) > 0){
                        rotation_DD(arbre); 
                    }else{
                        rotation_DG(arbre); 
                    }
                }else { // et inversement si c'est negatif. 
                    if (balanceFactor((*arbre)->gauche) < 0){
                        rotation_GG(arbre); 
                    }else{
                        rotation_GD(arbre); 
                    }
                }
            }while (balanceFactor(*arbre) > 1 || balanceFactor(*arbre) < -1);
        }
    }
}


//M 
void compression_optimiser (char* fichierTexte, char* fichierBinaire, char* fichierDictionnaire){
    FILE* fichierE = fopen(fichierTexte, "r"); 
    FILE* fichierS = fopen(fichierBinaire, "w"); 
    if (fichierE != NULL && fichierS != NULL){
        Noeud* tableauDico = NULL;
        int taille = 0;  
        char letter; 
        while (fscanf(fichierE, "%c", &letter) == 1){
            ajout_dichotomie(&tableauDico, &taille, letter); 
        }
        trie_tableau(tableauDico, taille);
        // afficherTab(tableauDico, taille); 
        Noeud* arbreHuffman = creation_arbre_file(tableauDico, taille); 
        // affichage_arbre(arbreHuffman); 
        printf("\n\n");

        Arbre_AVL* arbreAVL = NULL; 
        char codeBinaire[BUFSIZ]; 
        creation_AVL(arbreHuffman, &arbreAVL, codeBinaire, 0); 
        // afficher_AVL(arbreAVL); 
        rewind(fichierE); // Permet de replacer le curseur du fichier du dictonnaire au début
        ecriture_dictionnaire_AVL(fichierDictionnaire, arbreAVL); 
        // Compression
        Arbre_AVL* tmp = NULL; 
        while (fscanf(fichierE, "%c", &letter) == 1){
            tmp = arbreAVL; 
            while (tmp->letter != letter && tmp != NULL){
                if(tmp->letter > letter){   
                    tmp = tmp->gauche;
                }else{
                    tmp = tmp->droite;
                }        
            }
            fprintf(fichierS, "%s", tmp->codeBinaire); 
        }
        fclose(fichierE); 
        fclose(fichierS); 
    }
}


//N 
void ecriture_dictionnaire_AVL (char* Nomfichier, Arbre_AVL* arbre){
    if(arbre != NULL){
        FILE* fichier = fopen(Nomfichier, "a");
        if (fichier != NULL){
            fprintf(fichier,"%c : %s\n",arbre->letter,arbre->codeBinaire);
        }
        fclose(fichier);
        ecriture_dictionnaire_AVL(Nomfichier, arbre->gauche);
        ecriture_dictionnaire_AVL(Nomfichier, arbre->droite);
    }
}

void decompression_optimiser (char* fichierTexte, char* fichierBinaire, char* fichierDictionnaire){
    FILE* fichierDico = fopen(fichierDictionnaire, "r"); 
    FILE* fichierE = fopen(fichierBinaire, "r"); 
    FILE* fichierS = fopen(fichierTexte, "w"); 

    if (fichierDico != NULL && fichierE != NULL && fichierS != NULL){
        Noeud* arbreHuffman = malloc(sizeof(Noeud));
        arbreHuffman->occurence = 0;
        arbreHuffman->letter = '|'; 
        arbreHuffman->droite = NULL;  
        arbreHuffman->gauche = NULL;

        char lettre, bit;
        Noeud* tmp = NULL; 
        // On recreer l'arbre de Huffman  
        while ((lettre = fgetc(fichierDico)) != EOF){
            fseek(fichierDico, 3 , SEEK_CUR); // Permet de déplacer le curseur de deux cases vers la droite
            tmp = arbreHuffman; // On part de la racine
            do{
                bit = fgetc(fichierDico);
                if (bit == '\n'){
                    tmp->letter = lettre;
                    tmp->occurence = 0; 
                }
                else if(bit == '0'){
                    if(tmp->gauche == NULL){
                        // Allocation si le noeud n'existe pas
                        tmp->gauche = malloc(sizeof(Noeud));
                        tmp = tmp->gauche; 
                        tmp->occurence = 0; 
                        tmp->letter = '|'; 
                        tmp->droite = NULL;                         
                        tmp->gauche = NULL;                         
                    }else{
                        tmp = tmp->gauche; 
                    }
                }
                else {
                    if(tmp->droite == NULL){
                        tmp->droite = malloc(sizeof(Noeud));
                        tmp = tmp->droite; 
                        tmp->occurence = 0; 
                        tmp->letter = '|'; 
                        tmp->droite = NULL;                         
                        tmp->gauche = NULL;                         
                    }else{
                        tmp = tmp->droite; 
                    }
                }
            }while (bit != '\n');
        }
        // L'arbre a été crée entièrement, on se place dans l'abre et on suit les branches après
        tmp = arbreHuffman;
        while ((bit = fgetc(fichierE)) != EOF){
            if (bit == '0'){
                tmp = tmp->gauche;           
            }else{
                tmp = tmp->droite; 
            }
            if(tmp->letter != '|'){
                fprintf(fichierS, "%c", tmp->letter);
                tmp = arbreHuffman;  
            }   
        }
        fclose(fichierDico);
        fclose(fichierE);
        fclose(fichierS);
    }

}