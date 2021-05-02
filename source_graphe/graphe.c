/*
  Structures de type graphe
  Structures de donnees de type liste
  (Pas de contrainte sur le nombre de noeuds des  graphes)
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graphe.h"
#include "pile.h"
#include "file.h"

int appartient_tableau(psommet_t *tableau, psommet_t p, pgraphe_t g)
{
  int i = 0;
  while (tableau[i] != NULL && i < nombre_sommets(g)) {
    if (tableau[i] == p)
    {
      return 1;
    }
    i++;
  }
  return 0;
}

int appartient_tableau_arc(parc_t *tableau, parc_t p, pgraphe_t g)
{
  int i = 0;
  while (tableau[i] != NULL && i < nombre_arcs(g)) {
    if (tableau[i] == p)
    {
      return 1;
    }
    i++;
  }
  return 0;
}

psommet_t chercher_sommet(pgraphe_t g, int label)
{
  psommet_t s;

  s = g;

  while ((s != NULL) && (s->label != label))
  {
    s = s->sommet_suivant;
  }
  return s;
}

parc_t existence_arc(parc_t l, psommet_t s)
{
  parc_t p = l;

  while (p != NULL)
  {
    if (p->dest == s)
      return p;
    p = p->arc_suivant;
  }
  return p;
}

void ajouter_arc(psommet_t o, psommet_t d, int distance)
{
  parc_t parc;

  parc = (parc_t)malloc(sizeof(arc_t));

  if (existence_arc(o->liste_arcs, d) != NULL)
  {
    fprintf(stderr, "ajout d'un arc deja existant\n");
    exit(-1);
  }

  parc->poids = distance;
  parc->dest = d;
  parc->arc_suivant = o->liste_arcs;
  o->liste_arcs = parc;
  return;
}

// ===================================================================

int nombre_sommets(pgraphe_t g)
{
  psommet_t p = g;
  int nb = 0;

  while (p != NULL)
  {
    nb = nb + 1;
    p = p->sommet_suivant;
  }

  return nb;
}

int nombre_arcs(pgraphe_t g)
{

  psommet_t p = g;
  int nb_arcs = 0;

  while (p != NULL)
  {
    parc_t l = p->liste_arcs;

    while (l != NULL)
    {
      nb_arcs = nb_arcs + 1;
      l = l->arc_suivant;
    }

    p = p->sommet_suivant;
  }
  return nb_arcs;
}

void init_couleur_sommet(pgraphe_t g)
{
  psommet_t p = g;

  while (p != NULL)
  {
    p->couleur = 0;        // couleur indefinie
    p = p->sommet_suivant; // passer au sommet suivant dans le graphe
  }

  return;
}

int colorier_graphe(pgraphe_t g)
{
  /*
    coloriage du graphe g
    
    datasets
    graphe data/gr_planning
    graphe data/gr_sched1
    graphe data/gr_sched2
  */

  psommet_t p = g;
  parc_t a;
  int couleur;
  int max_couleur = INT_MIN; // -INFINI

  int change;

  init_couleur_sommet(g);

  while (p != NULL)
  {
    couleur = 1; // 1 est la premiere couleur

    // Pour chaque sommet, on essaie de lui affecter la plus petite couleur

    // Choix de la couleur pour le sommet p

    do
    {
      a = p->liste_arcs;
      change = 0;

      while (a != NULL)
      {
        if (a->dest->couleur == couleur)
        {
          couleur = couleur + 1;
          change = 1;
        }
        a = a->arc_suivant;
      }

    } while (change == 1);

    // couleur du sommet est differente des couleurs de tous les voisins

    p->couleur = couleur;
    if (couleur > max_couleur)
      max_couleur = couleur;

    p = p->sommet_suivant;
  }

  return max_couleur;
}

