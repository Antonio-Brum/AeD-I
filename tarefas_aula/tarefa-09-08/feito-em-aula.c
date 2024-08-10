/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
 struct TreeNode *InOrder (struct TreeNode* node, struct TreeNode *deepestNode, int *depthNow, int *greaterDepth){

    if (node == NULL){
        return deepestNode;
    }
    (*depthNow)++;
    deepestNode = InOrder(node->left, deepestNode, depthNow, greaterDepth);
    
    deepestNode = InOrder(node->right, deepestNode, depthNow, greaterDepth);

    if(*depthNow > *greaterDepth){
        deepestNode = node;
        *greaterDepth = *depthNow;
        
    } 

    (*depthNow)--;
    return deepestNode;
}

struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {

    //saber a profundida atual para comparar com a maior profundidade. Quando for encontrada a maior profundidade salvar o caminho mais curto até ela. Se houver mais de 1 nodo com a mesma maior profundidade, comparar os caminhos. Achar o primeiro elemento que difere um de outro e o elemento anterior será a menor árvore.
    //Se houver apenas 1 nodo mais profundo ele retornará este nodo;
    struct TreeNode *deepestNode;
    deepestNode = root;
    int depthNow = -1;
    int greaterDepth = 0;
    deepestNode = InOrder(root, deepestNode, &depthNow, &greaterDepth);

    printf("the deepest node has the value: %d and its depth is: %d", deepestNode->val, greaterDepth);
    return root;
}

