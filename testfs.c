#define CTEST_ENABLE

#include <stdio.h>
#include "image.h"
#include "block.h"
#include "ctest.h"
#include <string.h>
#include "free.h"
#include "inode.h"
#include "inode.c"

void test_image(void){
    CTEST_ASSERT(image_open("file_name.txt", 1 ) != -1 , "testing trunk is 0 ");
    CTEST_ASSERT(image_close() != -1 , "testing close ");
}

void test_block(void)
{
    CTEST_ASSERT(image_open("file_name.txt", 1 ) != -1 , "testing trunk is 0 ");
    int block_num= 1; 
    unsigned char block[BLOCK_SIZE] = {0};
    unsigned char block1[BLOCK_SIZE] = "foo";
   

    bwrite(block_num, block);
    bread(block_num, block1); 

    CTEST_ASSERT(memcmp(block,block1, BLOCK_SIZE )== 0 , "testing block");
    
    image_close();
}



void test_set_free(void) {
    unsigned char block[BLOCK_SIZE] = {0};
    // Make a full block
    int num = 2047;
    int byte_num = num / 8; 
    
    // Test setting a bit to 1
    set_free(block, num , 1);

    CTEST_ASSERT(block[byte_num] == 128, "test set free 1");

    // Test setting a bit to 0
    set_free(block, num , 0);

    CTEST_ASSERT(block[byte_num] == 0, "test set free 0" ); 
}



void test_find_free(void ) {
    unsigned char block[BLOCK_SIZE]; 
    // Fill up block with 0xFF
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] = 0xFF;
    }
    
    int freeEntry = find_free(block);
    // printf("Free entry found at index: %d\n", freeEntry);
    CTEST_ASSERT(freeEntry == -1, "test set free 0" ); 
    // Test set_free function
    set_free(block, 10, 0);
 
    freeEntry = find_free(block);
    // printf("Free entry found at index: %d\n", freeEntry);
    CTEST_ASSERT(freeEntry == 10, "test set free 0" );
}

void test_inode_ialloc(void){

    
    // Fill up block with 0xFF
    unsigned char inode_map[BLOCK_SIZE];
    bwrite(INODE_BLOCK_NUM, inode_map);

    int free_inode = ialloc();
    CTEST_ASSERT(free_inode == 0, "test inode when empty  " );
    // printf("Free inode found at index: %d\n", free_inode);

    int second_free_node= ialloc();

    CTEST_ASSERT(second_free_node== 1, "test inode when full " );

    // printf("Free inode found at index: %d\n", free_inode);
    
    int no_free_node = ialloc();
    CTEST_ASSERT(no_free_node !=-1, "test inode when not full " );
}




void test_alloc(void){

    CTEST_ASSERT(image_open("file_name.txt", 1 ) != -1 , "testing trunk is 0 ");
  // Fill up block with 0xFF
    unsigned char block_map[BLOCK_SIZE] = {0};

    bwrite(BLOCK_NUM, block_map);
    bread(BLOCK_NUM, block_map);
  

    int block1 = alloc();
    CTEST_ASSERT(block1 == 0, "test inode when empty  " );
    // printf("Free inode found at index: %d\n", free_inode);

    int block2= alloc();

    CTEST_ASSERT(block2== 1, "test inode when full " );

    // printf("Free inode found at index: %d\n", free_inode);
    
    int block3 = alloc();
    CTEST_ASSERT(block3 !=-1, "test inode when not full " );
}





int main(void)
{
 


    CTEST_VERBOSE(1);

    test_image();

    test_block(); 
    test_set_free();
    test_find_free();
    test_inode_ialloc();
    test_alloc();
  

}