void afficher_graphe_largeur(pgraphe_t g, int r)
{
  psommet_t p = g;
  while (p != NULL && p->label != r)
  {
    p = p->sommet_suivant;
  }

  if (p == NULL)
  {
    printf("Le sommet demandé n'est pas dans le graphe.\n");
    return;
  }

  pfile_t file = creer_file();
  psommet_t sommetsvisites[nombre_sommets(g)];
  sommetsvisites[0] = p;
  int j = 1;
  parc_t a;
  int nbvisites = 1;
  int size = nombre_sommets(g);

  enfiler(file, p);

  while (nbvisites <= size) {
    if (file_vide(file) == 0) {
      p = defiler(file);
      nbvisites++;

      printf("%d ", p->label);

      a = p->liste_arcs;

      while (a != NULL)
      {
        if (appartient_tableau(sommetsvisites, a->dest, g) == 0)
        {
          enfiler(file, a->dest);
          sommetsvisites[j] = a->dest;
          j++;
        }
        a = a->arc_suivant;
      }
    }
    else {
      p = g;
      while (appartient_tableau(sommetsvisites, p, g) == 1) {
        p = p->sommet_suivant;
      }
      enfiler(file, p);
      sommetsvisites[j] = p;
      j++;
    }
  }

  printf("\n");

  return;
}

void afficher_graphe_profondeur(pgraphe_t g, int r)
{
  psommet_t p = g;
  while (p != NULL && p->label != r)
  {
    p = p->sommet_suivant;
  }

  if (p == NULL)
  {
    printf("Le sommet demandé n'est pas dans le graphe.\n");
    return;
  }

  ppile_t pile = creer_pile();
  psommet_t sommetsvisites[nombre_sommets(g)];
  sommetsvisites[0] = p;
  int j = 1;
  int k = j;
  parc_t a;
  int nbvisites = 1;
  int size = nombre_sommets(g);

  empiler(pile, p);

  while (nbvisites <= size) {
    if (pile_vide(pile) == 0) {
      p = depiler(pile);
      nbvisites++;

      printf("%d ", p->label);

      a = p->liste_arcs;
      k = j;

      while (a != NULL)
      {
        if (appartient_tableau(sommetsvisites, a->dest, g) == 0)
        {
          sommetsvisites[j] = a->dest;
          j++;
        }
        a = a->arc_suivant;
      }

      for (int i = j - 1; i > k - 1; i--)
      {
        empiler(pile, sommetsvisites[i]);
      }
    }
    else {
      p = g;
      while (appartient_tableau(sommetsvisites, p, g) == 1) {
        p = p->sommet_suivant;
      }
      empiler(pile, p);
      sommetsvisites[j] = p;
      j++;
    }
  }

  printf("\n");

  return;
}

int min_d2(int *d, int *F, int size) // Fonction Auxiliaire
{
  int min = 9999;
  int res = -1;
  int i = 0;
  while(i<size){
    if(F[i] != -1){
      if(d[F[i]-1] < min){
        min = d[F[i]-1];
        res = F[i]-1;
      }
    }
  i++;
  }
  return res;
}

int tableau_vide(int *tab, int size) // Fonction Auxiliaire
{
  int i = 0;
  while(i < size){
    if(tab[i] != -1){
      return 0;
    }
    i++;
  }
  return 1;
}

void algo_dijkstra(pgraphe_t g, int r)
{
  /*
    algorithme de dijkstra
    des variables ou des chanmps doivent etre ajoutees dans les structures.
  */

  psommet_t p = g;
  while (p != NULL && p->label != r)
  {
    p = p->sommet_suivant;
  }

  if (p == NULL)
  {
    printf("Le sommet demandé n'est pas dans le graphe.\n");
    return;
  }

  int size = nombre_sommets(g);
  int *d = malloc(size * sizeof(int));
  int F[size];

  int i = 0;
  for (int i = 0; i < size; i++) {
    F[i] = i+1;
    d[i] = 9999;
  }

  d[r-1] = 0;
    
  while(tableau_vide(F,size) == 0){
    int position_min = min_d2(d,F,size);
    if (position_min == -1) {
      break;
    }
    psommet_t u = chercher_sommet(g,position_min+1);
    F[position_min] = -1;

    parc_t l = u->liste_arcs;

    while (l != NULL)
    {
      //Relachement
      if(d[l->dest->label-1] > d[u->label-1] + l->poids){
        d[l->dest->label-1] = d[u->label-1] + l->poids;
      }
      //Relachement
      l = l->arc_suivant;
    }
    
  }

  for (int i = 0; i < size; i++) {
    if (F[i] != -1) {
      d[i] = -1;
    }
  }
  
  
  i = 0;
  p = g;
  while(i!=size){
    if (d[i] == -1) {
      printf("La distance entre le sommet de départ et le sommet %d est infini (sommet inatteignable) \n", p->label);
    }
    else {
      printf("La distance entre le sommet de départ et le sommet %d est : %d \n", p->label, d[i]);
    }
    i++;
    p = p->sommet_suivant;
  }

  return;
}

