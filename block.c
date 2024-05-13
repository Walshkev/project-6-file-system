#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "image.h"
#include "block.h"

#include "free.h"
#include "inode.h"

int blockSize = BLOCK_SIZE;

unsigned char *bread(int block_num, unsigned char *block) {
    off_t offset = block_num * blockSize;

    lseek(image_fd, offset, SEEK_SET);
    if (read(image_fd, block, blockSize) == -1) {
        perror("read ");
    }

    return block;
}

void bwrite(int block_num, unsigned char *block) {
    off_t offset = block_num * blockSize;

    lseek(image_fd, offset, SEEK_SET);
    write(image_fd, block, blockSize);
}





// void alloc(void) {
//     unsigned char block[blockSize];

//     // Call bread() to get the inode map
//     bread(0, block);

//     // Call find_free() to locate a free inode
//     int free_inode = find_free(block);

//     // Call set_free() to mark the inode as non-free
//     set_free(free_inode, 1, 0);

//     // Call bwrite() to save the inode back out to disk
//     bwrite(0, block);
// }