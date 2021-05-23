#include "test.h"


int main(int argc, char *argv[])
{
     //  unsigned char *grayPhoto;
     // unsigned char *dftPhoto;
     // int rank, size, i;

     // int width, height, channels;
     // unsigned char *img;
     // img = stbi_load("photos/stopSign.jpeg", &width, &height, &channels, 0);
     // if (img == NULL)
     // {
     //      printf("an error occured while loading image \n");
     //      return 0;
     // }
     // printf("Loaded image has \t width = %d \t height = %d \t channels = %d \n", width, height, channels); 

     // grayPhoto = convertToGray(img, width, height, channels);
     // float *grayMinimalPhoto = convertBetweenZeroAndOne(grayPhoto, width, height);
     // float complex *firstDft = twoDimenDft(grayMinimalPhoto, height, width);
     // float *grayInversedPhoto = twoDimenReverseDft(firstDft, height, width);
     // dftPhoto = changePhotoToChar(grayInversedPhoto,width,height);
     // stbi_write_jpg("photos/denemeWithSuhaHoca1.jpg", width, height, 1, dftPhoto, 100);
     // free(grayPhoto);
     // free(dftPhoto);
     // free(grayInversedPhoto);
     // stbi_image_free(img);
     
     
     float *points = create1DFloatArray(16);
     for (size_t i = 0; i < 16; i++)
     {
          points[i] = 1.0 * (i + 1);
     }
     printFloatArray(points, 16);
     float complex *ilkDft = twoDimenDft(points, 4, 4);
     float complex *ilkfft = twoDimenFft(points, 4, 4);
     printFloatComplexArray(ilkDft, 16);
     printFloatComplexArray(ilkfft, 16);
     float *ilkinverseDft = twoDimenReverseDft(ilkDft, 4, 4);
     float *ilkinverseFft = twoDimenInverseFft(ilkfft, 4, 4);
     printFloatArray(ilkinverseDft, 16);
     printFloatArray(ilkinverseFft, 16);
     return 0;
}