// ======================================================================

int degre_sortant_sommet(pgraphe_t g, psommet_t s)
{
  /*
    Cette fonction retourne le nombre d'arcs sortants 
    du sommet n dans le graphe g
  */

  if (g != NULL)
  {

    psommet_t p = g;
    while (p != s)
    {
      p = p->sommet_suivant;
    }

    if (p == NULL)
    {
      printf("Le sommet demandé n'est pas dans le graphe.\n");
      return 0;
    }

    int dss = 0;                //degré sortant du sommet
    parc_t arc = s->liste_arcs; //on prend le premier arc
    while (arc != NULL)
    {
      dss++;
      arc = arc->arc_suivant;
    }
    return dss;
  }
  return 0;
}

int degre_entrant_sommet(pgraphe_t g, psommet_t s)
{
  /*
    Cette fonction retourne le nombre d'arcs entrants 
    dans le noeud n dans le graphe g
  */

  if (g != NULL)
  {

    psommet_t p = g;
    while (p != s)
    {
      p = p->sommet_suivant;
    }

    if (p == NULL)
    {
      printf("Le sommet demandé n'est pas dans le graphe.\n");
      return 0;
    }

    pfile_t file = creer_file();
    psommet_t sommetsvisites[nombre_sommets(g)];
    sommetsvisites[0] = p;
    int j = 1;
    parc_t a;
    int des = 0;

    enfiler(file, p);

    while (file_vide(file) == 0)
    {
      p = defiler(file);

      a = p->liste_arcs;

      while (a != NULL)
      {
        if (appartient_tableau(sommetsvisites, a->dest, g) == 0)
        {
          enfiler(file, a->dest);
          sommetsvisites[j] = a->dest;
          j++;
        }

        if (a->dest == s)
        {
          des++;
        }
        a = a->arc_suivant;
      }
    }

    return des;
  }
  return 0;
}

int degre_maximal_graphe(pgraphe_t g)
{
  /*
    Max des degres des sommets du graphe g
  */

  if (g == NULL)
  {
    return 0;
  }

  psommet_t p = g;
  int maxDeg = degre_sortant_sommet(g, p) + degre_entrant_sommet(g, p);
  p = p->sommet_suivant;
  while (p != NULL)
  {
    int inter = degre_sortant_sommet(g, p) + degre_entrant_sommet(g, p);
    if (inter > maxDeg)
    {
      maxDeg = inter;
    }
    p = p->sommet_suivant;
  }
  return maxDeg;
}

int degre_minimal_graphe(pgraphe_t g)
{
  /*
    Min des degres des sommets du graphe g
  */
  if (g == NULL)
  {
    return 0;
  }

  psommet_t p = g;
  int minDeg = degre_sortant_sommet(g, p) + degre_entrant_sommet(g, p);
  p = p->sommet_suivant;
  while (p != NULL)
  {
    int inter = degre_sortant_sommet(g, p) + degre_entrant_sommet(g, p);
    if (inter < minDeg)
    {
      minDeg = inter;
    }
    p = p->sommet_suivant;
  }
  return minDeg;
}

