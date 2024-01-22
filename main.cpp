#include <stdio.h>

#include "src/binary_tree.h"

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

    /*The output of the tree, by means of recursion, 
    the user's containerPrint function is called*/
    TreeOut(tree, TREE_REVERSE_OUT);

    /*Macro calling _TreeDump 
    (for the sake of file name, line number and function name )*/
    TreeDump(tree, {TREE_ALL_OK});

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
    printf("NUM : %llu, VAL : %c;\n", container->key, container->value);
}

unsigned long long f(unsigned long long x, unsigned long long y) {
    return ((x + y) * (x + y + 1)) / 2 + x;
}