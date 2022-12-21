#include <stdio.h>
#include <stdlib.h> // macros
#include <string.h> // strerror
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include "array_int.h"
#include "array2d.h"
#include "utils.h"

extern int errno; // strerror

void exit_error(char const *str) {
    eprintf("%s\n", str);
    exit(EXIT_FAILURE);
}

FILE *get_input(char const *path) {
    FILE *input = path == NULL ? stdin : fopen(path, "r");
    
    if (input == NULL) {
        eprintf("Could not open file: %s\n", path);
        exit(EXIT_FAILURE);
    }
    int ch = fgetc(input);
    
    if (ch == EOF)
        exit_error("given input is empty!");
    
    ungetc(ch, input);
    
    return input;
}

uint32_t lineno = 0, col = 0;

typedef enum parser_error_t: uint8_t {
    PARSER_ERR_EXTRA_OPENING_BRACKET,
    PARSER_ERR_EXTRA_CLOSING_BRACKET
} parser_error_t;
void /* never */ matrix_panic(parser_error_t error) {
    switch (error) {
        case PARSER_ERR_EXTRA_OPENING_BRACKET:
            eprintf("Extra opening bracket at %u:%u\n", lineno, col);
            break;
            
        case PARSER_ERR_EXTRA_CLOSING_BRACKET:
            eprintf("Extra closing bracket at %u:%u\n", lineno, col);
            break;
            
        default:
            eprintf("Unefined error: %hhu\n", error);
            break;
    }
    
    exit(EXIT_FAILURE);
}

void row_push_number(array_int_t *restrict row, int64_t *restrict number, bool *restrict numberHasSet) {
    if (!*numberHasSet || !row) return;
    
    array_int_push(row, *number);
    *number = 0;
    *numberHasSet = false;
}

void parse_matrix_file(FILE *restrict input, array2d_t *restrict matrix) {
    bool hasOpenBracket = false;
    int64_t number = 0;
    bool numberHasSet = false;
    array_int_t *row = NULL;
    
    while(!feof(input)) {
        int ch = fgetc(input);
        ++col;
        
        if(isdigit(ch)) {
            number *= 10;
            number += ch - '0';
            numberHasSet = true;
            continue;
        }
        
        switch (ch) {
            case ';':
                row_push_number(row, &number, &numberHasSet);
                if (row && row->size != 0)
                    array2d_push(matrix, row);
                row = array_int_create();
                break;
                
            case '\n':
                ++lineno;
                col = 0;
                
            case ' ':
            case '\r':
            case '\t':
            case '\v':
            case '\f':
                row_push_number(row, &number, &numberHasSet);
                break;
                
            case '[':
                if (hasOpenBracket)
                    matrix_panic(PARSER_ERR_EXTRA_OPENING_BRACKET);
                
                hasOpenBracket = true;
                row = array_int_create();
                break;
                
            case ']':
                if (!hasOpenBracket)
                    matrix_panic(PARSER_ERR_EXTRA_CLOSING_BRACKET);
                
                hasOpenBracket = false;
                
                row_push_number(row, &number, &numberHasSet);
                if (row && row->size != 0)
                    array2d_push(matrix, row);
                row = NULL;
                break;
        }
    }
    
    if (hasOpenBracket)
        matrix_panic(PARSER_ERR_EXTRA_OPENING_BRACKET);
}

int main(int argc, const char * argv[]) {
    if (argc > 2) {
        eprintf("bad option: %s\n", argv[2]);
        exit_error("usage: txt2matrix [input-file]");
    }
    
    FILE *input = get_input(argc == 2 ? argv[1] : NULL);
    array2d_t *matrix = array2d_create();
    
    parse_matrix_file(input, matrix);
    
    array2d_print(matrix);
    
    array2d_free(matrix);
    return EXIT_SUCCESS;
}
