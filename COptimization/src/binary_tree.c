#include "binary_tree.h"

/*A stream for dump and assert error output
You can override it to your output stream
To do this, use the TreeSetDebugOutStream function,
To reset the output stream, use the TreeResetDebugOutStream function*/
static FILE* TREE_DEBUG_OUTPUT_STREAM = NULL;
static void init_streams(void) __attribute__((constructor)); 
static void init_streams(void)
{
  TREE_DEBUG_OUTPUT_STREAM = stdout;
}

TreeBin* _TreeCtor(
                    void*   (*ContainerCtor)       (const void* container),
                    void    (*ContainerDtor)       (void* container),
                    void    (*ContainerCopy)       (void* dst, const void* src),
                    int     (*ContainerComp)       (const void* a, const void* b),
                    void    (*ContainerPaint)      (const void* container),

                    const char* creation_file_name,
                    const char* creation_func_name,
                    const int   creation_line_numb    
                )
{
    tree_assert(
        ContainerCtor != NULL,
        ((TreeBin*)NULL),
        TREE_ERROR_BAD_CTOR_POINTER,
        "Invalid pointer to the ContainerCtor function!"
    );

    tree_assert(
        ContainerDtor != NULL,
        ((TreeBin*)NULL),
        TREE_ERROR_BAD_DTOR_POINTER,
        "Invalid pointer to the ContainerDtor function!"
    );

    tree_assert(
        ContainerCopy != NULL,
        ((TreeBin*)NULL),
        TREE_ERROR_BAD_COPY_POINTER,
        "Invalid pointer to the ContainerCopy function!"
    );

    tree_assert(
        ContainerComp != NULL,
        ((TreeBin*)NULL),
        TREE_ERROR_BAD_COMP_POINTER,
        "Invalid pointer to the ContainerComp function!"
    );

    tree_assert(
        ContainerPaint != NULL,
        ((TreeBin*)NULL),
        TREE_ERROR_BAD_PRIN_POINTER,
        "Invalid pointer to the ContainerPaint function!"
    );

    tree_assert(
        creation_file_name != NULL,
        ((TreeBin*)NULL),
        TREE_ERROR_BAD_CRFI_POINTER,
        "Invalid pointer to the creation_file_name!"
    );

    tree_assert(
        creation_func_name != NULL,
        ((TreeBin*)NULL),
        TREE_ERROR_BAD_CRFU_POINTER,
        "Invalid pointer to the creation_func_name!"
    );

    TreeBin* tree = (TreeBin*)calloc(ONE_ELEMENT, sizeof(TreeBin));
    
    tree_assert(
        tree != NULL,
        tree,
        TREE_ERROR_TREECTOR_NOT_ALLOC_MEM,
        "Calloc failed to allocate memory!"
    );
    
    tree_checking_error(
        tree != NULL,
        tree,
        TREE_ERROR_TREECTOR_NOT_ALLOC_MEM,
        NON_VOID
    );

    tree->number_of_nodes = 0;

    tree->ContainerCtor     = ContainerCtor;
    tree->ContainerDtor     = ContainerDtor;
    tree->ContainerCopy     = ContainerCopy;
    tree->ContainerComp     = ContainerComp;
    tree->ContainerPrint    = ContainerPaint;

    tree->CREATION_FILE = creation_file_name;
    tree->CREATION_FUNC = creation_func_name;
    tree->CREATION_LINE = creation_line_numb;

    tree->nodes = NULL;

    return tree;
}

void TreeDtor(TreeBin* tree) 
{
    tree_assert(
        TreeVerificator(tree).bit_mask == TREE_ALL_OK,
        tree,
        TreeVerificator(tree).bit_mask,
        "Critical error in the tree structure!"
    );

    tree_assert(
        tree != NULL, 
        tree, 
        TREE_ERROR_BAD_BIN_POINTER,
        "Incorrect pointer to the tree!"
    );

    TreeNodeDeleteBranch(tree, tree->nodes);

    free(tree);
}

