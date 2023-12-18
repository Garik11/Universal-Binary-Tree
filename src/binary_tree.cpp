#include "binary_tree.h"

TreeBin* TreeCtor(
                    void*   (*ContainerCtor)       (const void* container),
                    void    (*ContainerCopy)       (void* dst, const void* src),
                    void    (*ContainerDtor)       (void* container),
                    void    (*ContainerPaint)      (const void* container),
                    int     (*ContainerComparator) (const void* a, const void* b)
                    
){

    assert(ContainerCtor != NULL);
    assert(ContainerCopy != NULL);
    assert(ContainerDtor != NULL);
    assert(ContainerPaint != NULL);
    assert(ContainerComparator != NULL);

    TreeBin* tree = (TreeBin*)calloc(ONE_ELEMENT, sizeof(TreeBin));
    assert(tree != NULL);

    tree->number_of_nodes = 0;

    tree->containerComparator   = ContainerComparator;
    tree->containerCtor         = ContainerCtor;
    tree->containerCopy         = ContainerCopy;
    tree->containerPrint        = ContainerPaint;
    tree->containerDtor         = ContainerDtor;

    tree->nodes = NULL;

    return tree;
}

void TreeDtor(TreeBin* tree){

    assert(tree != NULL);

    TreeNodeDeleteBranch(tree, tree->nodes);

    free(tree);
}

void TreeNodeDeleteBranch(TreeBin* tree, TreeNode* node){
    if(node != NULL){
        TreeNodeDeleteBranch(tree, node->left);
        TreeNodeDeleteBranch(tree, node->right);
        TreeNodeDeleteVertex(tree, node);
    }
}

void TreeNodeDeleteVertex(TreeBin* tree, TreeNode* node){
    
    assert(tree != NULL);
    assert(node != NULL);

    if(node->father != NULL){
        if(node->father->left == node){
            node->father->left = NULL;
        }
        else if(node->father->right == node){
            node->father->right = NULL;
        }
        else
            assert(false);
    }

    tree->containerDtor(node->container);

    *node = NULLNODE;

    free(node);
    assert(tree->number_of_nodes > 0);
    tree->number_of_nodes--;

    if(tree->number_of_nodes == ZERO_ELEMENTS)
        tree->nodes = NULL;

}

TreeNode* TreeNodeMake(
                        TreeBin*            tree    , 
                        TreeNode*           father  , 
                        const void*         element , 
                        const NODE_STATUS   status
                    )
{
    assert(tree != NULL);
    assert(element != NULL);

    TreeNode* node = (TreeNode*)calloc(ONE_ELEMENT, sizeof(TreeNode));
    assert(node != NULL);

    *node = NULLNODE;

    node->container = tree->containerCtor(element);
    tree->containerCopy(node->container, element);
    node->father = father;

    switch (status) {
        case TREE_THIS:
            {
                break;
            }
        case TREE_LEFT:
            {
                node->father->left = node;
                break;
            }
        case TREE_RIGHT:
            {
                node->father->right = node;
                break;
            }
        default:
            {
                assert(false);
                break;
            }
    }
    
    tree->number_of_nodes++;
    if(tree->number_of_nodes == FIRST_ELEMENT)
        tree->nodes = node;
    return node;
}

void TreeSetElement(TreeBin* tree, void* element){

    assert(tree != NULL);
    assert(element != NULL);

    int compare_status = 0;
    TreeNode* father = NULL;
    TreeNode* node = tree->nodes;

    do{
        if(node == NULL){
            node = TreeNodeMake(tree, father, element, (NODE_STATUS)compare_status);
            return;
        }
        compare_status = tree->containerComparator(node->container, element);
        switch (compare_status) {
            case TREE_THIS:
                {
                    tree->containerCopy(node->container, element);
                    return;
                }
            case TREE_LEFT:
                {
                    father = node;
                    node = node->left;
                    break;
                }
            case TREE_RIGHT:
                {
                    father = node;
                    node = node->right;
                    break;
                }
            default:
                assert(false);
        }
    }while(compare_status);

    assert(false);
}

void TreeOut(const TreeBin* tree, OUT_TYPE out_type){
    assert(tree != NULL);
    printf("TREE:%p\n", tree);
    TreeBranchOut(tree, tree->nodes, out_type);
}

void TreeBranchOut(const TreeBin* tree, const TreeNode* node, OUT_TYPE out_type){
    if(node != NULL){
        switch (out_type)
        {
        case TREE_NORMAL_OUT:{
            TreeBranchOut(tree, node->left, out_type);
            tree->containerPrint(node->container);
            TreeBranchOut(tree, node->right, out_type);
            break;
        }
        case TREE_REVERSE_OUT:{
            TreeBranchOut(tree, node->right, out_type);
            tree->containerPrint(node->container);
            TreeBranchOut(tree, node->left, out_type);
            break;
        }
        default:
            assert(false);
        }

    }
}

TreeNode* TreeNodeFindElement(TreeBin* tree, const void* element){

    assert(tree != NULL);
    assert(element != NULL);

    int compare_status = 0;

    TreeNode* node = tree->nodes;

    do{
        compare_status = tree->containerComparator(node->container, element);
        switch (compare_status) {
            case TREE_THIS:
                {
                    return node;
                    break;
                }
            case TREE_LEFT:
                {
                    node = node->left;
                    if(node == NULL)
                        return NULL;
                    break;
                }
            case TREE_RIGHT:
                {
                    node = node->right;
                    if(node == NULL)
                        return NULL;
                    break;
                }
            default:
                assert(false);
        }
    }while(compare_status);
    return NULL;
}

TreeNode* TreeNodeGetMin(TreeNode* node){

    assert(node != NULL);

    while(node->left != NULL)
        node = node->left;
    
    return node;
}

void TreeDelElement(TreeBin* tree, void* element){

    assert(tree != NULL);
    assert(element != NULL);

    TreeNode* node_element = TreeNodeFindElement(tree, element);

    TreeNode* node = tree->nodes;

    assert(node_element != NULL);
    if(node_element->left == NULL && node_element->right == NULL){
        
        TreeNodeDeleteVertex(tree, node_element);
    }
    else {
        TreeNode* node_replacement = NULL;
        if  (
                node_element->left == NULL && node_element->right != NULL ||
                node_element->left != NULL && node_element->right == NULL
        )
            node_replacement = (node_element->left == NULL) ?   node_element->right 
                                                            :   node_element->left;
        else if(node_element->left != NULL && node_element->right != NULL)
            node_replacement = TreeNodeGetMin(node->right);
        else
            assert(false);
            
        if(node_replacement->left != NULL || node_replacement->right != NULL){
            void* new_value = tree->containerCtor(node_replacement->container);
            TreeDelElement(tree, node_replacement->container);
            tree->containerCopy(node_element->container, new_value);
            tree->containerDtor(new_value);
        }
        else {
            tree->containerCopy(node_element->container, node_replacement->container);
            TreeNodeDeleteVertex(tree, node_replacement);
        }
    }
}  