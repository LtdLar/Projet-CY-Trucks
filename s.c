#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter un nœud de l'AVL
typedef struct Node {
    int idRoute;
    float distance_min;
    float distance_max;
    float distance_moy;
    struct Node *left;
    struct Node *right;
    int height;
    int e;
    int ecart;
    int key;
} Node;

// Fonction pour calculer la hauteur d'un nœud dans l'AVL
int height(Node *N) {
    if (N == NULL){
        return 0;
        }
        int heightleft = height(N->left);
        int heightright = height(N->right);
        return 1+ (heightleft > heightright ? heightleft : heightright);
}

// Fonction pour retourner le maximum entre deux entiers
int max(int a, int b) {
    if (a>b){
    return a;
    }
    else if (b>a){
    return b;
    }
    else{
    return a;
    }
}

// Fonction pour retourner le minimum entre deux entiers
int min(int a, int b) {
	if (a<b){
	return a;
	}
	else if (b<a){
	return b;
	}
	else{
	return a;
	}
}

// Fonction pour créer un nouveau nœud AVL
Node *createNode(int idRoute, float distance_min, float distance_max, float distance_moy) {
    Node* newnode = malloc(sizeof(Node));
    if (newnode==NULL){
    printf("Problème d'allocation mémoire\n");
    exit(1);
    }
    newnode->idRoute = idRoute;
    newnode->distance_min = distance_min;
    newnode->distance_max = distance_max;
    newnode->distance_moy = distance_moy;
    newnode->e = 0;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 1; // Nouveau nœud est à la hauteur 1
    return newnode;
}

// Fonction pour effectuer une rotation simple à droite
Node* rightrotate(Node* x) {
	if (x==NULL){
	printf("ERREUR\n");
	exit(1);
	}
Node *y = x->left;
x->left = y->right;
y->right = x;
x->e = height(x->right) - height(x->left);
y->e = height(y->right) - height(y->left);
return y;
}
    
// Fonction pour effectuer une rotation simple à gauche
Node *leftrotate(Node *x) {
    if (x==NULL){
    printf("ERREUR\n");
    exit(1);
	}
Node *y = x->right;
x->right = y->left;
y->left = x;
x->e = height(x->right) - height(x->left);
y->e = height(y->right) - height(y->left);
return y;
}

//Fonction pour effectuer une rotation double à gauche
Node *doubleleftrotate(Node *x){
	if (x==NULL){
	printf("ERREUR\n");
	exit(1);
	}
	x->right = rightrotate(x->right);
	return leftrotate(x);
}

//Fonction pour effectuer une rotation double à droite
Node* doublerightrotate(Node* x){
	if (x==NULL){
	printf("ERREUR\n");
	exit(1);
	}
	x->right = leftrotate(x->left);
	return rightrotate(x);
}

// Fonction pour équilibrer le facteur d'équilibre d'un nœud
Node *equilibreNode(Node *N) {
    if (N == NULL){
    printf ("ERREUR\n");
    exit(1);
    }
    if (N->e >1){
    	if (N->right->e <0){
    	N=doubleleftrotate(N);
    	}
    	else{
    	N= leftrotate(N);
    	}
    }
    else if (N->e <-1){
    	if (N->left->e >0){
    	N=doublerightrotate(N);
    	}
    	else{
    	N= rightrotate(N);
    	}
    }
    return N;
}
    	
// Fonction pour insérer un nœud dans l'AVL
Node *insert(Node *node, int key, int distance_min, int distance_max) {
    // Étape 1 : Effectuer l'insertion standard d'un nœud BST
    if (node == NULL){
         return 0;
    }
      
    if (key < node->key){
        node->left = insert(node->left, key, distance_min, distance_max);
    }
    else if (key > node->key){
        node->right = insert(node->right, key, distance_min, distance_max);
    }
    else {
        // Si la clé est déjà présente, comparer les distances_min
        if (distance_min < node->distance_min) {
            node->distance_min = distance_min;
        } 
        else {
            node->distance_max = distance_min;
        }
        return node;
    }

    // Étape 2 : Mettre à jour la hauteur du nœud actuel
    node->height = 1 + max(height(node->left), height(node->right));

    // Étape 3 : Obtenir le facteur d'équilibre de ce nœud pour vérifier l'équilibre
    int balance = 0;

    // Si le nœud devient déséquilibré, il y a 4 cas de rotation

    // Cas Gauche-Gauche
    if (balance > 1 && key < node->left->key){
        return rightrotate(node);
    }    

    // Cas Droit-Droit
    if (balance < -1 && key > node->right->key){
        return leftrotate(node);
    }

    // Cas Gauche-Droite
    if (balance > 1 && key > node->left->key) {
        node->left = leftrotate(node->left);
        return rightrotate(node);
    }

    // Cas Droite-Gauche
    if (balance < -1 && key < node->right->key) {
        node->right = rightrotate(node->right);
        return leftrotate(node);
    }

    // Si le nœud est déjà équilibré, retourner le nœud inchangé
    return node;
}

// Fonction pour parcourir l'AVL dans l'ordre
void inOrder(struct Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("Key: %d, Distance_min: %d, Distance_max: %d\n", root->key, root->distance_min, root->distance_max);
        inOrder(root->right);
    }
}

// Fonction principale
int main() {
    struct Donnees {
    int colonne1;
    int colonne5;
};
    struct Donnees *tableau;
    int nombreDeLignes = 6365542;  

    // Ouverture du fichier CSV en mode lecture
    FILE *fichier = fopen("data.csv", "r");

    // Vérification de l'ouverture du fichier
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;  // Quitter le programme avec un code d'erreur
    }

    // Allocation dynamique du tableau de structures
    tableau = (struct Donnees*)malloc(nombreDeLignes * sizeof(struct Donnees));

    // Vérification de l'allocation mémoire
    if (tableau == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation mémoire.\n");
        fclose(fichier);
        return 1;  // Quitter le programme avec un code d'erreur
    }

    // Lecture des données du fichier CSV et stockage dans le tableau
    for (int i = 0; i < nombreDeLignes; i++) {
        int colonne1, colonne5;

        // Utilisez le format approprié en fonction de votre fichier CSV
        if (fscanf(fichier, "%d,%*d,%*d,%*d,%d", &colonne1, &colonne5) != 2) {
            fprintf(stderr, "Erreur lors de la lecture des données à la ligne %d.\n", i + 1);
            free(tableau);
            fclose(fichier);
            return 1;  // Quitter le programme avec un code d'erreur
        }

        // Stockage des données dans le tableau de structures
        tableau[i].colonne1 = colonne1;
        tableau[i].colonne5 = colonne5;
    }
    
    // Fermeture du fichier CSV
    fclose(fichier);
    
      //On met les données dans un AVL
    struct Node * root = NULL;
    for (int i = 0; i < nombreDeLignes; ++i) {
        root = insert(root, tableau[i].colonne1, tableau[i].colonne5, 0);
    }

    // Afficher les données dans l'ordre
    inOrder(root);

    return 0;
}