TreeErrors TreeVerificator(const TreeBin* tree) 
{

    TreeErrors output;
    output.bit_mask = TREE_ALL_OK;

    if(tree == NULL){
        output.bit_mask |= TREE_ERROR_BAD_BIN_POINTER;
        return output;
    }

    if(tree->ContainerComp == NULL)
        output.bit_mask |= TREE_ERROR_BAD_COMP_POINTER;
    if(tree->ContainerCopy == NULL)
        output.bit_mask |= TREE_ERROR_BAD_COPY_POINTER;
    if(tree->ContainerCtor == NULL)
        output.bit_mask |= TREE_ERROR_BAD_CTOR_POINTER;
    if(tree->ContainerDtor == NULL)
        output.bit_mask |= TREE_ERROR_BAD_DTOR_POINTER;
    if(tree->ContainerPrint == NULL)
        output.bit_mask |= TREE_ERROR_BAD_PRIN_POINTER;
    if(tree->CREATION_FILE == NULL)
        output.bit_mask |= TREE_ERROR_BAD_CRFI_POINTER;
    if(tree->CREATION_FUNC == NULL)
        output.bit_mask |= TREE_ERROR_BAD_CRFU_POINTER;

    return output;
}

void _TreeDumpOutNodes(const TreeNode* node)
{
    if(node != NULL)
    {
        TreeNodePairOut(TREE_DEBUG_OUTPUT_STREAM, node);
        _TreeDumpOutNodes(node->left);
        _TreeDumpOutNodes(node->right);
    }
}

