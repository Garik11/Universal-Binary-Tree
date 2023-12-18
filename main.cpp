#include <stdio.h>
#include "src/binary_tree.h"

typedef struct _Container
{
    unsigned long long key;
    char value;
} Container;

int containerComparator(const void* a, const void* b){
    const Container* f = (const Container*)a;
    const Container* s = (const Container*)b;
    return (f->key < s->key) - (s->key < f->key);
}

void containerCopy(void* dst_pointer, const void* src_pointer){
    Container* dst = (Container*)dst_pointer;
    const Container* src = (const Container*)src_pointer;
    dst->key = src->key;
    dst->value = src->value;
}

void* containerCtor(const void* containter_pointer){
    void* new_containter = calloc(1, sizeof(Container));
    containerCopy(new_containter, containter_pointer);
    return new_containter;
}

void containerDtor(void* containter_pointer){
    free(containter_pointer);
}

void containerPrint(const void* containter_pointer){
    const Container* container = (const Container*)containter_pointer;
    printf("NUM:%llu VAL:%c \n", container->key, container->value);
}

int f(int, int);

int main(void) {
    TreeBin* tree = TreeCtor(
                                containerCtor,
                                containerCopy,
                                containerDtor,
                                containerPrint,
                                containerComparator
                                
                                );
    for(size_t i = 0; i < 3; i++){
        int x = {0}, y = {0};
        char c = {0};
        scanf("%d %d %c", &x, &y, &c);
        Container cont = {f(x, y), c};
        TreeSetElement(tree, (void*)(&cont));
    }
    TreeOut(tree, TREE_REVERSE_OUT);
    TreeDtor(tree);
}

int f(int x, int y) {
    return ((x + y) * (x + y + 1)) / 2 + x;
}