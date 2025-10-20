
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>

#define MAX_LINE_LEN 4000
#define PRINT_DEBUG 0

// declarations
void show_usage_screen(char* arg);
void print_debug_information();

bool debug = PRINT_DEBUG;

static char* target_string = NULL;
static char* replacement_string = NULL;
char* current_line = NULL;
char* modified_line = NULL;
char* current_line_copy = NULL;

int main(int argc, char *argv[]) {

    // argument parsing
    int option_index = 0;
    int c;
    static struct option long_options[] = {
        {"help",    no_argument,       0, 'h'},
        {"version", no_argument,       0, 'v'},
        {0, 0, 0, 0}
    };
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
    
    // old string is the 2nd last arg
    target_string = argv[argc - 2];
    // new string is the last arg
    replacement_string = argv[argc - 1];
    
    current_line = NULL;
    size_t max_line_len = MAX_LINE_LEN;
    ssize_t read = -1;
    
    read = getline(&current_line, &max_line_len, stdin);
    if (read != -1) {
        // success
        uint32_t len_current_line = 0;
        len_current_line = strlen(current_line);

        // calculate needed length of modified line
        const uint64_t difference = strlen(replacement_string) - strlen(target_string);
        uint32_t found_target_count = 0;
        char* occurence = current_line;
        while ((occurence = strstr(occurence, target_string)) != NULL) {
            occurence += strlen(target_string);
            found_target_count++;
        }
        uint32_t len_modified_line = strlen(current_line) + (found_target_count * difference);
        if (debug) { printf("found_target_count: %u \nlen_current_line: %u \nlen_modified_line: %u \n",
             found_target_count, len_current_line, len_modified_line);
        }


        
        // construct the modified line
        found_target_count = 0;
        modified_line = malloc(len_modified_line + 1);
        for (uint32_t i = 0; i < len_modified_line; i++) {
            modified_line[i] = '\0';
        }
        char* modified_line_ptr = modified_line;
        occurence = current_line;

        char* ptr_start = current_line;
        char* ptr_end = NULL;

        if (debug) {
            printf("&current_line[0]: %p \n", current_line);
        }
        while ((occurence = strstr(occurence, target_string)) != NULL) {
            if (debug) {
                found_target_count++;
                printf("%u. occurence [%p]  : %s", found_target_count, occurence, occurence);
            }
            ptr_end = occurence;
            uint32_t difference = ptr_end - ptr_start;
            strncpy(modified_line_ptr, ptr_start, difference);
            modified_line_ptr = modified_line_ptr + strlen(modified_line_ptr);
            strncpy(modified_line_ptr, replacement_string, strlen(replacement_string));
            modified_line_ptr = modified_line_ptr + strlen(replacement_string);
            occurence += strlen(target_string);
            ptr_start = ptr_end + strlen(target_string);

            if (debug) {
                printf("%s\n", modified_line);
            }
        }
        // if there is still a chunk left after the last occurrence
        // --> append it to the end of the modified_line
        if (strlen(ptr_start) > 0) {
            strncpy(modified_line_ptr, ptr_start, strlen(ptr_start));
        }

    } else {
        // failed
        printf("Couldn't read from stdin");
        return -1;
    }
    // if (debug) { print_debug_information(); }
    printf("%s", modified_line);
    return 0;

}

void show_usage_screen(char* arg) {
    printf("Usage: %s [--help] [--version] [--old <to-replace>] [--new <replacement>]\n", arg);
}

void print_debug_information() {
    printf("--------------\n");
    printf("old_string:\t'%s'\n", target_string);
    printf("new_string:\t'%s'\n", replacement_string);
    printf("%s:\t%u\n", "strlen(current_line)", (uint32_t) strlen(current_line));
    uint32_t len_copy = current_line_copy == NULL ? 0 : (uint32_t) strlen(current_line_copy);
    printf("%s:\t%u\n", "strlen(current_line_copy)", len_copy);
}