void _TreeDump(
                const TreeBin*  tree    , 
                const TreeErrors err    , 
                const char* tree_name   , 
                const char* file_name   , 
                const int   line_numb   , 
                const char* func_name
            )
{
    fprintf(
        TREE_DEBUG_OUTPUT_STREAM, 
        SWORDSKULDUMP
    );

    TreeErrors tree_errors = {TREE_ALL_OK};
    tree_errors.bit_mask = TreeVerificator(tree).bit_mask | err.bit_mask;

    const char* correctForOutputTrNm = (tree_name == NULL) ? "???" : tree_name;
    const char* correctForOutputFuNm = (func_name == NULL) ? "???" : func_name;
    const char* correctForOutputFlNm = (file_name == NULL) ? "???" : file_name;

    long int dump_time = time(NULL);
    fprintf(
        TREE_DEBUG_OUTPUT_STREAM,
        "Dump Time: %s\n", 
        ctime(&dump_time)
    );

    fprintf(
        TREE_DEBUG_OUTPUT_STREAM,
        "Tree[%p] %s called from %s in %s(%d)\n", 
        tree, 
        correctForOutputTrNm, 
        correctForOutputFuNm, 
        correctForOutputFlNm,
        line_numb
    );

    /*if TreeBin pointer is correct*/
    if(!(tree_errors.bit_mask & TREE_ERROR_BAD_BIN_POINTER)) 
    {

        tree_errors.bit_mask |= tree->error_status.bit_mask;

        fprintf(
            TREE_DEBUG_OUTPUT_STREAM, 
            "\t{\n"
        );
        fprintf(
            TREE_DEBUG_OUTPUT_STREAM, 
            "\t\t nodes              = %p\n",    
            tree->nodes
        );
        fprintf(
            TREE_DEBUG_OUTPUT_STREAM, 
            "\t\t number_of_nodes    = %lu\n",
            tree->number_of_nodes
        );
        fprintf(
            TREE_DEBUG_OUTPUT_STREAM, 
            "\t\t containerCtor      = %p\n",
            tree->ContainerCtor
        );
        fprintf(
            TREE_DEBUG_OUTPUT_STREAM, 
            "\t\t containerDtor      = %p\n",
            tree->ContainerDtor
        );
        fprintf(
            TREE_DEBUG_OUTPUT_STREAM, 
            "\t\t containerCopy      = %p\n",
            tree->ContainerCopy
        );
        fprintf(
            TREE_DEBUG_OUTPUT_STREAM, 
            "\t\t containerComp      = %p\n", 
            tree->ContainerComp
        );
        fprintf(
            TREE_DEBUG_OUTPUT_STREAM,
            "\t\t containerPrint     = %p\n",
            tree->ContainerPrint
        );

        const char* correctForOutputCrFl = 
            (tree->CREATION_FILE == NULL) ? 
                "???" : 
                tree->CREATION_FILE
        ;
        const char* correctForOutputCrFu = 
            (tree->CREATION_FUNC == NULL) ? 
                "???" : 
                tree->CREATION_FUNC
        ;

        fprintf(
            TREE_DEBUG_OUTPUT_STREAM, 
            "\t\t CREATION_FILE[%p] = %s\n",  
            tree->CREATION_FILE, 
            correctForOutputCrFl
        );
        fprintf(
            TREE_DEBUG_OUTPUT_STREAM, 
            "\t\t CREATION_FUNC[%p] = %s\n",
            tree->CREATION_FUNC,
            correctForOutputCrFu
        );
        fprintf(
            TREE_DEBUG_OUTPUT_STREAM,
            "\t\t CREATION_LINE[%p] = %d\n",
            &tree->CREATION_LINE,
            tree->CREATION_LINE
        );

        fprintf(
            TREE_DEBUG_OUTPUT_STREAM, 
            "\t}\n"
        );
    }

    fprintf(
        TREE_DEBUG_OUTPUT_STREAM,
        WRITELIGHTCOLOR(RED, "Error list:\n")
    );
    fprintf(
        TREE_DEBUG_OUTPUT_STREAM, 
        "\t{\n"
    );

    if(tree_errors.bit_mask & TREE_ERROR_BAD_BIN_POINTER) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")   , 
        PrintError(TREE_ERROR_BAD_BIN_POINTER)      ;
    if(tree_errors.bit_mask & TREE_ERROR_BAD_NODE_POINTER) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")   , 
        PrintError(TREE_ERROR_BAD_NODE_POINTER)     ;
    if(tree_errors.bit_mask & TREE_ERROR_BAD_LEFT_POINTER)
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")   , 
        PrintError(TREE_ERROR_BAD_LEFT_POINTER)     ;
    if(tree_errors.bit_mask & TREE_ERROR_BAD_RIGHT_POINTER) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")   , 
        PrintError(TREE_ERROR_BAD_RIGHT_POINTER)    ;
    if(tree_errors.bit_mask & TREE_ERROR_BAD_COMP_POINTER) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")   , 
        PrintError(TREE_ERROR_BAD_COMP_POINTER)     ;
    if(tree_errors.bit_mask & TREE_ERROR_BAD_CTOR_POINTER) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")   , 
        PrintError(TREE_ERROR_BAD_CTOR_POINTER)     ;
    if(tree_errors.bit_mask & TREE_ERROR_BAD_COPY_POINTER) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")   , 
        PrintError(TREE_ERROR_BAD_COPY_POINTER)     ;
    if(tree_errors.bit_mask & TREE_ERROR_BAD_DTOR_POINTER) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")   , 
        PrintError(TREE_ERROR_BAD_DTOR_POINTER)     ;
    if(tree_errors.bit_mask & TREE_ERROR_BAD_PRIN_POINTER) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")   , 
        PrintError(TREE_ERROR_BAD_PRIN_POINTER)     ;
    if(tree_errors.bit_mask & TREE_ERROR_BAD_CRFI_POINTER) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")   , 
        PrintError(TREE_ERROR_BAD_CRFI_POINTER)     ;
    if(tree_errors.bit_mask & TREE_ERROR_BAD_CRFU_POINTER)
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")   , 
        PrintError(TREE_ERROR_BAD_CRFU_POINTER)     ;

    if(tree_errors.bit_mask & TREE_ERROR_BAD_OUT_TYPE) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")       , 
        PrintError(TREE_ERROR_BAD_OUT_TYPE)             ;
    if(tree_errors.bit_mask & TREE_ERROR_COMP_ERROR_VALUE) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")       , 
        PrintError(TREE_ERROR_COMP_ERROR_VALUE)         ;
    if(tree_errors.bit_mask & TREE_ERROR_ELEMENT_NOT_EXIST) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")       , 
        PrintError(TREE_ERROR_ELEMENT_NOT_EXIST)        ;
    if(tree_errors.bit_mask & TREE_ERROR_CODE_IS_CORRUPTED) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")       , 
        PrintError(TREE_ERROR_CODE_IS_CORRUPTED)        ;
    if(tree_errors.bit_mask & TREE_ERROR_CTOR_NOT_ALLOC_MEM) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")       , 
        PrintError(TREE_ERROR_CTOR_NOT_ALLOC_MEM )      ;
    if(tree_errors.bit_mask & TREE_ERROR_INCORRECT_TREE_SIZE) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")       , 
        PrintError(TREE_ERROR_INCORRECT_TREE_SIZE)      ;
    if(tree_errors.bit_mask & TREE_ERROR_MAKENODE_BAD_STATUS) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")       , 
        PrintError(TREE_ERROR_MAKENODE_BAD_STATUS)      ;
    if(tree_errors.bit_mask & TREE_ERROR_ELEMENT_DOES_NOT_SET) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")       , 
        PrintError(TREE_ERROR_ELEMENT_DOES_NOT_SET)     ;
    if(tree_errors.bit_mask & TREE_ERROR_MAKENODE_NOT_ALLOC_MEM) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")       , 
        PrintError(TREE_ERROR_MAKENODE_NOT_ALLOC_MEM)   ;
    if(tree_errors.bit_mask & TREE_ERROR_TREECTOR_NOT_ALLOC_MEM) 
        fprintf(TREE_DEBUG_OUTPUT_STREAM, "\t\t")       , 
        PrintError(TREE_ERROR_TREECTOR_NOT_ALLOC_MEM)   ;
    fprintf(
        TREE_DEBUG_OUTPUT_STREAM, 
        "\t}\n"
    );

    if(!(tree_errors.bit_mask & TREE_ERROR_BAD_BIN_POINTER))
    {
        _TreeDumpOutNodes(tree->nodes);
    }
}

