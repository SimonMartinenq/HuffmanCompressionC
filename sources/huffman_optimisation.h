#ifndef OPTIMISATION_H
#define OPTIMISATION_H

#include "huffman.h"

/*!
   \file huffman_optimisation.h
   \brief header de la bibliothéque qui gère l'optimisation des fonctions de huffman.
   \author Simon Martinenq
   \date 05/12/2020
*/

/**
* \typedef struct Arbre_AVL.
* \brief un Arbre_AVL est un abre binaire de recherche équilibré
*/

typedef struct Arbre_AVL{
    char letter; /**< la lettre contenue dans un noeud */
    char* codeBinaire; /**< code binaire de la lettre contenue dans le noeud*/
    // int balanceFactor;
    struct Arbre_AVL* gauche; /**< enfant gauche du neoud */
    struct Arbre_AVL* droite; /**< enfant droit du noeud */
}Arbre_AVL;

/*!
   \brief Cette fonction permet d’ajout un caractère
    dans un tableau de la structure Nœud par recherche dichotomique.

   \param Un pointeur d’un tableau de Nœud (Nœud**) où il faut ajouter le nouveau caractère
          Un pointeur d’entier qui contient la taille du tableau de Nœud
          Un caractère à ajouter.

   \return pas de valeur de retour puisque le tableau est directement modifié.
*/
void ajout_dichotomie (Noeud** tab_Noeud, int* taille, char caractere);

/*!
   \brief Cette fonction trie de manière croissante un tableau de type Nœud par rapport aux occurrences.
   \param Un tableau de type Nœud et La taille du tableau.
   \return Cette fonction ne possède pas de valeurs de retour.
*/
void trie_tableau(Noeud * tableau, size_t taille);

/*!
   \brief Cette fonction accompagne la fonction de trie
   \param Deux éléments d'un tableau contigu
   \return La valeur de retour est la différence entre les deux cases. 
*/
int compare_dichotomie(const void * a, const void * b);


/*!
   \brief Cette fonction vient accompagner la fonction qsort présente dans trie tableau,
    elle renvoie la différence entre deux cases d’un tableau.
   \param Un pointeur const de type void, qui représente une case du tableau
    et	un pointeur const de type void, qui représente la case suivante du tableau.
   \return Un entier, qui est la différence de deux occurrences
   dans deux cases adjacentes du tableau de Nœud.
*/
int compare_occurence(const void * a, const void * b);

/*!
   \brief Cette fonction sert à vérifier qu’une file est vide ou non.
   \param un pointeur sur une structure listeN qui est représente une file.
   \return 1 si la file est vide.
   \return  0 si la file n'est pas vide.
*/
int estvide (listeN* file);

/*!
   \brief Cette fonction suit la règle d’une file premier entrée, premier sortie (FIFO),
   elle ajoute le nouvel élément à la fin de la file.
   \param Double pointeur sur une structure listeN qui est représenté une file et
    un pointeur de type Nœud qui est le nœud à ajouter à la file.
   \return pas de valeur de retour puisque la file est directement modifié
*/
void enfiler_elem (listeN** file, Noeud* dataNoeud);

/*!
   \brief Cette fonction suit la règle d’une file premier entrée, premier sortie (FIFO),
   elle supprime le premier élément de la file.
   \param Un double pointeur une structure listeN qui est représenté une file.
   \return pas de valeur de retour puisque la file est directement modifié
*/
void defiler_elem (listeN** file);

/*!
   \brief Cette fonction créer un arbre de Huffman à partir d’un tableau de Nœud.
   \param Un pointeur de type Nœud qui représente le tableau des occurrences trié et la Taille du tableau de type Nœud.
   \return  NULL si le tableau est NULL
   \return sinon la racine de l’arbre de l’arbre de Huffman.
*/
Noeud* creation_arbre_file (Noeud* tableau, int taille_tab);

/*!
   \brief elle consiste à calculer la profondeur des sous-arbres droit et gauche d’un nœud et de la renvoyer.
   \param Cette fonction possède un seul paramètre qui est un AVL qui ne sera pas modifié par la fonction.
   \return entier qui correspond à la profondeur d’un nœud.
*/
int profondeur_noeud (Arbre_AVL* arbre);

