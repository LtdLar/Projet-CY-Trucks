#define LONGUEUR_LIGNE 95
#define VILLE 50
#define CONDUCTEUR 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Définition de la structure Noeud de type Noeud, où la lettre e est le facteur équilibre, qui va stocker l'id de la route, le min, max et moyenne des distances
typedef struct Noeud {
    int RouteID;
    float distance_min;
    float distance_max;
    int distance_moy;
    int pas;
    int e;
    int ecart;
    struct Noeud* gauche;
    struct Noeud* droit;
} Noeud;

// Fonction pour créer une Noeud
Noeud* CreerNoeud(int RouteID, float distance) {
    Noeud* a = malloc(sizeof(Noeud));
    if (a == NULL) {
        printf("Échec de l'allocation mémoire\n");
        exit(1);
    }
    a->RouteID = RouteID;
    a->distance_min = distance;
    a->distance_max = distance;
    a->distance_moy = distance;
    a->pas = 1;
    a->e = 0;
    a->gauche = NULL;
    a->droit = NULL;
    return a;
}

int hauteur_s(Noeud* a) {
    if (a == NULL) {
        return 0;
    }
    int hauteurGauche = hauteur_s(a->gauche);
    int hauteurDroite = hauteur_s(a->droit);
    return 1 + (hauteurGauche > hauteurDroite ? hauteurGauche : hauteurDroite);
}

//Fonction qui retourne le distance_maximum entre deux entiers
int distance_maximum(const int a, const int b) {
    if(a>b){
		return a;
	}
	else if(b<a){
	   return b;
	}
	else{
		return a;
	}
}

//Fonction qui retourne le distance_minimum entre deux entiers
int distance_minimum(const int a, const int b) {
    if(a<b){
		return a;
	}
	else if(a>b){
	   return b;
	}
	else{
		return a;
	}
}

// Rotations Simples
Noeud* rotationGauche_s(Noeud* a) {
    if (a == NULL) {
        printf("ERREUR NULL\n");
        exit(0);
    }
    Noeud* b = a->droit;
    a->droit = b->gauche;
    b->gauche = a;
    a->e = hauteur_s(a->droit) - hauteur_s(a->gauche);
    b->e = hauteur_s(b->droit) - hauteur_s(b->gauche);
    return b;
}

Noeud* rotationDroite_s(Noeud* a) {
    if (a == NULL) {
        printf("ERREUR NULL\n");
        exit(0);
    }
    Noeud* b = a->gauche;
    a->gauche = b->droit;
    b->droit = a;

    a->e = hauteur_s(a->droit) - hauteur_s(a->gauche);
    b->e = hauteur_s(b->droit) - hauteur_s(b->gauche);

    return b;
}

// Rotations doubles
Noeud* rotationDoubleGauche_s(Noeud* a) {
    if (a == NULL) {
        printf("ERREUR NULL\n");
        exit(0);
    }
    a->droit = rotationDroite_s(a->droit);
    return rotationGauche_s(a);
}

Noeud* rotationDoubleDroite_s(Noeud* a) {
    if (a == NULL) {
        printf("ERREUR NULL\n");
        exit(0);
    }
    a->gauche = rotationGauche_s(a->gauche);
    return rotationDroite_s(a);
}

// Fonction pour équilibrer Noeud
Noeud* equilibrerNoeud(Noeud* a) {
    if (a == NULL) {
        printf("ERREUR NULL\n");
        exit(0);
    }
    if (a->e > 1) {
        if (a->droit->e < 0) {
            a = rotationDoubleGauche_s(a);
        } else {
            a = rotationGauche_s(a);
        }
    } else if (a->e < -1) {
        if (a->gauche->e > 0) {
            a = rotationDoubleDroite_s(a);
        } else {
            a = rotationDroite_s(a);
        }
    }
    return a;
}