void TreeNodeDeleteBranch(
                            TreeBin* tree, 
                            TreeNode* node
                        )
{
    tree_assert(
        TreeVerificator(tree).bit_mask == TREE_ALL_OK,
        tree,
        TreeVerificator(tree).bit_mask,
        "Critical error in the tree structure!"
    );

    if(node != NULL) {
        TreeNodeDeleteBranch(tree, node->left);
        TreeNodeDeleteBranch(tree, node->right);
        TreeNodeDeleteVertex(tree, node);
    }
}

void TreeNodeDeleteVertex(
                            TreeBin* tree, 
                            TreeNode* node
                        )
{
    tree_assert(
        TreeVerificator(tree).bit_mask == TREE_ALL_OK,
        tree,
        TreeVerificator(tree).bit_mask,
        "Critical error in the tree structure!"
    );

    tree_assert(
        node != NULL,
        tree,
        TREE_ERROR_BAD_NODE_POINTER,
        "Incorrect pointer to the node!"
    );

    if(node->father != NULL)
    {
        if(node->father->left == node)
        {
            node->father->left = NULL;
        }
        else if(node->father->right == node)
        {
            node->father->right = NULL;
        }
        else
        {
            tree_assert(
                false,
                tree,
                TREE_ERROR_CODE_IS_CORRUPTED,
                "The executable file code is corrupted, an impossible exception situation has occurred"
            );
        }
    }

    tree->ContainerDtor(node->container);

    *node = NULLNODE;

    free(node);

    tree_assert(
        tree->number_of_nodes > ZERO_ELEMENTS,
        tree,
        TREE_ERROR_INCORRECT_TREE_SIZE,
        "Deleting an element contradicts the number of elements in the tree (it is empty)!"
    );

    tree->number_of_nodes--;

    if(tree->number_of_nodes == ZERO_ELEMENTS)
    {
        tree->nodes = NULL;
    }
}

