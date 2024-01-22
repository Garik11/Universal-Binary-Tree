#ifndef TREE_CONFIG_H
#define TREE_CONFIG_H

/*Debugging status, affects the behavior of the asserts
If enabled, the assertions cause a dump and exit the program
If disabled, the assertions exit the function saving errors*/
#define DEBUG

/*The author's pseudonym
git: https://github.com/Garik11*/
const char AUTOR_NAME   [] = "KXI";
/*Program version*/
const char VERSION      [] = "0.4";

/*Used for debugging*/
#ifdef DEBUG
    #define ON_DEBUG(...) __VA_ARGS__
#elif 
    #define ON_DEBUG(...) //ignone all ON_DEBUG
#endif

#endif // !TREE_CONFIG_H