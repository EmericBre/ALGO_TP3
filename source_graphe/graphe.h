
typedef struct a *parc_t ;

/*
  definition des types sommet et pointeur de sommet
  un graphe est constitué d'une liste de sommets
*/

typedef struct s
{
  int        label ; // label du sommet
  parc_t     liste_arcs ; // arcs sortants du sommet
  struct s   *sommet_suivant ; // sommet suivant dans le graphe
  int        couleur ; // couleur du sommet
} sommet_t, *psommet_t ;

/*
  definition des types arc et pointeur d'arc
  Les arcs sortants d'un sommet sont chainés
  Pour chaque arc, il y a un poids qui peut par exemple correspondre a une distance
*/

typedef struct a {
  
                  int         poids ; // poids de l arc
                  psommet_t   dest ;  // pointeur sommet destinataire
                  struct a *  arc_suivant ; // arc suivant
  
} arc_t, *parc_t ;

/*
  pgraphe_t: pointeur vers le premier sommet d'un graphe
*/

typedef psommet_t pgraphe_t ;

typedef struct c {
  psommet_t start;
  parc_t arc;
  struct c * suivant;
} chemin_t, *pchemin_t ;

psommet_t chercher_sommet (pgraphe_t g, int label) ;

parc_t existence_arc(parc_t l, psommet_t s) ;

void ajouter_arc (psommet_t o, psommet_t d, int distance) ;

int nombre_arcs (pgraphe_t g) ;

int nombre_sommets (pgraphe_t g) ;

void lire_graphe (char * file_name, pgraphe_t *g) ;

void ecrire_graphe (psommet_t p) ;

void ecrire_graphe_colorie (psommet_t p) ;

void init_couleur_sommet(pgraphe_t g) ;

int degre_sortant_sommet(pgraphe_t g, psommet_t s) ;

int degre_entrant_sommet(pgraphe_t g, psommet_t s) ;

int degre_maximal_graphe(pgraphe_t g) ;

int degre_minimal_graphe(pgraphe_t g) ;

int independant(pgraphe_t g) ;

int complet(pgraphe_t g) ;

int regulier(pgraphe_t g) ;



int colorier_graphe (pgraphe_t g) ;

void afficher_graphe_profondeur (pgraphe_t g, int r) ;

void afficher_graphe_largeur (pgraphe_t g, int r) ;

void algo_dijkstra (pgraphe_t g, int r) ;




int longueur_chemin(pchemin_t c) ;

int destination(pchemin_t c) ;

pchemin_t plus_court_chemin(pgraphe_t g, int x, int y) ;

void afficher_chemin(pchemin_t c) ;

pchemin_t ajouter_arc_chemin(pchemin_t c, parc_t arc) ;

pchemin_t creer_chemin(pgraphe_t g) ;

pchemin_t creer_chemin_bis(pgraphe_t g, parc_t arc) ;

void tab_chemin(pchemin_t *tab, pgraphe_t g) ;

int elementaire (pgraphe_t g, pchemin_t c);

int simple (pgraphe_t g, pchemin_t c);

int eulerien (pgraphe_t g, pchemin_t c);

int hamiltonien (pgraphe_t g, pchemin_t c);

int graphe_eulerien (pgraphe_t g);

int graphe_hamiltonien (pgraphe_t g);

int distance (pgraphe_t g, int x, int y);

int excentricite (pgraphe_t g, int n);

int diametre (pgraphe_t g);