TreeNode* TreeNodeMake(
                        TreeBin*    tree    , 
                        TreeNode*   father  , 
                        const void* element , 
                        const TREE_NODE_STATUS status
                    )
{
    tree_assert(
        TreeVerificator(tree).bit_mask == TREE_ALL_OK,
        tree,
        TreeVerificator(tree).bit_mask,
        "Critical error in the tree structure!"
    );

    tree_assert(
        element != NULL, 
        tree, 
        TREE_ERROR_ELEMENT_NOT_EXIST, 
        "Incorrect pointer to element!"
    );

    TreeNode* node = (TreeNode*)calloc(ONE_ELEMENT, sizeof(TreeNode));
    
    tree_assert(
        node != NULL, 
        tree,
        TREE_ERROR_MAKENODE_NOT_ALLOC_MEM,
        "Calloc failed to allocate memory!"
    );

    tree_checking_error(
        node != NULL, 
        tree,
        TREE_ERROR_MAKENODE_NOT_ALLOC_MEM,
        NON_VOID
    );

    *node = NULLNODE;

    node->container = tree->ContainerCtor(element);
    tree->ContainerCopy(node->container, element);
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
                tree_assert(
                    false,
                    tree,
                    TREE_ERROR_MAKENODE_BAD_STATUS,
                    "Incorrect information about the location of the branch!(not left, not right, not this)!"
                );
                break;
            }
    }
    
    tree->number_of_nodes++;

    if(tree->number_of_nodes == FIRST_ELEMENT)
    {
        tree->nodes = node;
    }

    return node;
}

