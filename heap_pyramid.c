#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

//vector unit
typedef struct node {
    char c;
    struct node* next;
} node_t;

//returns length of vector
unsigned long int vec_len(node_t* head) {
    if (head == NULL) return 0;

    unsigned long int len = 1;
    node_t* current_node = head;
    while (current_node->next != NULL) {
        len++;
        current_node = current_node->next;
    }
    return len;
}

//init vector
node_t* vector(char first) {
    node_t* head = malloc(sizeof(node_t));
    if (head == NULL) return NULL;
    head->c = first;
    head->next = NULL;
    return head;
}

// returns 1 if error && 0 if ok
int vec_push(node_t* head, unsigned long int index, char chr) {
    if (head == NULL) return 1;

    unsigned long int internal_index = 0;
    node_t* target = head;

    while (internal_index < index) {
        if (target->next == NULL) { //then make some
            target->next = (node_t*) malloc(sizeof(node_t));
            if (target->next == NULL) return 1;
            target->next->next = NULL;
            target->next->c = ' ';
        }

        target = target->next;
        internal_index++;
    }

    if (internal_index > index) return 1;

    target->c = chr;
    return 0;
}

//print vector
int print_vec(node_t* head) {
    if (head == NULL) return 1;

    printf("%c", head->c);

    node_t* target = head;
    while (target->next != NULL) {
        target = target->next;
        printf("%c", target->c);
    }

    return 0;
}
int println_vec(node_t* head) {
    int ec = print_vec(head);
    printf("\n");
    return ec;
}



int main() {
    //get the terminal dimentions
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != 0) {
        printf("Cannot get terminal dimensions.");
        return 1;
    }

    //init stuff
    node_t* vec = vector(' ');
    if (vec == NULL) {
        printf("Cannot allocate enough heap.");
        return 1;
    }
    unsigned long int middle = (w.ws_col - (w.ws_col%2))/2;

    for (unsigned long int row = 0; row <= w.ws_row - 10; row++) {

        //create the vec
        if (vec_push(vec, middle + row, '*') != 0) {
            printf("Cannnot allocate enough heap.");
            return 1;
        }
        if (vec_push(vec, middle - row, '&') != 0) { //one degenerate execution for row = 0
            printf("Cannnot allocate enough heap.");
            return 1;
        }

        println_vec(vec);
    }

    free(vec);
    return 0;
}