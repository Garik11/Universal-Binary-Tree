#ifndef BINARY_TREE
#define BINARY_TREE

#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enum NODE_STATUS{
    TREE_THIS    =  0,
    TREE_LEFT    = -1,
    TREE_RIGHT   =  1
};

enum{
    ZERO_ELEMENTS = 0,
    FIRST_ELEMENT = 1
};

enum OUT_TYPE{
    TREE_NORMAL_OUT,
    TREE_REVERSE_OUT
};

typedef struct _TreeNode
{
    void* container;

    struct _TreeNode* father;
    struct _TreeNode* left;
    struct _TreeNode* right;

} TreeNode;

typedef struct _TreeBin
{
    
    TreeNode* nodes;
    size_t number_of_nodes;

    int     (*containerComparator) (const void* a, const void* b);
    void*   (*containerCtor)       (const void* container);
    void    (*containerCopy)       (void* dst, const void* src);
    void    (*containerDtor)       (void* container);
    void    (*containerPrint)      (const void* container);

} TreeBin;

static const size_t ONE_ELEMENT = 1;

static const TreeNode         NULLNODE         = {NULL, NULL, NULL, NULL};

TreeBin* TreeCtor(
                    void*   (*ContainerCtor)       (const void* container),
                    void    (*ContainerCopy)       (void* dst, const void* src),
                    void    (*ContainerDtor)       (void* container),
                    void    (*ContainerPaint)      (const void* container),
                    int     (*ContainerComparator) (const void* a, const void* b)
                    
);
void TreeDtor(TreeBin* tree);

void TreeNodeDeleteBranch(TreeBin* tree, TreeNode* node);

TreeNode* TreeNodeMake(
                        TreeBin*            tree    , 
                        TreeNode*           father  , 
                        const void*         element , 
                        const NODE_STATUS   status
                    );

void TreeSetElement(TreeBin* tree, void* element);
void TreeDelElement(TreeBin* tree, void* element);

void TreeNodeDeleteVertex(TreeBin* tree, TreeNode* node);

void TreeOut(const TreeBin* tree, const OUT_TYPE out_type = TREE_NORMAL_OUT);

void TreeBranchOut(
                    const TreeBin* tree, 
                    const TreeNode* node, 
                    const OUT_TYPE out_type = TREE_NORMAL_OUT
                );

TreeNode* TreeNodeFindElement(TreeBin* tree, const void* element);
TreeNode* TreeNodeGetMin        (TreeNode* node);


#endif