#ifndef TEST_HUFFMAN
#define TEST_HUFFMAN

/*!
   \file test_fonctions_huffman.h
   \brief header des fonctions de test.
   \date 11/12/2020
*/

/*!
   \brief Cette fonction permet de tester la compression de Huffman par la méthode sans optimisation (FONCTION DEV)
   \param Pas de paramètre
   \return pas de valeur de retour 
*/
void test_compression_fichier_huffman (); 

/*!
   \brief Cette fonction permet de tester la décompression de Huffman par la méthode sans optimisation (FONCTION DEV)
   \param Pas de paramètre
   \return pas de valeur de retour
*/
void test_decompression_fichier_huffman (); 

/*!
   \brief  Cette fonction permet de tester la compression de Huffman par la méthode optimisé (FONCTION DEV)
   \param Pas de paramètre
   \return pas de valeur de retour
*/
void test_compression_optimiser (); 

/*!
   \brief Cette fonction permet de tester la décompression de Huffman par la méthode optimisé (FONCTION DEV)
   \param Pas de paramètre
   \return pas de valeur de retour
*/
void test_decompression_optimiser (); 

#endif //TEST_HUFFMAN
