#include "binary_tree.h"

static void _TreeDumpOutNodes(const TreeNode* node);

TreeBin* _TreeCtor(
                    void*   (*ContainerCtor)       (const void* container),
                    void    (*ContainerDtor)       (void* container),
                    void    (*ContainerCopy)       (void* dst, const void* src),
                    int     (*ContainerComp)       (const void* a, const void* b),
                    void    (*ContainerPaint)      (const void* container),

                    const char* creation_file_name,
                    const char* creation_func_name,
                    const int   creation_line_numb
                    
){

    assert(ContainerCtor    != NULL);
    assert(ContainerDtor    != NULL);
    assert(ContainerCopy    != NULL);
    assert(ContainerComp    != NULL);
    assert(ContainerPaint   != NULL);

    assert(creation_file_name != NULL);
    assert(creation_func_name != NULL);
    assert(creation_line_numb != NULL);

    TreeBin* tree = (TreeBin*)calloc(ONE_ELEMENT, sizeof(TreeBin));
    assert(tree != NULL);

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

void TreeDtor(TreeBin* tree){

    assert(tree != NULL);

    TreeNodeDeleteBranch(tree, tree->nodes);

    free(tree);
}

TreeErrors TreeVerificator(const TreeBin* tree){

    if(tree == NULL)
        return {TREE_ERROR_BAD_BIN_POINTER};

    TreeErrors output = tree->error_status;

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
    if(tree->CREATION_LINE == NULL)
        output.bit_mask |= TREE_ERROR_BDA_LINU_POINTER;
    return output;
}

static void _TreeDumpOutNodes(const TreeNode* node){
    if(node != NULL){
        TreeNodePairOut(node);
        _TreeDumpOutNodes(node->left);
        _TreeDumpOutNodes(node->right);
    }
}

void TreeDump(
                const TreeBin*  tree    , 
                const TreeErrors err    , 
                const char* tree_name   , 
                const char* file_name   , 
                const int   line_numb   , 
                const char* func_name
            )
{

    printf(SWORDSKULDUMP);

    TreeErrors tree_errors = {TREE_ALL_OK};
    tree_errors.bit_mask = TreeVerificator(tree).bit_mask | err.bit_mask;

    const char* correctForOutputTrNm = (tree_name == NULL) ? "???" : tree_name;
    const char* correctForOutputFuNm = (func_name == NULL) ? "???" : func_name;
    const char* correctForOutputFlNm = (file_name == NULL) ? "???" : file_name;

    printf(
        "Tree[%p] %s called from %s in %s(%d)\n", 
        tree, 
        correctForOutputTrNm, 
        correctForOutputFuNm, 
        correctForOutputFlNm,
        line_numb
    );

    /*if TreeBin pointer is correct*/
    if(!(tree_errors.bit_mask & TREE_ERROR_BAD_BIN_POINTER)){
        printf("\t{\n");
        printf("\t\t nodes              = %p\n",    tree->nodes             );
        printf("\t\t number_of_nodes    = %lu\n",   tree->number_of_nodes   );
        printf("\t\t containerCtor      = %p\n",    tree->ContainerCtor     );
        printf("\t\t containerDtor      = %p\n",    tree->ContainerDtor     );
        printf("\t\t containerCopy      = %p\n",    tree->ContainerCopy     );
        printf("\t\t containerComp      = %p\n",    tree->ContainerComp     );
        printf("\t\t containerPrint     = %p\n",    tree->ContainerPrint    );

        const char* correctForOutputCrFl = (tree->CREATION_FILE == NULL) ? "???" : tree->CREATION_FILE;
        const char* correctForOutputCrFu = (tree->CREATION_FUNC == NULL) ? "???" : tree->CREATION_FUNC;
        printf("\t\t CREATION_FILE[%p] = %s\n",  tree->CREATION_FILE, correctForOutputCrFl  );
        printf("\t\t CREATION_FUNC[%p] = %s\n",  tree->CREATION_FUNC, correctForOutputCrFu  );
        printf("\t\t CREATION_LINE[%p] = %d\n", &tree->CREATION_LINE, tree->CREATION_LINE   );

        printf("\t}\n");
    }

    printf("Error list:\n");
    printf("\t{\n");
    if(tree_errors.bit_mask & TREE_ERROR_BAD_BIN_POINTER    ) printf("\t\t"), printerror(TREE_ERROR_BAD_BIN_POINTER     );
    if(tree_errors.bit_mask & TREE_ERROR_BAD_NODE_POINTER   ) printf("\t\t"), printerror(TREE_ERROR_BAD_NODE_POINTER    );
    if(tree_errors.bit_mask & TREE_ERROR_BAD_LEFT_POINTER   ) printf("\t\t"), printerror(TREE_ERROR_BAD_LEFT_POINTER    );
    if(tree_errors.bit_mask & TREE_ERROR_BAD_RIGHT_POINTER  ) printf("\t\t"), printerror(TREE_ERROR_BAD_RIGHT_POINTER   );
    if(tree_errors.bit_mask & TREE_ERROR_BAD_COMP_POINTER   ) printf("\t\t"), printerror(TREE_ERROR_BAD_COMP_POINTER    );
    if(tree_errors.bit_mask & TREE_ERROR_BAD_CTOR_POINTER   ) printf("\t\t"), printerror(TREE_ERROR_BAD_CTOR_POINTER    );
    if(tree_errors.bit_mask & TREE_ERROR_BAD_COPY_POINTER   ) printf("\t\t"), printerror(TREE_ERROR_BAD_COPY_POINTER    );
    if(tree_errors.bit_mask & TREE_ERROR_BAD_DTOR_POINTER   ) printf("\t\t"), printerror(TREE_ERROR_BAD_DTOR_POINTER    );
    if(tree_errors.bit_mask & TREE_ERROR_BAD_PRIN_POINTER   ) printf("\t\t"), printerror(TREE_ERROR_BAD_PRIN_POINTER    );
    if(tree_errors.bit_mask & TREE_ERROR_BAD_CRFI_POINTER   ) printf("\t\t"), printerror(TREE_ERROR_BAD_CRFI_POINTER    );
    if(tree_errors.bit_mask & TREE_ERROR_BAD_CRFU_POINTER   ) printf("\t\t"), printerror(TREE_ERROR_BAD_CRFU_POINTER    );
    if(tree_errors.bit_mask & TREE_ERROR_BDA_LINU_POINTER   ) printf("\t\t"), printerror(TREE_ERROR_BDA_LINU_POINTER    );
    printf("\t}\n");

    _TreeDumpOutNodes(tree->nodes);

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

    tree->ContainerDtor(node->container);

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
                        const TREE_NODE_STATUS   status
                    )
{
    assert(tree != NULL);
    assert(element != NULL);

    TreeNode* node = (TreeNode*)calloc(ONE_ELEMENT, sizeof(TreeNode));
    assert(node != NULL);

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
                assert(false);
        }
    }while(compare_status);

    assert(false);
}

