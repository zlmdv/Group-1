#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

int encrypt(FILE *input, FILE *output, char *password); 


int main(int argc, char **argv){
    char password[] = "3";
    FILE *input = fopen(argv[1], "r"); 
    FILE *output = fopen(argv[2], "w"); 

    if(output == NULL){
        printf("Error opening encrypted file");
        return 1; 
    }
    encrypt(input, output, password); 

    fclose(input); 
    fclose(output); 
    return 0; 
}

/**
 * @brief function to encrypt text with an xor operation
 * 
 * @param input input file
 * @param output output file
 * @param password key for encryption
 * @return int 
 */

int encrypt(FILE *input,FILE *output,char *password){ 

    unsigned long int filesize;
    char *buffer;
    int length;

    length = strlen(password); 
    fseek(input, 0, SEEK_END); 
    filesize=ftell(input);
    buffer = malloc(filesize);      // this whole block of  code gets file siz3
    rewind(input); 
    printf("read %u\n", filesize);
    fread(buffer, 1, filesize, input); 
    for(int i = 0; i < filesize; i ++){
        buffer[i] = buffer[i] ^ password[i % length]; //executes xor operation     
    }
    int w = fwrite(buffer, 1, filesize, output );  //writes data to output file
    printf("written %d\n", w);      
    free(buffer); 
}