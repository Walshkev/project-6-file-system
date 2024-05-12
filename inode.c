#include <stdio.h>
#include "block.h"



int inode_map[BLOCK_SIZE]; // Inode map array

int ialloc(void) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        if (inode_map[i] == 0) { // Check if inode is free
            inode_map[i] = 1; // Mark inode as allocated
            return i; // Return the inode number
        }
    }
    return -1; // No free inodes found
}
