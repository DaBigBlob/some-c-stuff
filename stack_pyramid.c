#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>



int main() {
    //get the terminal dimentions
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != 0) {
        printf("Cannot get terminal dimensions.");
        return 1;
    }

    unsigned long int middle = (w.ws_col - (w.ws_col%2))/2;

    for (unsigned long int row = 0; row <= w.ws_row - 10; row++) {
        for (unsigned long int col = 0; col <= middle + row; col++) {
            if (col < middle - row) printf(" ");
            else if (col > middle) printf("*");
            else printf("&");
        }
        printf("\n");
    }

    return 0;
}