#include "test.h"
#include <stdio.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

void ndrTestFunc()
{
    printf("Hello World!\n");
}

void ndrWriteImage(const char* filename, int x, int y)
{
    void* data = malloc(x * y * 3);
    stbi_write_png(filename, x, y, 3, data, x * 3);
    free(data);
}