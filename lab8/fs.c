#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    const char* input_file = argv[1];
    const char* output_file = argv[2];

    int vvod = open(input_file, O_RDWR, 0600);
    int vivod = open(output_file, O_CREAT | O_RDWR, 0600);
    if (vvod < 0 || vivod < 0)
    {
        perror("error with open of map file");
        return -1;
    }

    struct stat* t_stat;
    fstat(vvod, t_stat);
    int dataSize = t_stat->st_size;
    char* data = (char*)mmap(NULL, dataSize, PROT_WRITE | PROT_READ, MAP_SHARED, vvod, 0);
    if (MAP_FAILED == data)
    {
        perror("error with mmap");
        return -2;
    }

    lseek(vivod, 0, SEEK_SET);
    write(vivod, data, dataSize);
    ftruncate(vivod, dataSize);
    close(vvod);
    close(vivod);
}