/*!
   \file huffman.h
   \brief header de la bibliothéque qui gère les fonctions de huffman.
   \author Jean Mopin DIET jean.mopin@efrei.net
   \date 05/12/2020
*/
#include <stdio.h>
#include <stdlib.h>

#ifndef HUFFMAN_H
#define HUFFMAN_H

/**
* \typedef struct Element 
* \brief Element est une liste d'éléments
*/
typedef struct Element {
    char letter; /**< la lettre  */
    size_t  occurrence ; /**<l'occurence de la lettre */
    struct Element* next; /**< Un pointeur sur l'élément suivant */
}Element;

/**
* \typedef struct Noeud 
* \brief Noeud est un arbre de noeuds
*/
typedef struct Noeud{
    size_t occurence;/**<l'occurence de la lettre */
    char letter; /**< la lettre  */
    struct Noeud* gauche; /**< Un pointeur sur le sous arbre gauche */
    struct Noeud* droite; /**< Un pointeur sur le sous arbre droit */
}Noeud;

/**
* \typedef struct ListeN 
* \brief ListeN est une liste de noeuds
*/
typedef struct listeN {
    Noeud* data; /**< le noeud contenant la lettre et son occurrence  */
    struct listeN* next; /**< Un pointeur sur le noeud  suivant */
}listeN;


/**
 * \brief Fonction qui crée une liste d'occurrences 
 * \param namefile : le nom du fichier texte
 * \return le pointeur sur la liste d'éléments, si elle a été créée, NULL sinon 
 */

Element* creation_LSC_occurrence(char* nameFile);

/**
 * \brief Fonction qui affiche une liste 
 * 
 * \param liste : la liste à afficher 
 * \return pas de valeur de retour
 */

void afficher_liste(Element* liste); 

/**
 * \brief Fonction qui crée une liste de noeuds
 * 
 * \param liste : la liste d'éléments servant de base pour créer la liste de noeuds
 * \return le pointeur sur la liste de noeuds, si elle a été créée, NULL sinon 
 */

listeN* creation_liste_noeud (const Element* liste); 

/**
 * \brief Fonction renvoie le minimum d'une liste de noeuds 
 * 
 * \param liste : la liste de noeuds en question 
 * \return le pointeur sur la plus petite liste de noeuds 
 */

listeN* minimum_liste_noeud (listeN* liste); 


/**
 * \brief Fonction qui crée un arbre de Huffman 
 * 
 * \param liste : la liste d'éléments servant de base pour créer l'arbre de huffman 
 * \return pointeur sur l'arbre de Huffman, si il a été crée, NULL sinon  
 */

Noeud* creation_arbre_huffman (Element* liste); 

/**
 * \brief Fonction qui affiche une liste de noeuds 
 * 
 * \param liste : la liste de noeuds à afficher 
 * \return pas de valeur de retour  
 */

void afficher_listeN (listeN* liste); 

/**
 * \brief Fonction qui affiche l'arbre de Huffman 
 * 
 * \param arbre : l'arbre de Huffman à afficher 
 * \return pas de valeur de retour 
 */

void affichage_arbre(Noeud* arbre);

/**
 * \brief Fonction 
 * 
 * \param Nomfichier : le nom du fichier contenant le dictionnaire 
 * \param \c codeBinaire : chaîne de caractères correspondant au code binaire d'une lettre
 * \param \c arbre : l'arbre de huffman 
 * \param \c pos : un compteur 
 * \return pas de valeur de retour  
 */

void ecriture_dictionnaire_fichier (char* Nomfichier, Noeud* arbre, char* codeBinaire, int pos); 

/**
 * \brief Fonction pour convertir un fichier texte en une suite binaire
 * 
 * \param nomFichierTexte : le nom du fichier contenant le texte à traduire 
 * \param \c nomfichierBinaire : le nom du fichier contenant la traduction binaire du fichier texte
 * \param \c nomFichierDictionnaire : le nom du fichier contenant le dictionnaire
 * \return pas de valeur de retour 
 */

void ecriture_fichier_binaire_huffman (char* nomFichierTexte, char* nomFichierBinaire, char* nomFichierDictionnaire);

#endif //HUFFMAN_H