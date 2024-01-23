#include <stdio.h>
#include <assert.h>

#include "src/binary_tree.h"

/*The file for containerPrint*/
FILE*       my_out_file         = NULL;

/*Simpe struct for example*/
typedef struct _Container
{
    unsigned long long key;
    char value;
} Container;

/*Constructor for struct*/
void*   containerCtor   (const void* containter_pointer);
/*Destructor for struct*/
void    containerDtor   (void* containter_pointer);
/*Structure copy function*/
void    containerCopy   (void* dst_pointer, const void* src_pointer);
/*The structure comparison function should return values from {-1, 0, 1}. 
If the comparison is incorrect, there will be undefined behavior.*/
int     containerComp   (const void* a, const void* b);
/*Output of structure elements, specifically for TreeOut*/
void    containerPrint  (const void* containter_pointer);

/*The function is not directly related to the work of the tree in any way
Bijection of two natural numbers into one*/
unsigned long long f(unsigned long long, unsigned long long);

int main(void) {
    /*For an example of the capabilities of the containerPrint function, 
    the values will be written to a separate file*/
    my_out_file = stdout; //fopen(my_out_file_name, "w");

    /*You can change the output stream of the dump and errors 
    (just keep in mind that the output will be colored, 
    this can be disabled in the config)*/
    //TreeSetDebugOutStream(my_out_file);

    /*The tree constructor itself
    A macro is called, the _TreeCtor function call is supplemented 
    with the file name, line number, and function name*/
    TreeBin* tree = TreeCtor(
                                containerCtor,
                                containerDtor,
                                containerCopy,
                                containerComp,
                                containerPrint
                            );
    /*A simple example of filling a tree*/
    srand((unsigned int)time(NULL));                        
    for(size_t i = 0; i < 10; i++){
        /*Example of a container*/
        Container cont = {
                            f(
                                (unsigned long long)rand(), 
                                (unsigned long long)rand()
                            ), 
                            'a' + (char)i
                        };
        /*The function adds elements to the tree, 
        and if they already exist, 
        it changes them to a new one.
        This includes calling the user's 
        containerCopy and containerComp functions*/
        TreeSetElement(tree, (void*)(&cont));
    }

    Container example = {123, 'z'};
    TreeSetElement(tree, (void*)(&example));

    /*The output of the tree, by means of recursion, 
    the user's containerPrint function is called*/
    TreeOut(tree, TREE_REVERSE_OUT);

    /*Macro calling _TreeDump 
    (for the sake of file name, line number and function name )*/
    TreeDump(tree, {TREE_ALL_OK});

    /*Example of returning the minimum and maximum element*/
    printf("MIN NODE:");
    containerPrint(TreeNodeGetMin(tree->nodes)->container);
    printf("MAX NODE:");
    containerPrint(TreeNodeGetMax(tree->nodes)->container);

    /*Example of searching for an element in a tree*/
    TreeNode* found_node_example = TreeFindElement(tree, (void*)(&example));
    printf("FOUND NODE:");
    containerPrint(found_node_example->container);

    /*Example of deleting an element from a tree*/
    TreeDelElement(tree, found_node_example->container);
    TreeOut(tree, TREE_REVERSE_OUT);

    /*Example of returning the minimum and maximum element*/
    printf("NEW MIN NODE:");
    containerPrint(TreeNodeGetMin(tree->nodes)->container);
    printf("NEW MAX NODE:");
    containerPrint(TreeNodeGetMax(tree->nodes)->container);

    /*An example of the output of a pair*/
    printf("An example of the output of a pair:");
    TreeNodePairOut(stdout, tree->nodes);

    /*The destructor of the tree, 
    including recursively calling the user's containerDtor function*/
    TreeDtor(tree);
}

void* containerCtor(const void* containter_pointer){
    void* new_containter = calloc(ONE_ELEMENT, sizeof(Container));
    /*Here I took the liberty of not doing any error checks, 
    but of course you should have them.*/
    containerCopy(new_containter, containter_pointer);
    return new_containter;
}

void containerDtor(void* containter_pointer){
    free(containter_pointer);
}

void containerCopy(void* dst_pointer, const void* src_pointer){
    Container* dst = (Container*)dst_pointer;
    const Container* src = (const Container*)src_pointer;
    dst->key = src->key;
    dst->value = src->value;
}

int containerComp(const void* a, const void* b){
    const Container* f = (const Container*)a;
    const Container* s = (const Container*)b;
    return (f->key < s->key) - (s->key < f->key);
}
void containerPrint(const void* containter_pointer){
    const Container* container = (const Container*)containter_pointer;
    fprintf(
        my_out_file, 
        "ADDR: %p, NUM : %llu, VAL : %c;\n", 
        containter_pointer,
        container->key, 
        container->value
    );
}

unsigned long long f(unsigned long long x, unsigned long long y) {
    return ((x + y) * (x + y + 1)) / 2 + x;
}