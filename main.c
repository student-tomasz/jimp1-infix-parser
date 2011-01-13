#include <stdlib.h>
#include <stdio.h>
#include "translator.h"

int main(int argc, char const *argv[])
{
    char *infix;
    
    
    infix = " ";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "\0";
    printf("%s -> %s\n", infix, translate(infix));
    
    infix = "3";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "3.5";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "a";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "abc";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "-3.5";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "-abc";
    printf("%s -> %s\n", infix, translate(infix));
    
    infix = " 3 - 3 ";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "a+-b";
    printf("%s -> %s\n", infix, translate(infix));
    
    infix = "3.5+123-0.5432*-qwe";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "3.5+123-(0.5432*-qwe)";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "3.5    + (123 -0.5432)* -qwe";
    printf("%s -> %s\n", infix, translate(infix));
    
    
    infix = "((a+b)/c)";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "--3.5";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "-(-3.5)";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "-(-9)-3.5";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "-(-9-3.5)";
    printf("%s -> %s\n", infix, translate(infix));    
    
    
    infix = "+";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "-";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "()";
    printf("%s -> %s\n", infix, translate(infix));
    infix = ")";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "(a*";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "a +";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "a-";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "a+b/";
    printf("%s -> %s\n", infix, translate(infix));
    infix = "-(-9-)3.5";
    printf("%s -> %s\n", infix, translate(infix));
    
    
    infix = "13123 123 + 4";
    printf("%s -> %s\n", infix, translate(infix));
    
    
    return 0;
}