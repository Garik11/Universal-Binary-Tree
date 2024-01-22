#ifndef BINARY_TREE
#define BINARY_TREE

#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

#include "GlobalHeaders/config.h"
#include "GlobalHeaders/colors.h"
#include "GlobalHeaders/skul.h"

/*Calls the DUMP, simplifies the call for the user*/
#define TreeDump(tree, errors)          \
    _TreeDump(                          \
                tree,                   \
                errors,                 \
                #tree,                  \
                __FILE__,               \
                __LINE__,               \
                __PRETTY_FUNCTION__     \
            )

/*Calls the constructor, simplifies the call for the user*/
#define TreeCtor(ContainerCtor, ContainerDtor, ContainerCopy, ContainerComp, ContainerPaint)    \
    _TreeCtor(                                                                                  \
                ContainerCtor,                                                                  \
                ContainerDtor,                                                                  \
                ContainerCopy,                                                                  \
                ContainerComp,                                                                  \
                ContainerPaint,                                                                 \
                __FILE__,                                                                       \
                __PRETTY_FUNCTION__,                                                            \
                __LINE__                                                                        \
            )                                

/*Error output, this design was made for ENUM*/
#define PrintError(error_name) printf(#error_name "\n");

/*Types of functions to determine the types of output 
(it seems to me this is workaround)*/
enum TYPE_OF_FUNCTION{
    VOID,
    NON_VOID
};

/*Exiting a void type function*/
#define FORCED_EXIT_FROM_VOID()     \
    return

/*Exiting a pointer type function*/
#define FORCED_EXIT_FROM_NON_VOID() \
    return NULL

/*Special assert for debugging, conveniently shows errors
If the debug mode, it displays the dump and exits the program, 
if it is normal, it saves the error to the structure and exits the function.
*/
#define tree_assert(condition, tree, error_code, title, STATUS)                     \
    do{                                                                             \
        if(!(condition)){                                                           \
            ON_DEBUG(                                                               \
                printf(                                                             \
                        WRITEBACKGROUNDCOLOR(RED, "FATAL_ERROR:")                   \
                        " "                                                         \
                        WRITELIGHTCOLOR(YELLOW, "%s")                               \
                        " "                                                         \
                        WRITECOLOR(PURPLE, "in %s(%d) \n\tin %s")                   \
                        ", "                                                        \
                        WRITELIGHTCOLOR(BLACK, "%s")                                \
                        " was not met!\n",                                          \
                        #error_code,                                                \
                        __FILE__,                                                   \
                        __LINE__,                                                   \
                        __PRETTY_FUNCTION__,                                        \
                        #condition                                                  \
                        );                                                          \
                printf(                                                             \
                        WRITELIGHTCOLOR(RED, "ERROR_TEXT:")                         \
                        " "                                                         \
                        WRITELIGHTCOLOR(GREEN, "%s\n"),                             \
                        title                                                       \
                    );                                                              \
                TreeDump(tree, {error_code});                                       \
                abort();                                                            \
            )                                                                       \
            TreeErrors tree_errors = TreeVerificator(tree);                         \
            if(!(tree_errors.bit_mask & TREE_ERROR_BAD_BIN_POINTER)){               \
                tree->error_status = tree_errors;                                   \
                tree->error_status.bit_mask |= error_code;                          \
            }                                                                       \
            FORCED_EXIT_FROM_##STATUS();                                            \
        }                                                                           \
    }                                                                               \
    while(0)

/*For comparator
    0   - equal
    -1  - left
    1   - right
*/
enum TREE_NODE_STATUS{
    /*equal*/
    TREE_THIS    =  0,
    /*left son*/
    TREE_LEFT    = -1,
    /*right son*/
    TREE_RIGHT   =  1
};

/*Convenient names*/
enum{
    /*There are no elements*/
    ZERO_ELEMENTS = 0,
    /*First element*/
    FIRST_ELEMENT = 1,
    /*One element*/
    ONE_ELEMENT   = 1  
};

/*Formatted out, will be include*/
enum TREE_OUT_TYPE{
    /*Output in ascending order*/
    TREE_NORMAL_OUT,
    /*Output in descending order*/
    TREE_REVERSE_OUT
};

