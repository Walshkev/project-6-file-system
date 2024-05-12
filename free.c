#include "free.h"
#include "block.h"


int find_low_clear_bit(unsigned char *block)
{
    for (int i = 0; i < 8; i++)
        if (!(*block & (1 << i)))
            return i;
    
    return -1;
}

void set_free(unsigned char *block, int num, int set) {
 int byte_index = num / BITS_PER_BYTE;
    // find the bit index 
    int bit_index = num % BITS_PER_BYTE; 
    
    int byte = block[byte_index];

    block[byte_index]= ((byte & ~(1 << bit_index)) | (set <<bit_index)); 
}

int  find_free(unsigned char *block) {
    for (int byte_num = 0; byte_num < BLOCK_SIZE; byte_num++) {
        if (block[byte_num] != 0xFF) {
            int bit_num = find_low_clear_bit(&block[byte_num]); // Pass the address of block[byte_num]
            if (bit_num != -1) {
                return (byte_num * 8) + bit_num; 
            }
        }
    }
    
    return -1; // No free entry found
}

