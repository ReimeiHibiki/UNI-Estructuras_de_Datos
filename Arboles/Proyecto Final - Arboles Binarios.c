#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
//Version 1, 02/12/2022

//Declaracion de la estructura principal
struct node
{
    int data;
    struct node *left;
    struct node *right;
};

//Declaracion de elementos de la estructura auxiliares
struct node *head = NULL, *newnode, *parentptr, *temp;

//Declaracion de prototipos de funciones
struct node *findSmallestElement(struct node *tree);
struct node *findLargestElement(struct node *tree);
struct node *minValueNode(struct node *node);
struct node *deleteNode(struct node *root, int key);

void insertElement(struct node *node);
void preorderTraversal(struct node *node);
void inorderTraversal(struct node *node);
void postorderTraversal(struct node *node);
void deleteTree(struct node *node);
int totalNodes(struct node *tree);
int totalExternalNodes(struct node *tree);
int totalInternalNodes(struct node *tree);
int Height(struct node *tree);
unsigned int getLeafCount(struct node* tree);

// Funcion main
int main()
{
    int tn, TEN, TIN, TLC, height;
    int option = 0;
    printf("\n**********--Programa de Estructura de Datos - Arbol--**********");
    printf("\n***************************************************");
    printf("\n***--------Menu Principal--------***");
    printf("\nTeclee la opcion que desee.");
    printf("\n1)  Insertar Elemento\n2) Recorrido Preorden\n3) Recorrido Entreorden\n4) Recorrido Postorden\n5)  Elemento mas Pequeno\n6)  Elemento mas Grande\n7)  Eliminar un Elemento\n8)  Contar el Numero Total de Nodos\n9)  Numero de Nodos Externos\n10) Numero de Nodos Internos\n11) Altura del Arbol\n12) Borrar Todo El Arbol\n13) Numero de Nodos Hojas\n14) Salir");
    do
    {
        printf("\nUsted quiere realizar la siguiente operacion: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            insertElement(head);
            break;

        case 2:
            preorderTraversal(head);
            break;

        case 3:
            inorderTraversal(head);
            break;

        case 4:
            postorderTraversal(head);
            break;

        case 5:
            printf("\nEl elemento mas pequeno es: %d", findSmallestElement(head)->data);
            break;

        case 6:
            printf("\nEl elemento mas largo es: %d", findLargestElement(head)->data);
            break;

        case 7:
            printf("\nInserta el valor que quieras borrar: ");
            int key;
            scanf("%d", &key);
            deleteNode(head, key);
            break;

        case 8:
            tn = totalNodes(head);
            printf("\nEl numero total de nodos es: %d", tn);
            break;

        case 9:
            TEN = totalExternalNodes(head);
            printf("\nEl numero de nodos externos es: %d", TEN);
            break;

        case 10:
            TIN = totalInternalNodes(head);
            printf("\nEl numero de nodos internos es: %d", TIN);
            break;

        case 11:
            height = Height(head);
            printf("\nLa altura del arbol es: %d", height);
            break;

        case 12:
            deleteTree(head);
            break;

        case 13:
            TLC = getLeafCount(head);
            printf("\nEl numero de nodos hojas es: %d", TLC);
            break;

        case 14:
            return 0;
            break;

        default:
            printf("\nAdvertencia: Opcion invalida.\n");
            break;
        }
    } while (option != 14);
    return 0;
}

//Definicion de las funciones
struct node *findSmallestElement(struct node *tree)
{
    if ((tree == NULL) || (tree->left == NULL))
        return tree;
    else
        return findSmallestElement(tree->left);
}

struct node *findLargestElement(struct node *tree)
{
    if ((tree == NULL) || (tree->right == NULL))
        return tree;
    else
        return findLargestElement(tree->right);
}

struct node *minValueNode(struct node *node)
{
    struct node *current = node;

    /* Loop hacia abajo para encontrar la hoja más a la izquierda */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct node *deleteNode(struct node *root, int key)
{

    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);

    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    else
    {
        // Nodo con solo 1 hijo o ningun hijo
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        struct node *temp = minValueNode(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void insertElement(struct node* tree)
{
    newnode = (struct node *)malloc(sizeof(struct node));
    printf("\nInserta el valor que desees agregar: ");
    scanf("%d", &newnode->data);
    int val = newnode->data;
    newnode->left = NULL;
    newnode->right = NULL;

    if (head == NULL)
    {
        head = newnode;
    }
    else
    {
        temp = head;
        while (temp != NULL)
        {
            parentptr = temp;
            if (val < temp->data)
                temp = temp->left;
            else
                temp = temp->right;
        }
        if (val < parentptr->data)
            parentptr->left = newnode;
        else
            parentptr->right = newnode;
    }
}

void preorderTraversal(struct node *node)
{
    if (node == NULL)
        return;

    printf("%d ", node->data);
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

void inorderTraversal(struct node *node)
{
    if (node == NULL)
        return;

    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

void postorderTraversal(struct node *node)
{
    if (node == NULL)
        return;

    postorderTraversal(node->left);
    postorderTraversal(node->right);
    printf("%d ", node->data);
}

int totalNodes(struct node *tree)
{
    if (tree == NULL)
        return 0;
    else
        return (totalNodes(tree->left) + totalNodes(tree->right) + 1);
}

int totalExternalNodes(struct node *tree)
{
    if (tree == NULL)
        return 0;
    else if ((tree->left == NULL) && (tree->right == NULL))
        return 1;
    else
        return (totalExternalNodes(tree->left) + totalExternalNodes(tree->right));
}

int totalInternalNodes(struct node *tree)
{
    if ((tree == NULL) || ((tree->left == NULL) && (tree->right == NULL)))
        return 0;
    else
        return (totalInternalNodes(tree->left) + totalInternalNodes(tree->right) + 1);
}

int Height(struct node *tree)
{
    int leftheight, rightheight;
    if (tree == NULL)
        return -1;

    leftheight = Height(tree->left);
    rightheight = Height(tree->right);

    if (leftheight > rightheight)
        return (leftheight + 1);
    else
        return (rightheight + 1);
}

void deleteTree(struct node *tree)
{
    head = NULL;
    if (tree != NULL)
    {
        deleteTree(tree->left);
        deleteTree(tree->right);
        free(tree);
    }
    else
        return;
}

unsigned int getLeafCount(struct node* tree)
{
    if(tree == NULL)
        return 0;
    if(tree->left == NULL && tree->right == NULL)
        return 1;
    else
        return getLeafCount(tree->left) + getLeafCount(tree->right);
}