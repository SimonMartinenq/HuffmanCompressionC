#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"
#include "huffman_optimisation.h"

// fonction qui permet de tester la compression
void test_compression_fichier_huffman (){
    //TEST 1 : Nom incohérent
    compression_fichier_huffman("Unfichierqui n'existe pas", "Unautre", "EncoreUnAutre");
    // La fonction normalement rien ne se passe
    /**********************************************************/
    // TEST 2 : Même fichier pour tout
    compression_fichier_huffman("..\\Fichiers\\texte.txt", "..\\Fichiers\\texte.txt","..\\Fichiers\\texte.txt");
    // Avec cette fonction le programme va fonctionner mais ne va pas le fichier texte contiendra le dictionnaire à la fin
    // Cela repose aussi sur le bon sens de l'utilisateur.
    /**********************************************************/
    // TEST 3 : Utilisation de la bonne manière
    // Teste avec la bonne méthode
    compression_fichier_huffman("..\\Fichiers\\texte.txt", "..\\Fichiers\\huffman.txt","..\\Fichiers\\dico.txt");   
}

// fonction qui permet de tester la décompression classique : Il faut utiliser 
void test_decompression_fichier_huffman (){
    Element* liste = creation_LSC_occurrence("..\\Fichiers\\texte.txt"); 
    Noeud* arbre = creation_arbre_huffman(liste);
    //TEST 1 : Nom incohérent
    decompression_fichier_huffman("Unfichierqui n'existe pas", "Unautre", arbre);
    // La fonction normalement rien ne se passe
    /**********************************************************/
    // TEST 2 : Même fichier pour tout
    decompression_fichier_huffman("..\\Fichiers\\texte.txt", "..\\Fichiers\\texte.txt",arbre);
    // Avec cette fonction le programme va fonctionner mais ne va pas le fichier texte contiendra le dictionnaire à la fin
    // Cela repose aussi sur le bon sens de l'utilisateur.
    /**********************************************************/
    // TEST 3 : Avec un arbre NULL
    // Teste avec la bonne méthode
    decompression_fichier_huffman("..\\Fichiers\\huffman.txt", "..\\Fichiers\\decompression.txt", NULL);
    /**********************************************************/
    // TEST 4 : Utilisation de la bonne manière
    // Teste avec la bonne méthode
    decompression_fichier_huffman("..\\Fichiers\\huffman.txt", "..\\Fichiers\\decompression.txt", arbre);
}



// fonction qui permet de tester la compression
void test_compression_optimiser (){
    //TEST 1 : Nom incohérent
    compression_optimiser("Unfichierqui n'existe pas", "Unautre", "EncoreUnAutre");
    // La fonction normalement rien ne se passe
    /**********************************************************/
    // TEST 2 : Même fichier pour tout
    compression_optimiser("..\\Fichiers\\texte.txt", "..\\Fichiers\\texte.txt","..\\Fichiers\\texte.txt");
    // Avec cette fonction le programme va fonctionner mais ne va pas le fichier texte contiendra le dictionnaire à la fin
    // Cela repose sur le bon sens de l'utilisateur.
    /**********************************************************/
    // TEST 3 : Utilisation de la bonne manière
    // Teste avec la bonne méthode
    compression_optimiser("..\\Fichiers\\texte.txt", "..\\Fichiers\\huffman.txt","..\\Fichiers\\dico.txt");   
}


// fonction qui permet de tester la compression
void test_decompression_optimiser (){
    //TEST 1 : Nom incohérent
    decompression_optimiser("Unfichierqui n'existe pas", "Unautre", "EncoreUnAutre");
    // La fonction normalement rien ne se passe
    /**********************************************************/
    // TEST 2 : Même fichier pour tout
    decompression_optimiser("..\\Fichiers\\texte.txt", "..\\Fichiers\\texte.txt","..\\Fichiers\\texte.txt");
    // Avec cette fonction le programme va fonctionner mais ne va pas le fichier texte contiendra le dictionnaire à la fin
    // Cela repose sur le bon sens de l'utilisateur.
    /**********************************************************/
    // TEST 3 : Même fichier pour tout
    decompression_optimiser("..\\Fichiers\\huffman.txt", "..\\Fichiers\\huffman.txt","..\\Fichiers\\huffman.txt");
    /**********************************************************/
    // TEST 4 : Utilisation de la bonne manière
    // Teste avec la bonne méthode
    decompression_optimiser("..\\Fichiers\\decompression.txt", "..\\Fichiers\\huffman.txt","..\\Fichiers\\dico.txt"); 
}
