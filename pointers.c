#include <stdio.h>

int main() {
    int a = 99;

    printf("integer a is: %i\n", a);

    // every var in c is stored in memory => every var in c MUST have an addres in memory
    // how do we get that address?
    // &()
    // &: variable --> address of that variable

    printf("address of a is: %p\n", &(a) );

    // &: variable --> address of that variable
    // *: address of a variable --> variable
    // *(address(variable)) --> variable

    printf("thing contained in the variable that has the address of a, is: %i\n", *(&(a)) );

    int (*(b));

    printf("address b is: %p\n", b);

    printf("value at address b is: %i\n", *(b));

    b = &(a);

    printf("NEW value of address b is: %p\n", b);

    printf("NEW value at address b is: %i\n", *(b));

    return 0;
}