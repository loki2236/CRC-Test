#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint16_t crc(char* input, int size, short int poly);

void main (void)
{
    char input[4092] = ""; //Max for CRC16 with HD4
    unsigned int poly;
    
    printf("\nEnter the input (string - 4092 Max): ");
    //using fgets to avoid scanf errors
    fgets(input, 4092, stdin);
    //removing trailing characters
    input[strcspn(input, "\r\n")] = 0;
    
    printf("\nEnter the polinomial (Hex - 4 Max): ");
    scanf("%x", &poly);
    
    printf("\nInput in Hex: ");
    for (int i=0;i<strlen(input);i++)
    {
        printf("%#2x ", input[i]);
    }
    printf("\nPolinomial: %d", poly);
    printf("\nFinal CRC: 0x%04X",  crc(input, strlen(input), poly));
}

// This one is mine (?
uint16_t crc(char* input, int size, short int poly){
    uint16_t crc = 0x0000; //Init parameter
    short int i;
    //Since we are doing CRC16 and doing byte-sized operations
    // I'll need one extra loop to get the correct result
    size++; 
    
    // while our input...
    while (size--){
        crc ^= *input++;
        // Lets do the magic
        for (i = 0;i<8;i++){
            // Is there any wiser way to check the first bit?
            crc = (crc & (0x8000)) ? (crc<<1)^poly : crc<<1;
        }
    }
    return(crc);
}