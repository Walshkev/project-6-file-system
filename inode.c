#include <stdio.h>
#include "block.h"
#include "inode.h"
#include "free.h"


int ialloc(void) {

    unsigned char inode_map[BLOCK_SIZE];
    
   
    bread(BLOCK_NUM,  inode_map);


    int free_inode= find_free(inode_map) ;


    if (free_inode!=-1 ) {
        set_free( inode_map, free_inode, 1);
        bwrite(BLOCK_NUM , inode_map);


    }
    return free_inode; 
}