int independant(pgraphe_t g)
{
  /* Les aretes du graphe n'ont pas de sommet en commun */

  if (g == NULL)
  {
    return 0;
  }

  psommet_t p = g;

  while (p != NULL)
  {
    if (1 != degre_entrant_sommet(g, p))
    {
      return 0;
    }
    p = p->sommet_suivant;
  }

  return 0;
}

int complet(pgraphe_t g)
{
  /* Toutes les paires de sommet du graphe sont jointes par un arc */

  if (g == NULL)
  {
    return 0;
  }

  if (nombre_sommets(g) * (nombre_sommets(g) - 1) == nombre_arcs(g))
  {
    return 1;
  }

  return 0;
}

int regulier(pgraphe_t g)
{
  /* 
     graphe regulier: tous les sommets ont le meme degre
     g est le ponteur vers le premier sommet du graphe
     renvoie 1 si le graphe est régulier, 0 sinon
  */

  return (degre_maximal_graphe(g) == degre_minimal_graphe(g));
}

/*
  placer les fonctions de l'examen 2017 juste apres
*/

int longueur_chemin(pchemin_t c)
{
  pchemin_t courant = c;
  int i = 0;
  while (courant != NULL)
  {
    i += courant->arc->poids;
    courant = courant->suivant;
  }
  return i;
}

int destination(pchemin_t c)
{
  pchemin_t courant = c;
  while (courant->suivant != NULL)
  {
    courant = courant->suivant;
  }
  return courant->arc->dest->label;
}

pchemin_t plus_court_chemin(pgraphe_t g, int x, int y)
{
  pchemin_t *chemins = malloc(sizeof(pchemin_t) * 20);

  tab_chemin(chemins, g);

  pchemin_t c = chemins[0];
  int i = 1;
  int min = 9999;
  pchemin_t minchemin;

  while (c != NULL)
  {
    if (c->start->label == x && destination(c) == y)
    {
      int lg = longueur_chemin(c);
      if (lg < min)
      {
        min = lg;
        minchemin = c;
      }
    }
    c = chemins[i];
    i++;
  }

  return minchemin;
}

int elementaire(pgraphe_t g, pchemin_t c)
{
  if (g != NULL && c != NULL)
  {
    psommet_t *sommetstrouves = malloc(sizeof(psommet_t) * nombre_sommets(g));

    sommetstrouves[0] = c->start;
    int j = 1;
    while (c != NULL)
    {
      if (appartient_tableau(sommetstrouves, c->arc->dest, g) == 1)
      {
        return 0;
      }
      sommetstrouves[j] = c->arc->dest;
      j++;
      c = c->suivant;
    }
    return 1;
  }
  return 1;
}

int simple(pgraphe_t g, pchemin_t c)
{
  if (g != NULL && c != NULL)
  {
    parc_t *arcstrouves = malloc(sizeof(parc_t) * nombre_arcs(g));

    arcstrouves[0] = c->arc;
    int j = 1;
    c = c->suivant;
    while (c != NULL)
    {
      if (appartient_tableau_arc(arcstrouves, c->arc, g) == 1)
      {
        return 0;
      }
      arcstrouves[j] = c->arc;
      j++;
      c = c->suivant;
    }
    return 1;
  }
  return 1;
}

