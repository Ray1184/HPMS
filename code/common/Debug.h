/*!
 * File Debug.h
 */

#pragma once

#include <cstdio>
#include <glad/glad.h>
#include <string>

namespace hpms
{

    // Put here debug functions.

    void DumpFBO(const std::string& filename, size_t width, size_t height)
    {
        FILE* output_image;
        size_t outWidth, outHeight;

        outWidth = width;
        outHeight = height;


        int i, j, k;
        unsigned char* pixels = (unsigned char*) malloc(outWidth * outHeight * 3);

        glReadBuffer(GL_BACK);
        glReadPixels(0, 0, outWidth, outHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels);

        output_image = fopen(filename.c_str(), "wt");
        fprintf(output_image, "P3\n");
        fprintf(output_image, "# HPMS Debug Dump\n");
        fprintf(output_image, "%d %d\n", outWidth, outHeight);
        fprintf(output_image, "255\n");

        k = 0;
        for (i = 0; i < outWidth; i++)
        {
            for (j = 0; j < outHeight; j++)
            {
                fprintf(output_image, "%u %u %u ", (unsigned int) pixels[k], (unsigned int) pixels[k + 1],
                        (unsigned int) pixels[k + 2]);
                k = k + 3;
            }
            fprintf(output_image, "\n");
        }
        free(pixels);
    }
}
