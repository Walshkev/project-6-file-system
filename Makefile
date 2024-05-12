testfs: testfs.o libvvsfs.a 
	gcc $^ -o $@

testfs.o: testfs.c image.h block.h ctest.h free.h inode.h
	gcc -Wall -Wextra  -c $<

image.o :image.c
	gcc -Wall -Wextra -c $<

block.o: block.c
	gcc -Wall -Wextra -c $<

libvvsfs.a : image.o block.o free.o inode.o
	ar rcs $@ $^

free.o: free.c
	gcc -Wall -Wextra -c $<
	
inode.o: inode.c
	gcc -Wall -Wextra -c $<

.PHONY: clean pristine

clean: 
	rm -f *.o

pristine: clean
	rm testfs