void TreeSetElement(
                        TreeBin* tree, 
                        const void* element
                    )
{
    tree_assert(
        TreeVerificator(tree).bit_mask == TREE_ALL_OK,
        tree,
        TreeVerificator(tree).bit_mask,
        "Critical error in the tree structure!"
    );

    tree_assert(
        element != NULL, 
        tree, 
        TREE_ERROR_ELEMENT_NOT_EXIST, 
        "Incorrect pointer to element!"
    );

    tree_checking_error(
        element != NULL, 
        tree, 
        TREE_ERROR_ELEMENT_NOT_EXIST, 
        VOID
    );

    int compare_status = 0;

    TreeNode* father    = NULL;
    TreeNode* node      = tree->nodes;

    do {
        if(node == NULL) 
        {
            node = TreeNodeMake(tree, father, element, (TREE_NODE_STATUS)compare_status);
            return;
        }

        compare_status = tree->ContainerComp(node->container, element);

        switch (compare_status) {
            case TREE_THIS:
                {
                    tree->ContainerCopy(node->container, element);
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
                {
                    tree_assert(
                        false,
                        tree,
                        TREE_ERROR_COMP_ERROR_VALUE,
                        "The comparator returned an incorrect value. \nThe comparator should return values in {-1, 0, 1}"
                    );
                    break;
                }
        }
    } while(compare_status);

    tree_assert(
        false,
        tree,
        TREE_ERROR_ELEMENT_DOES_NOT_SET,
        "Incorrect behavior of the TreeSetElement function!"
    );
}

void TreeOut(
                TreeBin* tree, 
                TREE_OUT_TYPE out_type
            )
{
    tree_assert(
        TreeVerificator(tree).bit_mask == TREE_ALL_OK,
        tree,
        TreeVerificator(tree).bit_mask,
        "Critical error in the tree structure!"
    );

    /*I don't know yet why this function is needed, 
    but maybe it will make sense later*/
    TreeBranchOut(tree, tree->nodes, out_type);
}

void TreeBranchOut(
                        TreeBin* tree, 
                        const TreeNode* node, 
                        TREE_OUT_TYPE out_type
                    )
{
    tree_assert(
        TreeVerificator(tree).bit_mask == TREE_ALL_OK,
        tree,
        TreeVerificator(tree).bit_mask,
        "Critical error in the tree structure!"
    );

    if(node != NULL) 
    {
        switch (out_type) {
            case TREE_NORMAL_OUT:
                {
                    TreeBranchOut(tree, node->left, out_type);
                    tree->ContainerPrint(node->container);
                    TreeBranchOut(tree, node->right, out_type);
                    break;
                }
            case TREE_REVERSE_OUT:
                {
                    TreeBranchOut(tree, node->right, out_type);
                    tree->ContainerPrint(node->container);
                    TreeBranchOut(tree, node->left, out_type);
                    break;
                }
            default:
                {
                    tree_assert(
                        false,
                        tree,
                        TREE_ERROR_BAD_OUT_TYPE,
                        "You must chose one of TREE_OUT_TYPE!"
                    );
                    break;
                }
        }
    }
}

void TreeNodePairOut(
                        FILE* out_stream,
                        const TreeNode* node
                    )
{
    tree_assert(
        out_stream != NULL,
        (TreeBin*)NULL,
        TREE_ERROR_BAD_OUT_STREAM,
        "You have set the output stream to NULL!"
    );

    tree_assert(
        node != NULL,
        (TreeBin*)NULL,
        TREE_ERROR_BAD_NODE_POINTER,
        "Null pointer to node!"
    );

    static const int address_width = 14;

    putc('\n', out_stream);
    if(node != NULL && node->left != NULL)
    {
        fprintf(
            out_stream,
            "\t\t\t\t"
            SETLIGHTCOLOR(GREEN)
            " Left ["
            WRITEBACKGROUNDCOLOR(RED, "%-*p")
            "]\n"
            CLOSECOLOR(),
            address_width,
            node->left
        );
	    fprintf(
            out_stream,
            "\t\t\t\t"
            WRITEBACKGROUNDCOLOR(PURPLE, "/")
            "\n"
        );
    }
	fprintf(
        out_stream,
        "%s", 
        (node == NULL) ?    SETLIGHTCOLOR(RED) :
                            SETLIGHTCOLOR(BLUE)
    );
	fprintf(
        out_stream,
        "Node["
        WRITEBACKGROUNDCOLOR(WHITE, "%-*p")
        "] ————————— "
        CLOSECOLOR()
        WRITEBACKGROUNDCOLOR(PURPLE, "| ")
        "\n",
        address_width,
        node
    );
	if(node != NULL && node->right != NULL)
    {
	    fprintf(
            out_stream,
            "\t\t\t\t"
            WRITEBACKGROUNDCOLOR(PURPLE, "\\")
            "\n"
        );
	    fprintf(
            out_stream,
            "\t\t\t\t"
            SETLIGHTCOLOR(GREEN)
            " Right["
            WRITEBACKGROUNDCOLOR(RED, "%-*p")
            "]\n"
            CLOSECOLOR(),
            address_width,
            node->right
        );
    }
    putc('\n', out_stream);   
}

TreeNode* TreeFindElement(
                                TreeBin* tree, 
                                const void* element
                            )
{
    tree_assert(
        TreeVerificator(tree).bit_mask == TREE_ALL_OK,
        tree,
        TreeVerificator(tree).bit_mask,
        "Critical error in the tree structure!"
    );

    tree_assert(
        element != NULL, 
        tree, 
        TREE_ERROR_ELEMENT_NOT_EXIST, 
        "Incorrect pointer to element!"
    );

    /*If the pointer is null, 
    then the element is obviously not found 
    (at the same time,  
    this behavior is an error from the point of view of the debug.
    Yes, I wanted it that way)*/
    if(element == NULL)
    {
        return NULL;
    }

    int compare_status = 0;

    TreeNode* node = tree->nodes;

    do {
        compare_status = tree->ContainerComp(node->container, element);

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
                {
                    tree_assert(
                        false,
                        tree,
                        TREE_ERROR_COMP_ERROR_VALUE,
                        "The comparator returned an incorrect value. \nThe comparator should return values in {-1, 0, 1}"
                    );
                    break;
                }
        }
    } while(compare_status);

    return NULL;
}

