#include <stdio.h>
#include <sys/stat.h> // For fstat()
#include <unistd.h>   // For lseek()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h> 
#include <errno.h>

//1mb = 256 blocks

#define USE_MMAP 0

int n = 2;
int read_size = 4096;
int read_order[] = {34, 100};

int main() {

    int fd = open("./dummy.dat",O_RDONLY);
    if (fd < 0) {
        printf("Open Failed");
        return 1;
    }

    #if USE_MMAP
    struct stat s;
    int status = fstat (fd, & s);
    if (status < 0) {
        printf("stat dummy.dat failed: %s", strerror (errno));
        return -1;
    }
    size_t size = s.st_size;

    const char *mapped;
    mapped = mmap (0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        printf("MMAP failed\n");
        return -1;
    }
    #endif

    char buf[read_size];
    for (int i = 0 ; i < n ; i++) {
        #if !USE_MMAP
            lseek(fd, read_order[i]*4096, SEEK_SET);
            printf("reading %d\n", read_order[i]);
            int bytes_read = read(fd, buf, read_size);
            if (bytes_read != read_size) {
                printf("Did not read enough bytes\n");
                return -1;
            }
            else {
                printf("read %x\n", *buf);
            }
        #else
            buf[0] = mapped[read_order[i]*4096];
            printf("read %x\n", *buf);
        #endif
    }

    return 0;
}
