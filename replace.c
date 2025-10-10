#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>

// declarations
void show_usage_screen(char* arg);


int main(int argc, char *argv[]) {

    int option_index = 0;
    int c;

    static struct option long_options[] = {
        {"help",    no_argument,       0, 'h'},
        {"version", no_argument,       0, 'v'},
        {"old",    required_argument, 0, 'o'},
        {"new",    required_argument, 0, 'n'},
        {0, 0, 0, 0}
    };

    char* old_string = NULL;
    char* new_string = NULL;

    uint64_t oldlen;
    uint64_t newlen;

    while ((c = getopt_long(argc, argv, "hvo:n:", long_options, &option_index)) != -1) {
        switch (c) {
            case 'h':
                show_usage_screen(argv[0]);
                return 0;
            case 'v':
                printf("Version 1.0\n");
                return 0;
            case 'o':
                oldlen = strlen(optarg);
                old_string = malloc(oldlen + 1);
                printf("Old string (len: %llu) : \"%s\"\n",oldlen , optarg);
                break;
            case 'n':
                newlen = strlen(optarg);
                printf("New string (len: %llu) : \"%s\"\n",newlen , optarg);

                break;
            default:
                return 1;
        }
    }

    return 0;

}

void show_usage_screen(char* arg) {
    printf("Usage: %s [--help] [--version] [--old <to-replace>] [--new <replacement>]\n", arg);
}