TreeNode* TreeNodeGetMin(TreeNode* node) 
{
    if(node == NULL)
        return NULL;

    while(node->left != NULL)
        node = node->left;
    
    return node;
}

TreeNode* TreeNodeGetMax(TreeNode *node)
{
    if(node == NULL)
        return NULL;

    while(node->right != NULL)
        node = node->right;
    
    return node;
}

void TreeDelElement(
                        TreeBin* tree, 
                        const void* element
                    )
{
    tree_assert(
        TreeVerificator(tree).bit_mask == TREE_ALL_OK,
        tree,
        TreeVerificator(tree).bit_mask,
        "Critical error in the tree structure!"
    );

    tree_assert(
        element != NULL, 
        tree, 
        TREE_ERROR_ELEMENT_NOT_EXIST, 
        "Incorrect pointer to element!"
    );

    tree_checking_error(
        element != NULL, 
        tree, 
        TREE_ERROR_ELEMENT_NOT_EXIST, 
        VOID
    );

    TreeNode* node_element = TreeFindElement(tree, element);

    tree_checking_error(
        node_element != NULL, 
        tree, 
        TREE_ERROR_ELEMENT_NOT_FOUND, 
        VOID
    );

    TreeNode* node = tree->nodes;

    if(node_element->left == NULL && node_element->right == NULL) {
        TreeNodeDeleteVertex(tree, node_element);
    }
    else 
    {
        TreeNode* node_replacement = NULL;
        if (
                (node_element->left == NULL && node_element->right != NULL) ||
                (node_element->left != NULL && node_element->right == NULL)
            )
        {
            node_replacement = (node_element->left == NULL) ?   node_element->right 
                                                            :   node_element->left;
        }
        else if(node_element->left != NULL && node_element->right != NULL) 
        {
            node_replacement = TreeNodeGetMin(node->right);

            tree_assert(
                node_replacement != NULL, 
                tree, 
                TREE_ERROR_ELEMENT_NOT_EXIST,
                "The minimum element was not found!"
            );
        }
        else 
        {
            tree_assert(
                false,
                tree,
                TREE_ERROR_CODE_IS_CORRUPTED,
                "The executable file code is corrupted, an impossible exception situation has occurred"
            );
        }
            
        if(node_replacement->left != NULL || node_replacement->right != NULL) 
        {
            void* new_value = tree->ContainerCtor(node_replacement->container);

            tree_assert(
                new_value != NULL,
                tree,
                TREE_ERROR_CTOR_NOT_ALLOC_MEM,
                "An error occurred in the constructor, a null pointer was returned"
            );

            tree_checking_error(
                new_value != NULL,
                tree,
                TREE_ERROR_CTOR_NOT_ALLOC_MEM,
                VOID
            );

            TreeDelElement(tree, node_replacement->container);
            tree->ContainerCopy(node_element->container, new_value);
            tree->ContainerDtor(new_value);
        }
        else 
        {
            tree->ContainerCopy(node_element->container, node_replacement->container);
            TreeNodeDeleteVertex(tree, node_replacement);
        }
    }
}

void TreeSetDebugOutStream(FILE *new_out_stream)
{
    tree_assert(
        new_out_stream != NULL,
        (TreeBin*)NULL,
        TREE_ERROR_BAD_OUT_STREAM,
        "You have set the output stream to NULL!"
    );

    TREE_DEBUG_OUTPUT_STREAM = new_out_stream;
}

void TreeResetDebugOutStream(){
    TREE_DEBUG_OUTPUT_STREAM = stdout;
}