/*Error codes*/
enum TREE_ERRORS_CODE{
    /*Everything is fine with the tree*/
    TREE_ALL_OK                     = 0 << 0,
    /*Incorrect pointer to the main structure TreeBin*/
    TREE_ERROR_BAD_BIN_POINTER      = 1 << 0,
    /*Incorrect pointer to a tree node*/
    TREE_ERROR_BAD_NODE_POINTER     = 1 << 1,
    /*Incorrect pointer to the left son*/
    TREE_ERROR_BAD_LEFT_POINTER     = 1 << 2,
    /*Incorrect pointer to the right son*/
    TREE_ERROR_BAD_RIGHT_POINTER    = 1 << 3,

    /*Invalid pointer to the ContainerCtor function*/
    TREE_ERROR_BAD_CTOR_POINTER     = 1 << 4,
    /*Invalid pointer to the ContainerDtor function*/
    TREE_ERROR_BAD_DTOR_POINTER     = 1 << 5,
    /*Invalid pointer to the ContainerCopy function*/
    TREE_ERROR_BAD_COPY_POINTER     = 1 << 6,
    /*Invalid pointer to the ContainerComp function*/
    TREE_ERROR_BAD_COMP_POINTER     = 1 << 7,
    /*Invalid pointer to the ContainerPrint function*/
    TREE_ERROR_BAD_PRIN_POINTER     = 1 << 8,

    /*Invalid pointer to CREATION_FILE*/
    TREE_ERROR_BAD_CRFI_POINTER     = 1 << 9 ,
    /*Invalid pointer to CREATION_FUNC*/
    TREE_ERROR_BAD_CRFU_POINTER     = 1 << 10,

    /*Container element does not exits*/
    TREE_ERROR_ELEMENT_NOT_EXIST        = 1 << 11,
    /*There is a situation in the program that cannot happen*/
    TREE_ERROR_CODE_IS_CORRUPTED        = 1 << 12,
    /*The user's constructor returned a null value*/
    TREE_ERROR_CTOR_NOT_ALLOC_MEM       = 1 << 13,
    /*The comparator returned a value not from {-1, 0, 1}*/
    TREE_ERROR_COMP_ERROR_VALUE         = 1 << 14,
    /*Incorrect tree output type*/
    TREE_ERROR_BAD_OUT_TYPE             = 1 << 15,
    /*The TreeSet Element has not completed its execution*/
    TREE_ERROR_ELEMENT_DOES_NOT_SET     = 1 << 16,
    /*Calloc failed to allocate memory in TreeNodeMake*/
    TREE_ERROR_MAKENODE_NOT_ALLOC_MEM   =1 << 17,
    /*The position of the son is incorrectly indicated (left or right)*/
    TREE_ERROR_MAKENODE_BAD_STATUS      = 1 << 18,
    /*The program tries to delete a vertex of a tree in which the number of vertices is zero*/
    TREE_ERROR_INCORRECT_TREE_SIZE      = 1 << 19,
    /*The tree constructor could not allocate memory*/
    TREE_ERROR_TREECTOR_NOT_ALLOC_MEM   =1 << 20
};

/*Node Struct*/
typedef struct _TreeNode
{
    /*Pointer to the structure*/
    void* container;

    /*The pointer to the father*/
    struct _TreeNode* father;
    /*The pointer to the left son*/
    struct _TreeNode* left;
    /*The pointer to the right son*/
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
    /*Pointer to the first node*/
    TreeNode* nodes;
    /*Number of vertices*/
    size_t number_of_nodes;

    /*Error status*/
    TreeErrors error_status;

    /*The constructor must return a pointer to the new object*/
    void*   (*ContainerCtor)       (const void* container);
    /*The destructor must delete the object and free up memory (if it was allocated)*/
    void    (*ContainerDtor)       (void* container);
    /*Copying the structure from src to dst*/
    void    (*ContainerCopy)       (void* dst, const void* src);
    /*Comparing two structures should return one of the values {-1, 0, 1}*/
    int     (*ContainerComp)       (const void* a, const void* b);
    /*Used for the TreeOut function to view the contents of all tree vertices*/
    void    (*ContainerPrint)      (const void* container);

    /*The name of the file where the tree was created*/
    const char* CREATION_FILE;
    /*The name of the function where the tree was created*/
    const char* CREATION_FUNC;
    /*The line number where the tree was created*/
    int         CREATION_LINE;

} TreeBin;

