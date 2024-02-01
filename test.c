#include <stdio.h>
#include <stdlib.h>

// Structure pour représenter un nœud de l'AVL
struct Node {
    int key;
    int distance_min;
    int distance_max;
    struct Node *left;
    struct Node *right;
    int height;
};

// Fonction pour calculer la hauteur d'un nœud dans l'AVL
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Fonction pour retourner le maximum de deux entiers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fonction pour créer un nouveau nœud AVL
struct Node *newNode(int key, int distance_min, int distance_max) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->distance_min = distance_min;
    node->distance_max = distance_max;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Nouveau nœud est à la hauteur 1
    return node;
}

// Fonction pour effectuer une rotation simple à droite
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Fonction pour effectuer une rotation simple à gauche
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Fonction pour obtenir le facteur d'équilibre d'un nœud
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Fonction pour insérer un nœud dans l'AVL
struct Node *insert(struct Node *node, int key, int distance_min, int distance_max) {
    // Étape 1 : Effectuer l'insertion standard d'un nœud BST
    if (node == NULL)
        return newNode(key, distance_min, distance_max);

    if (key < node->key)
        node->left = insert(node->left, key, distance_min, distance_max);
    else if (key > node->key)
        node->right = insert(node->right, key, distance_min, distance_max);
    else {
        // Si la clé est déjà présente, comparer les distances_min
        if (distance_min < node->distance_min) {
            node->distance_min = distance_min;
        } else {
            node->distance_max = distance_min;
        }
        return node;
    }

    // Étape 2 : Mettre à jour la hauteur du nœud actuel
    node->height = 1 + max(height(node->left), height(node->right));

    // Étape 3 : Obtenir le facteur d'équilibre de ce nœud pour vérifier l'équilibre
    int balance = getBalance(node);

    // Si le nœud devient déséquilibré, il y a 4 cas de rotation

    // Cas Gauche-Gauche
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Cas Droit-Droit
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Cas Gauche-Droite
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Cas Droite-Gauche
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
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
    int nombreDeLignes = 6365542;  // Mettez le nombre de lignes réel de votre fichier

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
    for (int i = 0; i < nombreDeLignes; ++i) {
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