int eulerien(pgraphe_t g, pchemin_t c)
{
  if (g != NULL && c != NULL)
  {
    parc_t *arcstrouves = malloc(sizeof(parc_t) * nombre_arcs(g));

    arcstrouves[0] = c->arc;
    int j = 1;
    c = c->suivant;
    while (c != NULL)
    {
      if (appartient_tableau_arc(arcstrouves, c->arc, g) == 0)
      {
        arcstrouves[j] = c->arc;
        j++;
      }
      c = c->suivant;
    }

    int compteur = 0;
    while (arcstrouves[compteur] != NULL)
    {
      compteur++;
    }
    if (compteur == nombre_arcs(g))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return 1;
}

int hamiltonien(pgraphe_t g, pchemin_t c)
{
  if (g != NULL && c != NULL)
  {
    psommet_t *sommetstrouves = malloc(sizeof(psommet_t) * nombre_sommets(g));

    sommetstrouves[0] = c->start;
    int j = 1;
    while (c != NULL)
    {

      if (appartient_tableau(sommetstrouves, c->arc->dest, g) == 0)
      {
        sommetstrouves[j] = c->arc->dest;
        j++;
      }
      c = c->suivant;
    }

    int compteur = 0;
    while (sommetstrouves[compteur] != NULL)
    {
      compteur++;
    }
    if (compteur == nombre_sommets(g))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return 1;
}

int graphe_eulerien(pgraphe_t g)
{
  pchemin_t *chemins = malloc(sizeof(pchemin_t) * 20);

  tab_chemin(chemins, g);

  pchemin_t c = chemins[0];
  int i = 1;

  while (c != NULL)
  {
    if (eulerien(g, c) == 0)
    {
      return 0;
    }
    c = chemins[i];
    i++;
  }

  return 1;
}

int graphe_hamiltonien(pgraphe_t g)
{
  pchemin_t *chemins = malloc(sizeof(pchemin_t) * 20);

  tab_chemin(chemins, g);

  pchemin_t c = chemins[0];
  int i = 1;

  while (c != NULL)
  {
    if (hamiltonien(g, c) == 0)
    {
      return 0;
    }
    c = chemins[i];
    i++;
  }

  return 1;
}

int distance(pgraphe_t g, int x, int y)
{
  return longueur_chemin(plus_court_chemin(g, x, y));
}

int excentricite(pgraphe_t g, int n)
{
  psommet_t current = g;
  int max = 0;
  int p;
  while (current != NULL)
  {
    p = distance(g, n, current->label);
    if (p > max)
    {
      max = p;
    }
    current = current->sommet_suivant;
  }
  return max;
}

int diametre(pgraphe_t g)
{
  psommet_t current = g;
  int max = 0;
  int p;
  while (current != NULL)
  {
    p = excentricite(g, current->label);
    if (p > max)
    {
      max = p;
    }
    current = current->sommet_suivant;
  }
  return max;
}

void afficher_chemin(pchemin_t c)
{
  pchemin_t courant = c;
  while (courant != NULL)
  {
    printf(" -> %i ", courant->arc->dest->label);
    courant = courant->suivant;
  }
}

pchemin_t ajouter_arc_chemin(pchemin_t c, parc_t arc)
{

  pchemin_t nouveau = malloc(sizeof(pchemin_t));
  pchemin_t courant;
  nouveau->arc = arc;
  nouveau->suivant = NULL;
  if (c == NULL)
    c = nouveau;
  else
  {
    courant = c;
    while (courant->suivant != NULL)
      courant = courant->suivant;
    courant->suivant = nouveau;
    nouveau->start = courant->arc->dest;
  }
  return c;
}

//Créer le premier chemin du graphe g
pchemin_t creer_chemin(pgraphe_t g)
{
  pchemin_t c = NULL;
  psommet_t p = g;
  parc_t a = p->liste_arcs;
  while ((a != NULL) && (simple(g, c)))
  {
    c = ajouter_arc_chemin(c, a);
    p = a->dest;
    a = p->liste_arcs;
  }

  return c;
}

//Permet de créer un chemin à partir d'un arc
pchemin_t creer_chemin_bis(pgraphe_t g, parc_t arc)
{
  pchemin_t c = NULL;
  psommet_t p;
  parc_t a = arc;
  while ((a != NULL) && (simple(g, c)))
  {
    c = ajouter_arc_chemin(c, a);
    p = a->dest;
    a = p->liste_arcs;
  }

  return c;
}

//Rempli un tableau de tous les chemins possibles pour le graphe g
void tab_chemin(pchemin_t *tab, pgraphe_t g)
{
  int i;
  pgraphe_t p = g;
  pchemin_t c = NULL;
  while (p != NULL)
  {
    parc_t a = p->liste_arcs;
    while ((a != NULL) && (simple(g, c)))
    {
      tab[i] = creer_chemin_bis(g, a);
      i++;
      a = a->arc_suivant;
    }
    p = p->sommet_suivant;
  }
}