// Fonction pour insérer un nouveau nœud dans l'arbre Noeud
void insererNoeud(Noeud** a, int RouteID, float distance, int* h) {
    // Gérer le cas où a est vide
    if (*a == NULL) {
        *a = CreerNoeud(RouteID, distance);
        *h = 1;
    } else if (RouteID < (*a)->RouteID) {
        insererNoeud(&((*a)->gauche), RouteID, distance, h);
        *h = -(*h);
    } else if (RouteID > (*a)->RouteID) {
        insererNoeud(&((*a)->droit), RouteID, distance, h);
    } else {
        // Gérer le cas égal 
        (*a)->pas++;
        if ((*a)->distance_max < distance) {
            (*a)->distance_max = distance;
        }
        if ((*a)->distance_min > distance) {
            (*a)->distance_min = distance;
        }
        (*a)->distance_moy += distance;
        (*a)->ecart = (*a)->distance_max - (*a)->distance_min;
        *h = 0;
        return;
    }
    if (*h != 0) {
        (*a)->e += *h;
        *a = equilibrerNoeud(*a);
        if ((*a)->e == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
}

// Fonction pour libérer Noeud
void libererNoeud(Noeud* a) {
    if (a == NULL){
    	return;
    }
    libererNoeud(a->gauche);
    libererNoeud(a->droit);
    free(a);
}

// Trier les villes en comparant leurs écarts distance_min-distance_max
int fonctionTri_s(const void* arg1, const void* arg2) {
    return (*(Noeud**)arg2)->ecart - (*(Noeud**)arg1)->ecart;
}

//Séléction des 50 villes avec le plus grand écart distance_min-distance_max
int Top50(Noeud* lligne, int* compter, Noeud* tab[50]) {
    if (lligne == NULL || tab == NULL) {
    	return 0;
    }
    if (lligne->pas <= 1){
    	return 1;
    }
    if (*compter < 50) {
    	tab[(*compter)++] = lligne;
    } else {
        int distance_min_id = 0;
        for (int i = 0; i < 50; i++) {
            if (tab[i]->ecart > tab[distance_min_id]->ecart) {
                distance_min_id = i;
            }
        }
        if (lligne->ecart > (tab[distance_min_id])->ecart) {
            tab[distance_min_id] = lligne;
        }
    }

    return 1;
}

int parcourirNoeud(Noeud* lligne, int* compter, Noeud* tab[50]) {
    if (lligne == NULL){
    	return 1;
    }
    parcourirNoeud(lligne->gauche, compter, tab);
    parcourirNoeud(lligne->droit, compter, tab);
    return Top50(lligne, compter, tab);
}

int main() {
    //Fonction principale
    char* ligne = malloc(sizeof(char) * LONGUEUR_LIGNE);
    int RouteID;
    float distance;
    int idEtape;
    char nomVille_A[VILLE + 1];
    char nomVille_B[VILLE + 1];
    char nomConducteur[CONDUCTEUR];
    Noeud* lligne = CreerNoeud(0, 0.0);
	//On ouvre le fichier data.csv et on stocke ses données
	FILE* fichierSource = fopen("data.csv", "r");
	if (fichierSource == NULL) {
		printf("Erreur d'ouverture du fichier");
		free(ligne);
		libererNoeud(lligne);
		return 0;
	}
	// En supposant que la première ligne contient les en-têtes
	fgets(ligne, sizeof(char) * (LONGUEUR_LIGNE), fichierSource);
	printf("Première ligne ignorée : %s\n", ligne);

	//On récupère et analyse toutes les lignes du fichier en calculant le nombre de fois que la ville est la ville de départ le chaque ligne
	while (!feof(fichierSource)) {
		fgets(ligne, sizeof(char) * LONGUEUR_LIGNE, fichierSource);
		if (fichierSource == NULL) {
			printf("Erreur de lecture du fichier");
			libererNoeud(lligne);
			free(ligne);
		return 0;
	}
	sscanf(ligne, "%d;%d;%50[^;];%50[^;];%f;%[^\n]", &RouteID, &idEtape, nomVille_A, nomVille_B, &distance, nomConducteur);
	insererNoeud(&lligne, RouteID, distance, &(lligne->e));
	}
	fclose(fichierSource);
    free(ligne);
    FILE* fichierSortie = fopen("temp/temps.txt", "w+");
    if (fichierSortie == NULL) {
        printf("Échec de la création du fichier de sortie ");
        libererNoeud(lligne);
        return 0;
    }
    int compter = 0;
    Noeud* tab[50];
    int res = parcourirNoeud(lligne, &compter, tab);
    if (1 != res) {
        printf("Erreur lors de la tentative d'obtention des 50 premiers.\n");
        libererNoeud(lligne);
        fclose(fichierSortie);
        return res;
    }
    qsort(tab, 50, sizeof(*tab), fonctionTri_s);
    for (int i = 0; i < 50; i++) {
        if (tab[i] != NULL) {
            fprintf(fichierSortie, "%d;%.3f;%.3f;%.3f\n", (tab[i])->RouteID, (tab[i])->distance_moy / (float)(tab[i])->pas, (tab[i])->distance_min, (tab[i])->distance_max);
        }
    }
    //On libére les mémoires alloués et on ferme le fichier de sortie
    fclose(fichierSortie);
    libererNoeud(lligne);
    return 1;
}
