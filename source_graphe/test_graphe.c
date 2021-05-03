#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"

int main(int argc, char **argv)
{
  pgraphe_t g;
  int nc;

  if (argc != 2)
  {
    fprintf(stderr, "erreur parametre \n");
    exit(-1);
  }

  /*
    la fonction lire_graphe alloue le graphe (matrice,...) 
    et lit les donnees du fichier passe en parametre
  */

  pchemin_t *chemins = malloc(sizeof(chemin_t) * 2);

  lire_graphe(argv[1], &g, chemins);

  /*
    la fonction ecrire_graphe affiche le graphe a l'ecran
  */

  printf("nombre de sommets du graphe %d nombre arcs %d \n", nombre_sommets(g), nombre_arcs(g));
  fflush(stdout);

  ecrire_graphe(g);

  nc = colorier_graphe(g);

  printf("nombre chromatique graphe = %d\n", nc);

  ecrire_graphe_colorie(g);

  printf("\nEntrez le label du sommet par lequel vous voulez commencer les différents parcours : \n");

  int sommet;

  scanf("%d", &sommet);

  printf("\nAffichage parcours en largeur : ");
  afficher_graphe_largeur(g, sommet);

  printf("\nAffichage parcours en profondeur : ");
  afficher_graphe_profondeur(g, sommet);

  printf("\nAlgo Dijkstra : \n");
  algo_dijkstra(g, sommet);

  printf("\nNombre de degrés sortants du sommet donné : %d \n", degre_sortant_sommet(g, chercher_sommet(g, sommet)));

  printf("\nNombre de degrés entrants du sommet donné : %d \n", degre_entrant_sommet(g, chercher_sommet(g, sommet)));

  printf("\nDegré maximal pour un sommet de g : %d \n", degre_maximal_graphe(g));
  printf("\nDegré minimal pour un sommet de g : %d \n", degre_minimal_graphe(g));

  if (complet(g) == 1)
  {
    printf("\nLe graphe est complet (tous les sommets sont liés à tous les autres)\n");
  }
  else
  {
    printf("\nLe graphe n'est pas complet (tous les sommets ne sont pas liés à tous les autres)\n");
  }

  if (regulier(g) == 1)
  {
    printf("\nLe graphe est régulier (tous les sommets ont le même degré)\n");
  }
  else
  {
    printf("\nLe graphe n'est pas régulier (tous les sommets n'ont pas le même degré)\n");
  }

  //-------------------------------------EXAMEN 2017 TESTS--------------------------------------------

  printf("\nEXAMEN 2017 : TESTS DES FONCTIONS\n");

  printf("Soit les chemins déclarés arbitrairement : \n\n");

  for (int i = 0; i < 2; i++)
  {
    afficher_chemin(chemins[i]);
    printf("\n");

    printf("\n--> Chemin simple :");
    if (simple(g, chemins[i]))
      printf(" Oui \n");
    else
      printf(" Non \n");

    printf("\n--> Chemin elementaire :");
    if (elementaire(g, chemins[i]))
      printf(" Oui \n");
    else
      printf(" Non \n");

    printf("\n--> Chemin eulerien :");
    if (eulerien(g, chemins[i]))
      printf(" Oui \n");
    else
      printf(" Non \n");

    printf("\n--> Chemin hamiltonien :");
    if (hamiltonien(g, chemins[i]))
      printf(" Oui \n");
    else
      printf(" Non \n");
  }

  // printf("--> Graphe eulérien :");
  // if (graphe_eulerien(g))
  //   printf(" Oui \n");
  // else
  //   printf(" Non \n");

  // printf("--> Graphe hamiltonien :");
  // if (graphe_hamiltonien(g))
  //   printf(" Oui \n");
  // else
  //   printf(" Non \n");

  // printf("--> Distance du chemin : %d\n", distance(g, 5, 4, chemins));

  // printf("--> Excentricité du chemin : %d\n", excentricite(g, 5, chemins));

  // printf("--> Diamètre du chemin : %d\n", diametre(g, chemins));
}
