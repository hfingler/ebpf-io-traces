#include <stdio.h>
#include <sys/stat.h> // For fstat()
#include <unistd.h>   // For lseek()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h> 
#include <errno.h>
#include <string.h>

//1mb = 256 4K blocks

int n = 4;
int read_size = 4096;
int read_order[] = {34, 100, 34, 100};

int main() {

    int fd = open("./dummy.dat",O_RDONLY);
    if (fd < 0) {
        printf("Open Failed");
        return 1;
    }

    //setup mmap
    struct stat s;
    int status = fstat(fd, & s);
    if (status < 0) {
        printf("stat dummy.dat failed: %s", strerror (errno));
        return -1;
    }
    size_t size = s.st_size;

    char *mapped;
    mapped = mmap (0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        printf("MMAP failed\n");
        return -1;
    }

    char buf[read_size];
    // do syscalls
    for (int i = 0 ; i < n ; i++) {

        lseek(fd, read_order[i]*4096, SEEK_SET);
        printf("reading %d\n", read_order[i]);
        int bytes_read = read(fd, buf, read_size);
        if (bytes_read != read_size) {
            printf("Did not read enough bytes\n");
            return -1;
        }
        else {
            printf("read %d, first char: %x\n", bytes_read, *buf);
        }
        
    }
    // do mmap
    for (int i = 0 ; i < n ; i++) {
        int base_offset = read_order[i]*4096; 
        for (int j = 0 ; j < read_size ; j++ ) {
            buf[j] = mapped[base_offset+j];
            mapped[base_offset+j] = j;
        }
    }

    return 0;
}
