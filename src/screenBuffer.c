#include "screenBuffer.h"
#include "ndrMath.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <stdlib.h>

#define IMAGE_CHANNELS 3

bool ndrCreateScreenBuffer(uvec2 size, ndrPixel clearColor, ndrScreenBuffer* result)
{
    if(result == NULL)
        return false;

    size_t dataSize = sizeof(ndrPixel) * size.x * size.y;
    *result = malloc(sizeof(ndrScreenBuffer_t) + dataSize);
    (*result)->size = size;
    (*result)->data = NDR_PTR_OFFSET((*result), sizeof(ndrScreenBuffer_t));
    for(uint32_t y = 0; y < size.y; y++)
    {
        for(uint32_t x = 0; x < size.x; x++)
        {
            ndrWritePixel(*result, NDR_MAKE_UVEC2(x, y), clearColor);
        }
    }
    return true;
}

void ndrDestroyScreenBuffer(ndrScreenBuffer screenBuffer)
{
    if(screenBuffer == NULL)
        return;
    
    free(screenBuffer);
}

bool ndrWritePixel(ndrScreenBuffer screenBuffer, uvec2 position, ndrPixel value)
{
    if(screenBuffer == NULL || screenBuffer->data == NULL || 
    position.x > screenBuffer->size.x || position.y > screenBuffer->size.y)
        return false;

    screenBuffer->data[screenBuffer->size.x * position.y + position.x] = value;
    return true;
}

bool ndrWriteFile(ndrScreenBuffer screenBuffer, const char* fileName)
{
    if(screenBuffer == NULL || fileName == NULL)
        return false;

    stbi_flip_vertically_on_write(1);
    return stbi_write_png(
        fileName, 
        screenBuffer->size.x, 
        screenBuffer->size.y, 
        IMAGE_CHANNELS, 
        screenBuffer->data, 
        screenBuffer->size.x * IMAGE_CHANNELS);
}