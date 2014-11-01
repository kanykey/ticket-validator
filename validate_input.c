#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* The following program accepts 12 digit barcodes and locations to be validated. 
 * If the input that is given does not match the input that is expected the program does not check it. 
 * Two files are then written with only the valid input.
 */
void validate_locations(char *file_name);
void validate_barcodes(void);

FILE *validated_locations;
FILE *error_log;

int main(int argc, char *argv[])
{
    // Check to make sure that enough arguments are passed to the program
    error_log = fopen("error.log", "a");
    if (argv[1] == NULL) {
        fprintf(error_log, "Not enough information is given to run the program.\n");
        return 0;
    }

    if (strcmp("--locations", argv[1]) == 0) {
        if (argv[2] != NULL) {
            validate_locations(argv[2]);
            validate_barcodes();
        } else {
            fprintf(error_log, "No file name is specified.\n");
        }
    }
    fclose(validated_locations);
    fclose(error_log);
    return 0;
}

// This method checks to make sure that the locations 
// provided are integers and that they are 4 integers long. 
void validate_locations(char *file_name) 
{ 
    char string[1000];

    validated_locations = fopen("valid_locations.txt", "w");
    FILE *input_file = fopen(file_name, "r");

    while (fgets(string, sizeof(string), input_file)) {
        string[strcspn(string, "\n")] = '\0';
        if (string[4] != '\0') {
            fprintf(error_log, "Invalid format for locations provided: %s\n", string);
            continue;
        }
        if (strlen(string) == 4) {
            int i;
            int indicator = 0;
            for (i = 0; i < 4; i++) {
                if (!isdigit(string[i])) {
                    indicator = 1;
                    break;
                }
            }
            if (indicator == 1) {
                fprintf(error_log, "Invalid format for locations provided: %s\n", string);
                continue;
            }
            fprintf(validated_locations, "%s\n", string);
        }
    }
    fclose(input_file);
}

// This method validates the input that was passed as barcodes. If the barcode 
// is not 12 digits long and all integers it does not get written to the file. 
void validate_barcodes(void)
{
    char string[1000];

    while(fgets(string, sizeof(string), stdin)) {
        string[strcspn(string, "\n")] = '\0';
        if (string[12] != '\0') {
            fprintf(error_log, "Invalid format for barcode provided: %s\n", string);
            continue;
        }
        if (strlen(string) == 12) {
            int indicator = 0;
            int i;
            for(i = 0; i < 12; i++) {
                if (!isdigit(string[i])) {
                    indicator = 1;
                    break;
                }
            }
            if (indicator == 1) {
                fprintf(error_log, "Invalid format for barcode provided: %s\n", string);
                continue;
            }
            fprintf(stdout, "%s\n", string);
        }
    }
}
