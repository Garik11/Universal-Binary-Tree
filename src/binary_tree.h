#ifndef BINARY_TREE
#define BINARY_TREE

#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "GlobalHeaders/config.h"
#include "GlobalHeaders/colors.h"
#include "GlobalHeaders/skul.h"

/*Easy Dump for user*/
#define TREE_DUMP(tree, errors)         \
    TreeDump(                           \
                tree,                   \
                errors,                 \
                #tree,                  \
                __FILE__,               \
                __LINE__,               \
                __PRETTY_FUNCTION__     \
            ); 

#define TreeCtor(ContainerCtor, ContainerDtor, ContainerCopy, ContainerComp, ContainerPaint)\
    _TreeCtor(ContainerCtor, ContainerDtor, ContainerCopy, ContainerComp, ContainerPaint, __FILE__, __PRETTY_FUNCTION__, __LINE__)                                

#define printerror(error_name) printf(#error_name "\n");

/*For comparator
    0   - equal
    -1  - left
    1   - right
*/
enum TREE_NODE_STATUS{
    TREE_THIS    =  0,
    TREE_LEFT    = -1,
    TREE_RIGHT   =  1
};

enum{
    ZERO_ELEMENTS = 0,
    FIRST_ELEMENT = 1,
    ONE_ELEMENT   = 1  
};

#warning add_new_format
/*Formatted out, will be include*/
enum TREE_OUT_TYPE{
    TREE_NORMAL_OUT,
    TREE_REVERSE_OUT
};

/*Error codes*/
enum TREE_ERRORS_CODE{

    TREE_ALL_OK                     = 0 << 0,
    TREE_ERROR_BAD_BIN_POINTER      = 1 << 0,
    TREE_ERROR_BAD_NODE_POINTER     = 1 << 1,
    TREE_ERROR_BAD_LEFT_POINTER     = 1 << 2,
    TREE_ERROR_BAD_RIGHT_POINTER    = 1 << 3,
    TREE_ERROR_BAD_COMP_POINTER     = 1 << 4,
    TREE_ERROR_BAD_CTOR_POINTER     = 1 << 5,
    TREE_ERROR_BAD_COPY_POINTER     = 1 << 6,
    TREE_ERROR_BAD_DTOR_POINTER     = 1 << 7,
    TREE_ERROR_BAD_PRIN_POINTER     = 1 << 8,

    TREE_ERROR_BAD_CRFI_POINTER     = 1 << 9 ,
    TREE_ERROR_BAD_CRFU_POINTER     = 1 << 10,
    TREE_ERROR_BDA_LINU_POINTER     = 1 << 11

};

/*Node Struct*/
typedef struct _TreeNode
{
    void* container;

    struct _TreeNode* father;
    struct _TreeNode* left;
    struct _TreeNode* right;

} TreeNode;

/*Struct for errors*/
typedef struct _TreeErrors
{
    //Errors bit_mask
    uint64_t bit_mask;
} TreeErrors;

/*Tree Struct*/
typedef struct _TreeBin
{
    
    TreeNode* nodes;
    size_t number_of_nodes;

    TreeErrors error_status;

    int     (*ContainerComp)       (const void* a, const void* b);
    void*   (*ContainerCtor)       (const void* container);
    void    (*ContainerCopy)       (void* dst, const void* src);
    void    (*ContainerDtor)       (void* container);
    void    (*ContainerPrint)      (const void* container);

    const char* CREATION_FILE;
    const char* CREATION_FUNC;
    int         CREATION_LINE;

} TreeBin;

static const TreeNode         NULLNODE         = {NULL, NULL, NULL, NULL};
/*Tree Constructor, uses malloc, you must you TreeDtor(for memory leaks)*/
TreeBin* _TreeCtor(
                    void*   (*ContainerCtor)       (const void* container),
                    void    (*ContainerDtor)       (void* container),
                    void    (*ContainerCopy)       (void* dst, const void* src),
                    int     (*ContainerComp)       (const void* a, const void* b),
                    void    (*ContainerPaint)      (const void* container),

                    const char* creation_file_name,
                    const char* creation_func_name,
                    const int   creation_line_numb
);
/*Tree Dtor*/
void TreeDtor(TreeBin* tree);

/*Check all errors and returns*/
TreeErrors TreeVerificator(const TreeBin* tree);

/*Out All errors and all tree*/
void TreeDump(
                const TreeBin* tree,
                const TreeErrors  err,
                const char* tree_name,
                const char* file_name,
                const int   line_numb,
                const char* func_name 
            );

/*Make New node, you should use TreeSetElement*/
TreeNode* TreeNodeMake(
                        TreeBin*                tree    , 
                        TreeNode*               father  , 
                        const void*             element , 
                        const TREE_NODE_STATUS  status
                    );

/*
Set or add tree element
For user
*/
void TreeSetElement(TreeBin* tree, void* element);

/*
Delete element, must exists
For user
*/
void TreeDelElement(TreeBin* tree, void* element);

void TreeNodeDeleteVertex(TreeBin* tree, TreeNode* node);
void TreeNodeDeleteBranch(TreeBin* tree, TreeNode* node);

/*
Out all tree
*/
void TreeOut(const TreeBin* tree, const TREE_OUT_TYPE out_type = TREE_NORMAL_OUT);

/*
Out all branch
*/
void TreeBranchOut(
                    const TreeBin* tree, 
                    const TreeNode* node, 
                    const TREE_OUT_TYPE out_type = TREE_NORMAL_OUT
                );
/*
Beautiful PairOut output for DUMP
*/
void TreeNodePairOut(const TreeNode* node);

TreeNode* TreeNodeFindElement   (TreeBin* tree, const void* element);
TreeNode* TreeNodeGetMin        (TreeNode* node);

#endif