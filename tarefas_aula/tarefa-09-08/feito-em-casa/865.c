/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
    //saber a profundida atual para comparar com a maior profundidade. Quando for encontrada a maior profundidade salvar o caminho mais curto até ela. Se houver mais de 1 nodo com a mesma maior profundidade, comparar os caminhos. Achar o primeiro elemento que difere um de outro e o anterior elemento anterior será a menor árvore.
    //Se houver apenas 1 nodo mais profundo ele retornará ele mesmo

void InOrder (struct TreeNode* node, int *depthNow, int *greatestDepth, struct TreeNode **path, struct TreeNode ****subtree, int *subTreeCounter){
    if (node == NULL){
        return;
    }

    (*depthNow)++;
    path[(*depthNow)] = node;

    InOrder(node->left, depthNow, greatestDepth, path, subtree, subTreeCounter);

    InOrder(node->right, depthNow, greatestDepth, path, subtree, subTreeCounter);
    
    if(*depthNow > *greatestDepth ){
        (*subtree)[0] = (struct TreeNode**) malloc(sizeof(struct TreeNode*) * (*depthNow + 1));
        for(int i = 0; i <= *depthNow; i++){
            (*subtree)[0][i] = path[i];
        }
        *greatestDepth = *depthNow;
        *subTreeCounter = 1;
    } else if (*depthNow == *greatestDepth){
        (*subTreeCounter)++;
        *subtree = (struct TreeNode ***) realloc(*subtree, sizeof(struct TreeNode **) * (*subTreeCounter));
        (*subtree)[*subTreeCounter-1] = (struct TreeNode**) malloc(sizeof(struct TreeNode *) * (*depthNow + 1));

        for(int i = 0; i <= *depthNow; i++){
            (*subtree)[*subTreeCounter-1][i] = path[i];
        }
    }

    (*depthNow)--;
    return;

}

struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {

    int depthNow = -1;
    int greatestDepth = 0;

    struct TreeNode **path;
    path = (struct TreeNode **) malloc (sizeof(struct TreeNode *) * 500);

    struct TreeNode ***subTree;
    subTree = (struct TreeNode ***) malloc(sizeof(struct TreeNode**));

    int subTreeCounter = 0;

    InOrder(root, &depthNow, &greatestDepth, path, &subTree, &subTreeCounter);

    struct TreeNode* result = subTree[0][0];

    for (int i = 0; i < subTreeCounter; i++) {
        free(subTree[i]);
    }
    free(subTree);
    free(path);

    return result;
}

