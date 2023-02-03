#include <stdio.h>

int main() {
    int a = 99;

    printf("a is %i\n", a);

    // a is a var => must exits on memory => 'a' must also have an address on memory
    // how get address of var 'a'?
    // &a is the address of 'a'
    // &(var) --> address or pointer of the var

    printf("address of a is %p\n", &a);


    // &: variable --> address of the variable
    // *: address or the pointer of a variable --> variable 

    printf("* applied on the address of a is %i\n", *&a ); // var --> point --> var

    int *b; // b is a pointer

    printf("pointer b is %p\n", b);

    printf("integer that b points to is %i\n", *b);

    b = &a;

    printf("*b when b = address of a, is %i\n", *b);

    return 0;
}