#include <stdio.h>
#include <stdlib.h>

//some string utls
//cp a --> b
void str_cp(char* a, char* b) {
    if ((a == NULL)||(b == NULL)) return;
    for (;;) {
        if (*a == '\0') {
            *b = '\0';
            break;
        }
        *b = *a;
        b++; a++;
    }
    return;
}
//--------------------
unsigned long int str_len(char* str) {
    if (str == NULL) return 0;
    unsigned long int len = 0;
    for (;;) {
        if (*str == '\0') break;
        len++; str++;
    }
    return len;
}


//global error system
typedef struct {
    int exit_code;
    char* err_msg;
} exit_error;
//-------------------------
exit_error* init_err() {
    exit_error* er_ptr = malloc(sizeof(exit_error));
    er_ptr->exit_code = 0;
    er_ptr->err_msg = NULL;
    return er_ptr;
}
//-------------------------
void set_err(exit_error* er_ptr, int err_code, char* err_msg) {
    er_ptr->exit_code = err_code;
    if (er_ptr->err_msg != NULL) free(er_ptr->err_msg);
    er_ptr->err_msg = (char*) malloc(sizeof(err_msg));
    str_cp(err_msg, er_ptr->err_msg);
}
//-------------------------
void exit_Werr(exit_error* er_ptr) {
    if (er_ptr->exit_code == 0) return;
    printf("[ERROR] %s\n", (er_ptr->err_msg == NULL) ? "<No Error Message Set>" : er_ptr->err_msg);
    free(er_ptr->err_msg);
    exit(er_ptr->exit_code);
}

// 0 for error; non-0 for ok
unsigned long int parse_int(char* int_char, exit_error* er_ptr) {
    char* last_addr = &int_char[0];
    unsigned short int idx = 1;
    for (;;) if (*last_addr == 0) {
        last_addr--;
        idx--;
        break;
    } else {
        last_addr++;
        idx++;
    }
    if (idx > 18) {
        set_err(er_ptr, 1, "Provided input too big. <Need unsigned long int>");
        return 0;
    } //overflow check

    unsigned long int cntr = 0, cn10 = 1;
    for (;;) {
        if (idx == 0) break;
        if ((*last_addr < 48)||(*last_addr > 57)) {
            set_err(er_ptr, 1, "Not a number. <Need positive integer>");
            return 0;
        }
        cntr += (*last_addr-48)*cn10;
        cn10 *= 10;
        last_addr--;
        idx--;
    }

    return cntr;
}

int main(int argc, char** argv) {
    //prim arg # check
    if (argc != 2) {
        printf("Too many/less arguments.\n");
        return 1;
    }

    exit_error* error = init_err();

    unsigned long int sqr = 0, idx = 0, gvn = parse_int(argv[1], error);
    exit_Werr(error);


    for (;;idx++) if (gvn > sqr) sqr += idx*2 + 1; else break; //single line of square root logic

    printf("Given: %lu.\n", gvn);
    printf("Closest square: %lu.\n", sqr);
    printf("Square root: %lu.\n", idx);

    free(error);
    return 0;
}