/*The value of the null node*/
static const TreeNode NULLNODE = {NULL, NULL, NULL, NULL};

/*Tree Constructor*/
TreeBin* _TreeCtor(
                    /*The constructor must return a pointer to the new object*/
                    void*   (*ContainerCtor)       (const void* container),
                    /*The destructor must delete the object and free up memory (if it was allocated)*/
                    void    (*ContainerDtor)       (void* container),
                    /*Copying the structure from src to dst*/
                    void    (*ContainerCopy)       (void* dst, const void* src),
                    /*Comparing two structures should return one of the values {-1, 0, 1}*/
                    int     (*ContainerComp)       (const void* a, const void* b),
                    /*Used for the TreeOut function to view the contents of all tree vertices*/
                    void    (*ContainerPaint)      (const void* container),

                    /*The name of the file where the tree was created*/
                    const char* creation_file_name,
                    /*The name of the function where the tree was created*/
                    const char* creation_func_name,
                    /*The line number where the tree was created*/
                    const int   creation_line_numb
);

/*Tree Dtor, Frees up memory and deletes all tree vertices*/
void TreeDtor(TreeBin* tree);

/*Checks for errors directly related to the tree 
(such errors are considered critical).
Other error codes occur during execution, 
this function is not able to check them*/
TreeErrors TreeVerificator(const TreeBin* tree);

/*Out All errors and all tree*/
void _TreeDump(
                const TreeBin* tree,
                const TreeErrors  err,
                const char* tree_name,
                const char* file_name,
                const int   line_numb,
                const char* func_name 
            );
/*Auxiliary function for DUMP, 
to create a recursion to output tree vertices*/
void _TreeDumpOutNodes(const TreeNode* node);

/*Make New node, you should use TreeSetElement*/
TreeNode* TreeNodeMake(
                        TreeBin*                tree    , 
                        TreeNode*               father  , 
                        const void*             element , 
                        const TREE_NODE_STATUS  status
                    );


/*Set or add tree element*/
void TreeSetElement(
                        TreeBin* tree, 
                        const void* element
                    );
/*Delete element, must exists*/
void TreeDelElement(
                        TreeBin* tree, 
                        const void* element
                    );
/*Checks if the element exists
If so, returns a pointer to it
If not, it returns NULL*/
TreeNode* TreeNodeFindElement(
                                TreeBin* tree, 
                                const void* element
                            );

/*Auxiliary recursive function, deletes the entire branch, 
calls the TreeNodeDeleteVertex function in the process*/
void TreeNodeDeleteBranch(
                            TreeBin* tree, 
                            TreeNode* node
                        );
/*Deletes one vertex*/
void TreeNodeDeleteVertex(
                            TreeBin* tree, 
                            TreeNode* node
                        );

/*Outputs the entire tree, 
in the process calls the user's ContainerPaint function
You can set the output type TREE_NORMAL_OUT or TREE_REVERSE_OUT, 
the standard output type is TREE_NORMAL_OUT*/
void TreeOut(
                TreeBin* tree, 
                const TREE_OUT_TYPE out_type = TREE_NORMAL_OUT
            );

/*Outputs a branch of targets, 
an auxiliary function for TreeOut, 
uses the user's ContainerPaint function*/
void TreeBranchOut(
                    TreeBin* tree, 
                    const TreeNode* node, 
                    const TREE_OUT_TYPE out_type = TREE_NORMAL_OUT
                );

/*Beautiful PairOut output for DUMP*/
void TreeNodePairOut(const TreeNode* node);

/*Returns the minimum element, returns NULL in case of failure*/
TreeNode* TreeNodeGetMin(TreeNode* node);

#endif