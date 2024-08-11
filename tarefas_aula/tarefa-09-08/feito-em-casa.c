#include <stdio.h>
#include <stdlib.h>


struct TreeNode_t {
    int val;
    struct TreeNode_t *left;
    struct TreeNode_t *right;
};

struct TreeNode_t *CreateNode ( int val );
struct TreeNode_t *CreateTree ( );
struct TreeNode_t *SubtreeWithAllDeepest ( struct TreeNode_t *root );
void InOrder_r ( struct TreeNode_t *node, int *depthNow, int *greatestDepth, struct TreeNode_t **path, struct TreeNode_t ****subtree, int *subTreeCounter );
struct TreeNode_t *CompareSubTrees ( struct TreeNode_t ***subTree, int greatestDepth, int subTreeCounter );


int main (  ) {
    struct TreeNode_t *root = CreateTree (  );
    struct TreeNode_t *result = SubtreeWithAllDeepest ( root );
    printf ( "A menor sub-árvore contendo todos os nodos mais profundos tem o valor: %d\n", result->val );
    free ( root->left->right->right );
    free ( root->left->right->left );
    free ( root->right->right );
    free ( root->right->left );
    free ( root->left->right );
    free ( root->left->left );
    free ( root->right );
    free ( root->left );
    free ( root );
    return 0;
}

/*
====================
CreateNode

    Cria um nodo da árvore
====================
*/
struct TreeNode_t *CreateNode ( int val ) {
    struct TreeNode_t *newNode = ( struct TreeNode_t* ) malloc  ( sizeof ( struct TreeNode_t ) );
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/*
====================
CreateTree 

    Cria a árvore para o teste
====================
*/
struct TreeNode_t *CreateTree ( ) {
    struct TreeNode_t *root = CreateNode ( 3 );
    root->left = CreateNode ( 5 );
    root->right = CreateNode ( 1 );
    root->left->left = CreateNode ( 6 );
    root->left->right = CreateNode ( 2 );
    root->right->left = CreateNode ( 0 );
    root->right->right = CreateNode ( 8 );
    root->left->right->left = CreateNode ( 7 );
    root->left->right->right = CreateNode ( 4 );
    return root;
}

/*
====================
SubtreeWithAllDeepest

    Inicializa as variáveis e os espaços de memória que serão utilizados para encontrar a menor árvore que contém todos os nodos mais profundos;
    Após ter encontrado o resultado executa free() onde foi alocado memória e retorna o resultado para a main
====================
*/
struct TreeNode_t *SubtreeWithAllDeepest ( struct TreeNode_t *root ) {

    int depthNow = -1;
    int greatestDepth = 0;
    int subTreeCounter = 0;

    struct TreeNode_t **path;
    path =  ( struct TreeNode_t** ) malloc  ( sizeof ( struct TreeNode_t* ) * 500 );

    struct TreeNode_t ***subTree;
    subTree =  ( struct TreeNode_t*** ) malloc ( sizeof ( struct TreeNode_t** ) );

    InOrder_r ( root, &depthNow, &greatestDepth, path, &subTree, &subTreeCounter );

    struct TreeNode_t *result = CompareSubTrees ( subTree, greatestDepth, subTreeCounter );

    for  ( int i = 0; i < subTreeCounter; i++ ) {
        free ( subTree [ i ] );
    }

    free ( subTree );
    free ( path );

    return result;
}

/*
====================
InOrder_r

    Função recursiva que percorre a árvore da esquerda para a direita;
    Armazena o caminho percorrido em um vetor;
    Se encontra um caminho mais profundo que o anterior, executa free() nos caminhos mais profundos encontrados anteriormente e aloca memória para armazenar o novo caminho;
    Se encontra um nodo tão profundo quanto o mais profundo encontrado anteriormente, aloca memória para armazenar este caminho;
    Após percorrer toda a árvore terá salvo a maior profundidade, a quantidade de caminhos mais profundos e os caminhos mais profundos;
====================
*/
void InOrder_r ( struct TreeNode_t *node, int *depthNow, int *greatestDepth, struct TreeNode_t **path, struct TreeNode_t ****subtree, int *subTreeCounter ){
    if  ( node == NULL ){
        return;
    }

     ( *depthNow ) ++;
    path [  ( *depthNow ) ] = node;

    InOrder_r ( node->left, depthNow, greatestDepth, path, subtree, subTreeCounter );

    InOrder_r ( node->right, depthNow, greatestDepth, path, subtree, subTreeCounter );
    
    if ( *depthNow > *greatestDepth  ){
        for  ( int i = 0; i < *subTreeCounter; i ++ ) {
            free (  ( *subtree ) [ i ] );
        }
        *subtree =  ( struct TreeNode_t*** ) realloc ( *subtree, sizeof ( struct TreeNode_t** ) * 1 );
         ( *subtree ) [ 0 ] =  ( struct TreeNode_t** ) malloc ( sizeof ( struct TreeNode_t* ) *  ( *depthNow + 1 ) );
        for ( int i = 0; i <= *depthNow; i ++ ){
             ( *subtree ) [ 0 ] [ i ] = path [ i ];
        }
        *greatestDepth = *depthNow;
        *subTreeCounter = 1;

    } else if  ( *depthNow == *greatestDepth ){
         ( *subTreeCounter ) ++;
        *subtree =  ( struct TreeNode_t*** ) realloc ( *subtree, sizeof ( struct TreeNode_t** ) *  ( *subTreeCounter ) );
         ( *subtree ) [ *subTreeCounter - 1 ] =  ( struct TreeNode_t** ) malloc ( sizeof ( struct TreeNode_t* ) *  ( *depthNow + 1 ) );

        for ( int i = 0; i <= *depthNow; i ++ ){
             ( *subtree ) [ *subTreeCounter - 1 ] [ i ] = path [ i ];
        }
    }

     ( *depthNow ) --;
    return;
}

/*
====================
CompareSubTrees

    Compara os caminhos mais profundos encontrados e retorna o menor caminho que é comum a todos;
    Se houver apenas um caminho mais profundo, retorna este caminho;
    Se houver mais de um caminho mais profundo, compara o primeiro caminho com o último e retorna a menor sub-árvore comum a eles;
====================
*/
struct TreeNode_t *CompareSubTrees ( struct TreeNode_t ***subTree, int greatestDepth, int subTreeCounter ){
    int i;
    if  ( subTree == NULL ){
        return subTree [ 0 ] [ 0 ];
    }
    if  ( subTreeCounter == 1 ){
        return subTree [ 0 ] [ greatestDepth ];
    }
    for ( i = 0; i <= greatestDepth; i ++ ){
        if ( subTree [ 0 ] [ i ] != subTree [ subTreeCounter - 1 ] [ i ] ){
            break;
        }
    }
    return subTree [ 0 ] [ i - 1 ];
}
