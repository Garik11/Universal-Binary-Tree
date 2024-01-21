#ifndef TREE_CONFIG_H
#define TREE_CONFIG_H

#include <stdint.h>

#define DEBUG

const char AUTOR_NAME   [] = "KXI";
const char VERSION      [] = "0.3";

#ifdef DEBUG
    #define ON_DEBUG(...) __VA_ARGS__
#elif 
    #define ON_DEBUG(...) //ignone all ON_DEBUG
#endif

#endif // !TREE_CONFIG_H