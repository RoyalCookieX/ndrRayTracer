#pragma once
#include "defines.h"

// Stores image data.
typedef struct ndrScreenBuffer_t {
    uvec2 size;
    ndrPixel* data;
} ndrScreenBuffer_t, *ndrScreenBuffer;

// Creates a screen buffer.
bool ndrCreateScreenBuffer(uvec2 size, ndrPixel clearColor, ndrScreenBuffer* result);
// Destroys a screen buffer.
void ndrDestroyScreenBuffer(ndrScreenBuffer screenBuffer);

// Writes a pixel to the screen buffer.
bool ndrWritePixel(ndrScreenBuffer screenBuffer, uvec2 position, ndrPixel value);
// Outputs the screen buffer to a file.
bool ndrWriteFile(ndrScreenBuffer screenBuffer, const char* fileName);
