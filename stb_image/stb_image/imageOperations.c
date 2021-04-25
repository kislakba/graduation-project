#include "imageOperations.h"


unsigned char *changePhotoToChar(float *photo, int width, int height)
{
     unsigned char *return_photo = malloc(width * height);
     for (int i = 0; i < width * height; i++)
     {
          return_photo[i] = (uint8_t)(photo[i]* 255);
     }
     return return_photo;
}

unsigned char *changePhotoToCharWithLogTransform(float *photo, int width, int height, float max)
{
     unsigned char *return_photo = malloc(width * height);
     float c = 255 / log(1 + max);
     for (int i = 0; i < width * height; i++)
     {
          return_photo[i] = (uint8_t)(c * log(1 + photo[i]));
     }
     return return_photo;
}

float *logTransform(float *photo, int width, int height, float max)
{
     float *return_photo = create1DFloatArray(width * height);
     float c = 255 / log(1 + max);
     printf("log birinci asama tamam \n");

     for (int i = 0; i < width * height; i++)
     {
          return_photo[i] = (c * log(1 + photo[i]));
     }
     return return_photo;
}

unsigned char *convertToGray(unsigned char *img, int width, int height, int channels)
{
     size_t img_size = width * height * channels;
     int gray_channels = channels == 4 ? 2 : 1;
     size_t gray_img_size = width * height * gray_channels;

     unsigned char *gray_img = malloc(gray_img_size);

     if (gray_img == NULL)
     {
          printf("an error occured while loading gray_image \n");
          return 0;
     }
     for (unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels)
     {
          *pg = (uint8_t)((0.2126 * (*p) + 0.7152 * (*(p + 1)) + 0.0722 * (*(p + 2))));
          if (channels == 4)
          {
               *(pg + 1) = *(p + 3);
          }
     }
     return gray_img;
}

float *convertBetweenZeroAndOne(unsigned char *img, int width, int height)
{
     float *newImage = create1DFloatArray(width * height);
     for (size_t i = 0; i < width*height; i++)
     {
          newImage[i] = ((float)img[i])/255;
     }
     return newImage;
}