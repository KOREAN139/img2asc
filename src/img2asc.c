#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[]){
  /* Get this from
     https://people.sc.fsu.edu/~jburkardt/data/ascii_art_grayscale/ascii_art_grayscale.html */
  char asc[70] = {
    '$', '@', 'B', '%', '8', '&', 'W', 
    'M', '#', '*', 'o', 'a', 'h', 'k',
    'b', 'd', 'p', 'q', 'w', 'm', 'Z',
    'O', '0', 'Q', 'L', 'C', 'J', 'U',
    'Y', 'X', 'z', 'c', 'v', 'u', 'n',
    'x', 'r', 'j', 'f', 't', '/', '\\',
    '|', '(', ')', '1', '{', '}', '[', 
    ']', '?', '-', '_', '+', '~', '<',
    '>', 'i', '!', 'l', 'I', ';', ':',
    ',', '"', '^', '`', '\'', '.', ' '
  };
  int i, j, idx;
  int width, height, size, padding;
  char *img;
  unsigned char grey;
  FILE *fp, *fpO;
  BITMAPFILEHEADER fileHeader;
  BITMAPINFOHEADER infoHeader;
  RGBTRIPLE *pixel; 

  /* Get bitmap file with binary mode */
  if(!(fp = fopen(argv[1], "rb"))) goto exit;
  fpO = fopen("out.txt", "w");

  /* Read file header from file stream */
  if(fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp) < 1){
    puts("Failed to read file header from file");
    fclose(fp);
    goto exit;
  }

  /* Check whether this file is bitmap or not */
  if(fileHeader.bfType != 0x4D42){
    puts("This file is not bitmap");
    fclose(fp);
    goto exit;
  }

  /* Read info header from file stream */
  if(fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp) < 1){
    puts("Failed to read info header from file");
    fclose(fp);
    goto exit;
  }

  width = infoHeader.biWidth;
  height = infoHeader.biHeight;
  size = infoHeader.biSizeImage;

  /* Calc padding size */
  padding = ((width * 3) % 4) & 3;

  /* Size may be set to zero for BI_RGB bitmaps */
  if(!size) size = (width * 3 + padding) * height;

  /* To get RGB info from bitmap */
  img = malloc(size);

  /* Set file pointer to point very start of pixel-data */
  fseek(fp, fileHeader.bfOffBits, SEEK_SET);

  fread(img, size, 1, fp);

  for(i = height; i--; fprintf(fpO, "\n")){
    for(j = 0; j < width; j++){
      idx = (j * 3) + (i * width * 3) + padding * i;
      pixel = (RGBTRIPLE *)&img[idx];
      grey = (pixel->rgbtBlue + pixel->rgbtGreen + pixel->rgbtRed) / 3;
      fprintf(fpO, "%c%c", asc[grey * 70 / 256], asc[grey * 70 / 256]);
    }
  }

exit:

  free(img);
  fclose(fp);
  fclose(fpO);
  return 0;
}
