#include "test.h"


int main(int argc, char *argv[])
{
     unsigned char *grayPhoto;
     unsigned char *dftPhoto;
     int n1 = atoi(argv[1]);
     int n2 = atoi(argv[2]);
     int rank, size, i;

     MPI_Init(NULL, NULL);
     int chunk = n1 / size;
     MPI_Comm_size(MPI_COMM_WORLD, &size);
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     int width, height, channels;
     unsigned char *img;
     if(rank == MASTER)
     {
          img = stbi_load("photos/stopSign.jpeg", &width, &height, &channels, 0);
          if (img == NULL)
          {
               printf("an error occured while loading image \n");
               return 0;
          }
          printf("Loaded image has \t width = %d \t height = %d \t channels = %d \n", width, height, channels);
     }

     unsigned char *img_local = malloc(chunk);
     MPI_Scatter(img, chunk * n2, MPI_UNSIGNED_CHAR, img_local, chunk * n2, MPI_UNSIGNED_CHAR, MASTER, MPI_COMM_WORLD);
     grayPhoto = convertToGray(img, width, height, channels);
     printImage(grayPhoto, 10);
     float *littleImage = convertBetweenZeroAndOne(grayPhoto, width, height); 
     float *grayDft = twoDimenDft(littleImage, height, width);
     dftPhoto = changePhotoToChar(grayDft, width, height);
     //log transform uygulamadan reverse et
     //sadece görsellikte log transf
     stbi_write_jpg("photos/denemeWithSuhaHoca.jpg", width, height, 1, dftPhoto, 100);
     free(grayPhoto);
     free(dftPhoto);
     free(grayDft);
     stbi_image_free(img);
     return 0;
}