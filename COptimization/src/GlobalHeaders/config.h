#ifndef TREE_CONFIG_H
#define TREE_CONFIG_H

/*The author's pseudonym
git: https://github.com/Garik11*/
static const char TREE_AUTOR_NAME   [] = "KXI";
/*Program version*/
static const char TREE_VERSION      [] = "0.5";  

/*Debugging status, affects the behavior of the asserts
If enabled, the assertions cause a dump and exit the program
If disabled, the assertions exit the function saving errors*/
#define DEBUG

/*Colors will be used for dump and assert output, 
in case of absence the text will be normal 
(this is done so that in console output it is better 
to look at colored text, 
and if you save the output in a file it is 
better to look at plain text)*/
#define COLORED_OUT

/*Used for debugging*/
#ifdef DEBUG
    #define ON_DEBUG(...) __VA_ARGS__
#else 
    #define ON_DEBUG(...) //ignone all ON_DEBUG
#endif

#endif // !TREE_CONFIG_H