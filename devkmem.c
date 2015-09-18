#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

#define DEVKMEM         "/dev/kmem"

#define PAGE_SIZE       0x1000
#define PAGE_MASK       (~(PAGE_SIZE-1))


int main(int argc, char* argv[])
{
    int fd;
    void *mbase;
    unsigned long ptr;
    unsigned long virAddr;

	if(argc < 2) {
		fprintf(stderr, "\nUsage:\t%s { address }\n"
			"\taddress : kernel address to act upon\n",
			argv[0]);
		exit(1);
	}

    virAddr = strtoul(argv[1], 0, 16);
    ptr = virAddr & ~(PAGE_MASK);

    fd = open(DEVKMEM, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(-1);
    }

    mbase = mmap(0, PAGE_SIZE, PROT_READ, MAP_SHARED, fd, (virAddr & PAGE_MASK));
    if (mbase == MAP_FAILED) {
        printf("map failed %s\n",strerror(errno));
	close(fd);
        exit(-1);
    }
    
    printf("virAddr = 0x%lX \n", virAddr);
    printf("mapbase = 0x%lX \n", (unsigned long)mbase);
    printf("value   = 0x%X \n",*(unsigned int*)(mbase+ptr));
    printf("char    = %c%c%c%c \n",
    				*(char *)(mbase+ptr), *(char *)(mbase+ptr+1),
    				*(char *)(mbase+ptr+2), *(char *)(mbase+ptr+3));
    
    close(fd);
    munmap(mbase,PAGE_SIZE);

    return 0;
}
