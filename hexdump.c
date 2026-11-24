#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// helper function called by hexdump to handle ascii print logic
void print_ascii(unsigned char *buf, int n) {
    int padding = 16 - n;

    padding = (padding * 3) + 1;
    printf("%*s", padding, "");

    for(int i = 0; i < n ; i++){
        if(buf[i] >= 32 && buf[i] <= 126) {putchar(buf[i]);} // ensure im printing only readable chars
        else printf(".");
    }
}

int hexdump(FILE *infile) {

    int hex;
    uint64_t count = 0; // avoids INT_MAX allowing for file size 1.8 x 10^19
    uint8_t buf[16]; // hold 16 1 byte values

    while ((hex = fgetc(infile)) != EOF)  {
        // count tracks the number of bytes read so far
        if (count % 16 == 0) {
            if (count != 0) { 
                print_ascii(buf, 16);
                printf("\n"); 
            }
            printf("%08llx: ", (unsigned long long)count); // casting mean portable between linux/windows 
        }

        printf("%02x ", hex); // print an int as lowercase hex, with at least two digits padding with zeros as necessary
        buf[count % 16] = (unsigned char) hex;
        count = count + 1;       
    }
    
    if(ferror(infile)) {
        fprintf(stderr, "Read Error\n");
        return EXIT_FAILURE;
    }

    if (count == 0) { return EXIT_SUCCESS; } // exit early for empty files
    else if (count % 16 == 0) { print_ascii(buf, 16); }
    else { print_ascii(buf, (int)(count % 16)); }

    printf("\n");
    return EXIT_SUCCESS;
}

int main(int argc, char **argv) {

    FILE *infile; // declare as local

    if(argc == 1){
        fprintf(stderr, "Please provide a file to dump.\n");
        return EXIT_FAILURE;
    }

    infile = fopen(argv[1], "rb"); 

    if (NULL == infile) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    int status = hexdump(infile);
    fclose(infile);

    return status;

}