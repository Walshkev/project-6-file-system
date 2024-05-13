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
    for (int i = 0; i < BLOCK_SIZE; i++) {
        inode_map[i] =1;
    }

    int free_inode = ialloc();
    // printf("Free inode found at index: %d\n", free_inode);
    CTEST_ASSERT(free_inode == -1, "test inode when full " );

    inode_map[20]=0;
    free_inode = ialloc();
    // printf("Free inode found at index: %d\n", free_inode);
    CTEST_ASSERT(free_inode == 20, "test inode when not full " );





}

// void test_alloc(void){

   
//     // Fill up block with 0xFF
  

//     int free_inode = alloc();
//     printf("Free inode found at index: %d\n", free_inode);
//     CTEST_ASSERT(free_inode == -1, "test inode when full " );



// }




int main(void)
{
 
//     // printf("Running normally!\n");

    CTEST_VERBOSE(1);

    test_image();

    test_block(); 
    test_set_free();
    test_find_free();
    test_inode_ialloc();
    // test_alloc();
  

    // printf("file_image = %d\n", image_open("file_name.txt", 200) );
    // // printf("file close = %d\n" , image_close() );
    // printf("bread test= %d\n",*bread(1, block) );
    // bwrite(1, block );
    // // printf( "bwrite test= %hhn\n" , block);
}

