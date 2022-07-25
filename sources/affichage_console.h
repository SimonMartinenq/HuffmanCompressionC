#ifndef AFFICHAGE_CONSOLE_H
#define AFFICHAGE_CONSOLE_H

#include "huffman.h"
#include "huffman_optimisation.h"

/*!
   \file affichage_console.h
   \brief header de la bibliothèque des affichage permettant les différents affichages necessaires
   \author "Your name"
   \date "DD"/"Month"/"Year"
*/

/*!
   \brief permet de compter le nombre de caractère contenue dans un fichierTexte.
   \param chaine de caractere correspondant au nom du fichier.
   \return entier correspondant au nombre de caractères du fichier.
*/
int nombre_char_fichier(char* nameFile);

/*!
   \brief permet d'afficher chaque caractère de la liste d'élément.
   \param liste d'element à afficher sans modification.
   \return pas de retour, la fonction réalise directement un affichage.
*/
void afficher_liste(Element* liste);

/*!
   \brief affiche la lettre et son occurence de chaque noeud du tableau .
   \param tableau de noeud et entier qui représente la taille du tableau.
   \return pas de retour, affichage directement à l'intérieur de la fonction.
*/
void afficherTab (const Noeud* tab, int taille);

/*!
   \brief affiche la lettre et son occurence de chaque noeud de l'abre par un parcour préfixe.
   \param pointeur sur un noeud représentant un arbre.
   \return pas de retour, affichage directement à l'intérieur de la fonction.
*/
void affichage_arbre(Noeud* arbre);

/*!
   \brief affiche la lettre et son occurence de chaque élément de la liste.
   \param pointeur sur une listeN représentant une liste d'élément.
   \return pas de retour, affichage directement à l'intérieur de la fonction.
*/
void afficher_listeN (listeN* liste);


#endif // AFFICHAGE_CONSOLE_H
