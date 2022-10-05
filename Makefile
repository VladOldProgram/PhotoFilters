filter: filter.o bmp_io.o bmp_gray.o bmp_emboss.o
	gcc -o filter filter.o bmp_io.o bmp_gray.o bmp_emboss.o

filter.o: filter.c bmp.h
	gcc -c -Wall -Wextra filter.c

bmp_gray.o: bmp_gray.c bmp.h
	gcc -c -Wall -Wextra bmp_gray.c

bmp_emboss.o: bmp_emboss.c bmp.h
	gcc -c -Wall -Wextra bmp_emboss.c

bmp_io.o: bmp_io.c bmp.h
	gcc -c -Wall -Wextra bmp_io.c
	
clean:
	rm -rf *.o filter