void TreeOut(const TreeBin* tree, TREE_OUT_TYPE out_type){
    assert(tree != NULL);
    printf("TREE:%p\n", tree);
    TreeBranchOut(tree, tree->nodes, out_type);
}

void TreeBranchOut(const TreeBin* tree, const TreeNode* node, TREE_OUT_TYPE out_type){
    if(node != NULL){
        switch (out_type)
        {
        case TREE_NORMAL_OUT:{
            TreeBranchOut(tree, node->left, out_type);
            tree->ContainerPrint(node->container);
            TreeBranchOut(tree, node->right, out_type);
            break;
        }
        case TREE_REVERSE_OUT:{
            TreeBranchOut(tree, node->right, out_type);
            tree->ContainerPrint(node->container);
            TreeBranchOut(tree, node->left, out_type);
            break;
        }
        default:
            assert(false);
        }

    }
}

void TreeNodePairOut(const TreeNode* node){
    putchar('\n');
    if(node != NULL && node->left != NULL){
        printf(
                "\t\t\t\t"
                SETLIGHTCOLOR(GREEN)
                " Left ["
                WRITEBACKGROUNDCOLOR(RED, "%-14p")
                "]\n"
                CLOSECOLOR(),
                node->left
            );
	    printf(
                "\t\t\t\t"
                WRITEBACKGROUNDCOLOR(PURPLE, "/")
                "\n"
            );
    }
	printf(
            (node == NULL) ?    SETLIGHTCOLOR(RED) :
                                SETLIGHTCOLOR(BLUE)
        );
	printf(
        "Node["
        WRITEBACKGROUNDCOLOR(WHITE, "%-14p")
        "] ————————— "
        CLOSECOLOR()
        WRITEBACKGROUNDCOLOR(PURPLE, "| ")
        "\n",
        node
    );
	if(node != NULL && node->right != NULL){
	    printf(
                "\t\t\t\t"
                WRITEBACKGROUNDCOLOR(PURPLE, "\\")
                "\n"
                );
	    printf(
                "\t\t\t\t"
                SETLIGHTCOLOR(GREEN)
                " Right["
                WRITEBACKGROUNDCOLOR(RED, "%-14p")
                "]\n"
                CLOSECOLOR(),
                node->right
            );
    }
    putchar('\n');   
}

TreeNode* TreeNodeFindElement(TreeBin* tree, const void* element){

    assert(tree != NULL);
    assert(element != NULL);

    int compare_status = 0;

    TreeNode* node = tree->nodes;

    do{
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

    #warning add_not_exists element

    TreeNode* node_element = TreeNodeFindElement(tree, element);

    TreeNode* node = tree->nodes;

    assert(node_element != NULL);
    if(node_element->left == NULL && node_element->right == NULL){
        
        TreeNodeDeleteVertex(tree, node_element);
    }
    else {
        TreeNode* node_replacement = NULL;
        if  (
                (node_element->left == NULL && node_element->right != NULL) ||
                (node_element->left != NULL && node_element->right == NULL)
        )
            node_replacement = (node_element->left == NULL) ?   node_element->right 
                                                            :   node_element->left;
        else if(node_element->left != NULL && node_element->right != NULL)
            node_replacement = TreeNodeGetMin(node->right);
        else
            assert(false);
            
        if(node_replacement->left != NULL || node_replacement->right != NULL){
            void* new_value = tree->ContainerCtor(node_replacement->container);
            TreeDelElement(tree, node_replacement->container);
            tree->ContainerCopy(node_element->container, new_value);
            tree->ContainerDtor(new_value);
        }
        else {
            tree->ContainerCopy(node_element->container, node_replacement->container);
            TreeNodeDeleteVertex(tree, node_replacement);
        }
    }
}  