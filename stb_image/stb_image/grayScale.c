#include <stdio.h>
#include <stdlib.h>

#define MAX(n1, n2) ((n1 > n2) ? n1 : n2)
#define MIN(n1, n2) ((n1 < n2) ? n1 : n2)

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
void printImage(float *T, int n)
{
    int i;
    float x;
    for (i = 0; i < n; i++)
    {
        x = (float)T[i] / 255;
        printf("%f \n", x);
    }
    puts("");
}
int main(void)
{
    int width, height, channels;
    float *img = stbi_loadf("stopSign.jpeg", &width, &height, &channels, 0);
    if (img == NULL)
    {
        printf("an error occured while loading image \n");
        return 0;
    }
    printf("Loaded image has \t width = %d \t height = %d \t channels = %d \n", width, height, channels);
    //printImage(img, height);

    //converting to gray
    size_t img_size = width * height * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * height * gray_channels;
    printf("gray : %d \n", gray_channels);
    printf("rgb channel : %d \n", channels);

    float *gray_img = malloc(gray_img_size);
    if (gray_img == NULL)
    {
        printf("an error occured while loading gray_image \n");
        return 0;
    }
    for (float *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels)
    {
        *pg = ((0.2126 * (*p) + 0.7152 * (*(p + 1)) + 0.0722 * (*(p + 2))));
        if (channels == 4)
        {
            *(pg + 1) = *(p + 3);
        }
    }
    //printImage(gray_img, gray_img_size);
    printf("Loaded image has \t width = %d \t height = %d \t channels = %d \n", width, height, gray_channels);

    stbi_write_jpg("stopSign_gray.jpg", width, height, gray_channels, gray_img, 100);

    free(gray_img);

    stbi_image_free(img);
}