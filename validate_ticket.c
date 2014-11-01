#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* The following program outputs the correct barcodes that match the locations file. 
 * It first makes sure that the input that is given is of the correct format for both the barcodes and the locations.
 * It then checks to make sure that the sum is reflective of the last digit. */
void validate_locations(char *file_name);
void bad_location(char *string);
void validate_barcodes(void);
void bad_barcode(char *string);
void check_sum(char *input_barcode);
void bad_sum(char *string);
void correct_location(void);
void unknown_location(char *string);

FILE *validated_locations;
FILE *validated_barcodes;
FILE *error_log;

int main(int argc, char *argv[])
{
    // Check to see if the program is given enough arguments for it to run
    error_log = fopen("error.log", "a");
    if (argv[1] == NULL) {
        fprintf(error_log, "Not enough information is given to run the program.\n");
        return 0;
    }

    if (strcmp("--locations", argv[1]) == 0) {
        if (argv[2] != NULL) {
            validate_locations(argv[2]);
            validate_barcodes();
            correct_location();
        } else {
            fprintf(error_log, "No file name is specified.\n");
        }
    }
    fclose(error_log);
    return 0;
}

// Go through all the locations provided and make sure that they match the expected input. 
// If they match the expected input write them to a file. 
void validate_locations(char *file_name) 
{ 
    validated_locations = fopen("validated_locations.txt", "w");
    FILE *input_file = fopen(file_name, "r");

    char string[2000];

    while (fgets(string, sizeof(string), input_file)) {
        string[strcspn(string, "\n")] = '\0';
        if (string[4] != '\0') {
            bad_location(string);
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
                bad_location(string);
                continue;
            }
            fprintf(validated_locations, "%s\n", string);
        } 
    }
    fclose(input_file);
    fclose(validated_locations);
}

// If the location provided does not match the input then output it to the error.log file
void bad_location(char *string)
{
    fprintf(error_log, "Invalid format for locations provided: %s\n", string);
}

// Go through all the barcodes and make sure that they match the expected input. 
void validate_barcodes(void)
{
    validated_barcodes = fopen("validated_barcodes.txt", "w");

    char string[2000];

    while(fgets(string, sizeof(string), stdin)) {
        string[strcspn(string, "\n")] = '\0';
        if (string[12] != '\0') {
            bad_barcode(string);
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
                bad_barcode(string);
                continue;
            }
            fprintf(validated_barcodes, "%s\n", string);
        }
    }
    fclose(validated_barcodes);
}

// If the barcode is not of valid input then append it to the error.log
void bad_barcode(char *string)
{
    fprintf(error_log, "Invalid format for barcode provided: %s\n", string);
}

// Make sure that the barcode supplied can be verified using the locations.txt file
void correct_location(void) 
{
    validated_locations = fopen("validated_locations.txt", "r");
    validated_barcodes = fopen("validated_barcodes.txt", "r");

    fpos_t start_position;
    fgetpos(validated_locations, &start_position);

    char string[1000];
    char buffer[2000];
    int barcode[12];
    int buffer_int[2000];

    while (fgets(string, sizeof(string), validated_barcodes)) {
        fsetpos(validated_locations, &start_position);
        int found = 0;
        while (fgets(buffer, sizeof(buffer), validated_locations)) {
            int i;
            int indicator = 0;
            for (i = 0; i < 4; i++) {
                barcode[i] = string[i] - '0';
                buffer_int[i] = buffer[i] - '0';
                if (barcode[i] != buffer_int[i]) {
                    indicator = 1;
                    break;
                }
            }
            if (indicator == 1) {
                continue;
            }
            found = 1;
            check_sum(string);
            break;
        }
        if (found == 0) {
            bad_location(string);
        }
    }
    fclose(validated_locations);
    fclose(validated_barcodes);
}

// If the barcode cannot be verified using locations.txt then append it to error.log 
void unknown_location(char *string) 
{
    fprintf(error_log, "Location was not found of barcode: %s\n", string);
}

// Check to see that the last digit of the valid barcode is reflective of the sum of all values
void check_sum(char *input_barcode) 
{
    int barcode[12];

    int i;
    int sum = 0;
    for (i = 0; i < 11; i++) {
        barcode[i] = input_barcode[i] - '0';
        sum = sum + barcode[i];
    }
    barcode[11] = input_barcode[11] - '0';
    sum = sum % 10;
    if (sum == barcode[11]) {
        fputs(input_barcode, stdout);
    } else {
        bad_sum(input_barcode);
    }
}

// If the barcode does not have a correct sum append it to error.log file
void bad_sum(char *string)
{
    fprintf(error_log, "Check sum failed for barcode: %s", string);
}
