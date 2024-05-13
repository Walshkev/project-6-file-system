#include <stdio.h>
#include "block.h"



int inode_map[BLOCK_SIZE]; // Inode map array

int ialloc(void) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        if (inode_map[i] == 0) { 
            inode_map[i] = 1; 
            return i; 
        }
    }
    return -1; 
}