/*!
   \brief Cette fonction calcul le balance factor d’un nœud.
   \param un AVL qui ne sera pas modifié par la fonction.
   \return entier qui correspond au balance facteur d’un nœud.
*/
int balanceFactor (const Arbre_AVL* arbre);

/*!
   \brief Cette fonction permet d’effectuer une rotation gauche-droite dans un arbre afin de le rendre équilibré.
   \param Double pointeur de type Arbre_AVL sur la racine de l’arbre.
   \return Pas de valeur de retour car l’arbre est directement modifié.
*/
void rotation_GD (Arbre_AVL** arbre);

/*!
   \brief Cette fonction permet d’effectuer une rotation droite-gauche dans un arbre afin de le rendre équilibré.
   \param Double pointeur de type Arbre_AVL sur la racine de l’arbre.
   \return Pas de valeur de retour car l’arbre est directement modifié.
*/
void rotation_DG (Arbre_AVL** arbre);

/*!
   \brief Cette fonction permet d’effectuer une rotation gauche-gauche dans un arbre afin de le rendre équilibré.
   \param Double pointeur de type Arbre_AVL sur la racine de l’arbre.
   \return Pas de valeur de retour car l’arbre est directement modifié.
*/
void rotation_GG (Arbre_AVL** arbre);

/*!
   \brief Cette fonction permet d’effectuer une rotation droite-droite dans un arbre afin de le rendre équilibré.
   \param Double pointeur de type Arbre_AVL sur la racine de l’arbre.
   \return Pas de valeur de retour car l’arbre est directement modifié.
*/
void rotation_DD (Arbre_AVL** arbre);

/*!
   \brief créer un AVL à partir d’un arbre de type Nœud.
   \param Un pointeur constant qui pointe sur un arbre de Huffman : arbre
    Un double pointeur de type Arbre_AVL (arbreAVL) qui est représente l’arbre que nous allons créer avec cette fonction
    Une chaine de caractère pour stocker le code binaire, codeBinaire
   Un entier qui indique la position dans la chaine de caractère, pos.
   \return pas de valeur de retour car l’AVL est directement modifier.
*/
void creation_AVL (const Noeud* arbre,Arbre_AVL** arbreAVL, char* codeBinaire, int pos);

/*!
   \brief equilibre un arbre de type Noeud grâce aus fonctions de rotation
   \param double pointeur de type Arbre_AVL sur la racine de l’arbre,
   ce qui va permettre de modifier la mémoire directement lors de l’équilibrage de l’arbre.
   \return pas de valeur de retour car l’arbre est directement modifié.
*/
void equilibrage_AVL (Arbre_AVL** arbre);

/*!
   \brief compresser un fichier texte en fichier binaire grâce à la méthode de Huffman de manière optimiser.
   Le fichier texte n’est pas modifié, seul le fichier binaire et le dictionnaire sont modifiés.
   \param Un pointeur de char qui représente le nom du fichier contenant le texte
          Un pointeur de char qui représente le nom du fichier qui contiendra le code binaire résultant
          Un pointeur de char qui représente le nom du fichier contenant le dictionnaire.
   \return pas de valeurs de retour.
*/
void compression_optimiser (char* fichierTexte, char* fichierBinaire, char* fichierDictionnaire);

/*!
   \brief écrire le dictionnaire d’un arbre de Huffman dans un fichier texte afin qu’il soit réutilisable pour décoder un texte en binaire.
   \param Un pointeur de type char, Nomfichier, qui représente la chaine de caractère qui représente le nom du fichier ou il faut écrire le dictionnaire
          Un AVL ou arbre équilibré, arbre, de type Arbre_AVL qui est un arbre contenant le dictionnaire.
   \return pas de valeur de retour.
*/
void ecriture_dictionnaire_AVL (char* Nomfichier, Arbre_AVL* arbre);

/*!
   \brief décompresser un fichier binaire en fichier texte grâce à la méthode de Huffman de manière optimiser.
   \param Un pointeur de char qui représente le nom du fichier contenant le texte
          Un pointeur de char qui représente le nom du fichier qui contiendra le code binaire résultant
          Un pointeur de char qui représente le nom du fichier contenant le dictionnaire.
   \return pas de valeurs de retour. 
*/
void decompression_optimiser (char* fichierTexte, char* fichierBinaire, char* fichierDictionnaire);
#endif // OPTIMISATION_H
