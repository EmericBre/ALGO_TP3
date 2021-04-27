#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"

int main (int argc, char **argv)
{
  pgraphe_t g ;
  int nc ;
  
  if (argc != 2)
    {
      fprintf (stderr, "erreur parametre \n") ;
      exit (-1) ;
    }

  /*
    la fonction lire_graphe alloue le graphe (matrice,...) 
    et lit les donnees du fichier passe en parametre
  */
  
  
  lire_graphe (argv [1], &g) ;

  /*
    la fonction ecrire_graphe affiche le graphe a l'ecran
  */  
  
  printf ("nombre de sommets du graphe %d nombre arcs %d \n", nombre_sommets (g), nombre_arcs (g)) ;
  fflush (stdout) ;
  
  ecrire_graphe (g) ;      

  nc = colorier_graphe (g) ;
  
  printf ("nombre chromatique graphe = %d\n", nc) ;

  ecrire_graphe_colorie (g) ;

  printf("\nAffichage parcours en largeur : ");
  afficher_graphe_largeur(g, 5);

  printf("\nAffichage parcours en profondeur : ");
  afficher_graphe_profondeur(g, 5);

  printf("\nNombre de degrés sortants : %d \n", degre_sortant_sommet(g, chercher_sommet(g, 3)));

  printf("\nNombre de degrés entrants : %d \n", degre_entrant_sommet(g, chercher_sommet(g, 3)));

  printf("\nDegré maximal pour un sommet de g : %d \n", degre_maximal_graphe(g));
  printf("\nDegré minimal pour un sommet de g : %d \n", degre_minimal_graphe(g));

  if (complet(g) == 1) {
    printf("\nLe graphe est complet (tous les sommets sont liés à tous les autres)\n");
  }
  else {
    printf("\nLe graphe n'est pas complet (tous les sommets ne sont pas liés à tous les autres)\n");
  }

  if (regulier(g) == 1) {
    printf("\nLe graphe est régulier (tous les sommets ont le même degré)\n");
  }
  else {
    printf("\nLe graphe n'est pas régulier (tous les sommets n'ont pas le même degré)\n");
  }



  //-------------------------------------EXAMEN 2017 TESTS--------------------------------------------

  printf("\nEXAMEN 2017 : TESTS DES FONCTIONS\n");

  pchemin_t c = creer_chemin(g);
  afficher_chemin(c);

  printf("\n--> Chemin simple :");
  if (simple(g, c))
    printf(" Oui \n");
  else
    printf(" Non \n");

  printf("\n--> Chemin elementaire :");
  if (elementaire(g, c))
    printf(" Oui \n");
  else
    printf(" Non \n");

  printf("\n--> Chemin eulerien :");
  if (eulerien(g, c))
    printf(" Oui \n");
  else
    printf(" Non \n");

  printf("\n--> Chemin hamiltonien :");
  if (hamiltonien(g, c))
    printf(" Oui \n");
  else
    printf(" Non \n");

  printf("--> Graphe eulérien :");
  if (graphe_eulerien(g))
    printf(" Oui \n");
  else
    printf(" Non \n");

  printf("--> Graphe hamiltonien :");
  if (graphe_hamiltonien(g))
    printf(" Oui \n");
  else
    printf(" Non \n");

  // printf("--> Distance du chemin :");
  // if (graphe_hamiltonien(g))
  //   printf(" Oui \n");
  // else
  //   printf(" Non \n");

  // printf("--> graphe hamiltonien :");
  // if (graphe_hamiltonien(g))
  //   printf(" Oui \n");
  // else
  //   printf(" Non \n");

  // printf("--> graphe hamiltonien :");
  // if (graphe_hamiltonien(g))
  //   printf(" Oui \n");
  // else
  //   printf(" Non \n");
}
