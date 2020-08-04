#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstring>

/*
 * SEEK_SET: file start head
 * SEEK_CUR: file point
 * SEEK_END: file end
 */

static unsigned lode_buffer(unsigned char * out, size_t size, const char * filename)
{
    FILE * file;
    size_t readsize;
    file = fopen(filename, "rb");
    if(!file) return 78;

    readsize = fread(out, 1, size, file);
    std::cout << "size = " << size << '\n';
    std::cout << "readsize = " << readsize << '\n';
    fclose(file);

    return 1;
}

int main()
{
    FILE *fp;
    fp = fopen("1.txt", "rb");
    if(!fp)
        return -1;

    long size;
    std::vector<unsigned char> buffer;

    fseek(fp, 0, SEEK_END); //
    size = ftell(fp);
    std::cout << "size1 = " << size << '\n';
    fclose(fp);
    buffer.resize((size_t) size);
    std::string filename = "1.txt";

    lode_buffer(&buffer[0], (size_t) size, filename.c_str());

    return 0;
}

