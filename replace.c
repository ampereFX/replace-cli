
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>

#define MAX_LINE_LEN 4000
#define PRINT_DEBUG 1

// declarations
void show_usage_screen(char* arg);
void print_debug_information();

static char* old_string = NULL;
static char* new_string = NULL;
char* current_line = NULL;
char* current_line_copy = NULL;

int main(int argc, char *argv[]) {

    int option_index = 0;
    int c;

    static struct option long_options[] = {
        {"help",    no_argument,       0, 'h'},
        {"version", no_argument,       0, 'v'},
        // {"old",    required_argument, 0, 'o'},
        // {"new",    required_argument, 0, 'n'},
        {0, 0, 0, 0}
    };

    old_string = argv[argc - 2];
    new_string = argv[argc - 1];

    uint64_t oldlen = 0;
    uint64_t newlen = 0;

    while ((c = getopt_long(argc, argv, "hv", long_options, &option_index)) != -1) {
        switch (c) {
            case 'h':
                show_usage_screen(argv[0]);
                // return 0;
            case 'v':
                printf("Version 1.0\n");
                // return 0;
        }
    }

    
    // printf("2Letzte: %s", argv[argc - 2]);
    // printf("1Letzte: %s", argv[argc - 1]);
    
    current_line = NULL;
    current_line_copy = NULL;
    size_t max_line_len = MAX_LINE_LEN;
    ssize_t read = -1;
    size_t line_len = 0;

    read = getline(&current_line, &max_line_len, stdin);
    if (read != -1) {
        // success
        line_len = strlen(current_line);
        current_line_copy = malloc(line_len + 1);
        strcpy(current_line_copy, current_line);
        char* newline_char = strrchr(current_line_copy, '\n');
        *newline_char = '\0';
        printf("%s\t%u\n", current_line_copy, (uint32_t) line_len);
    } else {
        // failed
    }
    PRINT_DEBUG ? print_debug_information(): 0;
    return 0;

}

void show_usage_screen(char* arg) {
    printf("Usage: %s [--help] [--version] [--old <to-replace>] [--new <replacement>]\n", arg);
}

void print_debug_information() {
    printf("--------------\n");
    printf("old_string:\t'%s'\n", old_string);
    printf("new_string:\t'%s'\n", new_string);
    printf("%s:\t%u\n", "strlen(current_line)", (uint32_t) strlen(current_line));
    printf("%s:\t%u\n", "strlen(current_line_copy)", (uint32_t) strlen(current_line_copy));
}