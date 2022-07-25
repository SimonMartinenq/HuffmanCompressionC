#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"
#include "huffman_optimisation.h"
#include "affichage_console.h"


int main(int argc, char const* argv[]) {

    int choix = 0, val, val2; 
    Element* liste = NULL; 
    Noeud* arbre = NULL; 

    FILE* fic = fopen("..\\Fichiers\\huffman.txt", "w"); // Pour ecraser ce qu'il y a dans le fichier
    fclose(fic);
    fic = fopen("..\\Fichiers\\sortie.txt", "w"); // Pour ecraser ce qu'il y a dans le fichier
    fclose(fic);
    fic = fopen("..\\Fichiers\\dico.txt", "w"); // Pour ecraser ce qu'il y a dans le fichier
    fclose(fic);
    fic = fopen("..\\Fichiers\\decompression.txt", "w"); // Pour ecraser ce qu'il y a dans le fichier
    fclose(fic);

    while (choix != -1){
        printf("\n\n\n\t\t\tMENU\n"); 
        printf(" - 1. Conversion d'un fichier texte en binaire par rapport au code ascii\n"); 
        printf(" - 2. Afficher la taille d'un fichier\n"); 
        printf(" - 3. Compression avec la methode de Huffman classique\n"); 
        printf(" - 4. Decompression avec la methode de Huffman classique\n");
        printf(" - 5. Compression avec la methode optimiser de Huffman\n");
        printf(" - 6. Decompression avec la methode optimiser de Huffman\n");
        printf(" - -1 . QUITTER\n");
        printf("Choisir ce que vous souhaitez faire: "); 
        scanf("%d", &choix); 
        switch (choix){
            case 1 : 
                ecriture_fichier_binaire("..\\Fichiers\\texte.txt", "..\\Fichiers\\sortie.txt");
                break;
            case 2 :
                val = nombre_char_fichier("..\\Fichiers\\sortie.txt");
                printf("\n\tLe nombre de caractere du fichier sortie.txt est de %d\n", val);
                val2 = nombre_char_fichier("..\\Fichiers\\huffman.txt");
                printf("\n\tLe nombre de caractere du fichier huffman.txt est de %d\n", val2);
                if (val2 != 0){
                    printf("\n\tLe taux de compression du fichier est de : %f %c", (float)(1 - (float)((float)val2/val))*100, '%'); 
                }
                break; 
            case 3 :
                fic = fopen("..\\Fichiers\\dico.txt", "w"); // Pour ecraser ce qu'il y a dans le fichier
                fclose(fic);
                compression_fichier_huffman("..\\Fichiers\\texte.txt", "..\\Fichiers\\huffman.txt","..\\Fichiers\\dico.txt");
                printf("\n\tCompression REUSSI du fichier texte.txt vers le fichier huffman.txt !\n");
                break; 
            case 4: 
                liste = creation_LSC_occurrence("..\\Fichiers\\texte.txt"); 
                arbre = creation_arbre_huffman(liste); 
                decompression_fichier_huffman("..\\Fichiers\\huffman.txt", "..\\Fichiers\\decompression.txt", arbre);
                break; 
            case 5 :
                fic = fopen("..\\Fichiers\\dico.txt", "w"); // Pour ecraser ce qu'il y a dans le fichier
                fclose(fic);
                compression_optimiser("..\\Fichiers\\texte.txt", "..\\Fichiers\\huffman.txt","..\\Fichiers\\dico.txt"); 
                break; 
            case 6:
                decompression_optimiser("..\\Fichiers\\decompression.txt", "..\\Fichiers\\huffman.txt","..\\Fichiers\\dico.txt"); 
                break;
            case -1:
                printf("\n\tAu revoir !\n");
                break;  
            default:
                printf("\n\tCe choix n'est pas disponible !\n"); 
                break;
        } 
        printf("\n\n");
    }
    return 0;
}


