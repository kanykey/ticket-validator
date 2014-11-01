#include <stdio.h>
#include <string.h>
 
/* The following program accepts input as a 12 digit barcode. It checks 
 * whether the last digit is equivalent to the sum of all digits mod 10. */
int main(int argc, char *argv[])
{
    int barcode[12];
    char string[1000];

    // All the errors are appended to error.log
    FILE *error_log = fopen("error.log", "a");
    while(fgets(string, sizeof(string), stdin)) {
        int i;
        int sum = 0;
        for (i = 0; i < 11; i++) {
            barcode[i] = string[i] - '0';
            sum = sum + barcode[i];
        }
        barcode[11] = string[11] - '0';
        sum = sum % 10;
        if (sum == barcode[11]) {
            fputs(string, stdout);
        } else {
            string[strcspn(string, "\n")] = '0';
            fprintf(error_log, "The barcode '%s' is invalid\n", string);
        }
    }
    fclose(error_log);
    return 0;
}

