#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(void)
{
    int width, height, channels;
    unsigned char *img = stbi_load("stopSign.jpeg",&width, &height, &channels,0);
    if(img == NULL)
    {
        printf("an error occured while loading image \n");
        return 0;
    }
    printf("Loaded image has \t width = %d \t height = %d \t channels = %d \n",width,height,channels);

    //converting to gray
    size_t img_size = width * height * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * height * gray_channels;
    
    unsigned char *gray_img = malloc(gray_img_size);
    if(gray_img == NULL)
    {
        printf("an error occured while loading gray_image \n");
        return 0;
    }
    for (unsigned char *p = img, *pg = gray_img; p != img + img_size; p+=channels, pg +=gray_channels)
    {
        *pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
         if(channels == 4)
         {
            *(pg + 1) = *(p + 3);
         }
    }
    printf("Loaded image has \t width = %d \t height = %d \t channels = %d \n",width,gray_img_size,gray_channels);

    stbi_write_jpg("stopSign_gray.jpg",width,height,gray_channels,gray_img,100);

    stbi_image_free(img);
    free(gray_img);
}