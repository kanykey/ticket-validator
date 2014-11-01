#include <stdio.h>
#include <string.h>

/* The following programs accepts a 12 digit 
 * barcode from stdin and validates it using an external file. */
int main(int argc, char *argv[])
{
    FILE *input_file;
    fpos_t start_position; 
    
    // All the errors will be appended to error.log
    FILE *error_log = fopen("error.log", "a");

    // Validate the input to make sure that enough arguments are given
    if (argv[1] == NULL) {
        fprintf(stderr, "Not enough information is given to run the program.\n");
        return 0;
    } else if (strcmp("--locations", argv[1]) == 0) {
        if (argv[2] != NULL) {
            input_file = fopen(argv[2], "r");
            fgetpos(input_file, &start_position);
        } else {
            printf("No file name is specified.\n");
            return 0;
        }
    }

    char string[1000];
    char buffer[2000];
    int barcode[12];
    int buffer_int[2000];

    // Look for input
    while(fgets(string, sizeof(string), stdin)) {
        fsetpos(input_file, &start_position);
        int found = 0;
        
        // Scan the input against the data stored at the specified file
        while (fgets(buffer, sizeof(buffer), input_file)) {
            int i;
            int indicator = 0;
            for (i = 0; i < 4; i++) {
                barcode[i] = string[i] - '0';
                buffer_int[i] = buffer[i] - '0';
                if (barcode[i] != buffer_int[i]) {
                    indicator = 1;;
                }
            }
            if (indicator == 1) {
                continue;
            }
            fputs(string, stdout);
            found = 1;
            break;
        }
        // If the input could not be validated append the error to error.log 
        // Else print the barcode to stdout
        if (found == 0) {
            fprintf(error_log, "The barcode could not be located in locations.txt: %s", string);
        }
    }

    fclose(input_file);
    fclose(error_log);
    return 0;
}

